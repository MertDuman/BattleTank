// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * UTankTurret is responsible for its own rotation. Stores a max turn speed.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTurret();

	// -1 for min +1 for max
	void Move( float RelativeSpeed);

private:
	UPROPERTY(EditAnywhere)
	float MaxTurnSpeedDegrees;
	
};
