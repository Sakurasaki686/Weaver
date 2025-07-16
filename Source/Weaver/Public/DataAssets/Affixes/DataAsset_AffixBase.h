// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_AffixBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Abstract)
class WEAVER_API UDataAsset_AffixBase : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Affix")
	FGameplayTag AffixTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Affix|UI")
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Affix|UI")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Affix|UI", meta = (MultiLine = true))
	FText Description;
};
