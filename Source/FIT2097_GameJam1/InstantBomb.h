// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bomb.h"
#include "TimerManager.h"
#include "InstantBomb.generated.h"

/**
 * 
 */
UCLASS()
class FIT2097_GAMEJAM1_API AInstantBomb : public ABomb
{
	GENERATED_BODY()

public:
	AInstantBomb();

	virtual void OnExplode() override;

	/** called when projectile hits something */
	UFUNCTION()
		void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
