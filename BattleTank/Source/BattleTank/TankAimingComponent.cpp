// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "Tank.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if ( Barrel == nullptr) { return; }

	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	// Gets a velocity vector to see where to aim at.
	bool AimLocationFound = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	FVector AimDirection = LaunchVelocity.GetSafeNormal();
	float Time = GetWorld()->GetTimeSeconds();

	if ( AimLocationFound) {
		UE_LOG( LogTemp, Warning, TEXT( "%f Aim Loc Found"), Time);
		//MoveBarrelTowards(AimDirection);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("%f Aim Loc NOT Found"), Time);
	}
	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection) {
	// AimDirection is a unit vector which tells us where to point at.
	// Calculate the difference between the barrel's rotation and AimDirection.
	// Move the barrel accordingly.

	
	FRotator BarrelRotator = Barrel->GetComponentRotation();
	FRotator AimAsRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimAsRotator - BarrelRotator;
	//UE_LOG(LogTemp, Warning, TEXT("BarrelRotator: %s"), *BarrelRotator.ToString());
	UE_LOG(LogTemp, Warning, TEXT("AimAsRotator: %s"), *AimAsRotator.ToString());
	
	Barrel->Elevate(5);
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UStaticMeshComponent * TurretToSet) {
	Turret = TurretToSet;
}

