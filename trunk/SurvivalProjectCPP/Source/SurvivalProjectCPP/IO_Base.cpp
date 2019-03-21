// Fill out your copyright notice in the Description page of Project Settings.

#include "IO_Base.h"
#include "MyGameInstance.h"
#include "LogManager.h"

// Sets default values
AIO_Base::AIO_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AIO_Base::BeginPlay()
{
    ALogManager::Log(FString::Printf(TEXT("[AIO_Base]BeginPlay()")));

	Super::BeginPlay();

    info.ItemType = FMath::RandRange(1, 4);
    info.Amount = 1;
    info.Animation = 4;
    info.castingTime = 1.f;
}

// Called every frame
void AIO_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIO_Base::Execute()
{
    /*switch (info.ItemType) {
    case 1:
    {*/
        if (character) {
            character->AddItemToInventory(info.ItemType, info.Amount);
            FVector Location = GetActorLocation();
            FRotator Rotation(0.f, 0.f, 0.f);

            // 제자리에 아이템 드랍
            UMyGameInstance* game = dynamic_cast<UMyGameInstance*>(GetGameInstance());
            if (game) {
                if (game->GetDataTableManager()) {
                    FTD_Interact& interaction = game->GetDataTableManager()->GetInteractionData(InteractionType);
                    ALogManager::Log(FString::Printf(TEXT("[IO_BASE]Interaction item type[%d]"), interaction.ItemType));
                    if (interaction.ItemType != 0) {
                        int drop = game->GetDataTableManager()->FindDropItem(interaction.ItemType);
                        ALogManager::Log(FString::Printf(TEXT("[IO_BASE]Drop item type[%d]"), drop));

                        if (drop != 0) {
                            AIO_Base* obj = GetWorld()->SpawnActor<AIO_Base>(IO_Blueprint, Location, Rotation);
                            if (obj) {
                                obj->SetInteractionType(drop);
                                obj->SetItemStaticMesh();
                            }
                        }
                    }
                }
            }
            this->Destroy();
        }
    /*}
    break;

    default:
    {
        this->Destroy();
    }
    break;

    }*/
}

void AIO_Base::SetInteractionInfo()
{
    // type != 0 이면 interaction table 의 값으로 설정
    // 우선은 아이템 타입을 랜덤으로
    if (InteractionType == 0) {
        info.ItemType = FMath::RandRange(1, 4);
        info.Amount = 1;
        info.Animation = 1;
        info.castingTime = 1.f;
    }
    else {
        UMyGameInstance* game = dynamic_cast<UMyGameInstance*>(GetGameInstance());
        if (game) {
            if (game->GetDataTableManager()) {
                FTD_Interact& info = game->GetDataTableManager()->GetInteractionData(InteractionType);
                this->info.ItemType = info.ItemType;
                this->info.Amount = info.ItemCount;
                this->info.Animation = info.Animation;
                this->info.castingTime = info.CastingTime;
                ALogManager::Log(FString::Printf(TEXT("[IO_BASE]item %d, amount %d, animation %d, time %f"), this->info.ItemType, this->info.Amount, this->info.Animation, this->info.castingTime));
            }
            else {
                ALogManager::Log(FString::Printf(TEXT("[IO_BASE]Invalid TableManager")));
            }
        }
        else {
            ALogManager::Log(FString::Printf(TEXT("[IO_BASE]Invalid GameInstance")));
        }
    }
}

void AIO_Base::SetItemStaticMesh()
{
    if (!m_meshComponent) {
        if (GetRootComponent()) {
            TArray<USceneComponent*> components;
            GetRootComponent()->GetChildrenComponents(false, components);
            for (auto &info : components) {
                if (info->GetName().Compare("StaticMesh") == 0) {
                    m_meshComponent = dynamic_cast<UStaticMeshComponent*>(info);

                    if (!m_meshComponent) {
                        ALogManager::Log(FString::Printf(TEXT("[AIO_Base]NotFound Static Mesh Component")));
                    }
                }
            }
        }
    }

    if (m_meshComponent) {
        UMyGameInstance* game = dynamic_cast<UMyGameInstance*>(GetGameInstance());
        if (game) {
            if (game->GetDataTableManager()) {

                FTD_Interact& interaction = game->GetDataTableManager()->GetInteractionData(InteractionType);

                FTD_Item& item = game->GetDataTableManager()->GetItemData(interaction.ItemType);

                m_meshComponent->SetStaticMesh(item.Mesh);
            }
        }
    }
}