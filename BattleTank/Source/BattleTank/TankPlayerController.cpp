// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "DrawDebugHelpers.h"

ATankPlayerController::ATankPlayerController() {
	CrosshairXLocation = 0.5f;
	CrosshairYLocation = 0.275f;
	LineTraceRange = 1000000.f; // 10km
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	FoundAimingComponent( GetPawn()->FindComponentByClass<UTankAimingComponent>());
}

void ATankPlayerController::Tick( float DeltaTime) {
	Super::Tick(DeltaTime);
	
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	FHitResult HitResult;
	if ( GetLineTraceHitLocation( HitResult)) {
		GetPawn()->FindComponentByClass<UTankAimingComponent>()->AimAt( HitResult); //TODO Not doing anything when aiming at sky.
	}
}

// Get world location with line trace through crosshair.
bool ATankPlayerController::GetLineTraceHitLocation(FHitResult& out_HitResult) {

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
	bool HitFound = GetWorld()->LineTraceSingleByChannel(
		out_HitResult,
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

	UE_LOG(LogTemp, Warning, TEXT("%s"), *out_HitResult.ToString())
	if ( !HitFound) { 
		return false; 
	}

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


