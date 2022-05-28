// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RaidPlayerController.generated.h"

class UNiagaraSystem;
class ARaidHUD;
class ARaidPlayerCharacter;
class ADefaultCharacterAI;

/**
 * 
 */
UCLASS()
class GUILDSIMULATOR_API ARaidPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ARaidPlayerController();
	
protected:
	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;
	
	UPROPERTY()
	ARaidHUD* RaidHUD;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ARaidPlayerCharacter* DefaultPlayerRaid;
	
	// Beginning of Camera functionality.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ZoomSpeed = 65.f;
	UPROPERTY()
	float MinZoom = 500.f;
	UPROPERTY()
	float MaxZoom = 1800.f;
	// End of Camera functionality

	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	// End PlayerController interface

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();
	void OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location);
	void OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location);
	void SelectionPressed();
	void SelectionReleased();
	void MoveForwardBackPlayerCamera(float Value);
	void MoveLeftAndRightPlayerCamera(float Value);
	void ZoomInAndOut(float Value);
	
	TArray<ADefaultCharacterAI*> SelectedActors;
private:
	bool bInputPressed; // Input is bring pressed
	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
};
