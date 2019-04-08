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
    int Index;  // �ε���

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FName Name; // �̸�

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UTexture2D* Image;  // ������

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UStaticMesh* Mesh;  // �޽�

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int MaxHP;  // ������

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int DecHP;  // ������ ���ҷ�

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool NoBreak;   // �ı� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int MaxCount;   // �ִ� ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int Skill;  // ��ų ����

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int EquipSlot;  // ��� ����
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
    //Drop Group Index,	type(����/������ ��), ����� ������ Index,	����,	Ȯ�� ��..
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
    // UE4�� ������ ���̺�
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

    // ���̺� �Ŵ����� ��� ���� ���̺� ����
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
