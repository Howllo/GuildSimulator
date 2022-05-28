// Copyright (c) Astral Games. All right reserved.

#include "UserInterface/InventorySystem/InventorySlot.h"
#include "Character/OverworldPlayerCharacter.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "GameMisc/GuildSimEnums.h"
#include "GameMisc/OverworldPlayerController.h"
#include "GameMisc/SingleClassCharStats.h"
#include "GameMisc/Item/Item.h"
#include "Kismet/GameplayStatics.h"
#include "UserInterface/OverworldHUD.h"
#include "UserInterface/InventorySystem/ItemInformationBox.h"
#include "UserInterface/InventorySystem/ItemPopup.h"
#include "UserInterface/InventorySystem/OptionMenuWidget.h"

#define LOCTEXT_NAMESPACE "PopupButtonText"

UInventorySlot::UInventorySlot(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UItemPopup> ItemPopup(TEXT("/Game/Blueprints/UserInterface/Inventory/WBP_Popup"));
	if(ItemPopup.Succeeded())
	{
		BP_ItemPopup = ItemPopup.Class;
	}
}

void UInventorySlot::OnSlotClicked()
{
	if(!MainItem) return;
	
	bSelected = true;
	AOverworldHUD* HUD = Cast<AOverworldHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD());
	const AOverworldPlayerCharacter* PlayerCharacter = Cast<AOverworldPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	const AOverworldPlayerController* PlayerController = Cast<AOverworldPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UInventorySlot* SelectedSlot = PlayerCharacter->GetInventorySystem()->GetSelectedSlot();
	UItemInformationBox* ResultsInfoBox = HUD->GetOptionMenuWidget()->GetInfoBox();
	
	// Popup Widget Creation.
	PopupWidget();

	// Set Popup Buttons
	ChangePopupButtons();
	
	if(!PopupInfo->IsInViewport())
		bIsActive = false;
	
	// Set Popup
	if(!bIsActive)
	{
		float PosX, PosY;
		PlayerController->GetMousePosition(PosX, PosY);
		PopupInfo->SetPositionInViewport(FVector2D(PosX, PosY));
		bIsActive = true;
	}
	
	// Start of Selection
	if(SelectedSlot != nullptr)
	{
		if(SelectedSlot->bSelected)
		{
			SelectedSlot->bSelected = false;
			SelectedSlot->BackgroundRarity->SetBrushFromTexture(SelectedSlot->MainItem->BackgroundRarity);
		}
	}
	
	if(bSelected)
	{
		PlayerCharacter->GetInventorySystem()->SetSelectedSlot(this);
		BackgroundRarity->SetBrushFromTexture(MainItem->BackgroundRaritySelected);
	}
	// End of Selection
	
	ResultsInfoBox->ButtonHorizontalBox->SetVisibility(ESlateVisibility::Collapsed);
	ResultsInfoBox->VerticalBox->SetVisibility(ESlateVisibility::Collapsed);
	ResultsInfoBox->ItemDescription->SetVisibility(ESlateVisibility::Visible);
	ResultsInfoBox->ItemName->SetText(FText::FromString(MainItem->ItemName.ToString()));
	ResultsInfoBox->ItemDescription->SetText(FText::FromString(MainItem->ItemDescription.ToString()));
	ResultsInfoBox->ItemIcon->SetBrushFromTexture(MainItem->ItemIcon);
	ResultsInfoBox->SetVisibility(ESlateVisibility::Visible);

	// Armor and Weapon
	if(MainItem->ItemType == IType_Armor  && MainItem->CharStats || MainItem->ItemType == IType_Weapon && MainItem->CharStats){
		ResultsInfoBox->ButtonHorizontalBox->SetVisibility(ESlateVisibility::Visible);
		ResultsInfoBox->ItemDescription->SetVisibility(ESlateVisibility::Collapsed);

		if(MainItem->CharStats->TotalDurability != 0)
		{
			ResultsInfoBox->Durability->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->Durability->SetText(FText::FromString("Durability: "
				+ FString::FromInt(MainItem->CharStats->CurrentDurability) + " / "
				+ FString::FromInt(MainItem->CharStats->TotalDurability)));
		}
		
		if(MainItem->CharStats->BasePhysicalDamage != 0)
		{
			ResultsInfoBox->BasePhysicalDamage->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->BasePhysicalDamage->SetText
			(FText::FromString("Physical Damage: " + FString::FromInt(MainItem->CharStats->BasePhysicalDamage)));
		}

		if(MainItem->CharStats->TotalGeneralDamage != 0)
		{
			ResultsInfoBox->TotalGeneralDamage->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->TotalGeneralDamage->SetText
				(FText::FromString("General Damage: " +  FString::FromInt(MainItem->CharStats->TotalGeneralDamage)));
		}

		if(MainItem->CharStats->TotalFrostDamage != 0)
		{
			ResultsInfoBox->TotalFrostDamage->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->TotalFrostDamage->SetText
				(FText::FromString("Frost Damage " + FString::FromInt(MainItem->CharStats->TotalFrostDamage)));
		}

		if(MainItem->CharStats->TotalFireDamage != 0)
		{
			ResultsInfoBox->TotalFireDamage->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->TotalFireDamage->SetText 
				(FText::FromString("Fire Damage: " + FString::FromInt(MainItem->CharStats->TotalFireDamage)));
		}
		
		if(MainItem->CharStats->TotalEarthDamage != 0)
		{
			ResultsInfoBox->TotalEarthDamage->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->TotalEarthDamage->SetText 
				(FText::FromString("Earth Damage: " + FString::FromInt(MainItem->CharStats->TotalEarthDamage)));
		}

		if(MainItem->CharStats->TotalWaterDamage != 0)
		{
			ResultsInfoBox->TotalWaterDamage->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->TotalWaterDamage->SetText
				(FText::FromString("Water Damage: " + FString::FromInt(MainItem->CharStats->TotalWaterDamage)));
		}

		if(MainItem->CharStats->TotalDarkDamage != 0)
		{
			ResultsInfoBox->TotalDarkDamage->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->TotalDarkDamage->SetText
				(FText::FromString("Dark Damage: " + FString::FromInt(MainItem->CharStats->TotalDarkDamage)));
		}

		if(MainItem->CharStats->TotalLightDamage != 0)
		{
			ResultsInfoBox->TotalLightDamage->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->TotalLightDamage->SetText
				(FText::FromString("Light Damage: " + FString::FromInt(MainItem->CharStats->TotalLightDamage)));
		}
		
		if(MainItem->CharStats->TotalArcaneDamage != 0)
		{
			ResultsInfoBox->TotalArcaneDamage->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->TotalArcaneDamage->SetText
				(FText::FromString("Arcane Damage: " + FString::FromInt(MainItem->CharStats->TotalArcaneDamage)));
		}

		if(MainItem->CharStats->IncreasedHealthPoints != 0)
		{
			ResultsInfoBox->IncreasedHealthPoints->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->IncreasedHealthPoints->SetText
				(FText::FromString("Health Added: " + FString::FromInt(MainItem->CharStats->IncreasedHealthPoints)));
		}
		
		if(MainItem->CharStats->IncreasedManaPoints != 0)
		{
			ResultsInfoBox->IncreasedManaPoints->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->IncreasedManaPoints->SetText
				(FText::FromString("Mana Added: " + FString::FromInt(MainItem->CharStats->IncreasedManaPoints)));
		}

		if(MainItem->CharStats->AttackPower != 0)
		{
			ResultsInfoBox->AttackPower->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->AttackPower->SetText
				(FText::FromString("Attack Power: " + FString::FromInt(MainItem->CharStats->AttackPower)));
		}

		if(MainItem->CharStats->MagicPower != 0)
		{
			ResultsInfoBox->MagicPower->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->MagicPower->SetText
				(FText::FromString("Magic Power: " + FString::FromInt(MainItem->CharStats->MagicPower)));
		}

		if(MainItem->CharStats->CriticalHitChance != 0)
		{
			ResultsInfoBox->CriticalHitChance->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->CriticalHitChance->SetText
				(FText::FromString("Critical Chance: " + FString::FromInt(MainItem->CharStats->CriticalHitChance)));
		}

		if(MainItem->CharStats->SkillSpeed != 0)
		{
			ResultsInfoBox->SkillSpeed->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->SkillSpeed->SetText
				(FText::FromString("Skill Speed: " + FString::FromInt(MainItem->CharStats->SkillSpeed)));
		}

		if(MainItem->CharStats->SpellSpeed != 0)
		{
			ResultsInfoBox->SpellSpeed->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->SpellSpeed->SetText
				(FText::FromString("Spell Speed: " + FString::FromInt(MainItem->CharStats->SpellSpeed)));
		}

		if(MainItem->CharStats->PhysicalDefense != 0)
		{
			ResultsInfoBox->PhysicalDefense->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->PhysicalDefense->SetText
				(FText::FromString("Physical Defense: " + FString::FromInt(MainItem->CharStats->PhysicalDefense)));
		}

		if(MainItem->CharStats->MagicalDefense != 0)
		{
			ResultsInfoBox->MagicalDefense->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->MagicalDefense->SetText
				(FText::FromString("Magical Defense: " + FString::FromInt(MainItem->CharStats->MagicalDefense)));
		}

		if(MainItem->CharStats->FrostResistance != 0)
		{
			ResultsInfoBox->FrostResistance->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->FrostResistance->SetText
				(FText::FromString("Frost Resistance: " + FString::FromInt(MainItem->CharStats->FrostResistance)));
		}

		if(MainItem->CharStats->FireResistance != 0)
		{
			ResultsInfoBox->FireResistance->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->FireResistance->SetText 
				(FText::FromString("Fire Resistance: " + FString::FromInt(MainItem->CharStats->FireResistance)));
		}

		if(MainItem->CharStats->WaterResistance != 0)
		{
			ResultsInfoBox->WaterResistance->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->WaterResistance->SetText
				(FText::FromString("Water Resistance: " + FString::FromInt(MainItem->CharStats->WaterResistance)));
		}

		if(MainItem->CharStats->EarthResistance != 0)
		{
			ResultsInfoBox->EarthResistance->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->EarthResistance->SetText
				(FText::FromString("Earth Resistance: " + FString::FromInt(MainItem->CharStats->EarthResistance)));
		}

		if(MainItem->CharStats->LightResistance != 0)
		{
			ResultsInfoBox->LightResistance->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->LightResistance->SetText
				(FText::FromString("Light resistance: " + FString::FromInt(MainItem->CharStats->LightResistance)));
		}

		if(MainItem->CharStats->DarkResistance != 0)
		{
			ResultsInfoBox->DarkResistance->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->DarkResistance->SetText
				(FText::FromString("Dark Resistance: " + FString::FromInt(MainItem->CharStats->DarkResistance)));
		}
		if(MainItem->CharStats->ArcaneResistance != 0)
		{
			ResultsInfoBox->ArcaneResistance->SetVisibility(ESlateVisibility::Visible);
			ResultsInfoBox->ArcaneResistance->SetText
				(FText::FromString("Arcane Resistance: " + FString::FromInt(MainItem->CharStats->ArcaneResistance)));
		}
	}

	//TODO: Add Consumable.
}

void UInventorySlot::SetSlot()
{
	if(!MainItem) return;
	
	//Set Stars Rating
	if(MainItem->StarCount == IEC_One)
	{
		StarOne->SetVisibility(ESlateVisibility::Visible);
		StarTwo->SetVisibility(ESlateVisibility::Collapsed);
		StarThree->SetVisibility(ESlateVisibility::Collapsed);
	} else if(MainItem->StarCount == IEC_Two)
	{
		StarOne->SetVisibility(ESlateVisibility::Visible);
		StarTwo->SetVisibility(ESlateVisibility::Visible);
		StarThree->SetVisibility(ESlateVisibility::Collapsed);
	} else
	{
		StarOne->SetVisibility(ESlateVisibility::Visible);
		StarTwo->SetVisibility(ESlateVisibility::Visible);
		StarThree->SetVisibility(ESlateVisibility::Visible);
	}
		
	InformationText->SetText(FText::FromString(FString::FromInt(MainItem->Quantity)));
	ItemIcon->SetBrushFromTexture(MainItem->ItemIcon);

	// Set icon for resistance type.
	if(MainItem->ResistanceType != nullptr)
	{
		ResistanceType->SetBrushFromTexture(MainItem->ResistanceType);
	}
	else
	{
		ResistanceType->SetVisibility(ESlateVisibility::Collapsed);
	}

	//Set Upgrade Icon
	if(MainItem->ItemUpgradeIcon != nullptr)
	{
		UpgradedIcon->SetBrushFromTexture(MainItem->ItemUpgradeIcon);
	} else
	{
		UpgradedIcon->SetVisibility(ESlateVisibility::Collapsed);	
	}
		
	BackgroundRarity->SetBrushFromTexture(MainItem->BackgroundRarity);
}

UItemPopup* UInventorySlot::GetPopup()
{
	return PopupInfo;
}

bool UInventorySlot::GetIsActive()
{
	return bIsActive;
}

void UInventorySlot::PopupWidget()
{
	if(!PopupInfo)
	{
		PopupInfo = CreateWidget<UItemPopup>(this, BP_ItemPopup);
	}
	
	if(!PopupInfo->IsInViewport())
	{
		PopupInfo->AddToViewport(6);
	}
}

void UInventorySlot::ChangePopupButtons() const
{
	if(!PopupInfo) return;

	const FText TextEquip = NSLOCTEXT("PopupButtonText", "ItemEquip", "Equip");
	const FText TextEat = NSLOCTEXT("PopupButtonText", "ItemEat", "Eat");
	const FText TextUse = NSLOCTEXT("PopupButtonText", "ItemUse", "Use");
	const ItemType IType = MainItem->ItemType;
	
	if(IType == IType_Armor || IType == IType_Weapon)
	{
		PopupInfo->UseText->SetText(TextEquip);
		PopupInfo->UseText->SetVisibility(ESlateVisibility::Visible);
	}

	if(IType == IType_Consumable)
	{
		PopupInfo->UseText->SetText(TextEat);
		PopupInfo->UseText->SetVisibility(ESlateVisibility::Visible);
	}

	if(IType == IType_Material)
	{
		PopupInfo->UseText->SetText(TextUse);
		PopupInfo->UseText->SetVisibility(ESlateVisibility::Collapsed);
	}
}
#undef LOCTEXT_NAMESPACE
