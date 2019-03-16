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

    void SetCharacter(ASurvivalProjectCPPCharacter* character) { this->character = character; }

private:
    UPROPERTY(EditAnywhere, Category = "Interaction")
    //UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Interaction", meta = (AllowPrivateAccess = "true"))
    int InteractionType;

    FInteraction info;

    ASurvivalProjectCPPCharacter* character;

    UPROPERTY(EditAnywhere)
    TSubclassOf<AIO_Base> IO_Blueprint;
};

USTRUCT()
struct FInteractor
{
    GENERATED_USTRUCT_BODY()

public:
    FInteractor() : _object(nullptr) {}

    void Reset() { _object = nullptr; }

    void Start(AIO_Base* obj, float time = 1.5f)
    {
        _object = obj;
		_time = time * 100.f;
    }

    void Complete()
    {
        if (_object) {
            _object->Execute();
        }
        Reset();
    }

public:
    AIO_Base* GetObject() { return _object; }

    bool IsInteracting() { return (_object != nullptr); }

	void SetTime(float time) { _time = time; }
	float GetTime() { return _time; }

private:
    AIO_Base* _object;
	float _time;
};