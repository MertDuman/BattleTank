// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"
#include "Engine/World.h"

UTankTurret::UTankTurret() {
	MaxTurnSpeedDegrees = 5.f;
}

void UTankTurret::Move(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp( RelativeSpeed, -1.f, 1.f);

	float AzimuthChange = RelativeSpeed * MaxTurnSpeedDegrees * GetWorld()->GetDeltaSeconds();
	float FinalAzimuth = RelativeRotation.Yaw + AzimuthChange;

	SetRelativeRotation( FRotator( 0.f, FinalAzimuth, 0.f));
}


