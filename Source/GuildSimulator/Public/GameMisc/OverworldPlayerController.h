// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GuildSimEnums.h"
#include "GameFramework/PlayerController.h"
#include "OverworldPlayerController.generated.h"

class UNiagaraSystem;
class AOverworldPlayerCharacter;
class USpringArmComponent;
class AOverworldHUD;

/**
 * 
 */
UCLASS()
class GUILDSIMULATOR_API AOverworldPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AOverworldPlayerController();

	/** Time Threshold to know if it was a short press */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	float ShortPressThreshold;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* FXCursor;

	/** FX Class that we will spawn when clicking */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UNiagaraSystem* DashParticleEffect;
	
	//Set / Getting Dash Timer
	FORCEINLINE void SetCooldownDashTimer(float SetTimer) { CooldownDashTimer = SetTimer; }
	FORCEINLINE float GetCooldownDashTimer() const { return CooldownDashTimer; }
	FORCEINLINE void SetOverworldChar(AOverworldPlayerCharacter* Char) { PlayerChar = Char; }
	FORCEINLINE EControllerScheme GetControllerScheme() const { return ControllerScheme; }
protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;
	// End PlayerController interface

	/* Movement System */
	void MovementForwardBackward(float Value);
	void MovementLeftRight(float Value);
	static void LookAtMouse();
	void ControllerTurnCharacter(float Value) const;
	void Zoom(float Value);
	
	//Get player jump from CharacterMovementComp.
	void StartPlayerJump();
	void StopPlayerJump();

	//Make Character Dash.
	void StartDash();
	void StopDash() const;
	
	//Character Input Disabler
	void SetCharacterInputDisable(const float TotalTimeSeconds);
	FORCEINLINE void EnableInputAgain() { EnableInput(this); }

	//User Interface
	void OpenInventory();
private:
	//Controller Scheme
	EControllerScheme ControllerScheme;
	
	//Casted to version of GetHUD.
	UPROPERTY()
	AOverworldHUD* OverworldHUD;
	
	UPROPERTY()
	AOverworldPlayerCharacter* PlayerChar;
	
	//Start of Input
	bool bInputPressed; // Input is bring pressed
	bool bIsTouch; // Is it a touch device
	float FollowTime; // For how long it has been pressed
	float TurnRate = 2.f; // Character controller rotation rate.
	//End of Input
	
	//Start of Zoom Input
	float ZoomMultiplier = 200.f;	// How fast the zoom is.
	float ZoomMin = 200.f;	// Min zoom in with the spring arm to overworld character.
	float ZoomMax = 1000;	// Max zoom out with the spring arm to overworld character.
	float ZoomDeltaTime;	//Literally just delta time from PlayerTick.
	float ZoomInterpSpeed = 9.f; // InterpSpeed for zoom.
	float TargetZoom = 500.f;
	//End of Zoom Input
	
	//Start of Dash
	float TotalDashTimer;	// Dash Reset Timer.
	float CooldownDashTimer = 5.f;	//Dash Cooldown timer.
	float DashPower = 3000;	// The power on which the character is launch on XY axis.
	float DashHeight = 200;	// The height at which the character is forced on the Z axis.a
	float DashStopTimer = 0.2f;	// The timer between the dash activating and the dash ending.
	bool bIsDashReady = false;	// Check to see if the Character Dash is Ready.
	//End of Dash

	/**
	 * @brief - This allows for instantly check of whether there is some element is true to disable
	 *			the ability to move the character. This also works as a false to disable the ability to
	 *			call keys that are already being used. TODO: This system probably needs to be replaced.
	 * @return - Return a boolean if one of the statements within the if statement is true, or false.
	 */
	bool CheckForDisableInputs() const;
};