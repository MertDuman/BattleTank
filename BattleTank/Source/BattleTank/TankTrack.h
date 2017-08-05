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

	UFUNCTION(BlueprintCallable, Category = Input)
	void SetThrottle( float Throttle);

private:
	virtual void BeginPlay() override;

	float CurrentThrottle = 0;

	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 40000000;

	// Makes the tank movement more natural. Tanks don't strafe.
	void ApplyCounterSlippageForce();

	// Applies force to tracks depending on the current throttle and then resets it.
	void DriveTrack();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
};
