// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SurvivalProjectCPPCharacter.h"
#include "SurvivalProjectCPPGameMode.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "LogManager.h"
#include "MyGameInstance.h"
#include "Engine/World.h"
#include "UserWidget.h"

const int gb_nMaxInvenSlot = 16;
const int gb_nMaxQuickSlot = 8;

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
	m_inventory.Reset();
    AddItemToInventory(1, 1);
    AddItemToInventory(2, 2);
    AddItemToInventory(3, 3);
    AddItemToInventory(4, 4);
    AddItemToInventory(0, 0);
    AddItemToInventory(0, 0);
    AddItemToInventory(0, 0);
    AddItemToInventory(0, 0);
    AddItemToInventory(0, 0);
    AddItemToInventory(0, 0);
    AddItemToInventory(0, 0);
    AddItemToInventory(0, 0);
    AddItemToInventory(0, 0);
    AddItemToInventory(0, 0);
    AddItemToInventory(0, 0);
    AddItemToInventory(0, 0);

	m_QuickSlot.Reset();
	m_QuickSlot.Add(0);
	m_QuickSlot.Add(1);
	m_QuickSlot.Add(2);
	m_QuickSlot.Add(3);
    m_QuickSlot.Add(gb_nMaxInvenSlot);
    m_QuickSlot.Add(gb_nMaxInvenSlot);
    m_QuickSlot.Add(gb_nMaxInvenSlot);
    m_QuickSlot.Add(gb_nMaxInvenSlot);
}

void ASurvivalProjectCPPCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("UseItem_01", IE_Pressed, this, &ASurvivalProjectCPPCharacter::InputUseItemKey01);
	PlayerInputComponent->BindAction("UseItem_02", IE_Pressed, this, &ASurvivalProjectCPPCharacter::InputUseItemKey02);
	PlayerInputComponent->BindAction("UseItem_03", IE_Pressed, this, &ASurvivalProjectCPPCharacter::InputUseItemKey03);
	PlayerInputComponent->BindAction("UseItem_04", IE_Pressed, this, &ASurvivalProjectCPPCharacter::InputUseItemKey04);
	PlayerInputComponent->BindAction("ActiveInven", IE_Pressed, this, &ASurvivalProjectCPPCharacter::InputActiveInven);
	PlayerInputComponent->BindAction("ActiveCombine", IE_Pressed, this, &ASurvivalProjectCPPCharacter::InputActiveCombine);
}

void ASurvivalProjectCPPCharacter::AddItemToInventory(int itemType, int amount)
{
    if (itemType == 0) {
        FInvenItemInfo info;
        info.itemType = itemType;
        info.amount = amount;
        m_inventory.Add(GetNextEmptySlot(), info);
        return;
    }

    int index = FindItemIndexForType(itemType);
    if (index != gb_nMaxInvenSlot) {
        FInvenItemInfo* find = m_inventory.Find(index);
        if (find) {
            (*find).amount += amount;
        }
    }
    else {
        FInvenItemInfo info;
        info.itemType = itemType;
        info.amount = amount;
        m_inventory.Add(GetNextEmptySlot(), info);
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
	if (!ExistItem(index)) {
		return false;
	}

	int value = DeleteItem(index);
	ALogManager::Log(FString::Printf(TEXT("[Log]UseItem index : %d, count : %d"), index, value));

	return true;
}

int ASurvivalProjectCPPCharacter::FindItemIndexForType(int itemType)
{
    for (int i = 0; i < gb_nMaxInvenSlot; i++) {
        FInvenItemInfo* info = m_inventory.Find(i);

        if (!info) {
            continue;
        }

        if (info->itemType == itemType) {
            return i;
        }
    }

    return gb_nMaxInvenSlot;
}

bool ASurvivalProjectCPPCharacter::ExistItem(int index)
{
	if (m_inventory.Find(index) == nullptr) {
		return false;
	}

	if (m_inventory[index].amount <= 0) {
		return false;
	}

	return true;
}

int ASurvivalProjectCPPCharacter::GetItemType(int index)
{
	// 지금은 key가 type 이고, value가 count 인듯..
	if (m_inventory.Find(index) == nullptr) {
		return 0;
	}

	return m_inventory[index].itemType;
}

int ASurvivalProjectCPPCharacter::GetItemCount(int index)
{
	if (m_inventory.Find(index) == nullptr) {
		return 0;
	}

	return m_inventory[index].amount;
}

bool ASurvivalProjectCPPCharacter::SwapItemForIndex(const int src, const int dst)
{
    if (src == dst) {
        return false;
    }

    if (src >= gb_nMaxInvenSlot || dst >= gb_nMaxInvenSlot) {
        return false;
    }

    FInvenItemInfo tmp = m_inventory[src];
    m_inventory[src] = m_inventory[dst];
    m_inventory[dst] = tmp;

	return true;
}

int ASurvivalProjectCPPCharacter::DeleteItem(int index, int count)
{
	if (m_inventory.Find(index) == nullptr) {
		return false;
	}

	if (count == -1) {
		m_inventory[index].amount = 0;
	}
	else {
		int remain = m_inventory[index].amount - count;
		m_inventory[index].amount = (remain < 0) ? 0 : remain;
	}

	return m_inventory[index].amount;
}

bool ASurvivalProjectCPPCharacter::CombineItem(const int index)
{
	ASurvivalProjectCPPGameMode* mode = Cast<ASurvivalProjectCPPGameMode>(GetWorld()->GetAuthGameMode());
	if (!mode) {
		return false;
	}

	auto game = dynamic_cast<UMyGameInstance*>(GetGameInstance());
	if (!game) {
		return false;
	}

	ADataTableManager* table = game->GetDataTableManager();
	if (!table) {
		return false;
	}

	FTD_CombineItem& data = table->GetCombineItemData(index);

	if (!ExistItem(data.MaterialItemType1) || !ExistItem(data.MaterialItemType2)) {
		UE_LOG(LogClass, Log, TEXT("[Log]not enough Combine Material : %d, %d"), data.MaterialItemType1, data.MaterialItemType2);
		return false;
	}

	DeleteItem(data.MaterialItemType1);
	DeleteItem(data.MaterialItemType2);
	AddItemToInventory(data.ResultItemType);

	return true;
}

int ASurvivalProjectCPPCharacter::GetNextEmptySlot()
{
    for (int i = 0; i < gb_nMaxInvenSlot; i++) {
        if (!m_inventory.Find(i)) {
            return i;
        }
    }

    return gb_nMaxInvenSlot;
}

void ASurvivalProjectCPPCharacter::OnOffWidget(E_UI eUI)
{
	// 게임 인스턴스에서 받아오자
	UMyGameInstance* inst = dynamic_cast<UMyGameInstance*>(GetGameInstance());
	if (!inst) {
		return;
	}

	if (!inst->GetUIManager()) {
		return;
	}

	UUserWidget* widget = inst->GetUIManager()->GetUserWidget(eUI);
	if (!widget) {
		return;
	}

	ESlateVisibility eVis = widget->GetVisibility();
	if ((widget->GetVisibility() == ESlateVisibility::Visible) || (widget->GetVisibility() == ESlateVisibility::SelfHitTestInvisible)) {
		widget->SetVisibility(ESlateVisibility::Hidden);
	}
	else if (widget->GetVisibility() == ESlateVisibility::Hidden) {
		widget->SetVisibility(ESlateVisibility::Visible);
	}
}

void ASurvivalProjectCPPCharacter::InputActiveInven()
{
	OnOffWidget(E_UI::eUI_Inven);
}

void ASurvivalProjectCPPCharacter::InputActiveCombine()
{
	OnOffWidget(E_UI::eUI_Combine);
}

int ASurvivalProjectCPPCharacter::GetQuickSlot(const int index)
{
	if (gb_nMaxQuickSlot <= index) {
		return gb_nMaxInvenSlot;
	}

	//ALogManager::Log(FString::Printf(TEXT("[Log]Slot = %d (index : %d)"), m_QuickSlot[index], index));

	return m_QuickSlot[index];
}

bool ASurvivalProjectCPPCharacter::SwapQuickSlot(const int src, const int dst)
{
	ALogManager::Log(FString::Printf(TEXT("quickslot swap : %d to %d"), src, dst));

	int size = (int)m_QuickSlot.GetAllocatedSize() / sizeof(int);
	if (size <= src) {
		return false;
	}

	if (size <= dst) {
		return false;
	}

	m_QuickSlot.Swap(src, dst);

	return true;
}