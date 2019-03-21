// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ExternHeader.h"
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* Mesh;
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

USTRUCT(BlueprintType)
struct FTD_Interact : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int ItemCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Animation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CastingTime;
};

USTRUCT(BlueprintType)
struct FTD_Character : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int CharacterType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    USkeletalMesh* SkeletalMesh;
};

USTRUCT(BlueprintType)
struct FTD_ItemDrop : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int ItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int DropItemType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int DropItemCount;
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
	// Load Table data
	UFUNCTION(BlueprintCallable)
	bool LoadDataTable();

	UFUNCTION(BlueprintCallable)
	bool LoadItemTable();

    UFUNCTION(BlueprintCallable)
    bool LoadInteractionTable();

    UFUNCTION(BlueprintCallable)
    bool LoadCharacterTable();

    UFUNCTION(BlueprintCallable)
    bool LoadItemDropTable();

    // Get Table Item
    UFUNCTION(BlueprintCallable)
    FTD_Item& GetItemData(int index);

    UFUNCTION(BlueprintCallable)
    FTD_CombineItem& GetCombineItemData(int index);

    UFUNCTION(BlueprintCallable)
    FTD_Interact& GetInteractionData(int index);

    UFUNCTION(BlueprintCallable)
    FTD_Character& GetCharacterData(int index);

    UFUNCTION(BlueprintCallable)
    FTD_ItemDrop& GetItemDropData(int index);

    UFUNCTION(BlueprintCallable)
    int FindDropItem(int sourceItem);

private:
    // UE4의 데이터 테이블
    UPROPERTY(EditAnywhere)
    UDataTable* m_ItemTable;

    UPROPERTY(EditAnywhere)
    UDataTable* m_CombineItemTable;

    UPROPERTY(EditAnywhere)
    UDataTable* m_InteractionTable;

    UPROPERTY(EditAnywhere)
    UDataTable* m_CharacterTable;

    UPROPERTY(EditAnywhere)
    UDataTable* m_ItemDropTable;

    // 테이블 매니저가 들고 있을 테이블 정보
    TMap<int, FTD_Item> m_mapItems;
    TMap<int, FTD_CombineItem> m_mapCombineItems;
    TMap<int, FTD_Interact> m_mapInteractions;
    TMap<int, FTD_Character> m_mapCharacters;
    TMap<int, FTD_ItemDrop> m_mapItemDrops;
};
