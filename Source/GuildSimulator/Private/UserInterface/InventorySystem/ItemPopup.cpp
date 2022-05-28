// Copyright (c) Astral Games. All right reserved.


#include "UserInterface/InventorySystem/ItemPopup.h"
#include "Character/OverworldPlayerCharacter.h"
#include "Character/CharacterSubsystems/InventorySystem.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/OverworldHUD.h"
#include "UserInterface/InventorySystem/InventorySlot.h"
#include "UserInterface/InventorySystem/OptionMenuWidget.h"


void UItemPopup::ButtonCalledUse()
{
	const AOverworldPlayerCharacter* PlayerCharacter = Cast<AOverworldPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	PlayerCharacter->GetInventorySystem()->GetSelectedSlot()->MainItem->OnUse();
	this->RemoveFromParent();
}

void UItemPopup::ButtonCalledDrop()
{ 
	const AOverworldPlayerCharacter* PlayerCharacter = Cast<AOverworldPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	this->RemoveFromParent();
	PlayerCharacter->GetInventorySystem()->GetPlayerHUD()->GetOptionMenuWidget()->DropAction();
}

void UItemPopup::ButtonCalledCancel()
{
	const AOverworldPlayerCharacter* PlayerCharacter = Cast<AOverworldPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	this->RemoveFromParent();
}
