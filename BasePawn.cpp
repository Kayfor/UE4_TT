// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));

	StaticMeshBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	StaticMeshBase->SetupAttachment(CapsuleComp);	
	
	StaticMeshTurret = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	StaticMeshTurret->SetupAttachment(StaticMeshBase);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileComponent"));
	ProjectileSpawnPoint->SetupAttachment(StaticMeshTurret);

	TurretFireParticleSys = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticles"));
	TurretFireParticleSys->SetupAttachment(StaticMeshTurret);

	ShutSound = CreateDefaultSubobject<USoundCue>(TEXT("Shut_Sound"));
	ReChargeSound = CreateDefaultSubobject<USoundCue>(TEXT("RC_Sound"));
	RootComponent = CapsuleComp;

// Floats
	Damage = 20.f;

// Ints
	
	
	MaxAmmo = 40;
	Ammo = 40;
	

// Bools
	//ReadyToFire = true;
	
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - StaticMeshTurret->GetComponentLocation();
	
	// Vector to rotate turret mesh due to cursor's position
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);
	// actual rotation of component
	StaticMeshTurret->SetWorldRotation(LookAtRotation);
}

void ABasePawn::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT(" 'Fire' was called! "));

	UGameplayStatics::PlaySound2D(this, ShutSound);
	/*if (ShutSound)
	{
		UGameplayStatics::PlaySound2D(this, ShutSound);
	}*/

	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();	
	FRotator ProjectileSpawnPointRotation = ProjectileSpawnPoint->GetComponentRotation();

	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation);
	Projectile->SetOwner(this);


	//DrawDebugSphere(GetWorld(), ProjectileSpawnPointLocation, 12, 15.f, FColor::Purple, false, 10.f);
	//const FTransform SpawnTransform;
	//UGameplayStatics::SpawnEmitterAtLocation(this,TurretFireParticleSys,SpawnTransform,	true, EPSCPoolMethod::AutoRelease,true);
}
