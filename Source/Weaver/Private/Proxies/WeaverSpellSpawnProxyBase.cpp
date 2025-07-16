// Sakurasaki All Rights Reserved.


#include "Proxies/WeaverSpellSpawnProxyBase.h"

AWeaverSpellSpawnProxyBase::AWeaverSpellSpawnProxyBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AWeaverSpellSpawnProxyBase::ExecuteSpawn_Implementation(AActor* InInstigator, const FGameplayTag& InTunerTag, UDataAsset_ElementBase* InElementDA, UDataAsset_EffectBase* InEffectDA)
{
}
