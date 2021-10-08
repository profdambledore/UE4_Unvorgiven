// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE4_UnforgivenGameModeBase.h"

#include "PlayerHUD.h"
#include "UObject/ConstructorHelpers.h"

// Constructor Function
AUE4_UnforgivenGameModeBase::AUE4_UnforgivenGameModeBase() : Super()
{
	// Set Base Classes for Gamemode
	// Default Pawn
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnObject(TEXT("/Game/Player/BP/BP_PlayerCharacter"));
	if (DefaultPawnObject.Succeeded())
	{
		DefaultPawnClass = DefaultPawnObject.Class;
	}

	// Default HUD
	HUDClass = APlayerHUD::StaticClass();
}