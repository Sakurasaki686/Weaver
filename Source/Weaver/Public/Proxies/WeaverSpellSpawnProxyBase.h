// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "WeaverSpellSpawnProxyBase.generated.h"

class UDataAsset_EffectBase;
class UDataAsset_ElementBase;

UCLASS()
class WEAVER_API AWeaverSpellSpawnProxyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaverSpellSpawnProxyBase();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Spawn Proxy")
	void ExecuteSpawn(AActor* InInstigator, const FGameplayTag& InTunerTag, UDataAsset_ElementBase* InElementDA, UDataAsset_EffectBase* InEffectDA);
};
