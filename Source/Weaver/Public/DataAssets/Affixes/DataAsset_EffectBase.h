// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Affixes/DataAsset_AffixBase.h"
#include "WeaverTypes/WeaverEnumTypes.h"
#include "DataAsset_EffectBase.generated.h"

class AWeaverSpellSpawnProxyBase;
class UProjectileExtensionComponentBase;
/**
 * 
 */
UCLASS(BlueprintType)
class WEAVER_API UDataAsset_EffectBase : public UDataAsset_AffixBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	EWeaverEffectTriggerPhase TriggerPhase = EWeaverEffectTriggerPhase::AfterCast;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	TSubclassOf<UProjectileExtensionComponentBase> EffectComponentClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect", meta = (EditCondition = "TriggerPhase == EWeaverEffectTriggerPhase::OnCast"))
	TSubclassOf<AWeaverSpellSpawnProxyBase> SpawnProxyClass;
};
