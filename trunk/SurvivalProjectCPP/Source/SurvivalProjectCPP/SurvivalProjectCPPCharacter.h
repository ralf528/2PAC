// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "ExternHeader.h"
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivalProjectCPPCharacter.generated.h"

enum E_UI;

USTRUCT(Blueprintable)
struct FInvenItemInfo
{
    GENERATED_BODY()
public:

    UPROPERTY()
    int itemType;

    UPROPERTY()
    int amount;
};

DECLARE_MULTICAST_DELEGATE(FOnHPChangedDelegate);

UCLASS(Blueprintable)
class ASurvivalProjectCPPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASurvivalProjectCPPCharacter();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

    virtual void PostInitProperties() override;

    virtual void PostInitializeComponents() override;

    /** Allows a Pawn to set up custom input bindings. Called upon possession by a PlayerController, using the InputComponent created by CreatePlayerInputComponent(). */
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

    UFUNCTION(BlueprintCallable, Category = "MyUnit")
    void AddItemToInventory(int itemType, int amount = 1);

	// key binding
	void InputUseItemKey01();
	void InputUseItemKey02();
	void InputUseItemKey03();
	void InputUseItemKey04();

	void InputActiveInven();
	void InputActiveCombine();

    // 아이템
    UFUNCTION(BlueprintCallable, Category = "MyUnit")
    bool UseItemForIndex(const int index);

    UFUNCTION(BlueprintCallable, Category = "MyUnit")
    bool UseItemForType(const int itemType);

    UFUNCTION(BlueprintCallable, Category = "MyUnit")
    int FindItemIndexForType(int itemType);

    UFUNCTION(BlueprintCallable, Category = "MyUnit")
    bool ExistItem(int index);

	UFUNCTION(BlueprintCallable, Category = "MyUnit")
	int GetItemType(int index);

	UFUNCTION(BlueprintCallable, Category = "MyUnit")
	int GetItemCount(int index);

    UFUNCTION(BlueprintCallable, Category = "MyUnit")
    int GetItemCountByType(int itemType);

	UFUNCTION(BlueprintCallable, Category = "MyUnit")
	bool SwapItemForIndex(const int src, const int dst);

	UFUNCTION(BlueprintCallable, Category = "MyUnit")
    int DeleteItem(int index, int count = 1);

    UFUNCTION(BlueprintCallable, Category = "MyUnit")
    bool CombineItem(const int index);

    UFUNCTION(BlueprintCallable, Category = "MyUnit")
    int GetNextEmptySlot();

    // Equipment
    UFUNCTION(BlueprintCallable, Category = "Equipment")
    int GetEquipTool() { return m_equipTool; }

    UFUNCTION(BlueprintCallable, Category = "Equipment")
    void AttachmentWeapon(int itemIndex);

	// ui
	void OnOffWidget(E_UI eUI);

	// 퀵 슬롯
	UFUNCTION(BlueprintCallable, Category = "QuickSlot")
	int GetQuickSlot(const int index);

    UFUNCTION(BlueprintCallable, Category = "QuickSlot")
    bool AddQuickSlot(const int index, const int itemType);

	UFUNCTION(BlueprintCallable, Category = "QuickSlot")
	bool SwapQuickSlot(const int src, const int dst);
	
    // hp ui 델리게이트
    FOnHPChangedDelegate OnHPChanged;

    float GetHPRatio() { return m_currentHP / 100.f; }

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyUnit", meta = (AllowPrivateAccess = "true"))
    TMap<int, FInvenItemInfo> m_inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyUnit", meta = (AllowPrivateAccess = "true"))
	TArray<int> m_QuickSlot;

    UPROPERTY(VisibleAnywhere, Category = Weapon)
    UStaticMeshComponent* m_Weapon;

    UPROPERTY(EditAnywhere, Category = Weapon)
    UStaticMesh* m_WeaponMesh;

    UPROPERTY(EditAnywhere, Category = "MyUnit")
    int m_equipTool;

    // hp 관련
    UPROPERTY(VisibleAnywhere, Category = UI)
    class UWidgetComponent* m_HeadUpHPBar;

    UPROPERTY(Transient, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAceess = true))    // Transient : Serialization 에 포함되지 않음
    float m_currentHP;
};