// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

/**
 * 
 */
class SURVIVALPROJECTCPP_API Util_Interaction
{
public:
	Util_Interaction();
	~Util_Interaction();
};

class AIO_Base;
class AItem_Base;
class ASurvivalProjectCPPCharacter;

//USTRUCT()
struct FInteractor
{
    //GENERATED_BODY()

public:
    FInteractor() : _object(nullptr) {}

    void Reset() { _object = nullptr; _item = nullptr; }

    void Start(AIO_Base* obj, float time = 1.5f)
    {
        _object = obj;
        _item = nullptr;
        _time = time * 100.f;
    }

    void Start(AItem_Base* obj, float time = 0.1f)
    {
        _item = obj;
        _object = nullptr;
        _time = time * 100.f;
    }

    void Complete();

public:
    AIO_Base* GetObject() { return _object; }

    bool IsInteracting() { return (_object != nullptr) || (_item != nullptr); }

    void SetTime(float time) { _time = time; }
    float GetTime() { return _time; }

    void SetCharacter(ASurvivalProjectCPPCharacter* character) { m_character = character; }

private:
    AIO_Base* _object;
    AItem_Base* _item;
    float _time;

    ASurvivalProjectCPPCharacter* m_character;
};