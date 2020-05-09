// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ABCharacterWidget.generated.h"

/**
 * 
 */
UCLASS()
class SURVIVALPROJECTCPP_API UABCharacterWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    void BindCharacter(class ASurvivalProjectCPPCharacter* character);

protected:
    virtual void NativeConstruct() override;
    void UpdateHPWidget();
	
private :
    TWeakObjectPtr<class ASurvivalProjectCPPCharacter> currentCharacter;

    UPROPERTY()
    class UProgressBar* HPProgressBar;
};
