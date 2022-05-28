// Copyright (c) Astral Games. All right reserved.


#include "UserInterface/OverworldHUD.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/InventorySystem/ItemInformationBox.h"
#include "UserInterface/InventorySystem/OptionMenuWidget.h"
#include "Components/UniformGridPanel.h"

AOverworldHUD::AOverworldHUD()
{
	//Inventory Inventory UI
	static ConstructorHelpers::FClassFinder<UOptionMenuWidget> Inventory_UI(TEXT("/Game/Blueprints/UserInterface/Inventory/WBP_InventorySystem"));
	if(Inventory_UI.Succeeded())
	{
		BP_Inventory = Inventory_UI.Class;
	}
}

void AOverworldHUD::BeginPlay()
{
	Super::BeginPlay();

	//Setup OptionMenuWidget
	if(BP_Inventory)
	{
		OptionMenuWidget = CreateWidget<UOptionMenuWidget>(UGameplayStatics::GetPlayerController(GetWorld(),
			0), BP_Inventory);
		if(OptionMenuWidget)
		{
			OptionMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
			OptionMenuWidget->AddToViewport();

			//Set Defaults
			OptionMenuWidget->OnMaterialTab();
			OptionMenuWidget->GetConsumableGridPanel()->SetVisibility(ESlateVisibility::Collapsed);
			OptionMenuWidget->GetArmorGridPanel()->SetVisibility(ESlateVisibility::Collapsed);
			OptionMenuWidget->GetWeaponGridPanel()->SetVisibility(ESlateVisibility::Collapsed);
			OptionMenuWidget->GetOutfitGridPanel()->SetVisibility(ESlateVisibility::Collapsed);
			OptionMenuWidget->GetCraftedGridPanel()->SetVisibility(ESlateVisibility::Collapsed);

			//Information Box
			OptionMenuWidget->GetInfoBox()->OnStatsClick();
			OptionMenuWidget->GetInfoBox()->SetAllCollapse();
			OptionMenuWidget->GetInfoBox()->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

UOptionMenuWidget* AOverworldHUD::GetOptionMenuWidget()
{
	return OptionMenuWidget;
}
