// Copyright (c) Astral Games. All right reserved.


#include "GameMisc/SingleClassCharStats.h"

USingleClassCharStats::USingleClassCharStats()
{
	for(int32 i = ECT_NONE + 1; i != ECT_Last; i++)
	{
		const ECharacterStats CharacterStats = static_cast<ECharacterStats>(i);
		CharacterStatsMap.Add(CharacterStats, 0);
	}
}



#if WITH_EDITOR // Limits
void USingleClassCharStats::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	
}
#endif
