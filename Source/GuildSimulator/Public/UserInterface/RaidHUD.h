// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RaidHUD.generated.h"

class ARaidGameMode;
class ADefaultCharacterAI;
class ARaidPlayerCharacter;

/**
 * 
 */
UCLASS()
class GUILDSIMULATOR_API ARaidHUD : public AHUD
{
	GENERATED_BODY()
public:
	FVector2D FirstPoint;
	FVector2D CurrentPoint;
	FVector2D GetMousePos2D() const;
	bool bStartSelecting;

	UPROPERTY()
	ARaidGameMode* GameMode;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	ARaidPlayerCharacter* GetRaidPlayer;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<ADefaultCharacterAI*> FoundActors;
	
	//This is Tick()
	virtual void  DrawHUD() override;
protected:
	virtual void BeginPlay() override;
	
};
