// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OverworldGameMode.generated.h"

class ADefaultCharacterAI;

/**
 * 
 */
UCLASS()
class GUILDSIMULATOR_API AOverworldGameMode : public AGameModeBase
{
	GENERATED_BODY()
	virtual  void BeginPlay() override;
public:
	AOverworldGameMode();

	void PauseGame(bool bIsPaused);
	
protected:
	UPROPERTY()
	ADefaultCharacterAI* PlayerCharacter;
};
