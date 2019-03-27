// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SurvivalProjectCPPCharacter.h"
#include "IO_Base.generated.h"

USTRUCT()
struct FInteraction
{
    GENERATED_USTRUCT_BODY()

public:
    int ItemType;
    int Amount;
    int Animation;
    float castingTime;
};

class AItem_Base;

UCLASS(Blueprintable)
class SURVIVALPROJECTCPP_API AIO_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AIO_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    FInteraction GetInfo() { return info; }

    UFUNCTION(BlueprintCallable)
    int GetInteractionType() { return InteractionType; }

    UFUNCTION(BlueprintCallable)
    void SetInteractionType(int type) { InteractionType = type; }

    void Execute();

    void SetInteractionInfo();

    UFUNCTION(BlueprintCallable)
    void SetItemStaticMesh();

private:
    UPROPERTY(EditAnywhere, Category = "Interaction")
    //UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
    int InteractionType;

    FInteraction info;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AItem_Base> Item_Blueprint;

    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* m_meshComponent;
};