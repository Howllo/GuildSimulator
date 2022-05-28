// Copyright (c) Astral Games. All right reserved.

#include "GameMisc/RaidPlayerController.h"
#include "NavigationSystem.h"
#include "GameFramework/Pawn.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Character/DefaultCharacterAI.h"
#include "Character/RaidPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/RaidHUD.h"

ARaidPlayerController::ARaidPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void ARaidPlayerController::BeginPlay()
{
	Super::BeginPlay();
	RaidHUD = Cast<ARaidHUD>(GetHUD());
	DefaultPlayerRaid = Cast<ARaidPlayerCharacter>(GetPawn());
}

void ARaidPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

}

void ARaidPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Selection", IE_Pressed, this, &ARaidPlayerController::SelectionPressed);
	InputComponent->BindAction("Selection", IE_Released, this, &ARaidPlayerController::SelectionReleased);

	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ARaidPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ARaidPlayerController::OnSetDestinationReleased);

	InputComponent->BindAxis("MoveForwardBack", this, &ARaidPlayerController::MoveForwardBackPlayerCamera);
	InputComponent->BindAxis("MoveSideToSide", this, &ARaidPlayerController::MoveLeftAndRightPlayerCamera);
	InputComponent->BindAxis("ZoomInAndOut", this, &ARaidPlayerController::ZoomInAndOut);
	
	// support touch devices 
	InputComponent->BindTouch(IE_Pressed, this, &ARaidPlayerController::OnTouchPressed);
	InputComponent->BindTouch(IE_Released, this, &ARaidPlayerController::OnTouchReleased);
}

void ARaidPlayerController::OnSetDestinationPressed()
{
	// We flag that the input is being pressed
	bInputPressed = true;
}

void ARaidPlayerController::OnSetDestinationReleased()
{
	// Player is no longer pressing the input
	bInputPressed = false;

	// If it was a short press
	if(FollowTime <= ShortPressThreshold)
	{
		if(SelectedActors.Num() > 0)
		{
			for(int32 i = 0; i < SelectedActors.Num(); i++)
			{
				FHitResult Hit;
				GetHitResultUnderCursor(ECC_Visibility, false, Hit);
				FVector MoveLocation = Hit.Location;
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(SelectedActors[i]->GetController(), MoveLocation);
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, FXCursor, MoveLocation, FRotator::ZeroRotator, FVector(1.f, 1.f, 1.f), true, true, ENCPoolMethod::None, true);
			}
		}
	}
}

void ARaidPlayerController::OnTouchPressed(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = true;
	OnSetDestinationPressed();
}

void ARaidPlayerController::OnTouchReleased(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	bIsTouch = false;
	OnSetDestinationReleased();
}

void ARaidPlayerController::SelectionPressed()
{
	if(RaidHUD)
	{
		RaidHUD->FirstPoint = RaidHUD->GetMousePos2D();
		RaidHUD->bStartSelecting = true;
	} else if(RaidHUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("DefaultHUD is a nullptr."));
	}
}

void ARaidPlayerController::SelectionReleased()
{
	if(RaidHUD)
	{
		RaidHUD->bStartSelecting = false;
		SelectedActors = RaidHUD->FoundActors;
	}
}

void ARaidPlayerController::MoveForwardBackPlayerCamera(float Value)
{
	if((GetPawn()->Controller != nullptr) && (Value != 0.0f))
	{
		GetPawn()->AddMovementInput(GetPawn()->GetActorForwardVector(), Value* 1.2f);
	}
}

void ARaidPlayerController::MoveLeftAndRightPlayerCamera(float Value)
{
	if((GetPawn()->Controller != nullptr) && (Value != 0.0f))
	{
		GetPawn()->AddMovementInput(GetPawn()->GetActorRightVector(), Value * 1.2f);
	}
}

void ARaidPlayerController::ZoomInAndOut(float Value)
{
    if(Value == 0.0f) return;
	const float NewCameraLength = DefaultPlayerRaid->SpringArmComp->TargetArmLength + Value * ZoomSpeed;
	DefaultPlayerRaid->SpringArmComp->TargetArmLength = FMath::Clamp(NewCameraLength, MinZoom, MaxZoom);
}