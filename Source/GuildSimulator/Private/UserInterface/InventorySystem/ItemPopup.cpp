// Copyright (c) Astral Games. All right reserved.


#include "UserInterface/InventorySystem/ItemPopup.h"
#include "Character/OverworldPlayerCharacter.h"
#include "Character/CharacterSubsystems/EquipmentSystem.h"
#include "Character/CharacterSubsystems/InventorySystem.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "GameMisc/SingleClassCharStats.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/OverworldHUD.h"
#include "UserInterface/InventorySystem/InventorySlot.h"
#include "UserInterface/InventorySystem/ItemInformationBox.h"
#include "UserInterface/InventorySystem/InventoryUI.h"

#define LOCTEXT_NAMESPACE "SlotText"
void UItemPopup::ButtonCalledUse()
{
	if(!PlayerCharacter)
		PlayerCharacter = Cast<AOverworldPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	UItem* Item = PlayerCharacter->GetInventorySystem()->GetSelectedSlot()->MainItem;

	if(!Item)
		return;
	
	const FText RingSlotOneText = NSLOCTEXT("SlotText", "RingSlotOne", "Ring Slot 1");
	const FText RingSlotTwoText = NSLOCTEXT("SlotText", "RingSlotTwo", "Ring Slot 2");
	const FText TrinketSlotOneText = NSLOCTEXT("SlotText", "TrinketSlotOne", "Trinket Slot 1");
	const FText TrinketSlotTwoText = NSLOCTEXT("SlotText", "TrinketSlotTwo", "Trinket Slot 2");
	
	if(Item->ItemStats)
	{
		if(Item->ItemStats->ArmorEnum == EAT_Ring)
		{
			SlotOneText->SetText(RingSlotOneText);
			SlotTwoText->SetText(RingSlotTwoText);
			SlotOne->SetVisibility(ESlateVisibility::Visible);
			SlotTwo->SetVisibility(ESlateVisibility::Visible);
			
			UseText->SetVisibility(ESlateVisibility::Collapsed);
			ItemDrop->SetVisibility(ESlateVisibility::Collapsed);
			ItemCancel->SetVisibility(ESlateVisibility::Collapsed);
		} else
		{
			SlotOneText->SetText(TrinketSlotOneText);
			SlotTwoText->SetText(TrinketSlotTwoText);
			SlotOne->SetVisibility(ESlateVisibility::Visible);
			SlotTwo->SetVisibility(ESlateVisibility::Visible);
			
			UseText->SetVisibility(ESlateVisibility::Collapsed);
			ItemDrop->SetVisibility(ESlateVisibility::Collapsed);
			ItemCancel->SetVisibility(ESlateVisibility::Collapsed);
		}
	} else
	{
		Item->OnUse();
		RemoveFromParent();
	}
}

void UItemPopup::ButtonCalledDrop()
{
	if(!PlayerCharacter)
		PlayerCharacter = Cast<AOverworldPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	RemoveFromParent();
	PlayerCharacter->GetInventorySystem()->GetPlayerHUD()->GetOptionMenuWidget()->DropAction();
}

void UItemPopup::ButtonCalledCancel()
{
	RemoveFromParent();
}

void UItemPopup::ButtonCalledSlotOne()
{
	if(!PlayerCharacter)
		PlayerCharacter = Cast<AOverworldPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	UItem* Item = PlayerCharacter->GetInventorySystem()->GetSelectedSlot()->MainItem;
	AOverworldHUD* HUD = Cast<AOverworldHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	UItemInformationBox* ResultsInfoBox = HUD->GetOptionMenuWidget()->GetInfoBox();
	
	if(Item->ItemStats->ArmorEnum == EAT_Ring)
	{
		PlayerCharacter->GetPlayerEquipment()->SetPlayerRing(Item, 1);
		ResultsInfoBox->SetVisibility(ESlateVisibility::Collapsed);
		RemoveFromParent();
		return;
	}

	if(Item->ItemStats->ArmorEnum == EAT_Trinket)
	{
		PlayerCharacter->GetPlayerEquipment()->SetPlayerTrinket(Item, 1);
		ResultsInfoBox->SetVisibility(ESlateVisibility::Collapsed);
		RemoveFromParent();
	}
}

void UItemPopup::ButtonCalledSlotTwo()
{
	if(!PlayerCharacter)
		PlayerCharacter = Cast<AOverworldPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	UItem* Item = PlayerCharacter->GetInventorySystem()->GetSelectedSlot()->MainItem;
	AOverworldHUD* HUD = Cast<AOverworldHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	UItemInformationBox* ResultsInfoBox = HUD->GetOptionMenuWidget()->GetInfoBox();
	
	if(Item->ItemStats->ArmorEnum == EAT_Ring)
	{
		PlayerCharacter->GetPlayerEquipment()->SetPlayerRing(Item, 2);
		ResultsInfoBox->SetVisibility(ESlateVisibility::Collapsed);
		RemoveFromParent();
		return;
	}

	if(Item->ItemStats->ArmorEnum == EAT_Trinket)
	{
		PlayerCharacter->GetPlayerEquipment()->SetPlayerTrinket(Item, 2);
		ResultsInfoBox->SetVisibility(ESlateVisibility::Collapsed);
		RemoveFromParent();
	}
}
#undef  LOCTEXT_NAMESPACE
