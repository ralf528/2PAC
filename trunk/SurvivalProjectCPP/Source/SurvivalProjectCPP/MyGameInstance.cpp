// Fill out your copyright notice in the Description page of Project Settings.

#include "MyGameInstance.h"

UMyGameInstance::UMyGameInstance()
{
	m_dataTableManager = nullptr;
	m_UIManager = nullptr;
}

void UMyGameInstance::Init()
{
	Super::Init();
}

void UMyGameInstance::SetDataTableManager(ADataTableManager* dataTable)
{
	if (!m_dataTableManager)
	{
		m_dataTableManager = dataTable;
	}
}

void UMyGameInstance::SetUIManager(AUIManager* uiManager)
{
	if (!m_UIManager)
	{
		m_UIManager = uiManager;
	}
}