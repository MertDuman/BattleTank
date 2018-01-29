// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "GameFramework/Controller.h"
#include "TankAIController.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	
}

void UTankTrack::ApplyCounterSlippageForce() {
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	// Apply a counter force. F = m * a, we know m, we need a.
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector SlippageCounterAcceleration = -(SlippageSpeed / DeltaTime) * GetRightVector(); // Change in speed per frame.

	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector SlippageCounterForce = TankRoot->GetMass() * SlippageCounterAcceleration / 2; // Two tracks.

	TankRoot->AddForce(SlippageCounterForce);
}

void UTankTrack::DriveTrack(float Direction) {
	FVector ForceApplied = GetForwardVector() * Direction * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation() + (GetForwardVector() * -300) + (GetUpVector() * 75);
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	
	if (IsOnObjectLineTrace()) {
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
		ApplyCounterSlippageForce();
	}
}

void UTankTrack::Turn(float Direction) {
	FVector ForceApplied = GetRightVector() * Direction * TrackMaxDrivingForce / 2;
	FVector ForceLocation = GetComponentLocation() + (GetForwardVector() * 200) + (GetUpVector() * 75);
	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	if (IsOnObjectLineTrace()) {
		TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	}
}

bool UTankTrack::IsOnObjectLineTrace() {
	FHitResult HitResult;

	return GetWorld()->LineTraceSingleByChannel(
		HitResult,
		GetComponentLocation(),
		GetComponentLocation() + (GetUpVector() * -100),
		ECollisionChannel::ECC_Camera,
		FCollisionQueryParams::DefaultQueryParam
	);
}


