// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WeaverTypes/WeaverStructTypes.h"
#include "AffixPoolSubsystem.generated.h"

class UDataAsset_EffectBase;
class UDataAsset_ElementBase;

USTRUCT(BlueprintType)
struct FAffixCombination
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "Affix")
	TSoftObjectPtr<UDataAsset_ElementBase> ElementAffix;

	UPROPERTY(BlueprintReadOnly, Category = "Affix")
	TSoftObjectPtr<UDataAsset_EffectBase> EffectAffix;

	bool operator==(const FAffixCombination& Other) const
	{
		return ElementAffix == Other.ElementAffix && EffectAffix == Other.EffectAffix;
	}
};

template<>
struct TStructOpsTypeTraits<FAffixCombination> : public TStructOpsTypeTraitsBase2<FAffixCombination>
{
	enum
	{
		WithIdenticalViaEquality = true,
		WithGetTypeHash = true
	};
};

FORCEINLINE uint32 GetTypeHash(const FAffixCombination& Combo)
{
	return HashCombine(GetTypeHash(Combo.ElementAffix), GetTypeHash(Combo.EffectAffix));
}

/**
 * 
 */
UCLASS(Blueprintable)
class WEAVER_API UAffixPoolSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Affix Pool")
	void AddAffixCombinationToPool(UDataAsset_ElementBase* InElement, UDataAsset_EffectBase* InEffect);

	UFUNCTION(BlueprintCallable, Category = "Affix Pool")
	bool GetRandomAffixCombination(FAffixCombination& OutCombination);

protected:
	UPROPERTY()
	TSet<FAffixCombination> AffixPool;
};
