// Sakurasaki All Rights Reserved.


#include "AbilitySystem/Abilities/WeaverPlayerGameplayAbility.h"

#include "AbilitySystem/WeaverAbilitySystemComponent.h"
#include "Characters/WeaverPlayerCharacter.h"
#include "Controllers/WeaverPlayerController.h"

AWeaverPlayerCharacter* UWeaverPlayerGameplayAbility::GetWeaverPlayerCharacterFromActorInfo()
{
	if (!CachedWeaverPlayerCharacter.IsValid())
	{
		CachedWeaverPlayerCharacter = Cast<AWeaverPlayerCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedWeaverPlayerCharacter.IsValid() ? CachedWeaverPlayerCharacter.Get() : nullptr;
}

AWeaverPlayerController* UWeaverPlayerGameplayAbility::GetWeaverPlayerControllerFromActorInfo()
{
	if (!CachedWeaverPlayerController.IsValid())
	{
		CachedWeaverPlayerController = Cast<AWeaverPlayerController>(CurrentActorInfo->PlayerController);
	}

	return CachedWeaverPlayerController.IsValid() ? CachedWeaverPlayerController.Get() : nullptr;
}

UPlayerCombatComponent* UWeaverPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetWeaverPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}

FGameplayEffectSpecHandle UWeaverPlayerGameplayAbility::MakePlayerDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InUsedComboCount)
{
	// check(EffectClass);
	//
	// FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	// ContextHandle.SetAbility(this);
	// ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	// ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	//
	// FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
	// 	EffectClass,
	// 	GetAbilityLevel(),
	// 	ContextHandle
	// );
	//
	// EffectSpecHandle.Data->SetSetByCallerMagnitude(
	// 	WeaverGameplayTags::Shared_SetByCaller_BaseDamage,
	// 	InWeaponBaseDamage
	// );
	//
	// if (InCurrentAttackTypeTag.IsValid())
	// {
	// 	EffectSpecHandle.Data->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InUsedComboCount);
	// }
	//
	// return EffectSpecHandle;

	return nullptr;
}

bool UWeaverPlayerGameplayAbility::GetAbilityRemainingCooldownTimeByTag(FGameplayTag InCooldownTag, float& TotalCooldownTime, float& RemainingCooldownTime)
{
	check(InCooldownTag.IsValid());

	FGameplayEffectQuery CooldownQuery = FGameplayEffectQuery::MakeQuery_MatchAnyOwningTags(InCooldownTag.GetSingleTagContainer());

	TArray<TPair<float, float>> TimeRemainingAndDuration = GetWeaverAbilitySystemComponentFromActorInfo()->GetActiveEffectsTimeRemainingAndDuration(CooldownQuery);

	if (!TimeRemainingAndDuration.IsEmpty())
	{
		RemainingCooldownTime = TimeRemainingAndDuration[0].Key;
		TotalCooldownTime = TimeRemainingAndDuration[0].Value;
	}

	return RemainingCooldownTime > 0.f;
}
