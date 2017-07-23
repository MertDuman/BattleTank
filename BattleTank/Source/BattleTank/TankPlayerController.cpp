// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


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

	// Get world location with line trace through crosshair.
		// Tell controlled tank to aim at this point
}


