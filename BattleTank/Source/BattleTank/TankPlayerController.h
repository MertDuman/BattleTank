// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	

protected:
	virtual void BeginPlay() override;

private:
	virtual void Tick( float DeltaTime) override;

	ATank* GetControlledTank() const;

	// Start the tank moving the barrel towards crosshair
	void AimTowardsCrosshair();
};
