// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Affixes/DataAsset_AffixBase.h"
#include "WeaverTypes/WeaverEnumTypes.h"
#include "DataAsset_EffectBase.generated.h"

class UProjectileExtensionComponentBase;
/**
 * 
 */
UCLASS()
class WEAVER_API UDataAsset_EffectBase : public UDataAsset_AffixBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	EWeaverEffectTriggerPhase TriggerPhase = EWeaverEffectTriggerPhase::OnSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Effect")
	TSubclassOf<UProjectileExtensionComponentBase> EffectComponentClass;
};
