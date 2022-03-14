// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();		

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	bool bRedyToFire;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
private:

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class UCameraComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		class USpringArmComponent* SpringArm;

	//UPROPERTY(VisibleAnywhere, Category = "Components")
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement" , meta = (AllowPrivateAccess = "true"))
		float Scaller;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
		float RotationRate;

	// Movement fubctionality
	void Move(float Value);
	void Turn(float Value);
	void Fire();
	void PlayReChargeSound();

	FTimerHandle  FireRateTimerHandler;
	float FireRate = 3.f;

	

//	void RotateTurret(FVector LookAtTarget);

	FHitResult HitResult;
	APlayerController* PlayerControllerRef;

	/*FVector ToTarget; 
	FVector TraceHitLocation;
	FVector TurretLocation;*/
};
