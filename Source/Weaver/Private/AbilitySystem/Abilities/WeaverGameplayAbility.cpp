// Sakurasaki All Rights Reserved.


#include "AbilitySystem/Abilities/WeaverGameplayAbility.h"

#include "AbilitySystemComponent.h"
#include "WeaverFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WeaverDebugHelper.h"
#include "WeaverGameplayTags.h"
#include "AbilitySystem/WeaverAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UWeaverGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (AbilityActivationPolicy == EWeaverAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UWeaverGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (AbilityActivationPolicy == EWeaverAbilityActivationPolicy::OnGiven)
	{
		if (ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UWeaverGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UWeaverAbilitySystemComponent* UWeaverGameplayAbility::GetWeaverAbilitySystemComponentFromActorInfo() const
{
	return Cast<UWeaverAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UWeaverGameplayAbility::NativeApplyGameplayEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle)
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	check(TargetASC && InSpecHandle.IsValid());
	
	return GetWeaverAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data,
		TargetASC
	);
}

void UWeaverGameplayAbility::ApplyGameplayEffectSpecHandleToHitTargetResults(const FGameplayEffectSpecHandle& InSpecHandle, const TArray<FHitResult>& InHitResults)
{
	if (InHitResults.IsEmpty())
	{
		return;
	}

	APawn* OwningPawn = CastChecked<APawn>(GetAvatarActorFromActorInfo());

	for (const FHitResult& Hit : InHitResults)
	{
		if (APawn* HitPawn = Cast<APawn>(Hit.GetActor()))
		{
			// if (UWeaverFunctionLibrary::IsTargetPawnHostile(OwningPawn, HitPawn))
			// {
			// 	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyGameplayEffectSpecHandleToTarget(HitPawn, InSpecHandle);
			//
			// 	if (ActiveGameplayEffectHandle.WasSuccessfullyApplied())
			// 	{
			// 		FGameplayEventData Data;
			// 		Data.Instigator = OwningPawn;
			// 		Data.Target = HitPawn;
			//
			// 		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			// 			HitPawn,
			// 			WeaverGameplayTags::Shared_Event_HitReact,
			// 			Data
			// 		);
			// 	}
			// }
		}
	}
}

FGameplayEffectSpecHandle UWeaverGameplayAbility::MakeDamageEffectSpecHandle(TSubclassOf<UGameplayEffect> EffectClass, const FScalableFloat& InBaseDamage)
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

	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		WeaverGameplayTags::Shared_SetByCaller_BaseDamage,
		InBaseDamage.GetValueAtLevel(GetAbilityLevel())
	);

	return EffectSpecHandle;
}

FActiveGameplayEffectHandle UWeaverGameplayAbility::BP_ApplyGameplayEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EWeaverSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = NativeApplyGameplayEffectSpecHandleToTarget(TargetActor, InSpecHandle);

	OutSuccessType = ActiveGameplayEffectHandle.WasSuccessfullyApplied() ? EWeaverSuccessType::Successful : EWeaverSuccessType::Failed;

	return ActiveGameplayEffectHandle;
}
