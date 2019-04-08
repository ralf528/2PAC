// Fill out your copyright notice in the Description page of Project Settings.

#include "GameSaver.h"



UGameSaver::UGameSaver()
{
    SaveSlotName = TEXT("None");
    UserIndex = 0;
    Inventory.Reset();
}
