// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "DataTableManager.generated.h"

USTRUCT(BlueprintType)
struct FTD_Item : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Image;
};

USTRUCT(BlueprintType)
struct FTD_CombineItem : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int ResultItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int MaterialItemType1;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int MaterialItemType2;
};


UCLASS(Blueprintable)
class SURVIVALPROJECTCPP_API ADataTableManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADataTableManager();

    // Load Table data
    UFUNCTION(BlueprintCallable)
    bool LoadDataTable();

    UFUNCTION(BlueprintCallable)
    bool LoadItemTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    UFUNCTION(BlueprintCallable)
    FTD_Item& GetItemData(int index);

    UFUNCTION(BlueprintCallable)
    FTD_CombineItem& GetCombineItemData(int index);

    /*UFUNCTION(BlueprintCallable)
    UDataTable* GetItemCombineTable() { return m_CombineItemTable; }*/

private:
    // UE4의 데이터 테이블
    UPROPERTY(EditAnywhere)
    UDataTable* m_ItemTable;

    UPROPERTY(EditAnywhere)
    UDataTable* m_CombineItemTable;

    // 테이블 매니저가 들고 있을 테이블 정보
    TMap<int, FTD_Item> m_mapItems;
    TMap<int, FTD_CombineItem> m_mapCombineItems;
};
