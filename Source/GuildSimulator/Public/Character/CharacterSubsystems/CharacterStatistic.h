// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameMisc/GuildSimEnums.h"
#include "Components/ActorComponent.h"
#include "CharacterStatistic.generated.h"

class UItem;
class ARaidPlayerCharacter;
class AOverworldPlayerCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GUILDSIMULATOR_API UCharacterStatistic : public UActorComponent
{
	GENERATED_BODY()

	/* Parent actor of the component. */
	UPROPERTY()
	ARaidPlayerCharacter* RaidPlayer;

	UPROPERTY()
	AOverworldPlayerCharacter* PlayerChar;

	//TODO: Add NPCs
public:
	// Sets default values for this component's properties
	UCharacterStatistic();
	
	/*The total amount of character health.*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Properities")
	int32 TotalHealthPoints;

	/*Current amount of the player HP.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Properities")
	int32 CurrentHealthPoint;

	/*Total amount of energy points.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properities")
	int32 TotalEnergyPoints;

	/*Current amount of energy points.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(ClampMax=100, ClampMin = 0), Category = "Character Properities")
	int32 CurrentEnergyPoints;

	/*Total amount of character mana points.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properities")
	int32 TotalManaPoints;

	/*Current amount of character mana points.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Properities")
	int32 CurrentManaPoints;
	
	/* Morale is based on a 100-0 scale. 100 they are happy. 0 they are miserable.
	 * The total amount percentage of damage that can be reduce is 50%.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMax = 100), meta=(ClampMin = 0), Category = "Character Properities")
	int32 TotalMorale;

	/*  Current amount of morale.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character Properities")
	int32 CurrentMorale;

	/*Threat level is the chances of damage over the aggro of a NPC.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Properities")
	int32 ThreatLevel;

	/* Physical damage is physical weapons are blunt weapons such as
	 * bows, swords, cannon balls, explosions, and others.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage")
	int32 BasePhysicalDamage;

	/* general Damage is meant mostly for healing spells. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Damage")
	int32 TotalGeneralDamage;
	
	/* Magical damage is anything that is cast and created out of the air like
	 * fireballs, lightning, light attacks, and such. Frost damage is based around
	 * cold objects such as ice and snow.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalFrostDamage;

	/* Fire damage is anything to do with heat such as fire, lava, friction, and
	 * any thing else.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalFireDamage;

	/*	Earth damage has anything to do with earth such as rocks, stones, tree magic,
	 *	soil, plants, air, and such.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalEarthDamage;

	/*	Deals with any type of water. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalWaterDamage;
	
	/* Light damage is one of the most basic, but most power magic in existence. All
	 * light magic has a faster spell cast. Light is just anything to do with white light or UV.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalLightDamage;

	/* Darkness is most heavy hitting attacks that a player can control. This can break time and space due to
	 * it controlling dark matter. Dark attacks has anything to do with darkness such as show, lack of light,
	 * or dark matter. And some people can create black hole like.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalDarkDamage;

	/*Arcane magic is one of the rarest types of magic. Such magic has the ability to control time itself.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage")
	int32 TotalArcaneDamage;

	/*Attack power increases teh player based physical damage.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage")
	int32 AttackPower;
	
	/*Attack magic power increased the base damage around magical attacks.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage")
	int32 MagicPower;

	/*Critical hit chances increase the chance that a attack turns into a critical hit.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Damage", meta=(ClampMin=0, ClampMax=500))
	float CriticalHitChance;

	/* Global cooldown is the chance that ability is affected by the timer between abilities.
	 * Abilities that are not affect by this are any type of abilities that are instant cast for
	 * magic users, and taunt like abilities for tanks.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMax = 3.f), meta=(ClampMin = 1.f), Category = "Character Abilities")
	float GlobalCoolDown;
	
	/*Skill speed decreases the requirement for skill speed to reset, and reduces GCD.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Abilities")
	int32 SkillSpeed;

	/*Spell speed decreased the spells timer.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Abilities")
	int32 SpellSpeed;

	/*Physical defense only deal with physical damage. This decreased the damage that is coming into the character.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=1000))
	int32 PhysicalDefense;

	/*Magic defense decreased the damage taken by magical damage.*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=1000))
	int32 MagicalDefense;

	/* Frost damage resistance. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 FrostResistance;

	/* Fire damage resistance. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 FireResistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 WaterResistance;

	/* Earth damage resistance. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 EarthResistance;

	/* Light damage resistance. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 LightResistance;

	/* Dark damage resistance. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 DarkResistance;

	/* Arcane damage resistance. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Defense", meta=(ClampMin=0, ClampMax=300))
	int32 ArcaneResistance;
	
	/* Main entry for taking damage. */
	void OnHitDamage(const ACharacter* GetEnemyRef, const DamageTypes DamageType, const bool IsCritical);

	/* Used for only alliance member of the raid. */
	void OnHitHealing(const ACharacter* GetAllianceRef, const bool IsCritical);
	
	/* Calculate the total amount of critical damage that a character will deal. */
	float GetTotalCriticalDamage(const DamageTypes Damage) const;

	/* Takes a DamageType parameter. Returns the damage based on a switch. */
	float GetDamageTypeReturns(const DamageTypes Damage) const;

	/* Convert any percentage based stats to percentage. */
	float static ConvertStatsToPercentage(const int32 IncomingStats);

	/* Check to see if character is dead or not. */
	bool IsCharacterDead() const;

	/**
	 * @brief Used for adding or removing stats from the character that the component is attached to.
	 * @param IncomingItem - Used to get the stats from the items.
	 * @param bIsRemoved - If true it will remove the stats from the character.
	 */
	void EquipmentStats(const UItem* IncomingItem, bool bIsRemoved);
protected:
	//protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
