// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);

class UParticleSystemComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const &DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	FTankDelegate OnDeath;
	
	UFUNCTION(BlueprintCallable, Category = Health)
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = Health)
	int32 GetMaxHealth() const;

	UFUNCTION(BlueprintCallable, Category = Health)
	int32 GetCurrentHealth() const;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetDeathExplosion(UParticleSystemComponent* DeathExplosionToSet);

	void ActivateDeathExplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = Health)
	int32 MaxHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = Health)
	int32 CurrentHealth;

	UPROPERTY(VisibleAnywhere, Category = Health)
	UParticleSystemComponent* DeathExplosion = nullptr;

};
