// Fill out your copyright notice in the Description page of Project Settings.
#include "DataTableManager.h"

// Sets default values
ADataTableManager::ADataTableManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADataTableManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ADataTableManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// 아이템 테이블의 데이터를 반환
FTD_Item* ADataTableManager::GetItemData(int index)
{
    FString strIndex = FString::FromInt(index);
    FTD_Item* row = m_ItemTable->FindRow<FTD_Item>(*strIndex, strIndex);
    if (row) {
        UE_LOG(LogClass, Log, TEXT("[Log]Item Row %d, %s"), row->ItemType, *row->Name.ToString());
        return row;
    }

    return nullptr;
}