// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Serialization/ArchiveCountMem.h"

struct FItem
{
	UClass* Class;
	int32 Count;
	SIZE_T Num;
	SIZE_T Max;
	/** Only exclusive resource size, the truer resource size. */
	FResourceSizeEx TrueResourceSize;

	FItem(UClass* InClass = NULL)
		: Class(InClass), Count(0), Num(0), Max(0), TrueResourceSize()
	{}

	FItem(UClass* InClass, int32 InCount, SIZE_T InNum, SIZE_T InMax, FResourceSizeEx InTrueResourceSize) :
		Class(InClass),
		Count(InCount),
		Num(InNum),
		Max(InMax),
		TrueResourceSize(InTrueResourceSize)
	{}

	void Add(FArchiveCountMem& Ar, FResourceSizeEx InTrueResourceSize)
	{
		Count++;
		Num += Ar.GetNum();
		Max += Ar.GetMax();
		TrueResourceSize += InTrueResourceSize;
	}
};

struct FSubItem
{
	UObject* Object;
	/** Size of the object, counting containers as current usage */
	SIZE_T Num;
	/** Size of the object, counting containers as total allocated (max usage) */
	SIZE_T Max;
	/** Resource size of the object and all of its references, the 'old-style'. */
	SIZE_T ResourceSize;
	/** Only exclusive resource size, the truer resource size. */
	FResourceSizeEx TrueResourceSize;

	FSubItem(UObject* InObject, SIZE_T InNum, SIZE_T InMax, FResourceSizeEx InTrueResourceSize)
		: Object(InObject), Num(InNum), Max(InMax), TrueResourceSize(InTrueResourceSize)
	{}
};
/**
 * 
 */
class MEMORYDEBUG_API MemoryMonitor
{
public:
	static MemoryMonitor& GetInstance();
	void Test();
	void CheckMemory();
	void SetUp();
	TArray<FSubItem> GetObjects()const;
private:
	static MemoryMonitor& Construct();
	static MemoryMonitor* instance;
	MemoryMonitor();
	~MemoryMonitor();

	UClass* CheckType = nullptr;
	UClass* MetaClass = nullptr;
	UObject* CheckOuter = nullptr;
	UPackage* InsidePackage = nullptr;
	UObject* InsideObject = nullptr;
	UClass* InsideClass = nullptr;

	bool bAll = false;
	bool bTrackDetailedObjectInfo = false;
	bool bOnlyListGCObjects = false;
	bool bOnlyListGCObjectsNoClusters = false;
	bool bOnlyListRootObjects = false;
	bool bShouldIncludeDefaultObjects = false;
	bool bOnlyListDefaultObjects = false;
	bool bShowDetailedObjectInfo = false;
	int32 Depth = -1;
	FString ObjectName;
	TArray<FItem> List;
	TArray<FSubItem> Objects;
	FItem Total;

};


