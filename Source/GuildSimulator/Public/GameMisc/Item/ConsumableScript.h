// Copyright (c) Astral Games. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameMisc/GuildSimEnums.h"
#include "UObject/Object.h"
#include "ConsumableScript.generated.h"

/**
 * 
 */
UCLASS()
class GUILDSIMULATOR_API UConsumableScript : public UObject
{
	GENERATED_BODY()
public:
	UConsumableScript();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Consumables")
	TEnumAsByte<EConsumableType> ConsumeType;
	
	/* Total HP added. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Consumables", meta=(ClampMin=0))
	int32 TotalHPRegain;

	/* Total MP regain. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Consumables", meta=(ClampMin=0))
	int32 TotalMPRegain;
	
	/* Total MP regain. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Consumables", meta=(ClampMin=0, ClampMax=100))
	int32 TotalEnergyRegain;

	/* Amount of time buff stays on in seconds. Max 30 minutes. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Consumables", meta=(ClampMin=0, ClampMax=600))
	float TotalSeconds;
};
