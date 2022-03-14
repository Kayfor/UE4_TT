// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
		UPROPERTY(EditAnywhere, Category = "Charackteristics")
		float MaxHealth;

		UPROPERTY(EditAnywhere, Category = "Charackteristics")
		float Health;
		
		UPROPERTY(EditAnywhere, Category = "Charackteristics")
		float DamageValue;

		UFUNCTION(BlueprintCallable, Category = "Damage system",meta = (AllowPrivateAccess = "true"))
		void DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* Instigator, AActor* DamageCauser);
		
};
