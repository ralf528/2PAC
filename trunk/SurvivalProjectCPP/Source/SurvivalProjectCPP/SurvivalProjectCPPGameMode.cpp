// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SurvivalProjectCPPGameMode.h"
#include "SurvivalProjectCPPPlayerController.h"
#include "SurvivalProjectCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASurvivalProjectCPPGameMode::ASurvivalProjectCPPGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ASurvivalProjectCPPPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

    m_dataTableManager = nullptr;
}