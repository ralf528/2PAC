// Fill out your copyright notice in the Description page of Project Settings.

#include "LogManager.h"


// Sets default values
ALogManager::ALogManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALogManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALogManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALogManager::Log(FString format)
{
    UE_LOG(LogClass, Log, TEXT("%s"), *format);

    /*
    �����μ� ó���� ����� �켱 �̷��� �������.
    ALogManager::Log(FString::Printf(TEXT("test = %d"), 10));
    */
}

