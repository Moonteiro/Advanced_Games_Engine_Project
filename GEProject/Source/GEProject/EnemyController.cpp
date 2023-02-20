// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GameplayStatics.h"
#include "NavigationSystem.h"
#include "EnemyController.h"



void AEnemyController::BeginPlay()
{

	Super::BeginPlay();

	NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);

	bRotationFocalPoint = true;

	GenerateRandomSearchLocation();

	MoveToRandomLocation();
}

void AEnemyController::Tick(float DeltaSeconds)
{

}

void AEnemyController::GenerateRandomSearchLocation()
{
	// Random Location inside the nav area to find a random location to go to
	RandomLocation = NavArea->GetRandomReachablePointInRadius(this, GetPawn()->GetActorLocation(), 10000.0f);
}

void AEnemyController::MoveToRandomLocation()
{
	MoveToLocation(RandomLocation);
	
	SetFocalPoint(RandomLocation);

	UpdateControlRotation(GetWorld()->DeltaTimeSeconds, bRotationFocalPoint);
}

void AEnemyController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

		GenerateRandomSearchLocation();
		MoveToRandomLocation();
}
