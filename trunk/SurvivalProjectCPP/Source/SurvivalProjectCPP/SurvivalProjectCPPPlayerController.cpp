// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "SurvivalProjectCPPPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "SurvivalProjectCPPCharacter.h"
#include "Engine/World.h"
#include "IO_Base.h"

ASurvivalProjectCPPPlayerController::ASurvivalProjectCPPPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
    m_bInteracting = false;
    m_InteractionTime = 0.f;
    m_InteractionItem = nullptr;
}

void ASurvivalProjectCPPPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}

    // interaction
    if (m_bInteracting) {
        m_InteractionTime += DeltaTime*100.f;
        if (m_InteractionTime > 100.f) {
            m_bInteracting = false;
            m_InteractionTime = 0.f;
            if (m_InteractionItem) {
                ASurvivalProjectCPPCharacter* character = dynamic_cast<ASurvivalProjectCPPCharacter*>(GetPawn());
                if (character) {
                    character->AddItemToInventory(m_InteractionItem->GetInteractionType());
                }

                m_InteractionItem->Destroy();
                m_InteractionItem = nullptr;
            }
            UE_LOG(LogClass, Log, TEXT("[Log]Interaction End"));
        }
    }
}

void ASurvivalProjectCPPPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ASurvivalProjectCPPPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ASurvivalProjectCPPPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ASurvivalProjectCPPPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ASurvivalProjectCPPPlayerController::MoveToTouchLocation);

	InputComponent->BindAction("ResetVR", IE_Pressed, this, &ASurvivalProjectCPPPlayerController::OnResetVR);

    // set interaction bindings
    InputComponent->BindAction("SetInteraction", IE_Pressed, this, &ASurvivalProjectCPPPlayerController::CheckInteractionObject);
}

void ASurvivalProjectCPPPlayerController::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ASurvivalProjectCPPPlayerController::MoveToMouseCursor()
{
	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
	{
		if (ASurvivalProjectCPPCharacter* MyPawn = Cast<ASurvivalProjectCPPCharacter>(GetPawn()))
		{
			if (MyPawn->GetCursorToWorld())
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
			}
		}
	}
	else
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		if (Hit.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(Hit.ImpactPoint);
		}
	}
}

void ASurvivalProjectCPPPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ASurvivalProjectCPPPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const MyPawn = GetPawn();
	if (MyPawn)
	{
		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if ((Distance > 120.0f))
		{
			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ASurvivalProjectCPPPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
    m_bInteracting = false;
    m_InteractionTime = 0.f;
}

void ASurvivalProjectCPPPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

void ASurvivalProjectCPPPlayerController::CheckInteractionObject()
{
    UE_LOG(LogClass, Log, TEXT("[Log]Check IO"));
    // Trace to see what is under the mouse cursor
    FHitResult Hit;
    GetHitResultUnderCursor(ECC_Visibility, false, Hit);

    if (Hit.bBlockingHit)
    {
        // We hit something, move there
        //SetNewMoveDestination(Hit.ImpactPoint);
        AActor* hitActor = Hit.GetActor();
        
        if (hitActor) {
            UE_LOG(LogClass, Log, TEXT("[Log]Is Actor:%s"), *hitActor->GetName());

            APawn* myPawn = GetPawn();
            if (!myPawn) {
                UE_LOG(LogClass, Log, TEXT("[Log]myPawn is nullptr"));
                return;
            }

            float distance = FMath::Abs(FVector::Dist(myPawn->GetActorLocation(), hitActor->GetActorLocation()));
            UE_LOG(LogClass, Log, TEXT("[Log]distance : %f"), distance);
            if (distance > 150.f) {
                return;
            }

            AIO_Base* comp = dynamic_cast<AIO_Base*>(hitActor);
            if (comp) {
                m_bInteracting = true;
                m_InteractionItem = comp;
            }

            /*bool bIO = hitActor->ActorHasTag("IO_Base");
            if (bIO) {
                UE_LOG(LogClass, Log, TEXT("[Log]Is IO"));
            }*/
        }
    }
}