// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "DataTableManager.generated.h"

USTRUCT()
struct FTD_Item : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:

    UPROPERTY(EditAnywhere)
    int ItemType;

    UPROPERTY(EditAnywhere)
    FName Name;

    UPROPERTY(EditAnywhere)
    UTexture2D* Image;
};

UCLASS(Blueprintable)
class SURVIVALPROJECTCPP_API ADataTableManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADataTableManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    FTD_Item* GetItemData(int index);

private:
    UPROPERTY(EditAnywhere)
    UDataTable* m_ItemTable;	
};
