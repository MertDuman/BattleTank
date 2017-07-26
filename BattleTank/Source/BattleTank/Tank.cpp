// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Adding a Component to the Tank object from C++ code instead of Blueprint.
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	LaunchSpeed = 10000;
	ReloadSpeedInSeconds = 2.f;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

	LastFireTime = -ReloadSpeedInSeconds;
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation) {
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire() {
	if ( Barrel == nullptr) { return; }

	if ( GetWorld()->GetTimeSeconds() - LastFireTime > ReloadSpeedInSeconds) {
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
		);

		if (Projectile == nullptr) { return; }
		Projectile->Launch(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();
	}
	
}

void ATank::SetBarrelReference( UTankBarrel * BarrelToSet) {
	Barrel = BarrelToSet;
	TankAimingComponent->SetBarrelReference( BarrelToSet);
}

void ATank::SetTurretReference( UTankTurret * TurretToSet) {
	TankAimingComponent->SetTurretReference( TurretToSet);
}

