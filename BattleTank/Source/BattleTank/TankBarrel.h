// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * UTankBarrel is responsible for its own elevation. Stores max elevation speeds and degrees.
 */
UCLASS(ClassGroup = (Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankBarrel();

	// -1 for min and +1 for max
	void Elevate( float RelativeSpeed);

private:
	/// Default values are in constructor
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees;
	
};
