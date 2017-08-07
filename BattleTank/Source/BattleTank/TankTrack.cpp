// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::BeginPlay() {
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit) {
	ApplyCounterSlippageForce();
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

void UTankTrack::SetThrottle(float Throttle) {
	CurrentThrottle = FMath::Clamp(CurrentThrottle + Throttle, -1.f, 1.f);
	DriveTrack();
}

void UTankTrack::DriveTrack() {
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();

	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
	CurrentThrottle = 0;
}


