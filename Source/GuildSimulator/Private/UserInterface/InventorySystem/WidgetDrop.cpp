// Copyright (c) Astral Games. All right reserved.


#include "UserInterface/InventorySystem/WidgetDrop.h"
#include "Character/OverworldPlayerCharacter.h"
#include "Character/CharacterSubsystems/InventorySystem.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/OverworldHUD.h"
#include "UserInterface/InventorySystem/InventorySlot.h"
#include "UserInterface/InventorySystem/OptionMenuWidget.h"

UWidgetDrop::UWidgetDrop(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
}

void UWidgetDrop::UserNumberFunction()
{
	const AOverworldPlayerCharacter* PlayerCharacter = Cast<AOverworldPlayerCharacter>
		(UGameplayStatics::GetPlayerPawn(this, 0));
	const FString TempString = UserNumberInput->GetText().ToString();
	const int32 TempIntConfirm = FCString::Atoi(*TempString);
	const int32 NumberMax = FMath::Clamp(TempIntConfirm, 0, PlayerCharacter->GetInventorySystem()->GetSelectedSlot()->MainItem->Quantity);
	UserNumberInput->SetText(FText::FromString(FString::FromInt(NumberMax)));
}

void UWidgetDrop::ConfirmButtonFunction()
{
	const AOverworldPlayerCharacter* PlayerCharacter = Cast<AOverworldPlayerCharacter>
		(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	const FString TempString = UserNumberInput->GetText().ToString();
	const int32 TempIntConfirm = FCString::Atoi(*TempString);
	
	if(TempIntConfirm > 0)
	{
		PlayerCharacter->GetInventorySystem()->DropItem(PlayerCharacter->GetInventorySystem()->GetSelectedSlot()->MainItem, TempIntConfirm);
		UserNumberInput->SetText(FText::FromString("0"));
		PlayerCharacter->GetInventorySystem()->GetPlayerHUD()->GetOptionMenuWidget()->GetWidgetDrop()->RemoveFromParent();
	} else
	{
		UserNumberInput->SetText(FText::FromString("0"));
		PlayerCharacter->GetInventorySystem()->GetPlayerHUD()->GetOptionMenuWidget()->GetWidgetDrop()->RemoveFromParent();
	}
	PlayerCharacter->GetInventorySystem()->SetSelectedSlot(nullptr);
}

void UWidgetDrop::MinusButtonFunction()
{
	const AOverworldPlayerCharacter* PlayerCharacter = Cast<AOverworldPlayerCharacter>
		(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	const FString TempString = UserNumberInput->GetText().ToString();

	//Clamp the math 0 to quantity.
	const int32 TempNumber = FMath::Clamp(FCString::Atoi(*TempString) - 1, 0,
			PlayerCharacter->GetInventorySystem()->GetSelectedSlot()->MainItem->Quantity);
	
	UserNumberInput->SetText(FText::FromString(FString::FromInt(TempNumber)));
}

void UWidgetDrop::PlusButtonFunction()
{
	const AOverworldPlayerCharacter* PlayerCharacter = Cast<AOverworldPlayerCharacter>
		(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	const FString TempString = UserNumberInput->GetText().ToString();
	
	//Clamp the math 0 to quantity.
	const int32 TempNumber = FMath::Clamp(FCString::Atoi(*TempString) + 1, 0,
			PlayerCharacter->GetInventorySystem()->GetSelectedSlot()->MainItem->Quantity);
	
	UserNumberInput->SetText(FText::FromString(FString::FromInt(TempNumber)));
}

void UWidgetDrop::AllButtonFunction()
{
	const AOverworldPlayerCharacter* PlayerCharacter = Cast<AOverworldPlayerCharacter>
		(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	
	if(PlayerCharacter->GetInventorySystem()->GetSelectedSlot())
	{
		UserNumberInput->SetText(FText::FromString
        		(FString::FromInt(PlayerCharacter->GetInventorySystem()->GetSelectedSlot()->MainItem->Quantity)));
	}
}
