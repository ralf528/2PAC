// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blueprint/UserWidget.h"
#include "UIManager.generated.h"

enum E_UI
{
	eUI_HPBar,
	eUI_Inven,
	eUI_Combine,
	eUI_CastingBar,
	eUI_Minimap,
	eUI_QuickSlot,
	eUI_MainPanel,
	SIZE
};

UENUM(BlueprintType)
enum class EC_UI : uint8
{
    ecUI_HPBar,
    ecUI_Inven,
    ecUI_Combine,
    ecUI_CastingBar,
    ecUI_Minimap,
    ecUI_QuickSlot,
    ecUI_MainPanel,
    SIZE
};

//class UUserWidget;

UCLASS()
class SURVIVALPROJECTCPP_API AUIManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AUIManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UUserWidget* GetUserWidget(E_UI ui);

	bool ActiveUI(E_UI eUI, bool bActive);

    UFUNCTION(BluePrintCallable)
    bool ActiveUI(EC_UI ecUI, bool bActive = true);

private:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> WidgetClass[E_UI::SIZE];

	UPROPERTY(EditAnywhere, Category = "UI")
	class UUserWidget* m_widget[E_UI::SIZE];
};
