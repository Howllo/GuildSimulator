// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GuildSimEnums.generated.h"

/* Character class types. */
UENUM(BlueprintType)
enum CharacterClass
{
	CC_NONE					UMETA(DisplayName = "No Class"),
	CC_WARRIOR				UMETA(DisplayName = "Warrior"),
	CC_GUNSLINGER			UMETA(DisplayName = "Gunslinger"),
	CC_SOULWEAVER			UMETA(DisplayName = "Soulwaver"),
	CC_SUMMONER				UMETA(DisplayName = "Summoner"),
	CC_NINJA				UMETA(DisplayName = "Ninja"),
	CC_DARK_KNIGHT			UMETA(DisplayName = "Dark Knight"),
	CC_RANGER				UMETA(DisplayName = "Ranger"),
	CC_NECROMANCER			UMETA(DisplayName = "Necromancer"),
	CC_MARTIAL_ARTIST		UMETA(DisplayName = "Martial Artist"),
	CC_ASTROMANCER			UMETA(DisplayName = "Artomancer"),
	CC_DRUNKEN_FIST			UMETA(DisplayName = "Drunken Fist"),
	CC_MECHA				UMETA(DisplayName = "Mecha")
};

/* Class specialization. Tank, Damage, and Healer. */
UENUM(BlueprintType)
enum ClassSpecialization
{
	CS_NONE					UMETA(DisplayName = "No Spec"),
	CS_Tank					UMETA(DisplayName = "Tank"),
	CS_Damage				UMETA(DisplayName = "Damage"),
	CS_Healer				UMETA(DispalyName = "Healer")
};

/** Character status types. */
UENUM(BlueprintType)
enum CurrentCharacterStates {
	CCS_NONE				UMETA(DisplayName = "Default State"),
	CCS_COMBAT				UMETA(DisplayName = "Is Character Combat"),
	CCS_DEAD				UMETA(DisplayName = "Is Character Dead"),
	CCS_STUNNED				UMETA(DisplayName = "Is Character Stunned"),
	CCS_GROUNDED			UMETA(DisplayName = "Is Character Grounded"),
	CCS_COLD_AREA			UMETA(DisplayName = "Is Character in Cold Area"),
	CCS_HOT_AREA			UMETA(Displayname = "Is Character in Hot Area"),
	CCS_CANNOT_BE_DAMAGED	UMETA(DisplayName = "Character Cannot Be Damaged"),
};

/* All character models that are linked here will be attached to a array of models. */
UENUM(BlueprintType)
enum CharacterModels {
	CM_NONE					UMETA(DisplayName = "Default State"),
};

/* Damage type consist of all the magic types of Physical, General, Frost, FIre, Earth, Water, Light, and Dark. */
UENUM(BlueprintType)
enum DamageTypes {
	DT_PHYSICAL_DAMAGE		UMETA(DisplayName = "Physical Damage"),
	DT_GENERAL_MAGIC		UMETA(DisplayName = "General Magic"),
	DT_FROST_DAMAGE			UMETA(DispalyName = "Frost Damage"),
	DT_FIRE_DAMAGE			UMETA(DisplayName = "Fire Damage"),
	DT_EARTH_DAMAGE			UMETA(DisplayName = "Earth Damage"),
	DT_WATER_DAMAGE			UMETA(DisplayName = "Water Damage"),
	DT_LIGHT_DAMAGE			UMETA(DisplayName = "Light Damage"),
	DT_DARK_DAMAGE			UMETA(DisplayName = "Dark Damage"),
	DT_ARCANE_DAMAGE		UMETA(DisplayName = "Arcane Damage")
};

UENUM(BlueprintType)
enum AbilitySystemEnum
{
	ASE_CAST		UMETA(DisplayName = "Casting"),
	ASE_STUN		UMETA(DisplayName = "Stun"),
	ASE_SLOW		UMETA(DisplayName = "Slow"),
	ASE_BUFF		UMETA(DisplayName = "Buff"),
	ASE_DEBUFF		UMETA(DisplayName = "Debuff"),
	ASE_COOLDOWN	UMETA(DisplayName = "Cooldown")
};

UENUM(BlueprintType)
enum CharacterType
{
	CT_NONE			UMETA(DisplayName = "None"),
	CT_ALLIANCE		UMETA(DisplayName = "Alliance"),
	CT_ENEMY		UMETA(DisplayName = "Enemy"),
	CT_ELITE		UMETA(DisplayName = "Elite"),
	CT_BOSS			UMETA(DisplayName = "Boss"),
	CT_MINIBOSS		UMETA(DisplayName = "MiniBoss")
};

/* All general character traits a player will get. */
UENUM(BlueprintType)
enum CharacterGeneralTraits {
	CGT_NONE				UMETA(DisplayName = "No Traits"),
};

/* All tank character traits a player will get. */
UENUM(BlueprintType)
enum CharacterTankTraits {
	CTT_NONE				UMETA(DisplayName = "No Traits"),
};

/* All damage character traits a player will get. */
UENUM(BlueprintType)
enum CharacterDamageTraits {
	CDT_None				UMETA(DisplayName = "No Traits"),
};

/* All healer character traits a player will get. */
UENUM(BlueprintType)
enum CharacterHealerTraits {
	CHT_None			UMETA(DisplayName = "No Traits"),
};

UENUM(BlueprintType)
enum ItemType
{
	IType_NONE			UMETA(DisplayName = "Set Item Type"),
	IType_Material		UMETA(DisplayName = "Material"),
	IType_Consumable	UMETA(DisplayName = "Consumable"),
	IType_Armor			UMETA(DisplayName = "Armor"),
	IType_Weapon		UMETA(DisplayName = "Weapon"),
	IType_Outfit		UMETA(DisplayName = "Outfit"),
	IType_Crafted		UMETA(DisplayName = "Crafted")
};

UENUM(BlueprintType)
enum ConsumableType
{
	CType_Food			UMETA(DisplayName = "Food"),
	CType_Elixir		UMETA(DisplayName = "Elixir"),
	CType_Potion		UMETA(DisplayName = "Potion")
};

UENUM(BlueprintType)
enum GameRarity
{
	RItem_Common		UMETA(DisplayName = "Normal"),
	RItem_Uncommon		UMETA(DisplayName = "Uncommon"),
	RItem_Epic			UMETA(DisplayName = "Epic"),
	RItem_Legendary		UMETA(DisplayName = "Legendary"),
	RItem_Artifact		UMETA(DisplayName = "Artifact")
};

UENUM(BlueprintType)
enum ItemStarCount
{
	IEC_One				UMETA(DisplayName = "One Star"),
	IEC_Two				UMETA(DisplayName = "Two Star"),
	IEC_Three			UMETA(DisplayName = "Three Star")
};

UENUM(BlueprintType)
enum ControllerScheme
{
	CScheme_KEY		UMETA(DisplayName = "Keyboard and Mouse"),
	CScheme_CONT	UMETA(DisplayName = "Controller"),
	CScheme_STEAM	UMETA(DisplayName = "Steam Controller"),
};

// What is the weapon?
UENUM(BlueprintType)
enum WeaponType
{
	EWT_NONE		UMETA(DisplayName = "None"),
	EWT_BattleAxe	UMETA(DisplayName = "Battle Axe"),
	EWT_Polearm		UMETA(DisplayName = "Polearm"),
	EWT_OneSword	UMETA(DisplayName = "One-Handed Sword"),
	EWT_TwoSword	UMETA(DisplayName = "Two-Handed Sword"),
	EWT_Warhammer	UMETA(DisplayName = "Warhammer"),
	EWT_Bow			UMETA(DisplayName = "Bow"),
	EWT_Shield		UMETA(DisplayName = "Shield"),
	EWT_Staff		UMETA(DisplayName = "None"),
	EWT_Hoe			UMETA(DisplayName = "Hoe"),
	EWT_Pickaxe		UMETA(DisplayName = "Pickaxe"),
	EWT_Axe			UMETA(DisplayName = "Axe"),
	EWT_Hammer		UMETA(DisplayName = "Hammer"),
};

// What is the weapon?
UENUM(BlueprintType)
enum EHandType
{
	EHT_NONE	UMETA(DisplayName = "None"),
	EHT_One		UMETA(DisplayName = "One-Handed"),
	EHT_Two		UMETA(DisplayName = "Two-Handed"),
	EHT_Off		UMETA(DispalyName = "Off-Handed")
};

// Armor Type
UENUM(BlueprintType)
enum ArmorType
{
	EAT_None		UMETA(DisplayName = "None"),
	EAT_Helm		UMETA(DisplayName = "Helm"),
	EAT_Chest		UMETA(DisplayName = "Chest"),
	EAT_Hand		UMETA(DisplayName = "Hands"),
	EAT_Legs		UMETA(DisplayName = "Leggings"),
	EAT_Feet		UMETA(DisplayName = "Feet"),
	EAT_Ring		UMETA(DisplayName = "Ring"),
	EAT_Trinket		UMETA(DisplayName = "Trinket"),
};

// Upgrade Type EX. Wood, Copper, Iron, Steel, Titanium
UENUM(BlueprintType)
enum ItemQualityType
{
	EWPType_None		UMETA(DisplayName = "None"),
	EWPType_Wood		UMETA(DisplayName = "Wood"),
	EWPType_Copper		UMETA(DisplayName = "Copper"),
	EWPType_Iron		UMETA(DisplayName = "Iron"),
	EWPType_Steel		UMETA(DisplayName = "Steel"),
	EWPType_Titanium	UMETA(DisplayName = "Titanium"),
	EWPType_Tungsten	UMETA(DisplayName = "Tungsten")
};