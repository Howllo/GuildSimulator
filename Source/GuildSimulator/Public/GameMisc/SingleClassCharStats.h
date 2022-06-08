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
	USingleClassCharStats();
	
	// The quality of the weapon 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Required")
	TEnumAsByte<EItemQualityType> ItemQuality;
	
	/* Armor type. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Required|Armor")
	TEnumAsByte<EArmorType> ArmorEnum;

	/* What type of weapon that the player is using. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Required|Weapon")
	TEnumAsByte<EWeaponType> WeaponEnum;
	
	// Is it one handed or two handed.
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Required|Weapon")
	TEnumAsByte<EHandType> HandStyle;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Required")
	TMap<TEnumAsByte<ECharacterStats>, int32> CharacterStatsMap;
private:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
