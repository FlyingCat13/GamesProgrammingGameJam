// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Bomb.generated.h"

UCLASS()
class FIT2097_GAMEJAM1_API ABomb : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		class UParticleSystem* ExplosionParticles;

	UPROPERTY(EditAnywhere)
		float ExplosionRadius = 300.0f;

	/** Sphere collision component */
	UPROPERTY(EditAnywhere)
		class USphereComponent* CollisionComp;
	
public:	
	// Sets default values for this actor's properties
	ABomb();

	/** Projectile movement component */
	UPROPERTY(EditAnywhere)
		class UProjectileMovementComponent* ProjectileMovement;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		virtual void OnExplode();

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};
