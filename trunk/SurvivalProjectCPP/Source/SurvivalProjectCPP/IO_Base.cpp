// Fill out your copyright notice in the Description page of Project Settings.

#include "IO_Base.h"


// Sets default values
AIO_Base::AIO_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AIO_Base::BeginPlay()
{
	Super::BeginPlay();
	
    //< �켱�� ������ Ÿ���� ��������
    info.Type = FMath::RandRange(1, 4);
}

// Called every frame
void AIO_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AIO_Base::Execute()
{
    switch (type) {
    case 1:
    {
        if (character) {
            character->AddItemToInventory(info.Type);
            this->Destroy();
        }
    }
    break;
    }
}

