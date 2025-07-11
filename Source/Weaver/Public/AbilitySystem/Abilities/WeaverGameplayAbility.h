// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WeaverTypes/WeaverEnumTypes.h"
#include "WeaverGameplayAbility.generated.h"

class UWeaverAbilitySystemComponent;
class UPawnCombatComponent;

UENUM(BlueprintType)
enum class EWeaverAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class WEAVER_API UWeaverGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface

	UPROPERTY(EditDefaultsOnly, Category = "WeaverAbility")
	EWeaverAbilityActivationPolicy AbilityActivationPolicy = EWeaverAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category = "Weaver|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category = "Weaver|Ability")
	UWeaverAbilitySystemComponent* GetWeaverAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyGameplayEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Ability", meta = (DisplayName = "Apply Gameplay Effect Spec Handle To Target", ExpandEnumAsExecs = "OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyGameplayEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EWeaverSuccessType& OutSuccessType);

	UFUNCTION(BlueprintCallable, Category = "Weaver|Ability")
	void ApplyGameplayEffectSpecHandleToHitTargetResults(const FGameplayEffectSpecHandle& InSpecHandle, const TArray<FHitResult>& InHitResults);
};
