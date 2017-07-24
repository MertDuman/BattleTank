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
	ATankPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	virtual void Tick( float DeltaTime) override;

	ATank* GetControlledTank() const;

	UPROPERTY(EditAnywhere)
	float CrosshairXLocation;

	UPROPERTY(EditAnywhere)
	float CrosshairYLocation; 

	UPROPERTY(EditAnywhere)
	float LineTraceRange;

	// Start the tank moving the barrel towards crosshair
	void AimTowardsCrosshair();

	// Changes the HitLocation to match where the crosshair points at.
	bool GetLineTraceHitLocation( FVector& out_HitLocation);

	// Hits the current object at SceneLocation based on the CollisionChannel
	bool HitScanAtScreenPosition( FVector2D ScreenLocation, ECollisionChannel CollisionChannel, FHitResult& out_HitResult);
};
