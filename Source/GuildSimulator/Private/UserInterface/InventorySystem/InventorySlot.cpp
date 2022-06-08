// Copyright (c) Astral Games. All right reserved.

#include "UserInterface/InventorySystem/InventorySlot.h"
#include "Blueprint/WidgetTree.h"
#include "Character/OverworldPlayerCharacter.h"
#include "Character/CharacterSubsystems/CharacterStatistic.h"
#include "Components/Button.h"
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
#include "UserInterface/InventorySystem/InventoryUI.h"

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

	AOverworldHUD* HUD = Cast<AOverworldHUD>(UGameplayStatics::GetPlayerController(this,0)->GetHUD());
	AOverworldPlayerCharacter* PlayerCharacter = Cast<AOverworldPlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	const AOverworldPlayerController* PlayerController = Cast<AOverworldPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	UInventorySlot* SelectedSlot = PlayerCharacter->GetInventorySystem()->GetSelectedSlot();
	UItemInformationBox* ResultsInfoBox = HUD->GetOptionMenuWidget()->GetInfoBox();
	UCharacterStatistic* CharacterStats = PlayerCharacter->GetCharStats();
	
	// Start of Selection
	if(SelectedSlot != nullptr)
	{
		if(SelectedSlot->bSelected)
		{
			SelectedSlot->bSelected = false;
			SelectedSlot->BackgroundRarity->SetBrushFromTexture(SelectedSlot->MainItem->BackgroundRarity);
		}
	}
	
	if(!bSelected)
	{
		PlayerCharacter->GetInventorySystem()->SetSelectedSlot(this);
		BackgroundRarity->SetBrushFromTexture(MainItem->BackgroundRaritySelected);
		bSelected = true;
	}
	// End of Selection

	// Set Result Info Box
	ResultsInfoBox->ButtonHorizontalBox->SetVisibility(ESlateVisibility::Collapsed);
	ResultsInfoBox->VerticalBox->SetVisibility(ESlateVisibility::Collapsed);
	ResultsInfoBox->ItemDescription->SetVisibility(ESlateVisibility::Visible);
	ResultsInfoBox->ItemName->SetText(MainItem->ItemName);
	ResultsInfoBox->ItemDescription->SetText(MainItem->ItemDescription);
	ResultsInfoBox->ItemIcon->SetBrushFromTexture(MainItem->ItemIcon);
	ResultsInfoBox->SetVisibility(ESlateVisibility::Visible);
	
	// Armor and Weapon
	auto Child = ResultsInfoBox->VerticalBox->GetAllChildren();
	ResultsInfoBox->VerticalBox->ClearChildren();
	for(int32 i = 0; i < Child.Num(); i++)
	{
		Child[i]->RemoveFromParent();
		Child[i]->MarkAsGarbage();
	}
	ResultsInfoBox->VerticalBox->ClearChildren();
	
	if(MainItem->ItemType == IType_Armor  && MainItem->ItemStats || MainItem->ItemType == IType_Weapon && MainItem->ItemStats)
	{
		ResultsInfoBox->ButtonHorizontalBox->SetVisibility(ESlateVisibility::Visible);
		ResultsInfoBox->ItemDescription->SetVisibility(ESlateVisibility::Collapsed);

		// Check Durability.
		if(MainItem->ItemStats->CharacterStatsMap[ECT_TotalDurability] != 0)
		{
			UTextBlock* HoldBlock = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
			ResultsInfoBox->VerticalBox->AddChildToVerticalBox(HoldBlock);
			HoldBlock->SetText(FText::FromString(CharacterStats->StatsFText.Find(ECT_TotalDurability)->ToString()
				+ FString::FromInt( *MainItem->ItemStats->CharacterStatsMap.Find(ECT_CurrentDurability))
				+ " / " + FString::FromInt(*MainItem->ItemStats->CharacterStatsMap.Find(ECT_TotalDurability))));
		}

		// Set Stats Box
		for(int32 i = ECT_NONE; i != ECT_Last; i++)
		{
			UTextBlock* Block;
			const ECharacterStats CharacterEnum = static_cast<ECharacterStats>(i);
			
			if(i == ECT_GlobalCooldown || i == ECT_TotalDurability || i == ECT_CurrentDurability)
				break;
			
			if(MainItem->ItemStats->CharacterStatsMap.Find(CharacterEnum) != nullptr)
			{
				Block = WidgetTree->ConstructWidget<UTextBlock>(UTextBlock::StaticClass());
				ResultsInfoBox->VerticalBox->AddChildToVerticalBox(Block);
				
				if( CharacterEnum != ECT_TotalDurability )
				{
					Block->SetText(FText::FromString(CharacterStats->StatsFText.Find(CharacterEnum)->ToString()
						+ FString::FromInt(*MainItem->ItemStats->CharacterStatsMap.Find(CharacterEnum))));
				}
			}
		}
	}

	//TODO: Add Consumable.
	// End of Result Box

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
	// End of Widget creation

	HUD->Popup = PopupInfo;
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
	const EItemType IType = MainItem->ItemType;
	
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

	PopupInfo->SlotOne->SetVisibility(ESlateVisibility::Collapsed);
	PopupInfo->SlotTwo->SetVisibility(ESlateVisibility::Collapsed);
	PopupInfo->ItemDrop->SetVisibility(ESlateVisibility::Visible);
	PopupInfo->ItemCancel->SetVisibility(ESlateVisibility::Visible);
}
#undef LOCTEXT_NAMESPACE