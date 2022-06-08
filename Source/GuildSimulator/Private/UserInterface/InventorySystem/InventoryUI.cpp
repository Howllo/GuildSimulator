// Copyright (c) Astral Games. All right reserved.

#include "UserInterface/InventorySystem/InventoryUI.h"
#include "UserInterface/InventorySystem/WidgetDrop.h"
#include "Character/OverworldPlayerCharacter.h"
#include "Components/Button.h"
#include "Components/UniformGridPanel.h"
#include "Kismet/GameplayStatics.h"
#include "GameMisc/GuildSimEnums.h"
#include "UserInterface/InventorySystem/InventorySlot.h"
#include "UserInterface/InventorySystem/NoItem.h"
#include "UserInterface/InventorySystem/ItemInformationBox.h"

UInventoryUI::UInventoryUI(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UInventorySlot> InvSlot(TEXT("/Game/Blueprints/UserInterface/Inventory/WBP_InventorySlot"));
	if(InvSlot.Succeeded())
	{
		BP_Slots = InvSlot.Class;
	}

	//Inventory No Item Slot
	static ConstructorHelpers::FClassFinder<UNoItem> InventoryNoItemUI(TEXT("/Game/Blueprints/UserInterface/Inventory/WBP_NoItem"));
	if(InventoryNoItemUI.Succeeded())
	{
		BP_NoItemInventory = InventoryNoItemUI.Class;
	}

	//Drop item UI
	static ConstructorHelpers::FClassFinder<UWidgetDrop> DropWidget(TEXT("/Game/Blueprints/UserInterface/Inventory/WBP_ItemDelete"));
	if(DropWidget.Succeeded())
	{
		BP_WidgetDrop = DropWidget.Class;
	}
}

UUniformGridPanel* UInventoryUI::GetMaterialGridPanel()
{
	return MatInventoryGrid;
}

UUniformGridPanel* UInventoryUI::GetConsumableGridPanel()
{
	return ConInventoryGrid;
}

UUniformGridPanel* UInventoryUI::GetArmorGridPanel()
{
	return ArmorInventoryGrid;
}

UUniformGridPanel* UInventoryUI::GetWeaponGridPanel()
{
	return WeaponInventoryGrid;
}

UUniformGridPanel* UInventoryUI::GetOutfitGridPanel()
{
	return OutfitInventoryGrid;
}

UUniformGridPanel* UInventoryUI::GetCraftedGridPanel()
{
	return CraftedInventoryGrid;
}

UItemInformationBox* UInventoryUI::GetInfoBox()
{
	return InformationBox;
}

void UInventoryUI::OnMaterialTab()
{
	ButtonSetup(MaterialTab, MatInventoryGrid);
}

void UInventoryUI::OnConsumableTab()
{
	ButtonSetup(ConsumableTab, ConInventoryGrid);
}

void UInventoryUI::OnArmorTab()
{
	ButtonSetup(ArmorTab, ArmorInventoryGrid);
}

void UInventoryUI::OnWeaponTab()
{
	ButtonSetup(WeaponTab, WeaponInventoryGrid);
}

void UInventoryUI::OnOutfitTab()
{
	ButtonSetup(OutfitTab, OutfitInventoryGrid);
}

void UInventoryUI::OnCraftedTab()
{
	ButtonSetup(CraftedTab, CraftedInventoryGrid);
}

void UInventoryUI::ButtonSetup(UButton* NewLastButton, UUniformGridPanel* NewPanel)
{
	if(!NewLastButton || !NewPanel) return;
	
	//New Button Settings
	NewLastButton->SetIsEnabled(false);
	NewPanel->SetVisibility(ESlateVisibility::Visible);
	
	//Last Button Settings
	if(LastButton != nullptr)
	{
		LastButton->bIsEnabled = true;
		LastButton->SetIsEnabled(true);
	}
	LastButton = NewLastButton;

	//Panel
	if(LastPanel != nullptr)
	{
		LastPanel->SetVisibility(ESlateVisibility::Collapsed);
	}
	LastPanel = NewPanel;

	InformationBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UInventoryUI::UpdateInventorySlots(TArray<UItem*>& Items, EItemType Type) const
{
	TArray<UWidget*> Child;
	int Row = 0, Col = 0;

	switch (Type)
	{
		case IType_Material:
			Child = MatInventoryGrid->GetAllChildren();
			MatInventoryGrid->ClearChildren();
			for(int32 i = 0; i < Child.Num(); i++)
			{
				Child[i]->RemoveFromParent();
				Child[i]->MarkAsGarbage();
			}
			MatInventoryGrid->ClearChildren();
			break;
		case IType_Consumable:
			Child = ConInventoryGrid->GetAllChildren();

			for(int32 i = 0; i < Child.Num(); i++)
			{
				Child[i]->RemoveFromParent();
				Child[i]->MarkAsGarbage();
			}
			ConInventoryGrid->ClearChildren();
			break;
		case IType_Armor:
			Child = ArmorInventoryGrid->GetAllChildren();

			for(int32 i = 0; i < Child.Num(); i++)
			{
				Child[i]->RemoveFromParent();
				Child[i]->MarkAsGarbage();
			}
			ArmorInventoryGrid->ClearChildren();
			break;
		case IType_Weapon:
			Child = WeaponInventoryGrid->GetAllChildren();

			for(int32 i = 0; i < Child.Num(); i++)
			{
				Child[i]->RemoveFromParent();
				Child[i]->MarkAsGarbage();
			}
			WeaponInventoryGrid->ClearChildren();
			break;
		case IType_Outfit:
			Child = OutfitInventoryGrid->GetAllChildren();

			for(int32 i = 0; i < Child.Num(); i++)
			{
				Child[i]->RemoveFromParent();
				Child[i]->MarkAsGarbage();
			}
			OutfitInventoryGrid->ClearChildren();
			break;
		case IType_Crafted:
			Child = CraftedInventoryGrid->GetAllChildren();

			for(int32 i = 0; i < Child.Num(); i++)
			{
				Child[i]->RemoveFromParent();
				Child[i]->MarkAsGarbage();
			}
			CraftedInventoryGrid->ClearChildren();
			break;
		default:
			return;
	}

	for(int32 i = 0; i < Items.Num(); i++)
	{
		if(Items[i]->Quantity == 0)
		{
			Items.RemoveAt(i);
			continue;
		}

		if(Items[i]->ItemType != Type) continue;
		
		UUserWidget* SlotWidget;
		UInventorySlot* TempSlot;
			
		switch (Type)
		{
			case IType_Material:
				SlotWidget = CreateWidget(MatInventoryGrid, BP_Slots);
				MatInventoryGrid->AddChildToUniformGrid(SlotWidget, Row, Col);
					
				if(Col == 7)
				{
					Row++;
					Col = 0;
				} else
				{
					Col++;
				}
					
				TempSlot = Cast<UInventorySlot>(SlotWidget);
				TempSlot->MainItem = Items[i];
				TempSlot->SetSlot();
				break;
			case IType_Consumable:
				SlotWidget = CreateWidget(ConInventoryGrid, BP_Slots);
				ConInventoryGrid->AddChildToUniformGrid(SlotWidget, Row, Col);

				if(Col == 7)
				{
					Row++;
					Col = 0;
				} else
				{
					Col++;
				}
					
				TempSlot = Cast<UInventorySlot>(SlotWidget);
				TempSlot->MainItem = Items[i];
				TempSlot->SetSlot();
				break;
			case IType_Armor:
				SlotWidget = CreateWidget(ArmorInventoryGrid, BP_Slots);
				ArmorInventoryGrid->AddChildToUniformGrid(SlotWidget, Row, Col);

				if(Col == 7)
				{
					Row++;
					Col = 0;
				} else
				{
					Col++;
				}
					
				TempSlot = Cast<UInventorySlot>(SlotWidget);
				TempSlot->MainItem = Items[i];
				TempSlot->SetSlot();
				break;
			case IType_Weapon:
				SlotWidget = CreateWidget(WeaponInventoryGrid, BP_Slots);
				WeaponInventoryGrid->AddChildToUniformGrid(SlotWidget, Row, Col);

				if(Col == 7)
				{
					Row++;
					Col = 0;
				} else
				{
					Col++;
				}
					
				TempSlot = Cast<UInventorySlot>(SlotWidget);
				TempSlot->MainItem = Items[i];
				TempSlot->SetSlot();
				break;
			case IType_Outfit:
				SlotWidget = CreateWidget(OutfitInventoryGrid, BP_Slots);
				OutfitInventoryGrid->AddChildToUniformGrid(SlotWidget, Row, Col);

				if(Col == 7)
				{
					Row++;
					Col = 0;
				} else
				{
					Col++;
				}
					
				TempSlot = Cast<UInventorySlot>(SlotWidget);
				TempSlot->MainItem = Items[i];
				TempSlot->SetSlot();
				break;
			case IType_Crafted:
				SlotWidget = CreateWidget(CraftedInventoryGrid, BP_Slots);
				CraftedInventoryGrid->AddChildToUniformGrid(SlotWidget, Row, Col);
					
				if(Col == 7)
				{
					Row++;
					Col = 0;
				} else
				{
					Col++;
				}
					
				TempSlot = Cast<UInventorySlot>(SlotWidget);
				TempSlot->MainItem = Items[i];
				TempSlot->SetSlot();
				break;
			default:
				return;
		}
	}
}

UWidgetDrop* UInventoryUI::GetWidgetDrop()
{
	return WidgetDrop;
}

void UInventoryUI::DropAction()
{
	if(!WidgetDrop)
	{
		WidgetDrop = CreateWidget<UWidgetDrop>(this, BP_WidgetDrop);
	} 

	if(!WidgetDrop->IsInViewport())
	{
		WidgetDrop->AddToViewport(99);
	}
}