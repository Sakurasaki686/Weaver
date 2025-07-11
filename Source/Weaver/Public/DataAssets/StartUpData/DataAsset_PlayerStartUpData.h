// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/DataAsset_StartUpDataBase.h"
#include "WeaverTypes/WeaverStructTypes.h"
#include "DataAsset_PlayerStartUpData.generated.h"

class UGameplayEffect;
class UWeaverGameplayAbility;
class UWeaverAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WEAVER_API UDataAsset_PlayerStartUpData : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWeaverAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FWeaverPlayerAbilitySet> PlayerStartUpAbilitySets;
};
