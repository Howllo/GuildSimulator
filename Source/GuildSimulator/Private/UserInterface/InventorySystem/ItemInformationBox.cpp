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
	Durability->SetVisibility(ESlateVisibility::Collapsed);
	IncreasedHealthPoints->SetVisibility(ESlateVisibility::Collapsed);
	IncreasedManaPoints->SetVisibility(ESlateVisibility::Collapsed);
	BasePhysicalDamage->SetVisibility(ESlateVisibility::Collapsed);
	TotalGeneralDamage->SetVisibility(ESlateVisibility::Collapsed);
	TotalFrostDamage->SetVisibility(ESlateVisibility::Collapsed);
	TotalEarthDamage->SetVisibility(ESlateVisibility::Collapsed);
	TotalFireDamage->SetVisibility(ESlateVisibility::Collapsed);
	TotalWaterDamage->SetVisibility(ESlateVisibility::Collapsed);
	TotalLightDamage->SetVisibility(ESlateVisibility::Collapsed);
	TotalDarkDamage->SetVisibility(ESlateVisibility::Collapsed);
	TotalArcaneDamage->SetVisibility(ESlateVisibility::Collapsed);
	AttackPower->SetVisibility(ESlateVisibility::Collapsed);
	MagicPower->SetVisibility(ESlateVisibility::Collapsed);
	CriticalHitChance->SetVisibility(ESlateVisibility::Collapsed);
	SkillSpeed->SetVisibility(ESlateVisibility::Collapsed);
	SpellSpeed->SetVisibility(ESlateVisibility::Collapsed);
	PhysicalDefense->SetVisibility(ESlateVisibility::Collapsed);
	MagicalDefense->SetVisibility(ESlateVisibility::Collapsed);
	FrostResistance->SetVisibility(ESlateVisibility::Collapsed);
	FireResistance->SetVisibility(ESlateVisibility::Collapsed);
	WaterResistance->SetVisibility(ESlateVisibility::Collapsed);
	LightResistance->SetVisibility(ESlateVisibility::Collapsed);
	DarkResistance->SetVisibility(ESlateVisibility::Collapsed);
	ArcaneResistance->SetVisibility(ESlateVisibility::Collapsed);
}
