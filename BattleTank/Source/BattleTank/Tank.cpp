// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

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

void ATank::Fire() {
	if ( !ensure(Barrel)) { return; }

	if (GetWorld()->GetTimeSeconds() - LastFireTime > ReloadSpeedInSeconds) {
		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);

		if ( !ensure(Projectile)) { return; }
		Projectile->Launch(LaunchSpeed);

		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

