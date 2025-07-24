// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WeaverGameplayAbility.h"
#include "WeaverEnemyGameplayAbility.generated.h"

class UEnemyCombatComponent;
class AWeaverEnemyCharacter;
/**
 * 
 */
UCLASS()
class WEAVER_API UWeaverEnemyGameplayAbility : public UWeaverGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Weaver|Ability")
	AWeaverEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Weaver|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Weaver|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat);

private:
	TWeakObjectPtr<AWeaverEnemyCharacter> CachedWeaverEnemyCharacter;
};
