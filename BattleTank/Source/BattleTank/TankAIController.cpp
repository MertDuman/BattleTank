// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	PlayerTank = Cast<ATank>( GetWorld()->GetFirstPlayerController()->GetPawn());
	AITank = Cast<ATank>( GetPawn());
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick( DeltaTime);

	if ( PlayerTank != nullptr) {
		AITank->AimAt(PlayerTank->GetActorLocation());
		AITank->Fire();
	}
}


