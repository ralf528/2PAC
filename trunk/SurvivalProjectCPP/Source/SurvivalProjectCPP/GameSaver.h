// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SurvivalProjectCPPCharacter.h"
#include "GameSaver.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALPROJECTCPP_API UGameSaver : public USaveGame
{
	GENERATED_BODY()
	
public:
    UGameSaver();

    UPROPERTY(VisibleAnywhere, Category = Basic)
    TMap<int, int> Inventory;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    FString SaveSlotName;

    UPROPERTY(VisibleAnywhere, Category = Basic)
    uint32 UserIndex;
	
};
