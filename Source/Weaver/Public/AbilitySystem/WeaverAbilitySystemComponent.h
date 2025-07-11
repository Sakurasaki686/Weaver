// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WeaverAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class WEAVER_API UWeaverAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);

	// UFUNCTION(BlueprintCallable, Category = "Weaver|Ability", meta = (ApplyLevel = "1"))
	// void GrantHeroWeaponAbilities(const TArray<FWeaverPlayerAbilitySet>& InDefaultWeaponAbilities, const TArray<FWeaverPlayerAbilitySet>& InSpecialWeaponAbilities, int32 ApplyLevel, TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles);
	//
	// UFUNCTION(BlueprintCallable, Category = "Weaver|Ability")
	// void RemoveGrantedHeroWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandlesToRemove);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Ability")
	bool TryActivateAbilityByTag(FGameplayTag AbilityTagToActivate);
};
