// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SurvivalProjectCPPCharacter.generated.h"

enum E_UI;

USTRUCT(Blueprintable)
struct FInvenItemInfo
{
    GENERATED_BODY()
public:
    int itemType;
    int amount;
};

UCLASS(Blueprintable)
class ASurvivalProjectCPPCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASurvivalProjectCPPCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

    virtual void PostInitProperties() override;

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

    // æ∆¿Ã≈€
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

	// ui
	void OnOffWidget(E_UI eUI);

	// ƒ¸ ΩΩ∑‘
	UFUNCTION(BlueprintCallable, Category = "QuickSlot")
	int GetQuickSlot(const int index);

	UFUNCTION(BlueprintCallable, Category = "QuickSlot")
	bool SwapQuickSlot(const int src, const int dst);
	

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
};