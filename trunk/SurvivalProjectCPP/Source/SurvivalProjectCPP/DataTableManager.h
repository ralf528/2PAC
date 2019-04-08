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
    int Index;  // 인덱스

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Name; // 이름

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Image;  // 아이콘

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* Mesh;  // 메쉬

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int MaxHP;  // 내구도

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int DecHP;  // 내구도 감소량

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool NoBreak;   // 파괴 여부

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int MaxCount;   // 최대 개수

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Skill;  // 스킬 정보

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int EquipSlot;  // 장비 슬롯
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
    FName Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Desc;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* Mesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int MaxHP;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int UseTool;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float CastingTime;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int DropGroup;
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
    //Drop Group Index,	type(스탯/아이템 등), 드랍할 아이템 Index,	개수,	확률 등..
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int DropGroupIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int DropType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int DropItemIndex;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int DropItemCount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int DropProbability;
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
    int FindDropItem(int nGroupIndex);

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

    // Invalid Data
    FTD_Item Item_Invalid;
    FTD_CombineItem CombineItem_Invalid;
    FTD_Interact Interact_Invalid;
    FTD_Character Character_Invalid;
    FTD_ItemDrop ItemDrop_Invalid;
};
