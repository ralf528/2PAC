// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IO_Base.generated.h"

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
    int GetInteractionType() { return m_type; }
	
private:
    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    int m_type;
};
