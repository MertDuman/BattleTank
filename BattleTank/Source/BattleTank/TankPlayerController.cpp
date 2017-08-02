// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "DrawDebugHelpers.h"

ATankPlayerController::ATankPlayerController() {
	CrosshairXLocation = 0.5f;
	CrosshairYLocation = 0.275f;
	LineTraceRange = 1000000.f; // 10km
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	if ( !ensure(GetControlledTank())) { return; }

	FoundAimingComponent( GetControlledTank()->FindComponentByClass<UTankAimingComponent>());
}

void ATankPlayerController::Tick( float DeltaTime) {
	Super::Tick(DeltaTime);
	
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if ( !ensure(GetControlledTank())) { return; }

	FVector HitLocation;
	if ( GetLineTraceHitLocation( HitLocation)) {
		GetControlledTank()->FindComponentByClass<UTankAimingComponent>()->AimAt( HitLocation, 10000); //TODO Not doing anything when aiming at sky.
	} // TODO Fix the magic number LaunchSpeed
}

// Get world location with line trace through crosshair.
bool ATankPlayerController::GetLineTraceHitLocation(FVector& out_HitLocation) {

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize( ViewportSizeX, ViewportSizeY);
	FVector2D AimDotLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// Deproject it to a world direction.
	FVector AimDotWorldLocation;
	FVector AimDotWorldDirection;
	DeprojectScreenPositionToWorld( 
		AimDotLocation.X, 
		AimDotLocation.Y, 
		AimDotWorldLocation, 
		AimDotWorldDirection
	);

	// Line trace to find the first visible blocking hit.
	FHitResult HitResult;

	bool HitFound = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		AimDotWorldLocation,
		AimDotWorldLocation + (AimDotWorldDirection * LineTraceRange),
		ECollisionChannel::ECC_Visibility,
		FCollisionQueryParams( "", false, GetPawn())
	);

	// Debug Line
	/*DrawDebugLine(
		GetWorld(),
		AimDotWorldLocation,
		HitResult.ImpactPoint,
		FColor::Blue,
		false,
		0.f,
		0.f,
		5.f
	);*/

	if ( !HitFound) { 
		out_HitLocation = FVector( 0.f);
		return false; 
	}
	out_HitLocation = HitResult.Location;

	return true;
}

bool ATankPlayerController::HitScanAtScreenPosition( FVector2D ScreenLocation, ECollisionChannel CollisionChannel, FHitResult& out_HitResult) {
	bool HitFound = GetHitResultAtScreenPosition(
		ScreenLocation,
		CollisionChannel,
		false,
		out_HitResult
	);

	if ( !HitFound) {
		return false;
	}

	return true;
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


