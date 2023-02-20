// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "MyDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GEPROJECT_API UMyDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor(float DeltaTime);

	void GetAllValidActors(float DeltaTime);

private:
	UPROPERTY(EditAnywhere, Category = "Door Open Target")
	float TargetHeight = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Door Speed")
	float MoveSpeed = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Door Open Rotation")
	FVector RotationZ;

	UPROPERTY(EditAnywhere, Category = "Door Open Target")
	ATriggerVolume* TriggerVol;

	FVector CurrentLocation;
};
