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

void UTankMovementComponent::IntendMoveForward(float Throttle) {
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->SetThrottle( Throttle);
	RightTrack->SetThrottle( Throttle);
}

void UTankMovementComponent::IntendTurnRight(float Throttle) {
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->SetThrottle( Throttle);
	RightTrack->SetThrottle( -Throttle);
}

void UTankMovementComponent::IntendStop() {
	if (!ensure(LeftTrack && RightTrack)) { return; }

	LeftTrack->ResetThrottle();
	RightTrack->ResetThrottle();
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) {
	// No need to call super
	FVector AITankForwardLoc = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector AITankMovementLoc = MoveVelocity.GetSafeNormal();

	// Gives us the cosine value since other vectors are of length 1.
	float CosineValue = FVector::DotProduct( AITankForwardLoc, AITankMovementLoc);

	// CrossProductResult.Z gives us the sign of sine since other vectors are of length 1.
	FVector CrossProductResult = FVector::CrossProduct( AITankForwardLoc, AITankMovementLoc);

	IntendMoveForward(CosineValue);
	IntendTurnRight(CrossProductResult.Z);
}
