// Fill out your copyright notice in the Description page of Project Settings.
#include "DataTableManager.h"
#include "LogManager.h"
#include "MyGameInstance.h"

// Sets default values
ADataTableManager::ADataTableManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADataTableManager::BeginPlay()
{
    ALogManager::Log(FString::Printf(TEXT("[ADataTableManager]BeginPlay()")));

	Super::BeginPlay();

	auto game = dynamic_cast<UMyGameInstance*>(GetGameInstance());
	if (!game) {
		return;
	}

	game->SetDataTableManager(this);
	LoadDataTable();
}

// Called every frame
void ADataTableManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool ADataTableManager::LoadDataTable()
{
	LoadItemTable();
    LoadInteractionTable();

	return true;
}

bool ADataTableManager::LoadItemTable()
{
	if (!m_ItemTable) {
		UE_LOG(LogClass, Log, TEXT("[Log]Failed to load table : ItemTable"));
		return false;
	}

	FString ContextString;
	TArray<FName> RowNames = m_ItemTable->GetRowNames();

	int i = 0;
	for (auto &name : RowNames) {
		FTD_Item* item = m_ItemTable->FindRow<FTD_Item>(name, ContextString);
		if (item) {
			m_mapItems.Add(i, *item);
			UE_LOG(LogClass, Log, TEXT("[Log]Item : %d, %s"), item->ItemType, *item->Name.ToString());
		}
	}

	return true;
}

bool ADataTableManager::LoadInteractionTable()
{
    if (!m_InteractionTable) {
        UE_LOG(LogClass, Log, TEXT("[Log]Failed to load table : ItemTable"));
        return false;
    }

    FString ContextString;
    TArray<FName> RowNames = m_InteractionTable->GetRowNames();

    int i = 0;
    for (auto &name : RowNames) {
        FTD_Interact* item = m_InteractionTable->FindRow<FTD_Interact>(name, ContextString);
        if (item) {
            m_mapInteractions.Add(i, *item);
            //UE_LOG(LogClass, Log, TEXT("[Log]Item : %d, %s"), item->, *item->Name.ToString());
        }
    }

    return true;
}

// 아이템 테이블의 데이터를 반환
FTD_Item& ADataTableManager::GetItemData(int index)
{
    FTD_Item tmp;
    tmp.ItemType = 0;
    if (!m_ItemTable) {
        //return nullptr;
        UE_LOG(LogClass, Log, TEXT("[Log]ItemTable is nullptr"));
        return tmp;
    }

    FString ContextString;
    FString strIndex = FString::FromInt(index);
    FName name = *strIndex;
    FTD_Item* row = m_ItemTable->FindRow<FTD_Item>(name, ContextString);
    if (row) {
        //UE_LOG(LogClass, Log, TEXT("[Log]Item Row %d, %s"), row->ItemType, *row->Name.ToString());
        return *row;
    }

    //return nullptr;
    UE_LOG(LogClass, Log, TEXT("[Log]failed to return ItemData"));
    return tmp;
}

// 아이템 조합 테이블 데이터 반환
FTD_CombineItem& ADataTableManager::GetCombineItemData(int index)
{
    FTD_CombineItem tmp;

    if (!m_CombineItemTable) {
        //return nullptr;
        return tmp;
    }

    FString strIndex = FString::FromInt(index);
    FTD_CombineItem* row = m_CombineItemTable->FindRow<FTD_CombineItem>(*strIndex, strIndex);
    if (row) {
        //UE_LOG(LogClass, Log, TEXT("[Log]CombineItem Row %d = %d + %d"), row->ResultItemType, row->MaterialItemType1, row->MaterialItemType2);
        return *row;
    }

    //return nullptr;
    return tmp;
}

// 인터렉션 테이블 데이터 반환
FTD_Interact& ADataTableManager::GetInteractionData(int index)
{
    FTD_Interact tmp;

    if (!m_InteractionTable) {
        UE_LOG(LogClass, Log, TEXT("[TableManager]Invalid InteractionTable"),);
        return tmp;
    }

    FString strIndex = FString::FromInt(index);
    FTD_Interact* row = m_InteractionTable->FindRow<FTD_Interact>(*strIndex, strIndex);
    if (row) {
        //UE_LOG(LogClass, Log, TEXT("[Log]CombineItem Row %d = %d + %d"), row->ResultItemType, row->MaterialItemType1, row->MaterialItemType2);
        return *row;
    }

    //return nullptr;
    return tmp;
}