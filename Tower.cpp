// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Projectile.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Particles/ParticleSystemComponent.h"




void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank)
	{
		if (InFireRange())
		{
			// turn to a target
			RotateTurret(Tank->GetActorLocation());					
		}
	}
	
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	// Find distance to the tank
	Tank = dynamic_cast<ATank*>(UGameplayStatics::GetPlayerPawn(this, 0));
	
	
	// If in range -> rotate turret toward tank -> open fire
	
	//FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();

	GetWorldTimerManager().SetTimer(FireRateTimerHandler, this, &ATower::CheckFireCondition, FireRate, true);	
	
}

void ATower::CheckFireCondition()
{
	if (InFireRange())
		Super::Fire();
}

bool ATower::InFireRange()
{
	if (Tank)
	{
		float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

		if (Distance <= ShootingRange)			
			return true;
	}
	return false;
}

//void ATower::Turn(float Value)
//{
//	FRotator DeltaRotation(0.0f, Value * RotationRate  * (UGameplayStatics::GetWorldDeltaSeconds(this)), 0.0f);
//	AddActorLocalRotation(DeltaRotation, true);
//}

/*
GetWorldTimerManager().SetTimer(FireRateTimerHandler, this, &ATower::CheckFireCondition, FireRate, true);
			DrawDebugSphere(GetWorld(), ProjectileSpawnPointLocation, 12, 15.f, FColor::Purple, false, 10.f);
*/