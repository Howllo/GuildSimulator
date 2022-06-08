// Copyright (c) Astral Games. All right reserved.


#include "Character/CharacterSubsystems/CharacterStatistic.h"
#include "Character/OverworldPlayerCharacter.h"
#include "Character/RaidPlayerCharacter.h"
#include "GameFramework/Character.h"
#include "GameMisc/SingleClassCharStats.h"
#include "GameMisc/Item/Item.h"

// Sets default values for this component's properties
UCharacterStatistic::UCharacterStatistic()
{
	for(int32 i = ECT_NONE + 1; i != ECT_Last; i++)
	{
		if(i != ECT_TotalDurability || i != ECT_CurrentDurability)
		{
			const ECharacterStats CharacterStats = static_cast<ECharacterStats>(i);
			CharacterStatsMap.Add(CharacterStats, 0);
		}
	}
	
	CharacterStatsMap[ECT_CurrentHealthPoints] = CharacterStatsMap[ECT_TotalHealthPoints];
	CharacterStatsMap[ECT_CurrentEnergyPoints] = CharacterStatsMap[ECT_TotalEnergyPoints];
	CharacterStatsMap[ECT_CurrentManaPoints] = CharacterStatsMap[ECT_TotalManaPoints];
	FEnumToString();
}

void UCharacterStatistic::OnHitDamage(const ACharacter* GetEnemyRef, const EDamageTypes DamageType, const bool IsCritical) {
	const UCharacterStatistic* EnemyStats = Cast<UCharacterStatistic>(GetEnemyRef->GetComponentByClass(StaticClass()));

	switch (DamageType)
	{
		case DT_PHYSICAL_DAMAGE:
			if(IsCritical)
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetTotalCriticalDamage(DT_PHYSICAL_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_PHYSICAL_DAMAGE) + CharacterStatsMap[ECT_PhysicalDefense]);
			else
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetDamageTypeReturns(DT_PHYSICAL_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_PHYSICAL_DAMAGE) + CharacterStatsMap[ECT_PhysicalDefense]);
			break;
		case DT_FROST_DAMAGE:
			if(IsCritical)
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetTotalCriticalDamage(DT_FROST_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_FROST_DAMAGE) + CharacterStatsMap[ECT_FrostResistance]);
			else
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetDamageTypeReturns(DT_FROST_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_FROST_DAMAGE) + CharacterStatsMap[ECT_FrostResistance]);
			break;
		case DT_FIRE_DAMAGE:
			if(IsCritical)
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetTotalCriticalDamage(DT_FIRE_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_FIRE_DAMAGE) + CharacterStatsMap[ECT_FireResistance]);
			else
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetDamageTypeReturns(DT_FIRE_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_FIRE_DAMAGE) + CharacterStatsMap[ECT_FireResistance]);
			break;
		case DT_EARTH_DAMAGE:
			if(IsCritical)
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetTotalCriticalDamage(DT_WATER_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_WATER_DAMAGE) + CharacterStatsMap[ECT_WaterResistance]);

			else
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetDamageTypeReturns(DT_WATER_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_WATER_DAMAGE) + CharacterStatsMap[ECT_WaterDamage]);
			break;
		case DT_LIGHT_DAMAGE:
			if(IsCritical)
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetTotalCriticalDamage(DT_EARTH_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_EARTH_DAMAGE) + CharacterStatsMap[ECT_EarthResistance]);
			else
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetDamageTypeReturns(DT_EARTH_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_EARTH_DAMAGE) + CharacterStatsMap[ECT_EarthResistance]);
			break;
		case DT_DARK_DAMAGE:
			if(IsCritical)
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetTotalCriticalDamage(DT_LIGHT_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_LIGHT_DAMAGE) + CharacterStatsMap[ECT_LightResistance]);
			else
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetDamageTypeReturns(DT_LIGHT_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_LIGHT_DAMAGE) + CharacterStatsMap[ECT_LightResistance]);
			break;
		case DT_WATER_DAMAGE:
			if(IsCritical)
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetTotalCriticalDamage(DT_DARK_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_DARK_DAMAGE) + CharacterStatsMap[ECT_DarkResistance]);
			else
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetDamageTypeReturns(DT_DARK_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_DARK_DAMAGE) + CharacterStatsMap[ECT_DarkResistance]);
			break;
		case DT_ARCANE_DAMAGE:
			if(IsCritical)
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetTotalCriticalDamage(DT_ARCANE_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_ARCANE_DAMAGE) + CharacterStatsMap[ECT_ArcaneResistance]);
			else
				CharacterStatsMap[ECT_CurrentHealthPoints] -= EnemyStats->GetDamageTypeReturns(DT_ARCANE_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_ARCANE_DAMAGE) + CharacterStatsMap[ECT_ArcaneResistance]);
			break;
		default:
			break;
	}

	if(IsCharacterDead())
	{
		//TODO: Set the character death animation. Set state character state to dead.
	}
}

void UCharacterStatistic::OnHitHealing(const ACharacter* GetAllianceRef, const bool IsCritical)
{
	const UCharacterStatistic* StatsAlly = Cast<UCharacterStatistic>(GetAllianceRef->GetComponentByClass(StaticClass()));
	
	if(IsCritical)
	{
		CharacterStatsMap[ECT_CurrentHealthPoints] += StatsAlly->GetTotalCriticalDamage(DT_GENERAL_MAGIC);
	} else
	{
		CharacterStatsMap[ECT_CurrentHealthPoints] += StatsAlly->GetDamageTypeReturns(DT_GENERAL_MAGIC);
	}
}

float UCharacterStatistic::GetTotalCriticalDamage(const EDamageTypes Damage) const
{
	switch (Damage)
	{
		case DT_PHYSICAL_DAMAGE:
			return GetDamageTypeReturns(DT_PHYSICAL_DAMAGE) * (1 + CharacterStatsMap[ECT_CriticalChance] / 100);
		case DT_FROST_DAMAGE:
			return GetDamageTypeReturns(DT_FROST_DAMAGE) * (1 + CharacterStatsMap[ECT_CriticalChance] / 100);
		case DT_FIRE_DAMAGE:
			return GetDamageTypeReturns(DT_FIRE_DAMAGE) * (1 + CharacterStatsMap[ECT_CriticalChance] / 100);
		case DT_EARTH_DAMAGE:
			return GetDamageTypeReturns(DT_EARTH_DAMAGE) * (1 + CharacterStatsMap[ECT_CriticalChance] / 100);
		case DT_LIGHT_DAMAGE:
			return GetDamageTypeReturns(DT_LIGHT_DAMAGE) * (1 + CharacterStatsMap[ECT_CriticalChance] / 100);
		case DT_DARK_DAMAGE:
			return GetDamageTypeReturns(DT_DARK_DAMAGE) * (1 + CharacterStatsMap[ECT_CriticalChance] / 100);
		case DT_WATER_DAMAGE:
			return GetDamageTypeReturns(DT_WATER_DAMAGE) * (1 + CharacterStatsMap[ECT_CriticalChance] / 100);
		case DT_ARCANE_DAMAGE:
			return GetDamageTypeReturns(DT_ARCANE_DAMAGE) * (1 + CharacterStatsMap[ECT_CriticalChance] / 100);
		default:
			return GetDamageTypeReturns(DT_GENERAL_MAGIC) * (1 + CharacterStatsMap[ECT_CriticalChance] / 100);
	}
}

float UCharacterStatistic::GetDamageTypeReturns(const EDamageTypes Damage) const
{
	switch (Damage)
	{
		case DT_PHYSICAL_DAMAGE:
			return (CharacterStatsMap[ECT_PhysicalDamage] * CharacterStatsMap[ECT_PhysicalDamage]) + CharacterStatsMap[ECT_AttackPower];
		case DT_FROST_DAMAGE:
			return (CharacterStatsMap[ECT_FrostDamage] * CharacterStatsMap[ECT_FrostDamage]) + CharacterStatsMap[ECT_MagicPower];
		case DT_FIRE_DAMAGE:
			return (CharacterStatsMap[ECT_FireDamage] * CharacterStatsMap[ECT_FireDamage]) + CharacterStatsMap[ECT_MagicPower];
		case DT_EARTH_DAMAGE:
			return (CharacterStatsMap[ECT_EarthDamage] * CharacterStatsMap[ECT_EarthDamage]) + CharacterStatsMap[ECT_MagicPower];
		case DT_LIGHT_DAMAGE:
			return (CharacterStatsMap[ECT_LightDamage] * CharacterStatsMap[ECT_LightDamage]) + CharacterStatsMap[ECT_MagicPower];
		case DT_DARK_DAMAGE:
			return (CharacterStatsMap[ECT_DarkDamage] * CharacterStatsMap[ECT_DarkDamage]) + CharacterStatsMap[ECT_MagicPower];
		case DT_WATER_DAMAGE:
			return CharacterStatsMap[ECT_WaterDamage] * CharacterStatsMap[ECT_WaterDamage] + CharacterStatsMap[ECT_MagicPower];
		case DT_ARCANE_DAMAGE:
			return CharacterStatsMap[ECT_ArcaneDamage] * CharacterStatsMap[ECT_ArcaneDamage] + CharacterStatsMap[ECT_MagicPower];
		default:
			return CharacterStatsMap[ECT_HealDamage] * CharacterStatsMap[ECT_HealDamage] + CharacterStatsMap[ECT_MagicPower];
	}
}

float UCharacterStatistic::ConvertStatsToPercentage(const int32 IncomingStats) 
{
	if(IncomingStats >= 0 && IncomingStats <= 100)
	{
		return IncomingStats / 100;
	}

	if(IncomingStats > 100 && IncomingStats <= 200)
	{
		return IncomingStats / 1000;
	}

	if(IncomingStats > 200 && IncomingStats <= 300)
	{
		return IncomingStats / 1000;
	}
	
	if(IncomingStats > 300 && IncomingStats <= 400)
	{
		return 0.4 * IncomingStats / (IncomingStats + 14.28);
	}

	if(IncomingStats > 400 && IncomingStats <= 500)
	{
		return 0.4 * IncomingStats / (IncomingStats + 14.28);
	}

	if(IncomingStats > 600 && IncomingStats <= 700)
	{
		return 0.4 * IncomingStats / (IncomingStats + 14.28);
	}

	if(IncomingStats > 700 && IncomingStats <= 800)
	{
		return 0.4 * IncomingStats / (IncomingStats + 14.28);
	}

	if(IncomingStats > 900 && IncomingStats <= 1000)
	{
		return 0.4 * IncomingStats / (IncomingStats + 14.28);
	}

	return 0.0f;
}

bool UCharacterStatistic::IsCharacterDead() const
{
	if(CharacterStatsMap[ECT_CurrentHealthPoints] <= 0)
	{
		return true;
	}
	return false;
}

void UCharacterStatistic::AddEquipmentStats(const UItem* IncomingItem, const bool bIsRemoved)
{
	if(!IncomingItem) return;
	
	int Value = 1;
	if(bIsRemoved)
		Value = -1;
	const USingleClassCharStats* CS = IncomingItem->ItemStats;

	//Health
	CharacterStatsMap[ECT_TotalHealthPoints] += Value * CS->CharacterStatsMap[ECT_TotalHealthPoints];
	CharacterStatsMap[ECT_TotalManaPoints] += Value * CS->CharacterStatsMap[ECT_TotalManaPoints];
	
	//Damage
	CharacterStatsMap[ECT_PhysicalDamage] += Value * CS->CharacterStatsMap[ECT_PhysicalDamage];
	CharacterStatsMap[ECT_FrostDamage] += Value * CS->CharacterStatsMap[ECT_FrostDamage];
	CharacterStatsMap[ECT_FireDamage] += Value * CS->CharacterStatsMap[ECT_FireDamage];
	CharacterStatsMap[ECT_EarthDamage] += Value * CS->CharacterStatsMap[ECT_EarthDamage];
	CharacterStatsMap[ECT_LightDamage] += Value * CS->CharacterStatsMap[ECT_LightDamage];
	CharacterStatsMap[ECT_DarkDamage] += Value * CS->CharacterStatsMap[ECT_DarkDamage];
	CharacterStatsMap[ECT_ArcaneDamage] += Value * CS->CharacterStatsMap[ECT_ArcaneDamage];
	
	//Abilities
	CharacterStatsMap[ECT_SpellSpeed] += Value * CS->CharacterStatsMap[ECT_SpellSpeed];
	CharacterStatsMap[ECT_SkillSpeed]  += Value * CS->CharacterStatsMap[ECT_SkillSpeed];

	//Defense
	CharacterStatsMap[ECT_PhysicalDefense] += Value * CS->CharacterStatsMap[ECT_PhysicalDefense];
	CharacterStatsMap[ECT_MagicalDefense] += Value * CS->CharacterStatsMap[ECT_MagicalDefense];
	CharacterStatsMap[ECT_FrostResistance]  += Value * CS->CharacterStatsMap[ECT_FrostResistance];
	CharacterStatsMap[ECT_FireResistance]  += Value * CS->CharacterStatsMap[ECT_FireResistance];
	CharacterStatsMap[ECT_WaterResistance]  += Value * CS->CharacterStatsMap[ECT_WaterResistance];
	CharacterStatsMap[ECT_EarthResistance]  += Value * CS->CharacterStatsMap[ECT_EarthResistance];
	CharacterStatsMap[ECT_LightResistance]  += Value * CS->CharacterStatsMap[ECT_LightResistance];
	CharacterStatsMap[ECT_DarkResistance]  += Value * CS->CharacterStatsMap[ECT_DarkResistance];
	CharacterStatsMap[ECT_ArcaneResistance]  += Value * CS->CharacterStatsMap[ECT_ArcaneResistance];
}

#define LOCTEXT_NAMESPACE "StatsNames"
void UCharacterStatistic::FEnumToString()
{
	const FText TotalHealthText = NSLOCTEXT("StatsNames", "Text_TotalHealthPoints", "Total Health: ");
	const FText CurrentHealthText = NSLOCTEXT("StatsNames", "Text_CurrentHealthPoints", "Current Health: ");
	const FText IncreasedHealthText = NSLOCTEXT("StatsNames", "Text_IncreaseHealth", "Increased Health: ");
	const FText TotalEnergyText = NSLOCTEXT("StatsNames", "Text_TotalEnergyPoints", "Total Energy: ");
	const FText CurrentEnergyText = NSLOCTEXT("StatsNames", "Text_CurrentEnergyPoints", "Current Energy: ");
	const FText TotalManaText = NSLOCTEXT("StatsNames", "Text_TotalManaPoints", "Total Mana: ");
	const FText CurrentManaText = NSLOCTEXT("StatsNames", "Text_CurrentManaPoints", "Current Mana: ");
	const FText IncreasedManaText = NSLOCTEXT("StatsNames", "Text_IncreaseManaPoints", "Increased Energy: ");
	const FText TotalMoraleText = NSLOCTEXT("StatsNames", "Text_TotalMorale", "Total Morale: ");
	const FText CurrentMoraleText = NSLOCTEXT("StatsNames", "Text_CurrentMorale", "Current Morale: ");
	const FText ThreatLevelText = NSLOCTEXT("StatsNames", "Text_ThreatLevel", "Threat Level: ");

	//Damage
	const FText PhysicalDamageText = NSLOCTEXT("StatsNames", "Text_PhysicalDamage", "Physical Damage: ");
	const FText HealDamageText = NSLOCTEXT("StatsNames", "Text_HealDamage", "Healing Power: ");
	const FText FrostDamageText = NSLOCTEXT("StatsNames", "Text_FrostDamage", "Frost Damage: ");
	const FText FireDamageText = NSLOCTEXT("StatsNames", "Text_FireDamage", "Fire Damage: ");
	const FText EarthDamageText = NSLOCTEXT("StatsNames", "Text_EarthDamage", "Earth Damage: ");
	const FText WaterDamageText = NSLOCTEXT("StatsNames", "Text_WaterDamage", "Water Damage: ");
	const FText LightDamageText = NSLOCTEXT("StatsNames", "Text_LightDamage", "Light Damage: ");
	const FText DarkDamageText = NSLOCTEXT("StatsNames", "Text_DarkDamage", "Dark Damage: ");
	const FText ArcaneDamageText = NSLOCTEXT("StatsNames", "Text_ArcaneDamage", "Arcane Damage: ");
	const FText AttackPowerText = NSLOCTEXT("StatsNames", "Text_AttackPower", "Attack Power: ");
	const FText MagicPowerText = NSLOCTEXT("StatsNames", "Text_MagicPower", "Magic Power: ");
	const FText CriticalChanceText = NSLOCTEXT("StatsNames", "Text_CriticalChance", "Critical Chance: ");
	const FText SkillSpeedText = NSLOCTEXT("StatsNames", "Text_SkillSpeed", "Skill Speed: ");
	const FText SpellSpeedText = NSLOCTEXT("StatsNames", "Text_SpellSpeed", "Spell Speed: ");

	//Defense
	const FText PhysicalDefenseText = NSLOCTEXT("StatsNames", "Text_PhysicalDefense", "Physical Defense: ");
	const FText MagicalDefenseText = NSLOCTEXT("StatsNames", "Text_MagicalDefense", "Magical Defense: ");
	const FText FrostResistanceText = NSLOCTEXT("StatsNames", "Text_FrostResistance", "Frost Resistance: ");
	const FText FireResistanceText = NSLOCTEXT("StatsNames", "Text_FireResistance", "Fire Resistance: ");
	const FText WaterResistanceText = NSLOCTEXT("StatsNames", "Text_WaterResistance", "Water Resistance: ");
	const FText EarthResistanceText = NSLOCTEXT("StatsNames", "Text_EarthResistance", "Earth Resistance: ");
	const FText LightResistanceText = NSLOCTEXT("StatsNames", "Text_LightResistance", "Light Resistance: ");
	const FText DarkResistanceText = NSLOCTEXT("StatsNames", "Text_DarkResistance", "Dark Resistance: ");
	const FText ArcaneResistanceText = NSLOCTEXT("StatsNames", "Text_ArcaneResistance", "Arcane Resistance: ");
	const FText GlobalCDText = NSLOCTEXT("StatsNames", "Text_GlobalCD", "Global Cooldown: ");

	TArray<FText> StatisticName =
		{
			TotalHealthText, CurrentHealthText, IncreasedHealthText, TotalEnergyText, CurrentEnergyText,
			TotalManaText, CurrentManaText, IncreasedManaText, TotalMoraleText, CurrentMoraleText,
			ThreatLevelText, PhysicalDamageText, HealDamageText, FrostDamageText, FireDamageText, EarthDamageText,
			WaterDamageText, LightDamageText, DarkDamageText, ArcaneDamageText, AttackPowerText, MagicPowerText,
			CriticalChanceText,SkillSpeedText, SpellSpeedText, PhysicalDefenseText, MagicalDefenseText,
			FrostResistanceText, FireResistanceText,WaterResistanceText, EarthResistanceText, LightResistanceText,
			ArcaneResistanceText, GlobalCDText
		};
	
	
	for(int32 i = ECT_NONE + 1; i != ECT_Last; i++)
	{
		const ECharacterStats CharacterStats = static_cast<ECharacterStats>(i);
		if(i == ECT_GlobalCooldown || i == ECT_TotalDurability || i == ECT_CurrentDurability || i == StatisticName.Num())
			break;
		StatsFText.Add(CharacterStats, StatisticName[i]);
	}
}
#undef  LOCTEXT_NAMESPACE

void UCharacterStatistic::BeginPlay()
{
	Super::BeginPlay();

	RaidPlayer = Cast<ARaidPlayerCharacter>(GetOwner());
	PlayerChar = Cast<AOverworldPlayerCharacter>(GetOwner());
}


// Called every frame
void UCharacterStatistic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}