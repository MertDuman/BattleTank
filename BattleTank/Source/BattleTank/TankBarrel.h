// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta=(BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankBarrel();

	void Elevate( float DegreesPerSecond);

private:
	/// Default values are in constructor
	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxDegreesPerSecond;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MaxElevationDegrees;

	UPROPERTY(EditAnywhere, Category = Setup)
	float MinElevationDegrees;
	
};
