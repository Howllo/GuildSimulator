// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OverworldHUD.generated.h"

class UOptionMenuWidget;

/**
 *	Overworld HUD holds all the User Widgets for the character. Every Widget that will be used will
 *	be created through HUD. This does not apply for sub-widget like inventory slots.
 *	
 */
UCLASS()
class GUILDSIMULATOR_API AOverworldHUD : public AHUD
{
	GENERATED_BODY()
public:
	AOverworldHUD();

	/**
	 * @brief 
	 * @return UUI_InventorySystem Widget
	 */
	UOptionMenuWidget* GetOptionMenuWidget();
protected:
	virtual void BeginPlay() override;
private:
	/* Pointer the primarily Option Menu Widget. */ 
	UPROPERTY(EditDefaultsOnly)
	UOptionMenuWidget* OptionMenuWidget;
	
	/* Inventory UI blueprint. */ 
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> BP_Inventory;
};
