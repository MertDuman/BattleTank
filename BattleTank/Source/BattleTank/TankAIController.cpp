// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "GameFramework/Pawn.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"

ATankAIController::ATankAIController() {

}

void ATankAIController::BeginPlay() {
	Super::BeginPlay();

	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	AITank = GetPawn();
}

/// We are using SetPawn here to make sure we have a possessed tank when we subscribe to the Delegate.
void ATankAIController::SetPawn(APawn * InPawn) {
	Super::SetPawn(InPawn);

	if ( !InPawn) { return; }

	ATank* ControlledTank = Cast<ATank>( InPawn);
	if ( !ControlledTank) { return; }

	// Subscribe to Tank's Delegate to be called after a Broadcast().
	ControlledTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath); //TODO put this at beginplay.
}

void ATankAIController::OnTankDeath() {
	if(!AITank) { return; }
	Cast<ATank>(AITank)->ActivateDeathExplosion();
	AITank->DetachFromControllerPendingDestroy();
}

void ATankAIController::Tick(float DeltaTime) {
	Super::Tick( DeltaTime);

	if (!ensure(PlayerTank && AITank)) { return; }

	// Move towards player
	MoveToActor( PlayerTank, AcceptanceRadius); // there is more to this method, but the defaults are fine

	// Aim and fire towards the player
	UTankAimingComponent* TankAimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
	if ( !ensure(TankAimingComponent)) { return; }

	// Needed because AimAt requires a FHitResult intead of an FVector
	FHitResult HitResult;
	HitResult.Location = PlayerTank->GetActorLocation();

	TankAimingComponent->AimAt( HitResult);

	if (!TankAimingComponent->IsBarrelMoving()) {
		TankAimingComponent->Fire();
	}
}


