// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SurvivalProjectCPPPlayerController.generated.h"

class AIO_Base;

UCLASS()
class ASurvivalProjectCPPPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASurvivalProjectCPPPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

    /** Navigate player to the current mouse cursor location. */
    void CheckInteractionObject();

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyUnit", meta = (AllowPrivateAccess = "true"))
    bool m_bInteracting;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MyUnit", meta = (AllowPrivateAccess = "true"))
    float m_InteractionTime;

    AIO_Base* m_InteractionItem;
};


