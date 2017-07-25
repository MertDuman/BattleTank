// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


UTankBarrel::UTankBarrel() {
	MaxDegreesPerSecond = 20.f;
	MaxElevationDegrees = 40.f;
	MinElevationDegrees = 0.f;
}

void UTankBarrel::Elevate(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp( RelativeSpeed, -1.f, 1.f);

	float ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->GetDeltaSeconds();
	float FinalElevation = RelativeRotation.Pitch + ElevationChange;

	FinalElevation = FMath::Clamp( FinalElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation( FRotator( FinalElevation, 0.f, 0.f));
}


