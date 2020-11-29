// Fill out your copyright notice in the Description page of Project Settings.


#include "LogExporter.h"
#include "TestEngineSubsystem.h"

#include "MemoryMonitor.h"


// Sets default values
ALogExporter::ALogExporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALogExporter::BeginPlay()
{
	Super::BeginPlay();

	MemoryMonitor& memoryMonitor = MemoryMonitor::GetInstance();
	memoryMonitor.SetUp();
	
}

// Called every frame
void ALogExporter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//UE_LOG(LogTemp, Log, TEXT("%s"),*name.ToString());
}

void ALogExporter::ShowMemoryLog() {
	MemoryMonitor& memoryMonitor = MemoryMonitor::GetInstance();
	memoryMonitor.CheckMemory();
	TArray<FSubItem> objects = memoryMonitor.GetObjects();
	UE_LOG(LogTemp, Log, TEXT("ObjectCount %d"), objects.Num());

	FString filterName = FString("Package /Game/Materials");
	for (const FSubItem& ObjItem : objects) {
		FString Path = ObjItem.Object->GetFullName();
		if (Path.Left(filterName.Len()) == filterName) {
			FColor _Col = FColor::White;
			FVector2D _Scl = FVector2D(1.0f, 1.0f);
			FString output = ObjItem.Object->GetFullName() + FString::SanitizeFloat(ObjItem.Num / 1024.0f);
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, _Col, output, true, _Scl);
			//UE_LOG(LogTemp, Log, TEXT("%s %10.2f MB"), *ObjItem.Object->GetFullName(), ObjItem.Num / 1024.0f);;
		}
	}
}
