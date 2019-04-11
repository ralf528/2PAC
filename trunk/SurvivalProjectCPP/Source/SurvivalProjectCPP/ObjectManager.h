// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectManager.generated.h"

UCLASS()
class SURVIVALPROJECTCPP_API AObjectManager : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AObjectManager();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // 월드에 배치된 Object 들의 List 를 들고 있고 좌표 정보등이 있음

    // 매니저에서도 오브젝트를 배치하고 List에 추가하며, 이미 배치되어 있는 오브젝트는 매니저에 정보만 추가한다.

};
