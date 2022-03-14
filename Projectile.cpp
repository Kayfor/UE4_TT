// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Tank.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/PrimitiveComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/WorldPSCPool.h"
#include "Sound/SoundCue.h"
#include "Misc/DateTime.h"
#include "TimerManager.h"




// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshShell = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shell_SM"));
	RootComponent = StaticMeshShell;

	ShellTailParticleSys = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Shell_tail_PS"));
	ShellTailParticleSys->SetupAttachment(StaticMeshShell);

	ProjectileMC = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovComp"));
	ProjectileMC->SetUpdatedComponent(StaticMeshShell);

	ShellHitParticleSys = CreateDefaultSubobject<UParticleSystem>(TEXT("Shell_hit_PS"));
	//ShellHitParticleSys->SetupAttachment(StaticMeshShell);

	HitSound = CreateDefaultSubobject<USoundCue>(TEXT("Shell_hit_Sound"));

	DamageAmount = 15.f;
}
	

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	//SetTimer(FTimerHandle& InOutHandle, float InRate, bool InbLoop, float InFirstDelay = -1.f)
	//GetWorldTimerManager().SetTimer(FireRateTimerHandler, this, &ATower::CheckFireCondition, FireRate, true);	
	GetWorldTimerManager().SetTimer(ProjectileLifeTimerHandler, this, &AProjectile::DestroyHandler, 3.f, true);
	//calling function throught deligate
	StaticMeshShell->OnComponentHit.AddDynamic(this, &AProjectile::OnHit/*(HitComp, OtherActor, OtherComp, NormalImpulse, Hit)*/);
}


// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if(StaticMeshShell->GetComponentLocation().Z ==2.f)
	{
		AActor::Destroy();
	}*/
	
}

void AProjectile::DestroyHandler()
{
	AActor::Destroy();
}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//** Aplying damage related variables **
	AController* CurrentOwner = dynamic_cast<AController*>(GetOwner());  // I did it slightly different.
	//if (CurrentOwner == nullptr) return;
	//CurrentOwner->GetInstigatorController();
	auto* DamageTypeClass = UDamageType::StaticClass();

	if(OtherActor /* && OtherActor != this && OtherActor != CurrentOwner*/)
	{ 
		ATank* Tank = Cast<ATank>(OtherActor);
		ATower* Tower = Cast<ATower>(OtherActor); 


		if (Tank || Tower)
		{
			// Let's spawn the particles
			if (Cast<ATank>(OtherActor) || Cast<ATower>(OtherActor))
			{						
				// Spawn some hit particles
				if (ShellHitParticleSys)
				{
					UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ShellHitParticleSys, GetActorLocation(), FRotator(0.f), false);
				}
				// Decrement health
				UGameplayStatics::ApplyDamage(OtherActor, DamageAmount, CurrentOwner, this, DamageTypeClass);

				
				// Play some hit sound
				if (HitSound)
				{
					UGameplayStatics::PlaySound2D(this, HitSound);
				}
			}
			// Destroy a projectile
			//StaticMeshShell->DestroyComponent(); 
			UE_LOG(LogTemp, Warning, TEXT(" OnHeat was called! %f damage was caused by %s!"), DamageAmount,OtherActor);
			AActor::Destroy();
		}
		
	}
	
	
}

