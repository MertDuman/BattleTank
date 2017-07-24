// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	ATank* PlayerTank = GetPlayerControlledTank();
	if (PlayerTank == nullptr) { return; }
	UE_LOG(LogTemp, Warning, TEXT("AI found Player Tank: %s"), *PlayerTank->GetName());
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick( DeltaTime);

	if ( GetPlayerControlledTank() != nullptr) {
		GetAIControlledTank()->AimAt(GetPlayerControlledTank()->GetTargetLocation());
	}
	
}

ATank* ATankAIController::GetAIControlledTank() const {
	return Cast<ATank>( GetPawn());
}

ATank* ATankAIController::GetPlayerControlledTank() const {
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if ( PlayerPawn == nullptr) { return nullptr; }
	return Cast<ATank>( PlayerPawn);
}


