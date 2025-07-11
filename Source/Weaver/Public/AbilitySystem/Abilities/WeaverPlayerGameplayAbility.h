// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WeaverGameplayAbility.h"
#include "WeaverPlayerGameplayAbility.generated.h"

class UPlayerCombatComponent;
class AWeaverPlayerController;
class AWeaverPlayerCharacter;
/**
 * 
 */
UCLASS()
class WEAVER_API UWeaverPlayerGameplayAbility : public UWeaverGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Weaver|Ability")
	AWeaverPlayerCharacter* GetWeaverPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Weaver|Ability")
	AWeaverPlayerController* GetWeaverPlayerControllerFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Weaver|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Weaver|Ability")
	FGameplayEffectSpecHandle MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Ability")
	bool GetAbilityRemainingCooldownTimeByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime);

private:
	TWeakObjectPtr<AWeaverPlayerCharacter> CachedWeaverPlayerCharacter;
	TWeakObjectPtr<AWeaverPlayerController> CachedWeaverPlayerController;
};
