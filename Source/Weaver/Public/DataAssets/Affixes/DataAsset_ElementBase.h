// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/Affixes/DataAsset_AffixBase.h"
#include "DataAsset_ElementBase.generated.h"

class UProjectileExtensionComponentBase;
class UGameplayEffect;
class AWeaverProjectileBase;
/**
 * 
 */
UCLASS()
class WEAVER_API UDataAsset_ElementBase : public UDataAsset_AffixBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
	TSubclassOf<AWeaverProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
	TSubclassOf<UGameplayEffect> BaseDamageEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Element")
	TSubclassOf<UProjectileExtensionComponentBase> ElementEffectComponentClass;
};
