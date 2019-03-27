// Fill out your copyright notice in the Description page of Project Settings.

#include "Item_Base.h"
#include "LogManager.h"
#include "MyGameInstance.h"

// Sets default values
AItem_Base::AItem_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    m_itemType = 1;
}

// Called when the game starts or when spawned
void AItem_Base::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItem_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem_Base::SetItemStaticMesh()
{
    if (!m_meshComponent) {
        if (GetRootComponent()) {
            TArray<USceneComponent*> components;
            GetRootComponent()->GetChildrenComponents(false, components);
            for (auto &info : components) {
                if (info->GetName().Compare("StaticMesh") == 0) {
                    m_meshComponent = dynamic_cast<UStaticMeshComponent*>(info);

                    if (!m_meshComponent) {
                        ALogManager::Log(FString::Printf(TEXT("[AItem_Base]NotFound Static Mesh Component")));
                    }
                }
            }
        }
    }

    if (m_meshComponent) {
        UMyGameInstance* game = dynamic_cast<UMyGameInstance*>(GetGameInstance());
        if (game) {
            if (game->GetDataTableManager()) {
                FTD_Item& item = game->GetDataTableManager()->GetItemData(m_itemType);

                m_meshComponent->SetStaticMesh(item.Mesh);
            }
        }
    }
}

