// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Sets the throttles on themselves and stores a max driving force.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();

	// Applies force to the back of the tank to simulate back tire driving. Positive for forward and negative for backwards.
	void DriveTrack(float Direction);

	// Applies force to the front of the tank to simulate front tire turning. Positive for right and negative for left.
	void Turn(float Direction);

private:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 30000000;

	// Makes the tank movement more natural. Tanks don't strafe.
	void ApplyCounterSlippageForce();

	// Line trace to the bottom of the tank to see if it is on an object.
	bool IsOnObjectLineTrace();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};
