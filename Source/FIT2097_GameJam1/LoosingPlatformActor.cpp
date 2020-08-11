// Fill out your copyright notice in the Description page of Project Settings.


#include "LoosingPlatformActor.h"

// Sets default values
ALoosingPlatformActor::ALoosingPlatformActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component")); 

	USceneComponent* Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene Component")); 
	Scene->SetupAttachment(RootComponent); 

	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visible Component")); 
	VisibleComponent->SetupAttachment(Scene); 

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Volume")); 
	TriggerVolume->SetupAttachment(Scene);

	Message = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Loosing Message")); 
	Message->SetupAttachment(Scene); 
	Message->SetHorizontalAlignment(EHTA_Center);
	Message->SetWorldSize(150.0f); 
	Message->SetText("");

}

// Called when the game starts or when spawned
void ALoosingPlatformActor::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &ALoosingPlatformActor::OnBoxOverlapBegin);
	
}

void ALoosingPlatformActor::OnBoxOverlapBegin(UPrimitiveComponent* OverlapComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult) {

	UE_LOG(LogTemp, Warning, TEXT("Overlap has begun"));
	Message->SetText("Game Over"); 
	OnTouched.Broadcast();
}



// Called every frame
void ALoosingPlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

