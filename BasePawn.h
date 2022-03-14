// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"
//#include "Components/CapsuleComponent.h"  replaced by forward declaration

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();
	
	UPROPERTY(EditAnywhere, Category = "Charackteristics")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "Charackteristics")
	int32 MaxAmmo;

	UPROPERTY(EditAnywhere, Category = "Charackteristics")
	int32 Ammo;

	/*UPROPERTY(VisibleInstanceOnly)
	bool ReadyToFire;*/

protected:
	void RotateTurret(FVector LookAtTarget);
		
	UFUNCTION(BlueprintCallable, meta = (AllowPrivateAccess = "true"))
	void Fire();

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp = nullptr;  // forward declaration

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMeshBase = nullptr;
	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* StaticMeshTurret = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint = nullptr;

	// Example how to get access blueprint to variables in private section
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* TurretFireParticleSys = nullptr;

	FHitResult HitResult;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class AProjectile> ProjectileClass;

 public:
	UPROPERTY(EditAnywhere, Category = "Combat | Sound")
		class USoundCue* ShutSound;

	UPROPERTY(EditAnywhere, Category = "Combat | Sound")
		 USoundCue* ReChargeSound;


public:	
	// Called every frame
	

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
