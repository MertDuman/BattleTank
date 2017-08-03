// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Tank.h"
#include "Regex.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	LaunchSpeed = 10000;
	ReloadSpeedInSeconds = 2.f;
	
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = -ReloadSpeedInSeconds;
	bIsReloaded = true;
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bIsReloaded = GetWorld()->GetTimeSeconds() - LastFireTime > ReloadSpeedInSeconds;
	bool bIsTank = false;

	if (HitResult.GetActor() != nullptr) {
		bIsTank = HitResult.GetActor()->GetClass()->IsChildOf<ATank>();
	}

	if ( !bIsReloaded) {
		FiringState = EFiringState::Reloading;
	} else if ( bIsTank) {
		FiringState = EFiringState::Locked;
	} else {
		FiringState = EFiringState::Aiming;
	}
}

void UTankAimingComponent::Fire() {
	if (!ensure(Barrel)) { return; }
	if (!ensure(ProjectileBlueprint)) { return; }

	if ( bIsReloaded) {
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		if (!ensure(Projectile)) { return; }
		Projectile->Launch( LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

void UTankAimingComponent::AimAt(FHitResult HitResult) {
	if ( !ensure(Barrel)) { return; }
	if ( !ensure(Turret)) { return; }

	this->HitResult = HitResult;

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Gets a velocity vector to see where to aim at.
	bool AimLocationFound = UGameplayStatics::SuggestProjectileVelocity(
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

	FVector AimDirection = LaunchVelocity.GetSafeNormal();

	if ( AimLocationFound) {
		MoveBarrelTowards(AimDirection);
		MoveTurretTowards(AimDirection);
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	if ( !ensure(Barrel)) { return; }

	FRotator BarrelRotator = Barrel->GetComponentRotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection) {
	if ( !ensure(Turret)) { return; }

	FRotator TurretRotator = Turret->GetComponentRotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - TurretRotator;

	if ( DeltaRotator.Yaw < 180.f && DeltaRotator.Yaw > -180.f) {
		Turret->Move(DeltaRotator.Yaw);
	} else {
		Turret->Move(-DeltaRotator.Yaw);
	}
	
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

