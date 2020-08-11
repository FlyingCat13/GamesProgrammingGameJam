// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Bomb.h"
#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "InstantBomb.h"
#include "Materials/Material.h"
#include "TimedBomb.h"
#include "Bomber.generated.h"

UCLASS()
class FIT2097_GAMEJAM1_API ABomber : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* VisibleComponent;

	UPROPERTY(EditAnywhere)
		UMaterial* TimedBombMaterial;

	UPROPERTY(EditAnywhere)
		UMaterial* InstantBombMaterial;

	UPROPERTY(EditAnywhere)
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
		USpringArmComponent* CameraBoom;

	/** Projectile class to spawn */
	UPROPERTY(EditAnywhere)
		TSubclassOf<class ABomb> ProjectileClass = AInstantBomb::StaticClass();

	UPROPERTY(EditAnywhere)
		class UArrowComponent* ShootDirectionIndicator;


public:
	// Sets default values for this pawn's properties
	ABomber();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ChargeBomb();
	void ShootBomb();
	void SwitchBomb();

	void AimHigher();
	void StopAimHigher();
	void AimLower();
	void StopAimLower();

	FRotator ShootRotation;
	bool IsAimingHigher = false;
	bool IsAimingLower = false;

	float RotateStep = 1.f;
	bool IsCharging = false;
	bool IsBombTimed = false;

	float BombSpeedStep = 720.f;
	const float BOMB_SPEED_MIN = 200.f;
	const float BOMB_SPEED_MAX = 2000.f;
	float BombSpeed = BOMB_SPEED_MIN;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
