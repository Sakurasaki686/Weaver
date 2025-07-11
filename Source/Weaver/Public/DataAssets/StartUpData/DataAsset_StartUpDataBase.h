// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UGameplayEffect;
class UWeaverGameplayAbility;
class UWeaverAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WEAVER_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UWeaverAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWeaverGameplayAbility>> ActivateOnGivenAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UWeaverGameplayAbility>> ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;

	void GrantAbilities(const TArray<TSubclassOf<UWeaverGameplayAbility>>& InAbilitiesToGive, UWeaverAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
