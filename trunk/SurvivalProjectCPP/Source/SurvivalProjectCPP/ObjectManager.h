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

    // ���忡 ��ġ�� Object ���� List �� ��� �ְ� ��ǥ �������� ����

    // �Ŵ��������� ������Ʈ�� ��ġ�ϰ� List�� �߰��ϸ�, �̹� ��ġ�Ǿ� �ִ� ������Ʈ�� �Ŵ����� ������ �߰��Ѵ�.

};
