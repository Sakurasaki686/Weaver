// Sakurasaki All Rights Reserved.


#include "AbilitySystem/Abilities/WeaverEnemyGameplayAbility.h"

#include "WeaverGameplayTags.h"
#include "AbilitySystem/WeaverAbilitySystemComponent.h"
#include "Characters/WeaverEnemyCharacter.h"

AWeaverEnemyCharacter* UWeaverEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if (!CachedWeaverEnemyCharacter.IsValid())
	{
		CachedWeaverEnemyCharacter = Cast<AWeaverEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}

	return CachedWeaverEnemyCharacter.IsValid() ? CachedWeaverEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UWeaverEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UWeaverEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(EffectClass);

	FGameplayEffectContextHandle ContextHandle = GetWeaverAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle EffectSpecHandle = GetWeaverAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		EffectClass,
		GetAbilityLevel(),
		ContextHandle
	);

	// EffectSpecHandle.Data->SetSetByCallerMagnitude(
	// 	WeaverGameplayTags::Shared_SetByCaller_BaseDamage,
	// 	InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel())
	// );

	return EffectSpecHandle;
}
