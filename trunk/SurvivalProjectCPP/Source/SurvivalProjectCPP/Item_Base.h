// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item_Base.generated.h"

UCLASS()
class SURVIVALPROJECTCPP_API AItem_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    void SetItemStaticMesh();

    void SetItemType(int nType) { m_itemType = nType; }
    int GetItemType() { return m_itemType; }

private:
    int m_itemType;

    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* m_meshComponent;
};
