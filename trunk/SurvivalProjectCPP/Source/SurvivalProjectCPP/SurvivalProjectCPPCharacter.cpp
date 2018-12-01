// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SurvivalProjectCPPCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"

ASurvivalProjectCPPCharacter::ASurvivalProjectCPPCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create a decal in the world to show the cursor's location
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UMaterial> DecalMaterialAsset(TEXT("Material'/Game/TopDownCPP/Blueprints/M_Cursor_Decal.M_Cursor_Decal'"));
	if (DecalMaterialAsset.Succeeded())
	{
		CursorToWorld->SetDecalMaterial(DecalMaterialAsset.Object);
	}
	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.0f, 0.0f, 0.0f).Quaternion());

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

    // Data Table
    //FItemStruct* row = m_DataTable->FindRow<FItemStruct>(TEXT("1"), TEXT(""));
    /*if (row) {
    UE_LOG(LogClass, Log, TEXT("[Log]Item Row %d"), row->ItemType);
    }*/
}

void ASurvivalProjectCPPCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	if (CursorToWorld != nullptr)
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (UWorld* World = GetWorld())
			{
				FHitResult HitResult;
				FCollisionQueryParams Params(NAME_None, FCollisionQueryParams::GetUnknownStatId());
				FVector StartLocation = TopDownCameraComponent->GetComponentLocation();
				FVector EndLocation = TopDownCameraComponent->GetComponentRotation().Vector() * 2000.0f;
				Params.AddIgnoredActor(this);
				World->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
				FQuat SurfaceRotation = HitResult.ImpactNormal.ToOrientationRotator().Quaternion();
				CursorToWorld->SetWorldLocationAndRotation(HitResult.Location, SurfaceRotation);
			}
		}
		else if (APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);
		}
	}
}

void ASurvivalProjectCPPCharacter::PostInitProperties()
{
    Super::PostInitProperties();

    //< 인벤토리 셋팅
    m_inventory.Add(1, 0);
    m_inventory.Add(2, 0);
    m_inventory.Add(3, 0);
    m_inventory.Add(4, 0);
}

void ASurvivalProjectCPPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAction("UseItem_01", IE_Pressed, this, &ASurvivalProjectCPPCharacter::InputUseItemKey01);
    PlayerInputComponent->BindAction("UseItem_02", IE_Pressed, this, &ASurvivalProjectCPPCharacter::InputUseItemKey02);
    PlayerInputComponent->BindAction("UseItem_03", IE_Pressed, this, &ASurvivalProjectCPPCharacter::InputUseItemKey03);
    PlayerInputComponent->BindAction("UseItem_04", IE_Pressed, this, &ASurvivalProjectCPPCharacter::InputUseItemKey04);
}

void ASurvivalProjectCPPCharacter::AddItemToInventory(int itemType)
{
    UE_LOG(LogClass, Log, TEXT("[Log]AddItem %d"), itemType); 

    int32* find = m_inventory.Find(itemType);
    if (find) {
        UE_LOG(LogClass, Log, TEXT("[Log]Find Item %d"), *find);
        (*find)++;
    }
}

void ASurvivalProjectCPPCharacter::InputUseItemKey01()
{
    UseItemForIndex(0);
}

void ASurvivalProjectCPPCharacter::InputUseItemKey02()
{
    UseItemForIndex(1);
}

void ASurvivalProjectCPPCharacter::InputUseItemKey03()
{
    UseItemForIndex(2);
}

void ASurvivalProjectCPPCharacter::InputUseItemKey04()
{
    UseItemForIndex(3);
}

bool ASurvivalProjectCPPCharacter::UseItemForIndex(const int index)
{
    UE_LOG(LogClass, Log, TEXT("[Log]UseItem %d"), index);

    //< 인벤토리
    /*if (index >= m_inventory.Num()) {
        return false;
    }

    int value = m_inventory[index];
    m_inventory[index]--;*/

    return true;
}