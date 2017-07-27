// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATankAIController();

protected:
	virtual void BeginPlay() override;


private:
	virtual void Tick( float DeltaTime) override;

	ATank* AITank;

	ATank* PlayerTank;

	// How close the AI tank can get.
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius;

};
