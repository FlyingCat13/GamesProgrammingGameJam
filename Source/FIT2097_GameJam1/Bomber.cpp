// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomber.h"

// Sets default values
ABomber::ABomber()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisibleComponent"));
	RootComponent = VisibleComponent;
	ConstructorHelpers::FObjectFinder<UStaticMesh> CapsuleMesh(TEXT("/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"));
	if (CapsuleMesh.Succeeded())
	{
		VisibleComponent->SetStaticMesh(CapsuleMesh.Object);
	}
	VisibleComponent->SetSimulatePhysics(true);
	VisibleComponent->SetMassScale(NAME_None, 10.0f);

	ConstructorHelpers::FObjectFinder<UMaterial> TimedBombMaterialObject(TEXT("/Game/StarterContent/Materials/M_Metal_Chrome.M_Metal_Chrome"));
	if (TimedBombMaterialObject.Succeeded())
	{
		TimedBombMaterial = TimedBombMaterialObject.Object;
	}
	ConstructorHelpers::FObjectFinder<UMaterial> InstantBombMaterialObject(TEXT("/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold"));
	if (InstantBombMaterialObject.Succeeded())
	{
		InstantBombMaterial = InstantBombMaterialObject.Object;
	}

	// Create a camera boom attached to the root (capsule)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Rotation of the character should not affect rotation of boom
	CameraBoom->bDoCollisionTest = false;
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 75.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f, 180.f, 0.f));

	// Create a camera and attach to boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	ShootRotation = GetActorRotation();
}

// Called when the game starts or when spawned
void ABomber::BeginPlay()
{
	Super::BeginPlay();

	VisibleComponent->SetMaterial(0, InstantBombMaterial);
}

// Called every frame
void ABomber::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsAimingHigher)
	{
		ShootRotation.Add(RotateStep, 0.0f, 0.0f);
	}
	else if (IsAimingLower)
	{
		ShootRotation.Add(-RotateStep, 0.0f, 0.0f);
	}
	UE_LOG(LogTemp, Warning, TEXT("%f"), ShootRotation.Pitch);
}

// Called to bind functionality to input
void ABomber::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &ABomber::ChargeBomb);
	PlayerInputComponent->BindAction("Shoot", IE_Released, this, &ABomber::ShootBomb);
	PlayerInputComponent->BindAction("SwitchBombs", IE_Pressed, this, &ABomber::SwitchBomb);

	PlayerInputComponent->BindAction("AimHigher", IE_Pressed, this, &ABomber::AimHigher);
	PlayerInputComponent->BindAction("AimHigher", IE_Released, this, &ABomber::StopAimHigher);
	PlayerInputComponent->BindAction("AimLower", IE_Pressed, this, &ABomber::AimLower);
	PlayerInputComponent->BindAction("AimLower", IE_Released, this, &ABomber::StopAimLower);
}

void ABomber::ChargeBomb()
{
	IsCharging = true;
}

void ABomber::ShootBomb()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{	
			const FRotator SpawnRotation = ShootRotation;
			// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
			const FVector SpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, 50.0f);

			//Set Spawn Collision Handling Override
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

			// spawn the projectile at the muzzle
			World->SpawnActor<ABomb>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}

void ABomber::SwitchBomb()
{
	IsBombTimed = !IsBombTimed;
	if (IsBombTimed)
	{
		VisibleComponent->SetMaterial(0, TimedBombMaterial);
	}
	else
	{
		VisibleComponent->SetMaterial(0, InstantBombMaterial);
	}
}

void ABomber::AimHigher()
{
	IsAimingHigher = true;
	if (IsAimingLower)
	{
		IsAimingLower = false;
	}
}

void ABomber::AimLower()
{
	IsAimingLower = true;
	if (IsAimingHigher)
	{
		IsAimingHigher = false;
	}
}

void ABomber::StopAimHigher()
{
	IsAimingHigher = false;
}

void ABomber::StopAimLower()
{
	IsAimingLower = false;
}