// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GECameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));

	GECameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	GECameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	GECameraComponent->bUsePawnControlRotation = true;

	ArmMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(ArmMesh != nullptr);

	ArmMesh->SetupAttachment(GECameraComponent);

	ArmMesh->bCastDynamicShadow = false;
	ArmMesh->CastShadow = false;

	ArmMesh->SetOnlyOwnerSee(true);

	GetMesh()->SetOwnerNoSee(true);


	health = 1.0f;

	energy = 1.0f;

	killcount = 0.0f;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::Jump);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyCharacter::Shoot);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AMyCharacter::EnableCrouch);

	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AMyCharacter::StopCrouch);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AMyCharacter::EnableSprint);

	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AMyCharacter::StopSprint);
}

void AMyCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AMyCharacter::MoveRight(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMyCharacter::EnableCrouch()
{
	Crouch();
}

void AMyCharacter::StopCrouch()
{
	UnCrouch();
}

void AMyCharacter::EnableSprint()
{
	float SprintValue = 1.5f;
	GetCharacterMovement()->MaxWalkSpeed *= SprintValue;
}

void AMyCharacter::StopSprint()
{
	float SprintValue = 1.5f;
	GetCharacterMovement()->MaxWalkSpeed /= SprintValue;
}


void AMyCharacter::Shoot()
{

	if (energy > 0.1f)
	{
		if (ProjectileClass)
		{
			FVector CameraLocation;
			FRotator CameraRotation;
			GetActorEyesViewPoint(CameraLocation, CameraRotation);



			MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

			FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

			FRotator MuzzleRotation = CameraRotation;
			MuzzleRotation.Pitch += 10.0f;

			UWorld* World = GetWorld();
			if (World)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();

				AGEProjectile* Projectile = World->SpawnActor<AGEProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
				if (Projectile)
				{
					FVector LaunchDirection = MuzzleRotation.Vector();
					Projectile->FireInDirection(LaunchDirection);
				}
			}

			energy = energy - 0.1;

			FString energyStr = FString::SanitizeFloat(killcount);
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, *energyStr);


		}
	}
}

void AMyCharacter::TakeDamage(float damageFloat)
{
	health -= damageFloat;

	if (health < 0.1f)
	{
		Respawn();
	}

	FString healthStr = FString::SanitizeFloat(health);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, *healthStr);

}

void AMyCharacter::PickUpHealth(float addedHealth)
{
		health = health + addedHealth;
		FString healthGrenStr = FString::SanitizeFloat(health);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, *healthGrenStr);
}



void AMyCharacter::PickUpEnergy(float addedEnergy)
{
	energy = energy + addedEnergy;

	FString energyStr = FString::SanitizeFloat(energy);
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, *energyStr);
}

void AMyCharacter::Respawn()
{
	health = 1.0f;
	energy = 1.0f;
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);

}

float AMyCharacter::CheckHealth(float checkHealth)
{
	checkHealth = health;
	return checkHealth;
}

float AMyCharacter::CheckEnergy(float checkEnergy)
{
	checkEnergy = energy;
	return checkEnergy;
}

float AMyCharacter::CheckKillCount(float checkKillCount)
{
	return checkKillCount;
}