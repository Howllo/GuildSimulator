// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GuildSimEnums.h"
#include "UObject/Object.h"
#include "SingleClassCharStats.generated.h"

/**
 * 
 */
UCLASS()
class GUILDSIMULATOR_API USingleClassCharStats : public UObject
{
	GENERATED_BODY()
public:
	/* What type of weapon that the player is using. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Required")
	TEnumAsByte<WeaponType> WeaponEnum;

	// Is it one handed or two handed.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Required")
	TEnumAsByte<EHandType> HandStyle;
	
	/* Armor type. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Required")
	TEnumAsByte<ArmorType> ArmorEnum;

	// The quality of the weapon 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Required")
	TEnumAsByte<ItemQualityType> WeaponQuality;
	
	/* Set static mesh for it be exist in World. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Armor")
	int32 TotalDurability;
	
	/* Set static mesh for it be exist in World. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Armor")
	int32 CurrentDurability;
	
	/* Increase the amount of health the character has. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Character Attributes")
	int32 IncreasedHealthPoints;

	/* Increase the amount of mana that a character has. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Attributes")
	int32 IncreasedManaPoints;

	/* Physical damage is physical weapons are blunt weapons such as
	 * bows, swords, cannon balls, explosions, and others.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Damage")
	int32 BasePhysicalDamage;

	/* general Damage is meant mostly for healing spells. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character Damage")
	int32 TotalGeneralDamage;
	
	/* Magical damage is anything that is cast and created out of the air like
	 * fireballs, lightning, light attacks, and such. Frost damage is based around
	 * cold objects such as ice and snow.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalFrostDamage;

	/* Fire damage is anything to do with heat such as fire, lava, friction, and
	 * any thing else.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalFireDamage;

	/*	Earth damage has anything to do with earth such as rocks, stones, tree magic,
	 *	soil, plants, air, and such.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalEarthDamage;

	/*	Deals with any type of water. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalWaterDamage;
	
	/* Light damage is one of the most basic, but most power magic in existence. All
	 * light magic has a faster spell cast. Light is just anything to do with white light or UV.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalLightDamage;

	/* Darkness is most heavy hitting attacks that a player can control. This can break time and space due to
	 * it controlling dark matter. Dark attacks has anything to do with darkness such as show, lack of light,
	 * or dark matter. And some people can create black hole like.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalDarkDamage;

	/*Arcane magic is one of the rarest types of magic. Such magic has the ability to control time itself.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalArcaneDamage;

	/*Attack power increases teh player based physical damage.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Damage")
	int32 AttackPower;
	
	/*Attack magic power increased the base damage around magical attacks.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Damage")
	int32 MagicPower;

	/*Critical hit chances increase the chance that a attack turns into a critical hit.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Damage", meta=(ClampMin=0, ClampMax=500))
	float CriticalHitChance;
	
	/* kill speed decreases the requirement for skill speed to reset, and reduces GCD. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Abilities")
	int32 SkillSpeed;

	/* Spell speed decreased the spells timer. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Abilities")
	int32 SpellSpeed;

	/* Physical defense only deal with physical damage. This decreased the damage that is coming into the character. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=1000))
	int32 PhysicalDefense;

	/*Magic defense decreased the damage taken by magical damage.*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=1000))
	int32 MagicalDefense;

	/* Frost damage resistance. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 FrostResistance;

	/* Fire damage resistance. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 FireResistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 WaterResistance;

	/* Earth damage resistance. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 EarthResistance;

	/* Light damage resistance. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 LightResistance;

	/* Dark damage resistance. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 DarkResistance;

	/* Arcane damage resistance. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 ArcaneResistance;
};
