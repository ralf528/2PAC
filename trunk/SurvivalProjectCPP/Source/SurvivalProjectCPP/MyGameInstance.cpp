// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"
#include "LogManager.h"
#include "GameSaver.h"
#include "Kismet/GameplayStatics.h"

UMyGameInstance::UMyGameInstance()
{
	m_dataTableManager = nullptr;
	m_UIManager = nullptr;
    m_nSelectCharacterType = 0;
}

void UMyGameInstance::Init()
{
	Super::Init();
}

bool UMyGameInstance::LoadGameData()
{
    UGameSaver* pLoaderInst = Cast<UGameSaver>(UGameplayStatics::CreateSaveGameObject(UGameSaver::StaticClass()));
    if (!pLoaderInst) {
        return false;
    }

    pLoaderInst = Cast<UGameSaver>(UGameplayStatics::LoadGameFromSlot(TEXT("Save01"), 1));
    if (!pLoaderInst) {
        return false;
    }

    /*for (auto item : pLoaderInst->Inventory) {
        ALogManager::Log(FString::Printf(TEXT("[Log]Item : %d, %d"), item.Value, item.Value));
        m_pCharacter->AddItemToInventory(item.Key, item.Value);
    }*/

    ALogManager::Log(FString::Printf(TEXT("[Log]LoadFromSlot : %d, %s"), pLoaderInst->UserIndex, *pLoaderInst->SaveSlotName));

    return true;
}

bool UMyGameInstance::SaveGameData()
{
    UGameSaver* pSaverInst = Cast<UGameSaver>(UGameplayStatics::CreateSaveGameObject(UGameSaver::StaticClass()));
    if (!pSaverInst) {
        return false;
    }

    pSaverInst->SaveSlotName = TEXT("Save01");
    pSaverInst->UserIndex = 1;

    //ASurvivalProjectCPPCharacter* character = Cast<ASurvivalProjectCPPCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    /*if (character) {
        ALogManager::Log(FString::Printf(TEXT("[Log]save character exist")));
        for (auto item : character->m_inventory) {
            ALogManager::Log(FString::Printf(TEXT("[Log]Item : %d, %d"), item.Value.itemType, item.Value.amount));
            pSaverInst->Inventory.Add(item.Key, item.Value.amount);
        }
    }
    else {
        ALogManager::Log(FString::Printf(TEXT("[Log]save character is nullptr")));
    }*/

    ALogManager::Log(FString::Printf(TEXT("[Log]SaveFromSlot : %d, %s"), pSaverInst->UserIndex, *pSaverInst->SaveSlotName));

    return UGameplayStatics::SaveGameToSlot(pSaverInst, pSaverInst->SaveSlotName, pSaverInst->UserIndex);
}

void UMyGameInstance::SetDataTableManager(ADataTableManager* dataTable)
{
	if (!m_dataTableManager)
	{
		m_dataTableManager = dataTable;
	}
}

void UMyGameInstance::SetUIManager(AUIManager* uiManager)
{
	if (!m_UIManager)
	{
		m_UIManager = uiManager;
	}
}