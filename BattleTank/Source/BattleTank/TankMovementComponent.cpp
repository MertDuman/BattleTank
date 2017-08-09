// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "GameFramework/Actor.h"


UTankMovementComponent::UTankMovementComponent() {

}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet) {
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMove(float Throttle) {
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->DriveTrack( Throttle);
	RightTrack->DriveTrack( Throttle);
}

void UTankMovementComponent::IntendTurn(float Throttle) {
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->Turn( Throttle);
	RightTrack->Turn( Throttle);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	// No need to call super
	FVector AITankForwardLoc = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AITankMovementLoc = MoveVelocity.GetSafeNormal();

	// Gives us the cosine value since other vectors are of length 1.
	float CosineValue = FVector::DotProduct( AITankForwardLoc, AITankMovementLoc);

	// CrossProductResult.Z gives us the sign of sine since other vectors are of length 1.
	FVector CrossProductResult = FVector::CrossProduct( AITankForwardLoc, AITankMovementLoc);

	IntendMove(CosineValue);
	IntendTurn(CrossProductResult.Z);
}
