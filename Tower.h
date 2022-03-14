// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float ShootingRange = 500.f;;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat")
		float RotationRate = 10.f;

	UParticleSystemComponent* TurretParticleSystem;

	//FVector PSP = ABasePawn::ProjectileSpawnPoint->GetComponentLocation();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

 private:

	 class ATank* Tank; // forward declare instead adding #include "Tank.h";

	 FHitResult HitResult;

	// void Turn(float Value);

	 FTimerHandle  FireRateTimerHandler;
	 float FireRate = 3.f;

	 UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	 void CheckFireCondition();

	 bool InFireRange();
};
