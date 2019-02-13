// Fill out your copyright notice in the Description page of Project Settings.

#include "UIManager.h"
#include "UObject/ConstructorHelpers.h"
//#include "Blueprint/UserWidget.h"
#include "LogManager.h"


// Sets default values
AUIManager::AUIManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FClassFinder<UUserWidget> widgetObjects[E_UI::SIZE]{
		TEXT("/Game/Resources/UI/UI_HealthPointBar"),
		TEXT("/Game/Resources/UI/UI_Inventory"),
		TEXT("/Game/Resources/UI/UI_Combine"),
		TEXT("/Game/Resources/UI/UI_CastingGauge"),
		TEXT("/Game/Resources/UI/UI_MiniMap"),
		TEXT("/Game/Resources/UI/UI_QuickSlot"),
		TEXT("/Game/Assets/BluePrints/UI/Panel/Main_UI")
	};

	/*static ConstructorHelpers::FClassFinder<UUserWidget> widgetObj_0(TEXT("/Game/Resources/UI/UI_HealthPointBar"));
	static ConstructorHelpers::FClassFinder<UUserWidget> widgetObj_1(TEXT("/Game/Resources/UI/UI_Inventory"));
	static ConstructorHelpers::FClassFinder<UUserWidget> widgetObj_2(TEXT("/Game/Resources/UI/UI_Combine"));
	static ConstructorHelpers::FClassFinder<UUserWidget> widgetObj_3(TEXT("/Game/Resources/UI/UI_CastingGauge"));
	static ConstructorHelpers::FClassFinder<UUserWidget> widgetObj_4(TEXT("/Game/Resources/UI/UI_MiniMap"));*/

	/*widgetObjects[0] = &widgetObj_0;
	widgetObjects[1] = &widgetObj_1;
	widgetObjects[2] = &widgetObj_2;
	widgetObjects[3] = &widgetObj_3;
	widgetObjects[4] = &widgetObj_4;*/

	for (int i = 0; i < (int)E_UI::SIZE; i++) {
		WidgetClass[i] = widgetObjects[i].Class;
	}
}

// Called when the game starts or when spawned
void AUIManager::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < (int)E_UI::SIZE; i++) {
		if (WidgetClass[i]) {
			m_widget[i] = CreateWidget<UUserWidget>(GetWorld(), WidgetClass[i]);

			if (m_widget[i]) {
				m_widget[i]->AddToViewport();
			}
		}
	}

	ActiveUI(eUI_Combine, false);
	ActiveUI(eUI_Inven, false);
}

// Called every frame
void AUIManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UUserWidget* AUIManager::GetUserWidget(E_UI ui)
{
	return m_widget[(int)ui];
}

bool AUIManager::ActiveUI(E_UI eUI, bool bActive)
{
	UUserWidget* widget = GetUserWidget(eUI);
	if (!widget) {
		return false;
	}

	if (bActive) {
		widget->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		widget->SetVisibility(ESlateVisibility::Hidden);
	}

	return true;
}

bool AUIManager::ActiveUI(EC_UI ecUI, bool bActive)
{
    return ActiveUI((E_UI)ecUI, bActive);
}