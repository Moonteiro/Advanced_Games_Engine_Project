// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "GEProjectile.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyCharacter.generated.h"

UCLASS()
class GEPROJECT_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	//UFUNCTION(BlueprintPure, Category = Health)
	//float StartHealth();

	//UFUNCTION(BlueprintPure, Category = Health)
	//float CurrentHealth();

	//UFUNCTION(BlueprintPure, Category = Health)
	//void UpdateCurrentHealth(float health);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void MoveForward(float Value);

	virtual void MoveRight(float Value);

	virtual void Shoot();

	virtual void EnableCrouch();

	virtual void StopCrouch();

	virtual void EnableSprint();

	virtual void StopSprint();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AGEProjectile> ProjectileClass;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(float damageFloat);

	UFUNCTION(BlueprintCallable)
	void PickUpHealth(float addedHealth);

	UFUNCTION(BlueprintCallable)
	void PickUpEnergy(float addedEnergy);

	UFUNCTION(BlueprintCallable)
	float CheckHealth(float checkHealth);

	UFUNCTION(BlueprintCallable)
	float CheckEnergy(float checkEnergy);

	UFUNCTION(BlueprintCallable)
	float CheckKillCount(float checkKillCount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = KillCount)
	float killcount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Health)
	float health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Energy)
	float energy;

	UFUNCTION(BlueprintCallable)
	void Respawn();

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* GECameraComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* ArmMesh;

	
};