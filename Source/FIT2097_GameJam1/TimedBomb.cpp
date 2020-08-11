// Fill out your copyright notice in the Description page of Project Settings.


#include "TimedBomb.h"

ATimedBomb::ATimedBomb() : ABomb()
{

}

// Called when the game starts or when spawned
void ATimedBomb::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle handle;
	GetWorld()->GetTimerManager().SetTimer(handle, this, &ATimedBomb::OnExplode, 3.f, false);

}

void ATimedBomb::OnExplode()
{
	Super::OnExplode();
	Destroy();
}