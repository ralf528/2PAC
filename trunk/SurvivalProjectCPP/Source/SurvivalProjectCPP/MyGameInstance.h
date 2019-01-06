// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
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
	UMyGameInstance() {}

	virtual void Init() override;

public:
	UFUNCTION(BlueprintCallable)
	AUIManager* GetUIManager() { return m_UIManager; }

	UFUNCTION(BlueprintCallable)
	void SetUIManager(AUIManager* uiManager) { if (!m_UIManager) { m_UIManager = uiManager; } }

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
	AUIManager* m_UIManager;
};
