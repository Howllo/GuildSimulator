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

	//	Character Stats check ECharacterStats code for explanation. 
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Character Stats")
	TMap<TEnumAsByte<ECharacterStats>, int32> CharacterStatsMap;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Character Stats|Misc")
	TMap<TEnumAsByte<ECharacterStats>, FText> StatsFText;
	
	/* Main entry for taking damage. */
	void OnHitDamage(const ACharacter* GetEnemyRef, const EDamageTypes DamageType, const bool IsCritical);

	/* Used for only alliance member of the raid. */
	void OnHitHealing(const ACharacter* GetAllianceRef, const bool IsCritical);
	
	/* Calculate the total amount of critical damage that a character will deal. */
	float GetTotalCriticalDamage(const EDamageTypes Damage) const;

	/* Takes a DamageType parameter. Returns the damage based on a switch. */
	float GetDamageTypeReturns(const EDamageTypes Damage) const;

	/* Convert any percentage based stats to percentage. */
	float static ConvertStatsToPercentage(const int32 IncomingStats);

	/* Check to see if character is dead or not. */
	bool IsCharacterDead() const;

	/**
	 * @brief Used for adding or removing stats from the character that the component is attached to.
	 * @param IncomingItem - Used to get the stats from the items.
	 * @param bIsRemoved - If true it will remove the stats from the character.
	 */
	void AddEquipmentStats(const UItem* IncomingItem, bool bIsRemoved);
protected:
	//protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Only for use of loading StatsFText Map.
	void FEnumToString();
};
