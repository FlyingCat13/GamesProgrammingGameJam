// Fill out your copyright notice in the Description page of Project Settings.


#include "SpinningActor.h"

// Sets default values
ASpinningActor::ASpinningActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")); 
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component")); 
	VisibleComponent->SetupAttachment(RootComponent); 

	RotationSpeed = 250;

}

// Called when the game starts or when spawned
void ASpinningActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpinningActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rotator(0, RotationSpeed * DeltaTime, 0);
	FQuat Quaternion(Rotator); 

	AddActorLocalRotation(Quaternion, false, nullptr, ETeleportType::None);
}

