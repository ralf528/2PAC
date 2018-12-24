// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct CastingTimer
{
public:
    void Start()
    {
        currentTime = 0.f;
    }

    void Update(float dt)
    {
        currentTime += dt;
    }

    bool IsComplete()
    {
        return (currentTime > castingTime);
    }

public:
    float startTime;
    float currentTime;
    float castingTime;
};

/**
 * 
 */
class SURVIVALPROJECTCPP_API ExternHeader
{
public:
	ExternHeader();
	~ExternHeader();
};
