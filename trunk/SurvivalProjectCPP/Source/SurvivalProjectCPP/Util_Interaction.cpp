// Fill out your copyright notice in the Description page of Project Settings.

#include "Util_Interaction.h"
#include "IO_Base.h"
#include "LogManager.h"
#include "Item_Base.h"

Util_Interaction::Util_Interaction()
{
}

Util_Interaction::~Util_Interaction()
{
}


////////////////////////////////////
// FInteractor

void FInteractor::Complete()
{
    ALogManager::Log(TEXT("[FInteractor]Complate"));

    if (_object) {
        ALogManager::Log(TEXT("[FInteractor]Complate object"));
        _object->Execute();
    }
    else if (_item) {
        ALogManager::Log(TEXT("[FInteractor]Complate item"));
        if (m_character) {
            ALogManager::Log(FString::Printf(TEXT("[FInteractor]Complate : AddItem[%d]"), _item->GetItemType()));
            m_character->AddItemToInventory(_item->GetItemType(), 1);
            _item->Destroy();
        }
    }
    Reset();
}
