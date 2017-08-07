// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ATank::GetHealthPercent() const {
	return (float)CurrentHealth / (float)MaxHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser) {
	int32 DamageToApply = FMath::Clamp(FMath::RoundToInt( DamageAmount), 0, CurrentHealth);
	CurrentHealth -= DamageToApply;
	UE_LOG(LogTemp, Warning, TEXT("DamageAmount:%f, DamageToApply:%i"), DamageAmount, DamageToApply)
	return DamageToApply;
}



