// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DataTableManager.h"
#include "UIManager.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALPROJECTCPP_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	virtual void Init() override;

public:
	// Table Manager
	UFUNCTION(BlueprintCallable)
	void SetDataTableManager(ADataTableManager* dataTable);

	UFUNCTION(BlueprintCallable)
	ADataTableManager* GetDataTableManager() { return m_dataTableManager; }

	// UI Manager
	UFUNCTION(BlueprintCallable)
	AUIManager* GetUIManager() { return m_UIManager; }

	UFUNCTION(BlueprintCallable)
	void SetUIManager(AUIManager* uiManager);

    UFUNCTION(BlueprintCallable)
    void SelectCharacterType(int nType) { m_nSelectCharacterType = nType; }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Manager", meta = (AllowPrivateAccess = "true"))
	ADataTableManager* m_dataTableManager;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Manager", meta = (AllowPrivateAccess = "true"))
	AUIManager* m_UIManager;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "info", meta = (AllowPrivateAccess = "true"))
    int m_nSelectCharacterType;
};
