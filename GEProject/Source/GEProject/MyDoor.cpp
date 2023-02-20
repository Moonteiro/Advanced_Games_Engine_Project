// Fill out your copyright notice in the Description page of Project Settings.


#include "MyDoor.h"

// Sets default values for this component's properties
UMyDoor::UMyDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMyDoor::BeginPlay()
{
	Super::BeginPlay();

	CurrentLocation = GetOwner()->GetActorLocation();

	TargetHeight += CurrentLocation.Z;

	// ...
	
}


// Called every frame
void UMyDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	GetAllValidActors(DeltaTime);

	// ...
}

void UMyDoor::OpenDoor(float DeltaTime)
{

	CurrentLocation.Z = FMath::FInterpConstantTo(CurrentLocation.Z, TargetHeight, DeltaTime, MoveSpeed);

	GetOwner()->SetActorLocation(CurrentLocation);

}

void UMyDoor::GetAllValidActors(float DeltaTime)
{
	TArray<AActor*> OverlappingActors;
	{
		if (TriggerVol != nullptr)
		{
			TriggerVol->GetOverlappingActors(OverlappingActors);

			if (OverlappingActors.Num() >= 1)
			{
				OpenDoor(DeltaTime);
			}
		}

	}
}

