// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Adding a Component to the Tank object from C++ code instead of Blueprint.
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	LaunchSpeed = 10000;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
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
	UE_LOG(LogTemp, Warning, TEXT("Firing"));
}

void ATank::SetBarrelReference( UTankBarrel * BarrelToSet) {
	TankAimingComponent->SetBarrelReference( BarrelToSet);
}

void ATank::SetTurretReference( UTankTurret * TurretToSet) {
	TankAimingComponent->SetTurretReference( TurretToSet);
}

