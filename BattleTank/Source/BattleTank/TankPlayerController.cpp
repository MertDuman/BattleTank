// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

ATankPlayerController::ATankPlayerController() {
	CrosshairXLocation = 0.5f;
	CrosshairYLocation = 0.275f;
	LineTraceRange = 100000; // 10km
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

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>( GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() {
	if ( GetControlledTank() == nullptr) { return; }

	FVector HitLocation;
	if ( GetSightRayHitLocation( HitLocation)) {
		UE_LOG(LogTemp, Warning, TEXT("%s"), *HitLocation.ToString());
		// Tell controlled tank to aim at this point
	}
}

// Get world location with line trace through crosshair.
bool ATankPlayerController::GetSightRayHitLocation(FVector& out_HitLocation) {

	// Find the crosshair position
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize( ViewportSizeX, ViewportSizeY);
	FVector2D AimDotLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

	

	UE_LOG(LogTemp, Warning, TEXT("AimDotLocation: %s"), *AimDotLocation.ToString());

	// Deproject it to a world direction.
	FVector CameraWorldLocation;
	FVector CameraWorldDirection;
	DeprojectScreenPositionToWorld( AimDotLocation.X, AimDotLocation.Y, CameraWorldLocation, CameraWorldDirection);

	UE_LOG( LogTemp, Warning, TEXT("Direction: %s"), *CameraWorldDirection.ToString());

	// Line trace by channel
	FHitResult HitResult;

	GetHitResultAtScreenPosition(
		AimDotLocation,
		ECollisionChannel::ECC_Pawn,
		false,
		HitResult
	);

	DrawDebugLine(
		GetWorld(),
		CameraWorldDirection + FVector( 0.f, 0.f, 100.f),
		HitResult.ImpactPoint,
		FColor::Blue,
		false,
		0.f,
		0.f,
		5.f
	);

	

	if ( HitResult.GetActor() == nullptr) { return false;}
	UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());
	
	
	return true;
}


