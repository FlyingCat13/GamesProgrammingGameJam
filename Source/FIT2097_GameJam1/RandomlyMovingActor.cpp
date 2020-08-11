// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomlyMovingActor.h"

// Sets default values
ARandomlyMovingActor::ARandomlyMovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")); 

	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component")); 
	VisibleComponent->SetupAttachment(RootComponent); 

	Speed = 100; 
	Tolerance = 10; 
	CurrentTarget = 0; 

}

// Called when the game starts or when spawned
void ARandomlyMovingActor::BeginPlay()
{
	Super::BeginPlay();
	
	CheckPoints.Add(GetActorLocation());
}

// Called every frame
void ARandomlyMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector CurrentPosition = GetActorLocation(); 
	FVector Direction = CheckPoints[CurrentTarget] - CurrentPosition; 
	Direction.Normalize(); 
	CurrentPosition += Direction * Speed * DeltaTime;

	if (FVector::Dist(CurrentPosition, CheckPoints[CurrentTarget]) <= Tolerance) {
		CurrentPosition = CheckPoints[CurrentTarget]; 
		CurrentTarget++; 

		if ((CurrentTarget > CheckPoints.Num() - 1) && CheckPoints.Num() > 0 ){
			CurrentTarget = 0 ;
		}

	}

	SetActorLocation(CurrentPosition);

}

