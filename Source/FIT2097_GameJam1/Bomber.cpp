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
	VisibleComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);

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
	CameraBoom->TargetArmLength = 666.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 110.f);
	CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	// Create a camera and attach to boom
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false; // We don't want the controller rotating the camera

	ShootRotation = GetActorRotation();

	ShootDirectionIndicator = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootDirection"));
	ShootDirectionIndicator->SetupAttachment(RootComponent);
	ShootDirectionIndicator->SetHiddenInGame(false);
	ShootDirectionIndicator->SetRelativeLocation(FVector(0.0f, 0.0f, 50.f));
	ShootDirectionIndicator->SetRelativeRotation(ShootRotation);
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
	if (IsCharging)
	{
		BombSpeed += FMath::Min(BombSpeedStep * DeltaTime, BOMB_SPEED_MAX);
	}
	ShootDirectionIndicator->SetRelativeRotation(ShootRotation);
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
			const FRotator SpawnRotation = ShootDirectionIndicator->GetComponentRotation();
			FVector Offset = SpawnRotation.RotateVector(FVector::ForwardVector);
			Offset.Normalize();
			const FVector SpawnLocation = ShootDirectionIndicator->GetComponentLocation() + Offset * 5;
			FTransform SpawnTransform(SpawnRotation, SpawnLocation);
			ABomb* TheBomb = Cast<ABomb>(UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ProjectileClass, SpawnTransform, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding));
			if (TheBomb != nullptr)
			{
				TheBomb->ProjectileMovement->InitialSpeed = BombSpeed;
				UGameplayStatics::FinishSpawningActor(TheBomb, SpawnTransform);
			}
		}
	}
	IsCharging = false;
	BombSpeed = BOMB_SPEED_MIN;
}

void ABomber::SwitchBomb()
{
	IsBombTimed = !IsBombTimed;
	if (IsBombTimed)
	{
		VisibleComponent->SetMaterial(0, TimedBombMaterial);
		ProjectileClass = ATimedBomb::StaticClass();
	}
	else
	{
		VisibleComponent->SetMaterial(0, InstantBombMaterial);
		ProjectileClass = AInstantBomb::StaticClass();
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