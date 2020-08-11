// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "LoosingPlatformActor.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTouched);
UCLASS()
class FIT2097_GAMEJAM1_API ALoosingPlatformActor : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	ALoosingPlatformActor();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent; 

	UPROPERTY(EditAnywhere)
		UBoxComponent* TriggerVolume; 	

	UPROPERTY(EditAnywhere)
		UTextRenderComponent* Message; 

	UPROPERTY(BlueprintAssignable)
		FOnTouched OnTouched;

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
