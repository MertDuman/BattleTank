// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

ATankAIController::ATankAIController() {
	AcceptanceRadius = 3000;
}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	PlayerTank = Cast<ATank>( GetWorld()->GetFirstPlayerController()->GetPawn());
	AITank = Cast<ATank>( GetPawn());
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick( DeltaTime);

	if ( PlayerTank != nullptr) {
		// Move towards player
		MoveToActor( PlayerTank, AcceptanceRadius); // there is more to this method, but the defaults are fine

		// Aim and fire towards the player
		AITank->GetAimingComponent()->AimAt(PlayerTank->GetActorLocation(), 10000); //TODO Fix magic number
		AITank->Fire();
	}
}


