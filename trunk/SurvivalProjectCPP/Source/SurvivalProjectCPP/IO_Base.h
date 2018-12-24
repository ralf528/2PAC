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
    int Type;
    int Animation;
    float castingTime;
};

UCLASS()
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
    int GetInteractionType() { return info.Type; }

    void Execute();

    void SetCharacter(ASurvivalProjectCPPCharacter* character) { this->character = character; }
	
private:
    UPROPERTY(EditAnywhere, Blueprintable, Category = "Interaction")
    int type;

    FInteraction info;

    ASurvivalProjectCPPCharacter* character;
};

USTRUCT()
struct FInteractor
{
    GENERATED_USTRUCT_BODY()

public:
    FInteractor() : _object(nullptr) {}

    void Reset() { _object = nullptr; }

    void Start(AIO_Base* obj)
    {
        _object = obj;
    }

    void Complete()
    {
        if (_object) {
            _object->Execute();
        }
        Reset();
    }

    AIO_Base* GetObject() { return _object; }

    bool IsInteracting() { return (_object != nullptr); }

private:
    AIO_Base* _object;
};