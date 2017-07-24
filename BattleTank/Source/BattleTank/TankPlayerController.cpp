// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ATankPlayerController::ATankPlayerController() {
	CrosshairXLocation = 0.5f;
	CrosshairYLocation = 0.275f;
	LineTraceRange = 1000000.f; // 10km
}

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if (Tank == nullptr) {	return; }
	UE_LOG(LogTemp, Warning, TEXT("Player possessed Tank: %s"), *Tank->GetName());
}

void ATankPlayerController::Tick( float DeltaTime) {
	Super::Tick(DeltaTime);
	
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair() {
	if ( GetControlledTank() == nullptr) { return; }

	FVector HitLocation;
	if ( GetLineTraceHitLocation( HitLocation)) {
		GetControlledTank()->AimAt( HitLocation);
	}
}

// Get world location with line trace through crosshair.
bool ATankPlayerController::GetLineTraceHitLocation(FVector& out_HitLocation) {

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize( ViewportSizeX, ViewportSizeY);
	FVector2D AimDotLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	// Deproject it to a world direction.
	FVector CameraWorldLocation;
	FVector CameraWorldDirection;
	DeprojectScreenPositionToWorld( 
		AimDotLocation.X, 
		AimDotLocation.Y, 
		CameraWorldLocation, 
		CameraWorldDirection
	);

	// Line trace to find the first visible blocking hit.
	FHitResult HitResult;

	bool HitFound = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		CameraWorldLocation,
		CameraWorldLocation + (CameraWorldDirection * LineTraceRange),
		ECollisionChannel::ECC_Visibility,
		FCollisionQueryParams( "", false, GetPawn())
	);

	// Debug Line
	DrawDebugLine(
		GetWorld(),
		CameraWorldLocation,
		HitResult.ImpactPoint,
		FColor::Blue,
		false,
		0.f,
		0.f,
		5.f
	);

	if ( !HitFound) { 
		out_HitLocation = FVector( 0.f);
		return false; 
	}
	out_HitLocation = HitResult.Location;

	UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());

	return true;
}

bool ATankPlayerController::HitScanAtScreenPosition( FVector2D ScreenLocation, ECollisionChannel CollisionChannel, FHitResult& out_HitResult) {
	GetHitResultAtScreenPosition(
		ScreenLocation,
		CollisionChannel,
		false,
		out_HitResult
	);

	if ( out_HitResult.GetActor() == nullptr) {
		return false;
	}

	return true;
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}


