// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "FIT2097_GameJam1GameMode.h"
#include "FIT2097_GameJam1Character.h"
#include "UObject/ConstructorHelpers.h"

AFIT2097_GameJam1GameMode::AFIT2097_GameJam1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
