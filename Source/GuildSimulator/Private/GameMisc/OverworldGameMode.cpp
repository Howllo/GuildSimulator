// Copyright (c) Astral Games. All right reserved.


#include "GameMisc/OverworldGameMode.h"
#include "GameMisc/OverworldPlayerController.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

void AOverworldGameMode::BeginPlay()
{
	Super::BeginPlay();
}

AOverworldGameMode::AOverworldGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AOverworldPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/GameInformation/BP_OverworldPlayer"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/Blueprints/GameInformation/BP_OverworldPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}

	static  ConstructorHelpers::FClassFinder<AHUD> PlayerHUDBPClass(TEXT("/Game/Blueprints/GameInformation/BP_OverworldHUD"));
	if(PlayerHUDBPClass.Class != nullptr)
	{
		HUDClass = PlayerHUDBPClass.Class;
	}
}

void AOverworldGameMode::PauseGame(bool bIsPaused)
{
	AOverworldPlayerController* PlayerController = Cast<AOverworldPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if(PlayerController)
	{
		PlayerController->SetPause(bIsPaused);
	}
}
