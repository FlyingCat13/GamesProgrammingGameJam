// Fill out your copyright notice in the Description page of Project Settings.


#include "PressurePadActor.h"

// Sets default values
APressurePadActor::APressurePadActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	USceneComponent* Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component"));
	Scene->SetupAttachment(RootComponent);

	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component"));
	VisibleComponent->SetupAttachment(Scene);

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume"));
	TriggerVolume->SetupAttachment(Scene);

}

// Called when the game starts or when spawned
void APressurePadActor::BeginPlay()
{
	Super::BeginPlay();

	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APressurePadActor::OnBoxOverlapBegin);

}

void APressurePadActor::OnBoxOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	UE_LOG(LogTemp, Warning, TEXT("Overlap has begun"));
	OnPressureActivated.Broadcast();
}

// Called every frame
void APressurePadActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

