// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class GEPROJECT_API AEnemyController : public AAIController
{
	GENERATED_BODY()

protected:

	void BeginPlay() override;
	void Tick(float DeltaSeconds) override;

private:

	//APawn* PlayerPawn;

	class AEnemyCharacter* ControlledEnemy;

	class UNavigationSystemV1* NavArea;

	FVector RandomLocation = FVector();
	
	bool bRotationFocalPoint;

	void GenerateRandomSearchLocation();
	
	void MoveToRandomLocation();

public:

	// Tells when enemy reached a certain part
	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;


};
