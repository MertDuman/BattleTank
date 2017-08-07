// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision Mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true); // Sets generate hit events' default value to true.

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	ExplosionForce = CreateDefaultSubobject<URadialForceComponent>(FName("Explosion Force"));
	ExplosionForce->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//ExplosionForce->bAutoActivate = false;
	
	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	MovementComponent->bAutoActivate = false;
	MovementComponent->bRotationFollowsVelocity = true;

	bAutoDestroyWhenFinished = true;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	CollisionMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit) {
	ImpactBlast->Activate();
	LaunchBlast->Deactivate();
	ExplosionForce->FireImpulse();

	// So the collision doesn't block actors.
	SetRootComponent(LaunchBlast);
	CollisionMesh->DestroyComponent();

	// Destroy the projectile after 2.5f seconds to improve performance.
	SetLifeSpan( 2.5f);

	//GetWorld()->GetTimerManager().SetTimer() would be used to call a method every X seconds.
}

void AProjectile::Launch(float Speed) {
	MovementComponent->SetVelocityInLocalSpace( FVector::ForwardVector * Speed);
	MovementComponent->Activate();
}

