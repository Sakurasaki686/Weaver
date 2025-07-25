// Sakurasaki All Rights Reserved.


#include "AbilitySystem/WeaverAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WeaverDebugHelper.h"
#include "WeaverFunctionLibrary.h"
#include "WeaverGameplayTags.h"

UWeaverAttributeSet::UWeaverAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitAttackMultiplier(1.f);
	InitDefensePower(1.f);
}

void UWeaverAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	// 处理生命值
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);
	}

	// 处理受到的伤害
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float OldHealth = GetCurrentHealth();
		const float DamageDone = GetDamageTaken();

		const float NewCurrentHealth = FMath::Clamp(OldHealth - DamageDone, 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		const FString DebugString = FString::Printf(
			TEXT("Old Health: %f, Damage Done: %f, NewCurrentHealth: %f"),
			OldHealth,
			DamageDone,
			NewCurrentHealth
		);

		Debug::Print(DebugString, FColor::Green);

		if (GetCurrentHealth() == 0.f)
		{
			UWeaverFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WeaverGameplayTags::Shared_Status_Dead);
		}
	}
}
