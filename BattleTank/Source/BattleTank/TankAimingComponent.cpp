// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Tank.h"
#include "Mortar.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = -ReloadSpeedInSeconds;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bIsReloaded = GetWorld()->GetTimeSeconds() - LastFireTime > ReloadSpeedInSeconds;
	bool bIsEnemy = false;

	if (HitResult.GetActor() != nullptr) {
		bIsEnemy = HitResult.GetActor()->GetClass()->IsChildOf<ATank>() || HitResult.GetActor()->GetClass()->IsChildOf<AMortar>();
	}

	if (AmmoCount <= 0) {
		FiringState = EFiringState::OutOfAmmo;
	} else if (!bIsReloaded) {
		FiringState = EFiringState::Reloading;
	} else if (bIsEnemy) {
		FiringState = EFiringState::Locked;
	} else {
		FiringState = EFiringState::Aiming;
	}
}

void UTankAimingComponent::Fire() {
	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }

	if (bIsReloaded && AmmoCount > 0) {
		if (GetOwner()->GetClass()->IsChildOf<ATank>()) {
			FireTankProjectile();
		} else if (GetOwner()->GetClass()->IsChildOf<AMortar>()) {
			FireMortarProjectiles();
		}

		LastFireTime = GetWorld()->GetTimeSeconds();
		AmmoCount--;
	}
}

void UTankAimingComponent::AimAt(FHitResult HitResult) {
	if (!ensure(Barrel)) { return; }
	if (!ensure(Turret)) { return; }

	this->HitResult = HitResult;

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	bool AimLocationFound;

	// Gets a velocity vector to see where to aim at.
	if (GetOwner()->GetClass()->IsChildOf<AMortar>()) {
		AimLocationFound = UGameplayStatics::SuggestProjectileVelocity(
			this,
			LaunchVelocity,
			StartLocation,
			HitResult.Location,
			LaunchSpeed,
			false, // Aim high with mortar
			0.f,
			0.f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
	} else {
		AimLocationFound = UGameplayStatics::SuggestProjectileVelocity(
			this,
			LaunchVelocity,
			StartLocation,
			HitResult.Location,
			LaunchSpeed,
			false,
			0.f,
			0.f,
			ESuggestProjVelocityTraceOption::DoNotTrace
		);
	}

	AimDirection = LaunchVelocity.GetSafeNormal();

	if (AimLocationFound) {
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}

}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if (!ensure(Barrel)) { return; }

	FRotator BarrelRotator = Barrel->GetComponentRotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) {
	if (!ensure(Turret)) { return; }
	
	FRotator TurretRotator = Turret->GetComponentRotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - TurretRotator;

	if ( FMath::Abs( DeltaRotator.Yaw) < 180.f) {
		Turret->Move(DeltaRotator.Yaw);
	} else {
		Turret->Move(-DeltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::FireMortarProjectiles() {
	AProjectile* Projectile1 = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile1")),
		Barrel->GetSocketRotation(FName("Projectile1"))
		);

	AProjectile* Projectile2 = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile2")),
		Barrel->GetSocketRotation(FName("Projectile2"))
		);

	AProjectile* Projectile3 = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile3")),
		Barrel->GetSocketRotation(FName("Projectile3"))
		);

	if (!ensure(Projectile1)) { return; }
	Projectile1->Launch(LaunchSpeed);

	if (!ensure(Projectile2)) { return; }
	Projectile2->Launch(LaunchSpeed);

	if (!ensure(Projectile3)) { return; }
	Projectile3->Launch(LaunchSpeed);
}

void UTankAimingComponent::FireTankProjectile() {
	AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")),
		Barrel->GetSocketRotation(FName("Projectile"))
		);

	if (!ensure(Projectile)) { return; }
	Projectile->Launch(LaunchSpeed);
}

bool UTankAimingComponent::IsBarrelMoving() const {
	if ( !ensure(Barrel)) { return false; }

	FVector BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals( AimDirection, 0.1);
}

int32 UTankAimingComponent::GetAmmoCount() const {
	return AmmoCount;
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

