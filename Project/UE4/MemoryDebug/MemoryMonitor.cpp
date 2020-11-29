// Fill out your copyright notice in the Description page of Project Settings.


#include "MemoryMonitor.h"
#include "Serialization/ArchiveCountMem.h"

MemoryMonitor* MemoryMonitor::instance;



MemoryMonitor::MemoryMonitor()
{
}

MemoryMonitor::~MemoryMonitor()
{
}

MemoryMonitor& MemoryMonitor::Construct() {
	static MemoryMonitor newInstance;
	instance = &newInstance;
	return newInstance;
}

MemoryMonitor& MemoryMonitor::GetInstance() {
	if (instance == nullptr) {
		return Construct();
	}
	return *instance;
}

void MemoryMonitor::Test() {
	UE_LOG(LogTemp, Log, TEXT("MemoryMonitorTestLog"));
}

TArray<FSubItem> MemoryMonitor::GetObjects()const {
	return Objects;
}

void MemoryMonitor::SetUp() {
	const TCHAR* Cmd = TEXT("OBJ LIST CLASS=PACKAGE");
	ParseObject<UClass>(Cmd, TEXT("CLASS="), CheckType, ANY_PACKAGE);
	ParseObject<UObject>(Cmd, TEXT("OUTER="), CheckOuter, ANY_PACKAGE);

	ParseObject<UPackage>(Cmd, TEXT("PACKAGE="), InsidePackage, nullptr);
	if (InsidePackage == nullptr)
	{
		ParseObject<UObject>(Cmd, TEXT("INSIDE="), InsideObject, nullptr);
	}
	if (InsidePackage == nullptr && InsideObject == nullptr)
	{
		ParseObject<UClass>(Cmd, TEXT("INSIDECLASS="), InsideClass, ANY_PACKAGE);
	}
	FParse::Value(Cmd, TEXT("DEPTH="), Depth);

	FParse::Value(Cmd, TEXT("NAME="), ObjectName);



	// support specifying metaclasses when listing class objects
	if (CheckType && CheckType->IsChildOf(UClass::StaticClass()))
	{
		ParseObject<UClass>(Cmd, TEXT("TYPE="), MetaClass, ANY_PACKAGE);
	}

	bAll = FParse::Param(Cmd, TEXT("ALL"));

	// if we specified a parameter in the command, but no objects of that parameter were found,
	// and they didn't specify "all", then don't list all objects
	if (bAll ||
		((CheckType || !FCString::Strifind(Cmd, TEXT("CLASS=")))
			&& (MetaClass || !FCString::Strifind(Cmd, TEXT("TYPE=")))
			&& (CheckOuter || !FCString::Strifind(Cmd, TEXT("OUTER=")))
			&& (InsidePackage || !FCString::Strifind(Cmd, TEXT("PACKAGE=")))
			&& (InsideObject || !FCString::Strifind(Cmd, TEXT("INSIDE=")))
			&& (InsideClass || !FCString::Strifind(Cmd, TEXT("INSIDECLASS=")))))
	{
		bTrackDetailedObjectInfo = bAll || (CheckType != NULL && CheckType != UObject::StaticClass()) || CheckOuter != nullptr || InsideObject != nullptr || InsidePackage != nullptr || InsideClass != nullptr || !ObjectName.IsEmpty();
		bOnlyListGCObjects = FParse::Param(Cmd, TEXT("GCONLY"));
		bOnlyListGCObjectsNoClusters = FParse::Param(Cmd, TEXT("GCNOCLUSTERS"));
		bOnlyListRootObjects = FParse::Param(Cmd, TEXT("ROOTONLY"));
		bShouldIncludeDefaultObjects = FParse::Param(Cmd, TEXT("INCLUDEDEFAULTS"));
		bOnlyListDefaultObjects = FParse::Param(Cmd, TEXT("DEFAULTSONLY"));
		bShowDetailedObjectInfo = FParse::Param(Cmd, TEXT("NODETAILEDINFO")) == false && bTrackDetailedObjectInfo;

	}
	UE_LOG(LogTemp, Log, TEXT("Complete SetUp"));

}

void MemoryMonitor::CheckMemory() {

	List.Empty();
	Objects.Empty();
	Total = FItem();

	for (FObjectIterator It; It; ++It)
	{
		//if (ForgottenObjects.Contains(FObjectKey(*It)))
		//{
		//	continue;
		//}
		if (It->IsTemplate(RF_ClassDefaultObject))
		{
			if (!bShouldIncludeDefaultObjects)
			{
				continue;
			}
		}
		else if (bOnlyListDefaultObjects)
		{
			continue;
		}

		if (bOnlyListGCObjects && GUObjectArray.IsDisregardForGC(*It))
		{
			continue;
		}

		if (bOnlyListGCObjectsNoClusters)
		{
			if (GUObjectArray.IsDisregardForGC(*It))
			{
				continue;
			}
			FUObjectItem* ObjectItem = GUObjectArray.ObjectToObjectItem(*It);
			if (ObjectItem->GetOwnerIndex() > 0)
			{
				continue;
			}
		}

		if (bOnlyListRootObjects && !It->IsRooted())
		{
			continue;
		}

		if (CheckType && !It->IsA(CheckType))
		{
			continue;
		}

		if (CheckOuter && It->GetOuter() != CheckOuter)
		{
			continue;
		}

		if (InsidePackage && !It->IsIn(InsidePackage))
		{
			continue;
		}

		if (InsideObject && !It->IsIn(InsideObject))
		{
			continue;
		}

		if (InsideClass && !It->IsInA(InsideClass))
		{
			continue;
		}

		if (!ObjectName.IsEmpty() && It->GetName() != ObjectName)
		{
			continue;
		}

		if (MetaClass)
		{
			UClass* ClassObj = Cast<UClass>(*It);
			if (ClassObj && !ClassObj->IsChildOf(MetaClass))
			{
				continue;
			}
		}

		FArchiveCountMem Count(*It);
		FResourceSizeEx TrueResourceSize = FResourceSizeEx(EResourceSizeMode::Exclusive);
		It->GetResourceSizeEx(TrueResourceSize);

		int32 i;

		// which class are we going to file this object under? by default, it's class
		UClass* ClassToUse = It->GetClass();
		// if we specified a depth to use, then put this object into the class Depth away from Object
		if (Depth != -1)
		{
			UClass* Travel = ClassToUse;
			// go up the class hierarchy chain, using a trail pointer Depth away
			for (int32 Up = 0; Up < Depth && Travel != UObject::StaticClass(); Up++)
			{
				Travel = Travel->GetSuperClass();
			}
			// when travel is a UObject, ClassToUse will be pointing to a class Depth away
			while (Travel != UObject::StaticClass())
			{
				Travel = Travel->GetSuperClass();
				ClassToUse = ClassToUse->GetSuperClass();
			}
		}

		for (i = 0; i < List.Num(); i++)
		{
			if (List[i].Class == ClassToUse)
			{
				break;
			}
		}
		if (i == List.Num())
		{
			i = List.Add(FItem(ClassToUse));
		}

		if (bShowDetailedObjectInfo)
		{
			Objects.Add(FSubItem(*It, Count.GetNum(), Count.GetMax(), TrueResourceSize));
		}
		List[i].Add(Count, TrueResourceSize);
		Total.Add(Count, TrueResourceSize);

	}

	//UE_LOG(LogTemp, Log, TEXT("Checked Memory %d"), Objects.Num());


}

