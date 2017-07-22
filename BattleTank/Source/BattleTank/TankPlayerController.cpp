// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();

	ATank* Tank = GetControlledTank();
	if (Tank == nullptr) {	return; }
	UE_LOG(LogTemp, Warning, TEXT("Possessed Tank: %s"), *Tank->GetName());
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>( GetPawn());
}


