// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


UTankMovementComponent::UTankMovementComponent() {

}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveForward(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle( Throw);
	RightTrack->SetThrottle( Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw) {
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle( Throw);
	RightTrack->SetThrottle( -Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	// No need to call super
	Super::RequestDirectMove( MoveVelocity, bForceMaxSpeed); // TODO Comment this out don't need it.
	UE_LOG(LogTemp, Warning, TEXT("%s"), *MoveVelocity.ToString());
	

}
