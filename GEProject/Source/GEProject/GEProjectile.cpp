// Fill out your copyright notice in the Description page of Project Settings.


#include "GEProjectile.h"

// Sets default values
AGEProjectile::AGEProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitialLifeSpan = 5.0f;

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("BulletSceneComponent"));
	}

	if (!CollisionComponent)
	{
		CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BulletComponent"));

		CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Bullet"));

		CollisionComponent->OnComponentHit.AddDynamic(this, &AGEProjectile::OnHit);

		CollisionComponent->InitSphereRadius(15.0f);

		RootComponent = CollisionComponent;
	}

	if (!BulletMovementComponent)
	{
		BulletMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("BulletMovementComponent"));
		BulletMovementComponent->SetUpdatedComponent(CollisionComponent);
		BulletMovementComponent->InitialSpeed = 3500.0f;
		BulletMovementComponent->MaxSpeed = 3500.0f;
		BulletMovementComponent->bRotationFollowsVelocity = true;
		BulletMovementComponent->bShouldBounce = true;
		BulletMovementComponent->Bounciness = 0.3f;
		BulletMovementComponent->ProjectileGravityScale = 0.0f;
	}

	if (!BulletMeshComponent)
	{
		BulletMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletMeshComponent"));

		static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("'/Game/Mesh/ProjectileBullet.ProjectileBullet'"));

		

		if (Mesh.Succeeded())
		{

			/*GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Worked! mesh"));*/

			BulletMeshComponent->SetStaticMesh(Mesh.Object);
		}

		static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("'/Game/Mesh/ProjectileBulletM.ProjectileBulletM'"));

		if (Material.Succeeded())
		{
			BulletMaterialInstance = UMaterialInstanceDynamic::Create(Material.Object, BulletMeshComponent);
		}

		BulletMeshComponent->SetMaterial(0, BulletMaterialInstance);
		BulletMeshComponent->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
		BulletMeshComponent->SetupAttachment(RootComponent);

	}
}

// Called when the game starts or when spawned
void AGEProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGEProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGEProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(BulletMovementComponent->Velocity * 100.0f, Hit.ImpactPoint);
	}
	Destroy();
}

void AGEProjectile::FireInDirection(const FVector& ShootDirection)
{
	BulletMovementComponent->Velocity = ShootDirection * BulletMovementComponent->InitialSpeed;
}

