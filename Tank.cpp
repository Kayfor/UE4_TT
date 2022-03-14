// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
//#include "DrawDebugHelpers.h"

ATank::ATank()
{
	Scaller = 1.f;
	Speed = 5.f;
	RotationRate = 30.f;
	bRedyToFire = true;
	

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());

	CameraBoom = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraBoom->SetupAttachment(SpringArm);

	// Vectors related to turret control
	/*ToTarget = FVector::ZeroVector;
	TraceHitLocation = FVector::ZeroVector;
	TurretLocation = FVector::ZeroVector;*/
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Super:: gives us a base class realisation
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn); 
	//PlayerInputComponent->BindAxis(TEXT("RotateTurret"), this, &ATank::RotateTurret());

	
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed ,this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (PlayerControllerRef)
	{		
		PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

		FVector CursorHitResult = HitResult.ImpactPoint;

		//DrawDebugSphere(GetWorld(), CursorHitResult, 12, 15.f, FColor::Blue, false, -1.f);

		RotateTurret(CursorHitResult);
	}
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = dynamic_cast<APlayerController*>(GetController());

	FVector CursorPoint(0.f, 0.f, 0.f); FVector TankHead(GetActorLocation() + FVector(0.f,0.f,50.f));

	

}

//deltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);

void ATank::Move(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Value);

	// X= Value * Scaller * DeltaTime

	FVector DeltaLocation(Value * Speed * Scaller *(UGameplayStatics::GetWorldDeltaSeconds(this)), 0.0f, 0.0f);

	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("%f"), Value);

	// FRotator DeltaRotation = FRotator::ZeroRotator;

	FRotator DeltaRotation(0.0f, Value * RotationRate * Scaller * (UGameplayStatics::GetWorldDeltaSeconds(this)), 0.0f);
	AddActorLocalRotation(DeltaRotation, true);	
}

void ATank::Fire()
{
	if (bRedyToFire)
	{
		Super::Fire();
		bRedyToFire=!bRedyToFire;
		
	}
	
	GetWorldTimerManager().SetTimer(FireRateTimerHandler, this, &ATank::PlayReChargeSound, FireRate, false);
	bRedyToFire=!bRedyToFire;
}

void ATank::PlayReChargeSound()
{
	if (ABasePawn::ReChargeSound)
	{
		UGameplayStatics::PlaySound2D(this, dynamic_cast<USoundCue*>(ABasePawn::ReChargeSound));
	}
}


