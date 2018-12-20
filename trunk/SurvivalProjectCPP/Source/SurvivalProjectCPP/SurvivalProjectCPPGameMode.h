// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DataTableManager.h"
#include "SurvivalProjectCPPGameMode.generated.h"

UCLASS(minimalapi)
class ASurvivalProjectCPPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASurvivalProjectCPPGameMode();

    UFUNCTION(BlueprintCallable)
    void SetDataTableManager(ADataTableManager* dataTable) { if (!m_dataTableManager) { m_dataTableManager = dataTable; } }

    UFUNCTION(BlueprintCallable)
    ADataTableManager* GetDataTableManager() { return m_dataTableManager; }

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "DataTable", meta = (AllowPrivateAccess = "true"))
    ADataTableManager* m_dataTableManager;
};



