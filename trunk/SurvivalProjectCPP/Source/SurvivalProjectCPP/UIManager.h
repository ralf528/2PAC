// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UIManager.generated.h"

enum E_UI
{
	eUI_HPBar,
	eUI_Inven,
	eUI_Combine,
	eUI_CastingBar,
	eUI_Minimap,
	SIZE
};

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

private:
	UPROPERTY(EditAnywhere, Category = "UI")
	TSubclassOf<class UUserWidget> WidgetClass[E_UI::SIZE];

	UPROPERTY(EditAnywhere, Category = "UI")
	class UUserWidget* m_widget[E_UI::SIZE];
};
