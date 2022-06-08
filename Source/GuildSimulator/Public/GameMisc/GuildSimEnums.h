// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GuildSimEnums.generated.h"

/* Character class types. */
UENUM(BlueprintType)
enum ECharacterClass
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
enum EClassSpecialization
{
	CS_NONE					UMETA(DisplayName = "No Spec"),
	CS_Tank					UMETA(DisplayName = "Tank"),
	CS_Damage				UMETA(DisplayName = "Damage"),
	CS_Healer				UMETA(DispalyName = "Healer")
};

/** Character status types. */
UENUM(BlueprintType)
enum ECurrentCharacterStates {
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
enum ECharacterModels {
	CM_NONE					UMETA(DisplayName = "Default State"),
};

/* Damage type consist of all the magic types of Physical, General, Frost, FIre, Earth, Water, Light, and Dark. */
UENUM(BlueprintType)
enum EDamageTypes {
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
enum EAbilitySystem
{
	ASE_CAST		UMETA(DisplayName = "Casting"),
	ASE_STUN		UMETA(DisplayName = "Stun"),
	ASE_SLOW		UMETA(DisplayName = "Slow"),
	ASE_BUFF		UMETA(DisplayName = "Buff"),
	ASE_DEBUFF		UMETA(DisplayName = "Debuff"),
	ASE_COOLDOWN	UMETA(DisplayName = "Cooldown")
};

UENUM(BlueprintType)
enum ECharacterType
{
	CT_NONE			UMETA(DisplayName = "None"),
	CT_NPC			UMETA(DisplayName = "NPC"),
	CT_OVERWORLD	UMETA(DisplayName = "Overworld Character"),
	CT_RAIDCHAR		UMETA(DisplayName = "Raid Character"),
	CT_ALLIANCE		UMETA(DisplayName = "Alliance"),
	CT_ENEMY		UMETA(DisplayName = "Enemy"),
	CT_ELITE		UMETA(DisplayName = "Elite"),
	CT_BOSS			UMETA(DisplayName = "Boss"),
	CT_MINIBOSS		UMETA(DisplayName = "MiniBoss")
};

/* All general character traits a player will get. */
UENUM(BlueprintType)
enum ECharacterGeneralTraits {
	CGT_NONE			UMETA(DisplayName = "No Traits"),
};

/* All tank character traits a player will get. */
UENUM(BlueprintType)
enum ECharacterTankTraits {
	CTT_NONE			UMETA(DisplayName = "No Traits"),
};

/* All damage character traits a player will get. */
UENUM(BlueprintType)
enum ECharacterDamageTraits {
	CDT_None			UMETA(DisplayName = "No Traits"),
};

/* All healer character traits a player will get. */
UENUM(BlueprintType)
enum ECharacterHealerTraits {
	CHT_None			UMETA(DisplayName = "No Traits"),
};

UENUM(BlueprintType)
enum EItemType
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
enum EConsumableType
{
	CType_Food			UMETA(DisplayName = "Food"),
	CType_Elixir		UMETA(DisplayName = "Elixir"),
	CType_Potion		UMETA(DisplayName = "Potion")
};

UENUM(BlueprintType)
enum EGameRarity
{
	GRarity_Common		UMETA(DisplayName = "Normal"),
	GRarity_Uncommon	UMETA(DisplayName = "Uncommon"),
	GRarity_Epic		UMETA(DisplayName = "Epic"),
	GRarity_Legendary	UMETA(DisplayName = "Legendary"),
	GRarity_Artifact	UMETA(DisplayName = "Artifact")
};

UENUM(BlueprintType)
enum EItemStarCount
{
	IEC_One				UMETA(DisplayName = "One Star"),
	IEC_Two				UMETA(DisplayName = "Two Star"),
	IEC_Three			UMETA(DisplayName = "Three Star")
};

UENUM(BlueprintType)
enum EControllerScheme
{
	CScheme_KEY			UMETA(DisplayName = "Keyboard and Mouse"),
	CScheme_CONT		UMETA(DisplayName = "Controller"),
	CScheme_STEAM		UMETA(DisplayName = "Steam Controller"),
};

// What is the weapon?
UENUM(BlueprintType)
enum EWeaponType
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
	EHT_Off		UMETA(DisplayName = "Off-Handed")
};

// Armor Type
UENUM(BlueprintType)
enum EArmorType
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
enum EItemQualityType
{
	EWPType_None		UMETA(DisplayName = "None"),
	EWPType_Wood		UMETA(DisplayName = "Wood"),
	EWPType_Copper		UMETA(DisplayName = "Copper"),
	EWPType_Iron		UMETA(DisplayName = "Iron"),
	EWPType_Steel		UMETA(DisplayName = "Steel"),
	EWPType_Titanium	UMETA(DisplayName = "Titanium"),
	EWPType_Tungsten	UMETA(DisplayName = "Tungsten")
};

// Used for TMap in Character Stats.
UENUM(BlueprintType)
enum ECharacterStats
{
	ECT_NONE				UMETA(DisplayName = "None"),			// Nothing
	ECT_TotalHealthPoints	UMETA(DisplayName = "TotalHealth"),		// The total amount of character health.
	ECT_CurrentHealthPoints UMETA(DisplayName = "CurrentHealth"),	// Current amount of the player HP.
	ECT_IncreaseHealth		UMETA(DisplayName = "IncreaseHealth"),	// The amoutn of health that increased.
	ECT_TotalEnergyPoints	UMETA(DisplayName = "TotalEnergy"),		// Total amount of energy points.
	ECT_CurrentEnergyPoints UMETA(DisplayName = "CurrentEnergy"),	// Current amount of energy points.
	ECT_TotalManaPoints		UMETA(DisplayName = "TotalMana"),		// Total amount of character mana points.
	ECT_CurrentManaPoints	UMETA(DisplayName = "CurrentMana"),		// Current amount of character mana points.
	ECT_IncreaseManaPoints	UMETA(DisplayName = "IncreaseMana"),	// Increased amount of mana.
	ECT_TotalMorale			UMETA(DisplayName = "TotalMorale"),		// Morale is based on a 100-0 scale. 100 they are happy. 0 they are miserable. The total amount percentage of damage that can be reduce is 50%.
	ECT_CurrentMorale		UMETA(DisplayName = "CurrentMorale"),	// Current amount of morale.
	ECT_ThreatLevel			UMETA(DisplayName = "ThreatLevel"),		// Threat level is the chances of damage over the aggro of a NPC.
	ECT_PhysicalDamage		UMETA(DisplayName = "PhysicalDamage"),	// Physical damage is physical weapons are blunt weapons such as bows, swords, cannon balls, explosions, and others.
	ECT_HealDamage			UMETA(DisplayName = "HealDamage"),		// General Damage is meant mostly for healing spells.
	ECT_FrostDamage			UMETA(DisplayName = "FrostDamage"),		// Magical damage is anything that is cast and created out of the air like fireballs, lightning, light attacks, and such. Frost damage is based around cold objects such as ice and snow.
	ECT_FireDamage			UMETA(DisplayName = "FireDamage"),		// Fire damage is anything to do with heat such as fire, lava, friction, and any thing else.
	ECT_EarthDamage			UMETA(DisplayName = "EarthDamage"),		// Earth damage has anything to do with earth such as rocks, stones, tree magic, soil, plants, air, and such.
	ECT_WaterDamage			UMETA(DisplayName = "WaterDamage"),		// Deals with any type of water.
	ECT_LightDamage			UMETA(DisplayName = "LightDamage"),		// Light damage is one of the most basic, but most power magic in existence. All light magic has a faster spell cast. Light is just anything to do with white light or UV.
	ECT_DarkDamage			UMETA(DisplayName = "DarkDamage"),		//  Darkness is most heavy hitting attacks that a player can control. This can break time and space due to it controlling dark matter. Dark attacks has anything to do with darkness such as show, lack of light, or dark matter. And some people can create black hole like.
	ECT_ArcaneDamage		UMETA(DisplayName = "ArcaneDamage"),	// Arcane magic is one of the rarest types of magic. Such magic has the ability to control time itself.
	ECT_AttackPower			UMETA(DisplayName = "AttackPower"),		// Attack power increases the player based physical damage.
	ECT_MagicPower			UMETA(DisplayName = "MagicPower"),		// Magic power increased the base damage around magical attacks.
	ECT_CriticalChance		UMETA(DisplayName = "CriticalChance"),	// Critical hit chances increase the chance that a attack turns into a critical hit.
	ECT_SkillSpeed			UMETA(DisplayName = "SkillSpeed"),		// Skill speed decreases the requirement for skill speed to reset, and reduces GCD.
	ECT_SpellSpeed			UMETA(DisplayName = "SpellSpeed"),		// Spell speed decreased the spells timer.
	ECT_PhysicalDefense		UMETA(DisplayName = "PhysicalDefense"),	// Physical defense only deal with physical damage. This decreased the damage that is coming into the character.
	ECT_MagicalDefense		UMETA(DisplayName = "MagicalDefense"),	// Magic defense decreased the damage taken by magical damage.
	ECT_FrostResistance		UMETA(DisplayName = "FrostResistance"),	// Frost damage resistance.
	ECT_FireResistance		UMETA(DisplayName = "FireResistance"),	// Fire damage resistance.
	ECT_WaterResistance		UMETA(DisplayName = "WaterResistance"),	// Water damage resistance.
	ECT_EarthResistance		UMETA(DisplayName = "EarthResistance"),	// Earth damage resistance.
	ECT_LightResistance		UMETA(DisplayName = "LightResistance"),	// Light damage resistance.
	ECT_DarkResistance		UMETA(DisplayName = "DarkResistance"),	// Darkness damage resistance.
	ECT_ArcaneResistance	UMETA(DisplayName = "ArcaneResistance"),// Arcane damage resistance.
	ECT_GlobalCooldown		UMETA(DisplayName = "GlobalCooldown"),	// Global cooldown is the chance that ability is affected by the timer between abilities. Abilities that are not affect by this are any type of abilities that are instant cast for magic users, and taunt like abilities for tanks.
	ECT_TotalDurability		UMETA(DIsplayName = "TotalDurability"),	// Total durability of a item.
	ECT_CurrentDurability	UMETA(DisplayName = "CurrentDura"),		// Current durability of a item.

	// Add new enums under this.
	
	ECT_Last														//		 Insert everything above this.
};