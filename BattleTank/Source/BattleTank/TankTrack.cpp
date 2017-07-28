// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack() {
	TrackMaxDrivingForce = 40000000; // 40.000kg, 500cm/s^2
}

void UTankTrack::SetThrottle(float Throttle) {
	Throttle = FMath::Clamp( Throttle, -1.f, 1.f);
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	//FVector FinalForceApplied = FVector(ForceApplied.X, ForceApplied.Y, 0.f);

	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>( GetOwner()->GetRootComponent());
	
	TankRoot->AddForceAtLocation( ForceApplied, ForceLocation);
	float TankSpeed = TankRoot->GetComponentVelocity().Size();
	float Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Speed: %f"), Time, TankSpeed)
}
