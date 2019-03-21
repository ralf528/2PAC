// Fill out your copyright notice in the Description page of Project Settings.
#include "DataTableManager.h"
#include "LogManager.h"
#include "MyGameInstance.h"

// Sets default values
ADataTableManager::ADataTableManager()
{
    ALogManager::Log(FString::Printf(TEXT("[ADataTableManager]Constructor()")));

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
    LoadCharacterTable();
    LoadItemDropTable();

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

bool ADataTableManager::LoadCharacterTable()
{
    if (!m_CharacterTable) {
        UE_LOG(LogClass, Log, TEXT("[Log]Failed to load table : ItemTable"));
        return false;
    }

    FString ContextString;
    TArray<FName> RowNames = m_CharacterTable->GetRowNames();

    int i = 0;
    for (auto &name : RowNames) {
        FTD_Character* item = m_CharacterTable->FindRow<FTD_Character>(name, ContextString);
        if (item) {
            m_mapCharacters.Add(i, *item);
            //UE_LOG(LogClass, Log, TEXT("[Log]Item : %d, %s"), item->, *item->Name.ToString());
        }
    }

    return true;
}

bool ADataTableManager::LoadItemDropTable()
{
    if (!m_ItemDropTable) {
        UE_LOG(LogClass, Log, TEXT("[Log]Failed to load table : ItemDrop"));
        return false;
    }

    FString ContextString;
    TArray<FName> RowNames = m_ItemDropTable->GetRowNames();

    int i = 0;
    for (auto &name : RowNames) {
        FTD_ItemDrop* item = m_ItemDropTable->FindRow<FTD_ItemDrop>(name, ContextString);
        if (item) {
            m_mapItemDrops.Add(i++, *item);
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
    UE_LOG(LogClass, Log, TEXT("[Log]failed to return ItemData[%d]"), index);
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
        UE_LOG(LogClass, Log, TEXT("[TableManager]Invalid InteractionTable"));
        return tmp;
    }

    FString strIndex = FString::FromInt(index);
    FTD_Interact* row = m_InteractionTable->FindRow<FTD_Interact>(*strIndex, strIndex);
    if (row != nullptr) {
        //UE_LOG(LogClass, Log, TEXT("[Log]Interaction Row [%d]"), row->ItemType);
        return *row;
    }

    UE_LOG(LogClass, Log, TEXT("[Log]Failed to Interaction Row[%d]"), index);

    //return nullptr;
    return tmp;
}

// 캐릭터 테이블 데이터 반환
FTD_Character& ADataTableManager::GetCharacterData(int index)
{
    FTD_Character tmp;

    if (!m_CharacterTable) {
        UE_LOG(LogClass, Log, TEXT("[TableManager]Invalid CharacterTable"));
        return tmp;
    }

    FString strIndex = FString::FromInt(index);
    FTD_Character* row = m_CharacterTable->FindRow<FTD_Character>(*strIndex, strIndex);
    if (row) {
        ALogManager::Log(FString::Printf(TEXT("[Log]Find Character")));
        return *row;
    }

    //return nullptr;
    return tmp;
}

// 아이템 드랍 데이터 반환
FTD_ItemDrop& ADataTableManager::GetItemDropData(int index)
{
    FTD_ItemDrop tmp;

    if (!m_ItemDropTable) {
        UE_LOG(LogClass, Log, TEXT("[TableManager]Invalid ItemDropTable"));
        return tmp;
    }

    FString strIndex = FString::FromInt(index);
    FTD_ItemDrop* row = m_ItemDropTable->FindRow<FTD_ItemDrop>(*strIndex, strIndex);
    if (row) {
        return *row;
    }

    return tmp;
}

// 드랍 아이템 정보
int ADataTableManager::FindDropItem(int sourceItem)
{
    for (auto &info : m_mapItemDrops) {
        UE_LOG(LogClass, Log, TEXT("[TableManager]Find Drop Item [%d]"), info.Value.ItemType);
        if (info.Value.ItemType == sourceItem)
        {
            return info.Value.DropItemType;
        }
    }

    UE_LOG(LogClass, Log, TEXT("[TableManager]NotFound Drop Item [sourceItem : %d]"), sourceItem);
    return 0;
}