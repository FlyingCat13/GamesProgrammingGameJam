// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "PressurePadActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPressureActivated);

UCLASS()
class FIT2097_GAMEJAM1_API APressurePadActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APressurePadActor();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;

	UPROPERTY(EditAnywhere)
		UBoxComponent* TriggerVolume;

	UPROPERTY(BlueprintAssignable)
		FOnPressureActivated OnPressureActivated;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnBoxOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
			bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
