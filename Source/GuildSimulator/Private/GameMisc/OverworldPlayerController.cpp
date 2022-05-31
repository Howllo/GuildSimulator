// Copyright (c) Astral Games. All right reserved.

#include "GameMisc/OverworldPlayerController.h"
#include <UserInterface/InventorySystem/ItemInformationBox.h>
#include "NiagaraComponent.h"
#include "GameFramework/Pawn.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Camera/CameraComponent.h"
#include "Character/OverworldPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/OverworldHUD.h"
#include "UserInterface/InventorySystem/InventorySlot.h"
#include "UserInterface/InventorySystem/ItemPopup.h"
#include "UserInterface/InventorySystem/OptionMenuWidget.h"
#include "UserInterface/InventorySystem/WidgetDrop.h"

//TODO: Detect the input.


AOverworldPlayerController::AOverworldPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AOverworldPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//Get Character and Particle Effects
	PlayerChar = Cast<AOverworldPlayerCharacter>(GetPawn());
	PlayerChar->ParticleComponent->SetAsset(DashParticleEffect);

	//Get cast version of HUD
	OverworldHUD = Cast<AOverworldHUD>(GetHUD());
 }

void AOverworldPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	
	//Smooth Zoom Camera
	if(!FMath::IsNearlyEqual(PlayerChar->GetCameraBoom()->TargetArmLength, TargetZoom, 0.5f))
	{
		const float CurrentZoom = FMath::FInterpTo(PlayerChar->GetCameraBoom()->TargetArmLength, TargetZoom,
			DeltaTime, ZoomInterpSpeed);
		PlayerChar->GetCameraBoom()->TargetArmLength = FMath::Clamp(CurrentZoom, ZoomMin, ZoomMax);
	}

	//TODO: Constantly check the last input of the player controller to set input systems.

	//Get Mouse Position
}

void AOverworldPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	
	//Option Menu
	InputComponent->BindAction("Inventory", IE_Pressed, this, &AOverworldPlayerController::OpenInventory);
	
	//Jump
	InputComponent->BindAction("Jump", IE_Pressed, this, &AOverworldPlayerController::StartPlayerJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AOverworldPlayerController::StopPlayerJump);

	//Dash
	InputComponent->BindAction("Dash", IE_Pressed, this, &AOverworldPlayerController::StartDash);

	//Movement
	InputComponent->BindAxis("Movement Up / Down", this, &AOverworldPlayerController::MovementForwardBackward);
	InputComponent->BindAxis("Movement Left / Right", this, &AOverworldPlayerController::MovementLeftRight);

	//Zoom
	InputComponent->BindAxis("Zoom In", this, &AOverworldPlayerController::Zoom);
}

// Characters Forward and Backwards movement.
void AOverworldPlayerController::MovementForwardBackward(float Value)
{
	if(Value == 0.0f || CheckForDisableInputs()) { return; }
	
	if(Value != 0.0f && PlayerChar != nullptr && GetPawn())
	{
		GetPawn()->AddMovementInput(PlayerChar->GetCharacterCamera()->GetForwardVector(), Value);
	}
}

// Character Side to Side movement.
void AOverworldPlayerController::MovementLeftRight(float Value)
{
	if(Value == 0.0f || CheckForDisableInputs()) { return; }
	
	if(Value != 0.0f && PlayerChar && GetPawn())
	{
		GetPawn()->AddMovementInput(PlayerChar->GetCharacterCamera()->GetRightVector(), Value);
	}
}

//Character mesh looking at the mouse cursor.
void AOverworldPlayerController::LookAtMouse()
{
	//DeprojectScreenPositionToWorld()
}

//Character control turn rate.
void AOverworldPlayerController::ControllerTurnCharacter(float Value) const
{
	GetPawn()->AddControllerYawInput(Value * TurnRate);
}

//Zoom in and Out.
void AOverworldPlayerController::Zoom(float Value)
{
	if(PlayerChar && Value != 0)
	{
		TargetZoom = FMath::Clamp(PlayerChar->GetCameraBoom()->TargetArmLength + ZoomMultiplier * Value, ZoomMin, ZoomMax);
	}
}


void AOverworldPlayerController::StartPlayerJump()
{
	if(CheckForDisableInputs()) { return; }
	
	if(PlayerChar)
	{
		PlayerChar->Jump();
	}
}

void AOverworldPlayerController::StopPlayerJump()
{
	if(CheckForDisableInputs()) { return; }
	
	if(PlayerChar)
	{
		PlayerChar->StopJumping();
	}
}

void AOverworldPlayerController::StartDash()
{
	if(CheckForDisableInputs()) { return; }
	
	if(GetWorld())
	{
		if(GetWorld()->GetTimeSeconds() < TotalDashTimer)
		{
			return;
		}
		bIsDashReady = true;
	
		if(PlayerChar && bIsDashReady)
		{
			bIsDashReady = false;
			PlayerChar->ParticleComponent->Activate();
			const float OriginalGroundFriction = PlayerChar->GetCharacterMovement()->GroundFriction;
			const float OriginalWalkingFriction = PlayerChar->GetCharacterMovement()->BrakingDecelerationWalking;
			const float OriginalBrakingFiction = PlayerChar->GetCharacterMovement()->BrakingFriction;
			
			PlayerChar->GetCharacterMovement()->GroundFriction = 0.0f;
			PlayerChar->GetCharacterMovement()->BrakingDecelerationWalking = 0.0f;
			PlayerChar->GetCharacterMovement()->BrakingFriction = 0.0f;
			PlayerChar->LaunchCharacter(FVector(PlayerChar->GetActorForwardVector().X * DashPower,
				PlayerChar->GetActorForwardVector().Y * DashPower, PlayerChar->GetActorForwardVector().Z + DashHeight),
				false, false);
			
			PlayerChar->GetCharacterMovement()->GroundFriction = OriginalGroundFriction;
			PlayerChar->GetCharacterMovement()->BrakingDecelerationWalking = OriginalWalkingFriction;
			PlayerChar->GetCharacterMovement()->BrakingFriction = OriginalBrakingFiction;

			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AOverworldPlayerController::StopDash,
				DashStopTimer, false);
			TotalDashTimer = GetWorld()->GetTimeSeconds() + CooldownDashTimer;
		}
	}
}

//Stop Dash movement based on DashTimer.
void AOverworldPlayerController::StopDash() const
{
	if(CheckForDisableInputs()) { return; }
	
	PlayerChar->GetCameraBoom()->bEnableCameraLag = true;
	PlayerChar->GetCameraBoom()->CameraLagSpeed = 9.f;
	PlayerChar->GetCharacterMovement()->StopMovementImmediately();

	FTimerHandle TimerHandler;
	GetWorld()->GetTimerManager().SetTimer(TimerHandler, [&]()
	{
		PlayerChar->GetCameraBoom()->bEnableCameraLag = false;
	}, 0.8f, false);
	PlayerChar->ParticleComponent->Deactivate();
}

void AOverworldPlayerController::SetCharacterInputDisable(const float TotalTimeSeconds)
{
	DisableInput(this);
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AOverworldPlayerController::EnableInputAgain,
		TotalTimeSeconds, false);
}

void AOverworldPlayerController::OpenInventory()
{
	UOptionMenuWidget* Options = OverworldHUD->GetOptionMenuWidget();
	
	if(!Options->IsVisible())
	{
		Options->SetVisibility(ESlateVisibility::Visible);
		PlayerChar->GetCharacterMovement()->StopMovementImmediately();
	} else
	{
		if(Options->GetWidgetDrop())
		{
			Options->GetWidgetDrop()->RemoveFromParent();
		}
		
		if(OverworldHUD->Popup)
		{
			OverworldHUD->Popup->RemoveFromParent();
			OverworldHUD->Popup = nullptr;
		}
		
		Options->SetVisibility(ESlateVisibility::Collapsed);
		Options->GetInfoBox()->SetVisibility(ESlateVisibility::Collapsed);
		PlayerChar->GetInventorySystem()->SetSelectedSlot(nullptr);
	}
}

bool AOverworldPlayerController::CheckForDisableInputs() const
{
	if(OverworldHUD->GetOptionMenuWidget()->IsVisible())
	{
		return true;
	}

	//Add more here
	return false;
}