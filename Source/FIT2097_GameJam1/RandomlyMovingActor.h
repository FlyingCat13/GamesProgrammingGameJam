// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "RandomlyMovingActor.generated.h"

UCLASS()
class FIT2097_GAMEJAM1_API ARandomlyMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARandomlyMovingActor();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent; 

	UPROPERTY(EditAnywhere)
		float Speed; 

	UPROPERTY(EditAnywhere)
		float Tolerance; 

	UPROPERTY(EditAnywhere)
		TArray<FVector> CheckPoints;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int32 CurrentTarget; 
	 

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
