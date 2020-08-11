// Fill out your copyright notice in the Description page of Project Settings.


#include "InstantBomb.h"
#include "Bomber.h"

AInstantBomb::AInstantBomb() : ABomb()
{
	this->OnActorHit.AddDynamic(this, &AInstantBomb::OnHit);		// set up a notification for when this component hits something blocking
}

void AInstantBomb::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("High"));
	// Only add impulse and destroy projectile if we hit a physics that is not the bomber
	if ((OtherActor != NULL) && (OtherActor != this) && (!Cast<ABomber>(OtherActor)))
	{
		OnExplode();
	}
}

void AInstantBomb::OnExplode()
{
	Super::OnExplode();
	Destroy();
}