// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Bomb.h"
#include "TimedBomb.generated.h"

/**
 * 
 */
UCLASS()
class FIT2097_GAMEJAM1_API ATimedBomb : public ABomb
{
	GENERATED_BODY()
	
public:
	ATimedBomb();

	virtual void OnExplode() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
