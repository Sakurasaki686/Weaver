// Sakurasaki All Rights Reserved.


#include "AbilitySystem/WeaverAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WeaverDebugHelper.h"
#include "WeaverFunctionLibrary.h"
#include "WeaverGameplayTags.h"
#include "Characters/WeaverBaseCharacter.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/PlayerUIComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/PawnUIInterface.h"

UWeaverAttributeSet::UWeaverAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitAttackMultiplier(1.f);
	InitDefensePower(1.f);
	InitMovementSpeedMultiplier(1.f);
	InitMaxRunSpeed(600.f);
	InitMaxWalkSpeed(200.f);
	InitAether(0.f);
}

void UWeaverAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s didn't implement IPawnUIInterface!"), *Data.Target.GetAvatarActor()->GetName());

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();

	checkf(PawnUIComponent, TEXT("Couldn't extract a PawnUIComponent from %s!"), *Data.Target.GetAvatarActor()->GetName());
	
	// 处理生命值
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth());

		SetCurrentHealth(NewCurrentHealth);

		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() <= 0.f)
		{
			UWeaverFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WeaverGameplayTags::Shared_Status_Dead);
		}
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
		
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());

		if (GetCurrentHealth() <= 0.f)
		{
			UWeaverFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WeaverGameplayTags::Shared_Status_Dead);
		}
	}

	// 处理 Aether
	if (Data.EvaluatedData.Attribute == GetAetherAttribute())
	{
		const float NewAether = FMath::Max(0.f, GetAether());

		SetAether(NewAether);

		if (UPlayerUIComponent* PlayerUIComponent = Cast<UPlayerUIComponent>(PawnUIComponent))
		{
			PlayerUIComponent->OnAetherAmountChanged.Broadcast(NewAether);
		}
	}
}
