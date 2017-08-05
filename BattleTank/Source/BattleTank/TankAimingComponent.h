// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;
class AProjectile;

UENUM()
enum class EFiringState : uint8 {
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AimAt(FHitResult HitResult);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = Firing)
	int32 GetAmmoCount() const;

	// For AI Tank use. AI Tanks will only fire if barrel isn't moving (with a tolerance)
	bool IsBarrelMoving() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, Category = State)
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	int32 AmmoCount = 5;

	bool bIsReloaded = true;

private:
	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;

	// Required for setting firing state.
	FHitResult HitResult;

	// Required for checking if barrel is moving.
	FVector AimDirection;

	// We need a UClass for SpawnActor. We could declare it as UClass, but that would mean any UClass could be used.
	// We use TSubclassOf<AProjectile> which limits what you can choose.
	UPROPERTY(EditAnywhere, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBlueprint;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchSpeed = 10000.f;

	UPROPERTY(EditAnywhere, Category = Firing)
	float ReloadSpeedInSeconds = 2.f;

	float LastFireTime;

	void MoveBarrelTowards( FVector AimDirection);

	void MoveTurretTowards( FVector AimDirection);
};
