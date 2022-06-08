// Copyright (c) Astral Games. All right reserved.


#include "UserInterface/InventorySystem/ItemInformationBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"

void UItemInformationBox::OnStatsClick()
{
	VerticalBox->SetVisibility(ESlateVisibility::Visible);
	ItemDescription->SetVisibility(ESlateVisibility::Collapsed);
	StatsInformation->SetIsEnabled(false);
	ItemInformation->SetIsEnabled(true);
}

void UItemInformationBox::OnItemInfoClick()
{
	ItemDescription->SetVisibility(ESlateVisibility::Visible);
	VerticalBox->SetVisibility(ESlateVisibility::Collapsed);
	StatsInformation->SetIsEnabled(true);
	ItemInformation->SetIsEnabled(false);
}


void UItemInformationBox::SetAllCollapse() const
{
	ItemDescription->SetVisibility(ESlateVisibility::Collapsed);
}