// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/DataTable.h"
#include "SurvivalProjectCPPCharacter.generated.h"

USTRUCT()
struct FItemStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY()
    int ItemType;
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
    void AddItemToInventory(int itemType);

    //< 아이템 사용
    void InputUseItemKey01();
    void InputUseItemKey02();
    void InputUseItemKey03();
    void InputUseItemKey04();
    bool UseItemForIndex(const int index);

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
    TMap<int, int> m_inventory;

    UPROPERTY(EditAnywhere)
    UDataTable* m_DataTable;
};

