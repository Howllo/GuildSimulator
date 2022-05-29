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
//	PrimaryComponentTick.bCanEverTick = true;

	//Character Properties
	TotalHealthPoints = 255;
	CurrentHealthPoint = TotalHealthPoints;
	TotalEnergyPoints = 100;
	CurrentEnergyPoints = TotalEnergyPoints;
	TotalManaPoints = 75;
	CurrentManaPoints = TotalManaPoints;
	TotalMorale = 100;
	CurrentMorale = TotalMorale;
	ThreatLevel = 0;
	
	//Damage
	BasePhysicalDamage = 2;
	TotalFrostDamage = 2;
	TotalFireDamage = 2;
	TotalEarthDamage = 2;
	TotalLightDamage = 2;
	TotalDarkDamage = 2;
	TotalArcaneDamage = 2;
	PhysicalDefense = 10;
	MagicalDefense = 10;
	AttackPower = 0;
	MagicPower = 0;
	CriticalHitChance = 0;

	//Abilities
	GlobalCoolDown = 2.f;
	SpellSpeed = 0;
	SkillSpeed = 0;

	//Defense
	PhysicalDefense = 0;
	MagicalDefense = 0;
	FrostResistance = 0;
	FireResistance = 0;
	WaterResistance = 0;
	EarthResistance = 0;
	LightResistance = 0;
	DarkResistance = 0;
	ArcaneResistance = 0;
}

void UCharacterStatistic::OnHitDamage(const ACharacter* GetEnemyRef, const DamageTypes DamageType, const bool IsCritical) {
	const UCharacterStatistic* EnemyStats = Cast<UCharacterStatistic>(GetEnemyRef->GetComponentByClass(StaticClass()));

	switch (DamageType)
	{
		case DT_PHYSICAL_DAMAGE:
			if(IsCritical)
				CurrentHealthPoint -= EnemyStats->GetTotalCriticalDamage(DT_PHYSICAL_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_PHYSICAL_DAMAGE) + PhysicalDefense);
			else
				CurrentHealthPoint -= EnemyStats->GetDamageTypeReturns(DT_PHYSICAL_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_PHYSICAL_DAMAGE) + PhysicalDefense);
			break;
		case DT_FROST_DAMAGE:
			if(IsCritical)
				CurrentHealthPoint -= EnemyStats->GetTotalCriticalDamage(DT_FROST_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_FROST_DAMAGE) + FrostResistance);
			else
				CurrentHealthPoint -= EnemyStats->GetDamageTypeReturns(DT_FROST_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_FROST_DAMAGE) + FrostResistance);
			break;
		case DT_FIRE_DAMAGE:
			if(IsCritical)
				CurrentHealthPoint -= EnemyStats->GetTotalCriticalDamage(DT_FIRE_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_FIRE_DAMAGE) + FireResistance);
			else
				CurrentHealthPoint -= EnemyStats->GetDamageTypeReturns(DT_FIRE_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_FIRE_DAMAGE) + FireResistance);
			break;
		case DT_EARTH_DAMAGE:
			if(IsCritical)
				CurrentHealthPoint -= EnemyStats->GetTotalCriticalDamage(DT_WATER_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_WATER_DAMAGE) + WaterResistance);

			else
				CurrentHealthPoint -= EnemyStats->GetDamageTypeReturns(DT_WATER_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_WATER_DAMAGE) + WaterResistance);
			break;
		case DT_LIGHT_DAMAGE:
			if(IsCritical)
				CurrentHealthPoint -= EnemyStats->GetTotalCriticalDamage(DT_EARTH_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_EARTH_DAMAGE) + EarthResistance);
			else
				CurrentHealthPoint -= EnemyStats->GetDamageTypeReturns(DT_EARTH_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_EARTH_DAMAGE) + EarthResistance);
			break;
		case DT_DARK_DAMAGE:
			if(IsCritical)
				CurrentHealthPoint -= EnemyStats->GetTotalCriticalDamage(DT_LIGHT_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_LIGHT_DAMAGE) + LightResistance);
			else
				CurrentHealthPoint -= EnemyStats->GetDamageTypeReturns(DT_LIGHT_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_LIGHT_DAMAGE) + LightResistance);
			break;
		case DT_WATER_DAMAGE:
			if(IsCritical)
				CurrentHealthPoint -= EnemyStats->GetTotalCriticalDamage(DT_DARK_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_DARK_DAMAGE) + DarkResistance);
			else
				CurrentHealthPoint -= EnemyStats->GetDamageTypeReturns(DT_DARK_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_DARK_DAMAGE) + DarkResistance);
			break;
		case DT_ARCANE_DAMAGE:
			if(IsCritical)
				CurrentHealthPoint -= EnemyStats->GetTotalCriticalDamage(DT_ARCANE_DAMAGE) /
					(EnemyStats->GetTotalCriticalDamage(DT_ARCANE_DAMAGE) + ArcaneResistance);
			else
				CurrentHealthPoint -= EnemyStats->GetDamageTypeReturns(DT_ARCANE_DAMAGE) /
					(EnemyStats->GetDamageTypeReturns(DT_ARCANE_DAMAGE) + ArcaneResistance);
			break;
		default:
			CurrentHealthPoint = CurrentHealthPoint;
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
		CurrentHealthPoint += StatsAlly->GetTotalCriticalDamage(DT_GENERAL_MAGIC);
	} else
	{
		CurrentHealthPoint += StatsAlly->GetDamageTypeReturns(DT_GENERAL_MAGIC);
	}
}

float UCharacterStatistic::GetTotalCriticalDamage(const DamageTypes Damage) const
{
	switch (Damage)
	{
		case DT_PHYSICAL_DAMAGE:
			return GetDamageTypeReturns(DT_PHYSICAL_DAMAGE) * (1 + CriticalHitChance / 100);
		case DT_FROST_DAMAGE:
			return GetDamageTypeReturns(DT_FROST_DAMAGE) * (1 + CriticalHitChance / 100);
		case DT_FIRE_DAMAGE:
			return GetDamageTypeReturns(DT_FIRE_DAMAGE) * (1 + CriticalHitChance / 100);
		case DT_EARTH_DAMAGE:
			return GetDamageTypeReturns(DT_EARTH_DAMAGE) * (1 + CriticalHitChance / 100);
		case DT_LIGHT_DAMAGE:
			return GetDamageTypeReturns(DT_LIGHT_DAMAGE) * (1 + CriticalHitChance / 100);
		case DT_DARK_DAMAGE:
			return GetDamageTypeReturns(DT_DARK_DAMAGE) * (1 + CriticalHitChance / 100);
		case DT_WATER_DAMAGE:
			return GetDamageTypeReturns(DT_WATER_DAMAGE) * (1 + CriticalHitChance / 100);
		case DT_ARCANE_DAMAGE:
			return GetDamageTypeReturns(DT_ARCANE_DAMAGE) * (1 + CriticalHitChance / 100);
		default:
			return GetDamageTypeReturns(DT_GENERAL_MAGIC) * (1 + CriticalHitChance / 100);
	}
}

float UCharacterStatistic::GetDamageTypeReturns(const DamageTypes Damage) const
{
	switch (Damage)
	{
		case DT_PHYSICAL_DAMAGE:
			return (BasePhysicalDamage * BasePhysicalDamage) + AttackPower;
		case DT_FROST_DAMAGE:
			return (TotalFrostDamage * TotalFrostDamage) + MagicPower;
		case DT_FIRE_DAMAGE:
			return (TotalFireDamage * TotalFireDamage) + MagicPower;
		case DT_EARTH_DAMAGE:
			return (TotalEarthDamage * TotalEarthDamage) + MagicPower;
		case DT_LIGHT_DAMAGE:
			return (TotalLightDamage * TotalLightDamage) + MagicPower;
		case DT_DARK_DAMAGE:
			return (TotalDarkDamage * TotalDarkDamage) + MagicPower;
		case DT_WATER_DAMAGE:
			return (TotalWaterDamage * TotalWaterDamage) + MagicPower;
		case DT_ARCANE_DAMAGE:
			return (TotalArcaneDamage * TotalArcaneDamage) + MagicPower;
		default:
			return (TotalGeneralDamage * TotalGeneralDamage) + MagicPower;
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
	if(CurrentHealthPoint <= 0)
	{
		return true;
	}
	return false;
}

void UCharacterStatistic::EquipmentStats(const UItem* IncomingItem, const bool bIsRemoved)
{
	int Value = 1;
	if(bIsRemoved)
		Value = -1;
	const USingleClassCharStats* CS = IncomingItem->CharStats;

	//Health
	TotalHealthPoints += Value * CS->IncreasedHealthPoints;
	TotalManaPoints += Value * CS->IncreasedManaPoints;
	
	//Damage
	BasePhysicalDamage += Value * CS->BasePhysicalDamage;
	TotalFrostDamage += Value * CS->TotalFrostDamage;
	TotalFireDamage += Value * CS->TotalFireDamage;
	TotalEarthDamage += Value * CS->TotalEarthDamage;
	TotalLightDamage += Value * CS->TotalLightDamage;
	TotalDarkDamage += Value * CS->TotalDarkDamage;
	TotalArcaneDamage += Value * CS->TotalArcaneDamage;
	PhysicalDefense += Value * CS->PhysicalDefense;
	MagicalDefense += Value * CS->MagicalDefense;
	AttackPower += Value * CS->AttackPower;
	MagicPower += Value * CS->MagicPower;
	CriticalHitChance += Value * CS->CriticalHitChance;

	//Abilities
	SpellSpeed += Value * CS->SpellSpeed;
	SkillSpeed += Value * CS->SkillSpeed;

	//Defense
	PhysicalDefense += Value * CS->PhysicalDefense;
	MagicalDefense += Value * CS->MagicalDefense;
	FrostResistance += Value * CS->FrostResistance;
	FireResistance += Value * CS->FireResistance;
	WaterResistance += Value * CS->WaterResistance;
	EarthResistance += Value * CS->EarthResistance;
	LightResistance += Value * CS->LightResistance;
	DarkResistance += Value * CS->DarkResistance;
	ArcaneResistance += Value * CS->ArcaneResistance;
}

void UCharacterStatistic::BeginPlay()
{
	Super::BeginPlay();

	RaidPlayer = Cast<ARaidPlayerCharacter>(GetOwner());

	// Get the owner.
	if(!RaidPlayer->CharacterType)
	{
		RaidPlayer = nullptr;
		PlayerChar = Cast<AOverworldPlayerCharacter>(GetOwner());
		if(!PlayerChar->CharType)
		{
			PlayerChar = nullptr;
			//TODO: Add NPC
		}
	}
}


// Called every frame
void UCharacterStatistic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}

