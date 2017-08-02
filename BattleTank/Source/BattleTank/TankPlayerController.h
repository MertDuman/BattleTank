// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATankPlayerController();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	ATank* GetControlledTank() const;

	// Can't use MULTICAST_DELEGATE becauuse that only works for Actors. Also no need for implementation because of the macro.
	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* AimingComponent);

private:
	virtual void Tick( float DeltaTime) override;

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
