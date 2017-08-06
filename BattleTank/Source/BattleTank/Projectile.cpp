// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	MovementComponent->bAutoActivate = false;
	MovementComponent->bRotationFollowsVelocity = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	// Sets generate hit events' default value to true.
	CollisionMesh->SetNotifyRigidBodyCollision(true);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle System"));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::Launch(float Speed) {
	MovementComponent->SetVelocityInLocalSpace( FVector::ForwardVector * Speed);
	MovementComponent->Activate();
}

