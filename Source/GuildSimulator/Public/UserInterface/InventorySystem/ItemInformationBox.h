// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemInformationBox.generated.h"

class UImage;
class UTextBlock;
class UButton;
class UVerticalBox;
class UHorizontalBox;

/**
 * 
 */
UCLASS()
class GUILDSIMULATOR_API UItemInformationBox : public UUserWidget
{
	GENERATED_BODY()
public:
	//Called by Blueprint
	UFUNCTION(BlueprintCallable)
	void OnStatsClick();

	//Called by Blueprint
	UFUNCTION(BlueprintCallable)
	void OnItemInfoClick();

	/**
	 * @brief Set all text block elements to collapsed.
	 */
	void SetAllCollapse() const;
	
	UPROPERTY(meta=(BindWidget))
	UImage* BackgroundRarity;

	UPROPERTY(meta=(BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta=(BindWidget))
	UButton* StatsInformation;

	UPROPERTY(meta=(BindWidget))
	UButton* ItemInformation;

	UPROPERTY(meta=(BindWidget))
	UVerticalBox* VerticalBox; 
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemDescription;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* ButtonHorizontalBox;

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* IconScrollBarBox;

	/* Set static mesh for it be exist in World. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Durability;
	
	// Stats
	/* Physical damage is physical weapons are blunt weapons such as
	 * bows, swords, cannon balls, explosions, and others.
	 */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* BasePhysicalDamage;

	/* general Damage is meant mostly for healing spells. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TotalGeneralDamage;

	/* Magical damage is anything that is cast and created out of the air like
	 * fireballs, lightning, light attacks, and such. Frost damage is based around
	 * cold objects such as ice and snow.
	 */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TotalFrostDamage;

	/* Fire damage is anything to do with heat such as fire, lava, friction, and
	 * any thing else.
	 */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TotalFireDamage;

	/*	Earth damage has anything to do with earth such as rocks, stones, tree magic,
	 *	soil, plants, air, and such.
	 */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TotalEarthDamage;

	/*	Deals with any type of water. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TotalWaterDamage;
	
	/* Light damage is one of the most basic, but most power magic in existence. All
	 * light magic has a faster spell cast. Light is just anything to do with white light or UV.
	 */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TotalLightDamage;

	/* Darkness is most heavy hitting attacks that a player can control. This can break time and space due to
	 * it controlling dark matter. Dark attacks has anything to do with darkness such as show, lack of light,
	 * or dark matter. And some people can create black hole like.
	 */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* TotalDarkDamage;

	/*Arcane magic is one of the rarest types of magic. Such magic has the ability to control time itself.*/
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  TotalArcaneDamage;
	
	/* Increase the amount of health the character has. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* IncreasedHealthPoints;

	/* Increase the amount of mana that a character has. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock* IncreasedManaPoints;

	/*Attack power increases teh player based physical damage.*/
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  AttackPower;
	
	/*Attack magic power increased the base damage around magical attacks.*/
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  MagicPower;

	/*Critical hit chances increase the chance that a attack turns into a critical hit.*/
	UPROPERTY(meta=(BindWidget))
	UTextBlock* CriticalHitChance;
	
	/* kill speed decreases the requirement for skill speed to reset, and reduces GCD. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  SkillSpeed;

	/* Spell speed decreased the spells timer. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  SpellSpeed;

	/* Physical defense only deal with physical damage. This decreased the damage that is coming into the character. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  PhysicalDefense;

	/*Magic defense decreased the damage taken by magical damage.*/
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  MagicalDefense;

	/* Frost damage resistance. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  FrostResistance;

	/* Fire damage resistance. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  FireResistance;

	UPROPERTY(meta=(BindWidget))
	UTextBlock*  WaterResistance;

	/* Earth damage resistance. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  EarthResistance;

	/* Light damage resistance. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  LightResistance;

	/* Dark damage resistance. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  DarkResistance;

	/* Arcane damage resistance. */
	UPROPERTY(meta=(BindWidget))
	UTextBlock*  ArcaneResistance;
};
