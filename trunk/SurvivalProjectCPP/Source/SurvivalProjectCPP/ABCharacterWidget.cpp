// Fill out your copyright notice in the Description page of Project Settings.

#include "ABCharacterWidget.h"
#include "SurvivalProjectCPPCharacter.h"
#include "Components/ProgressBar.h"

void UABCharacterWidget::BindCharacter(ASurvivalProjectCPPCharacter* character)
{
    //ABCHECK(nullptr != character);

    currentCharacter = character;
    //character->OnHPChanged.AddLambda([this]()->void {;}); //< ���ٸ� �߰��� ���� ����
    character->OnHPChanged.AddUObject(this, &UABCharacterWidget::UpdateHPWidget);
}

void UABCharacterWidget::NativeConstruct()
{
    Super::NativeConstruct();
    HPProgressBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));
    UpdateHPWidget();
}

void UABCharacterWidget::UpdateHPWidget()
{
    if (currentCharacter->IsValidLowLevel())
    {
        if (nullptr != HPProgressBar)
        {
            HPProgressBar->SetPercent(currentCharacter->GetHPRatio());
        }
    }
}