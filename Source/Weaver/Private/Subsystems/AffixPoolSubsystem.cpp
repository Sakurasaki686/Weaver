// Sakurasaki All Rights Reserved.


#include "DataAssets/Affixes/DataAsset_ElementBase.h"
#include "DataAssets/Affixes/DataAsset_EffectBase.h"
#include "Subsystems/AffixPoolSubsystem.h"

void UAffixPoolSubsystem::AddAffixCombinationToPool(UDataAsset_ElementBase* InElement, UDataAsset_EffectBase* InEffect)
{
	if (!InElement || !InEffect)
	{
		return;
	}

	FAffixCombination NewCombination;
	NewCombination.ElementAffix = InElement;
	NewCombination.EffectAffix = InEffect;
	
	AffixPool.Add(NewCombination);
}

bool UAffixPoolSubsystem::GetRandomAffixCombination(FAffixCombination& OutCombination)
{
	if (AffixPool.Num() == 0)
	{
		return false;
	}

	const TArray<FAffixCombination> PoolAsArray = AffixPool.Array();
	
	const int32 RandomIndex = FMath::RandRange(0, PoolAsArray.Num() - 1);
	OutCombination = PoolAsArray[RandomIndex];

	return true;
}
