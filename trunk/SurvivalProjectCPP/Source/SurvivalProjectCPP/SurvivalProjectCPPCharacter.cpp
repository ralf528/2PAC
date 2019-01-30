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

	//< �κ��丮 ����
	m_inventory.Reset();
	m_inventory.Add(1, 1);
	m_inventory.Add(2, 2);
	m_inventory.Add(3, 3);
	m_inventory.Add(4, 4);

	m_QuickSlot.Reset();
	m_QuickSlot.Add(1);
	m_QuickSlot.Add(2);
	m_QuickSlot.Add(3);
	m_QuickSlot.Add(4);
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
	int32* find = m_inventory.Find(itemType);
	if (find) {
		(*find) += amount;
		ALogManager::Log(FString::Printf(TEXT("[Log]Add Item %d"), itemType));
	}
	else {
		ALogManager::Log(FString::Printf(TEXT("[Log]not found Item %d"), itemType));
	}
}

void ASurvivalProjectCPPCharacter::InputUseItemKey01()
{
	UseItemForIndex(1);
}

void ASurvivalProjectCPPCharacter::InputUseItemKey02()
{
	UseItemForIndex(2);
}

void ASurvivalProjectCPPCharacter::InputUseItemKey03()
{
	UseItemForIndex(3);
}

void ASurvivalProjectCPPCharacter::InputUseItemKey04()
{
	UseItemForIndex(4);
}

bool ASurvivalProjectCPPCharacter::UseItemForIndex(const int index)
{
	//< �κ��丮
	if (m_inventory.Find(index) == nullptr) {
		return false;
	}

	if (!ExistItem(index)) {
		return false;
	}

	int value = DeleteItem(index);
	ALogManager::Log(FString::Printf(TEXT("[Log]UseItem index : %d, count : %d"), index, value));

	return true;
}

bool ASurvivalProjectCPPCharacter::ExistItem(int index)
{
	if (m_inventory.Find(index) == nullptr) {
		return false;
	}

	if (m_inventory[index] <= 0) {
		return false;
	}

	return true;
}

int ASurvivalProjectCPPCharacter::GetItemType(int index)
{
	// ������ key�� type �̰�, value�� count �ε�..
	if (m_inventory.Find(index) == nullptr) {
		return 0;
	}

	return m_inventory[index];
}

int ASurvivalProjectCPPCharacter::GetItemCount(int index)
{
	if (m_inventory.Find(index) == nullptr) {
		return 0;
	}

	return m_inventory[index];
}

bool ASurvivalProjectCPPCharacter::SwapItemForIndex(const int src, const int dst)
{
	if (src == dst) {
		return false;
	}

	if (!ExistItem(src)) {
		return false;
	}

	if (ExistItem(dst)) {
		int srcAmount = m_inventory[src];
		int dstAmount = m_inventory[dst];
		DeleteItem(src, -1);
		DeleteItem(dst, -1);
		AddItemToInventory(src, dstAmount);
		AddItemToInventory(dst, srcAmount);
	}
	else {
		AddItemToInventory(dst, m_inventory[src]);
		DeleteItem(src, -1);
	}

	return true;
}

int ASurvivalProjectCPPCharacter::DeleteItem(int index, int count)
{
	if (m_inventory.Find(index) == nullptr) {
		return false;
	}

	if (count == -1) {
		m_inventory[index] = 0;
	}
	else {
		int remain = m_inventory[index] - count;
		m_inventory[index] = (remain < 0) ? 0 : remain;
	}

	return m_inventory[index];
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

void ASurvivalProjectCPPCharacter::OnOffWidget(E_UI eUI)
{
	// ���� �ν��Ͻ����� �޾ƿ���
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
	if (m_QuickSlot.GetAllocatedSize() / sizeof(int) <= (unsigned)index) {
		return 0;
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