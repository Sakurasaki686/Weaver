// Sakurasaki All Rights Reserved.


#include "Components/Combat/PlayerCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WeaverDebugHelper.h"
#include "WeaverGameplayTags.h"
#include "AbilitySystem/WeaverAbilitySystemComponent.h"
#include "Characters/WeaverPlayerCharacter.h"
#include "Components/UI/PlayerUIComponent.h"
#include "DataAssets/Affixes/DataAsset_AffixBase.h"
#include "DataAssets/Affixes/DataAsset_EffectBase.h"
#include "DataAssets/Affixes/DataAsset_ElementBase.h"
#include "DataAssets/Affixes/DataAsset_TunerBase.h"
#include "Items/Weapons/WeaverPlayerWeapon.h"

UPlayerCombatComponent::UPlayerCombatComponent()
{
	CategorizedAffixes.Add(WeaverGameplayTags::Shared_Projectile_Affix_Tuner, FAffixCategory());
	CategorizedAffixes.Add(WeaverGameplayTags::Shared_Projectile_Affix_Element, FAffixCategory());
	CategorizedAffixes.Add(WeaverGameplayTags::Shared_Projectile_Affix_Effect, FAffixCategory());
}

void UPlayerCombatComponent::BeginPlay()
{
	Super::BeginPlay();
}

AWeaverPlayerWeapon* UPlayerCombatComponent::GetPlayerCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<AWeaverPlayerWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

AWeaverPlayerWeapon* UPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
	return Cast<AWeaverPlayerWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UPlayerCombatComponent::GetPlayerCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UPlayerCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	Super::OnHitTargetActor(HitActor);
}

void UPlayerCombatComponent::OnWeaponPulledFromTargetActor(AActor* InteractedActor)
{
	Super::OnWeaponPulledFromTargetActor(InteractedActor);
}

UDataAsset_TunerBase* UPlayerCombatComponent::GetSelectedTuner() const
{
	const FAffixCategory* TunerAffixesManager = CategorizedAffixes.Find(WeaverGameplayTags::Shared_Projectile_Affix_Tuner);

	if (!TunerAffixesManager)
	{
		return nullptr;
	}

	TArray<TObjectPtr<UDataAsset_AffixBase>> AcquiredAffixes = TunerAffixesManager->AcquiredAffixes;
	if (AcquiredAffixes.IsEmpty())
	{
		return nullptr;
	}

	TObjectPtr<UDataAsset_AffixBase> SelectedTuner = AcquiredAffixes[TunerAffixesManager->SelectedIndex];

	return Cast<UDataAsset_TunerBase>(SelectedTuner.Get());
}

FGameplayTag UPlayerCombatComponent::GetSelectedTunerTag() const
{
	UDataAsset_TunerBase* Tuner = GetSelectedTuner();

	if (Tuner && Tuner->AffixTag.IsValid())
	{
		return Tuner->AffixTag;
	}

	return FGameplayTag();
}

UDataAsset_ElementBase* UPlayerCombatComponent::GetSelectedElement() const
{
	const FAffixCategory* ElementAffixesManager = CategorizedAffixes.Find(WeaverGameplayTags::Shared_Projectile_Affix_Element);

	if (!ElementAffixesManager)
	{
		return nullptr;
	}

	TArray<TObjectPtr<UDataAsset_AffixBase>> AcquiredAffixes = ElementAffixesManager->AcquiredAffixes;
	if (AcquiredAffixes.IsEmpty())
	{
		return nullptr;
	}

	TObjectPtr<UDataAsset_AffixBase> SelectedElement = AcquiredAffixes[ElementAffixesManager->SelectedIndex];

	return Cast<UDataAsset_ElementBase>(SelectedElement.Get());
}

UDataAsset_EffectBase* UPlayerCombatComponent::GetSelectedEffect() const
{
	const FAffixCategory* EffectAffixesManager = CategorizedAffixes.Find(WeaverGameplayTags::Shared_Projectile_Affix_Effect);

	if (!EffectAffixesManager)
	{
		return nullptr;
	}

	TArray<TObjectPtr<UDataAsset_AffixBase>> AcquiredAffixes = EffectAffixesManager->AcquiredAffixes;
	if (AcquiredAffixes.IsEmpty())
	{
		return nullptr;
	}

	TObjectPtr<UDataAsset_AffixBase> SelectedEffect = AcquiredAffixes[EffectAffixesManager->SelectedIndex];

	return Cast<UDataAsset_EffectBase>(SelectedEffect.Get());
}

void UPlayerCombatComponent::SetSelectedTuner(UDataAsset_TunerBase* InTuner)
{
	if (InTuner == nullptr)
	{
		Debug::Print(TEXT("InTuner is null, cannot set selected tuner."), FColor::Red, 5.f);
		return;
	}
	
	// Set 的前提是玩家已经拥有当前词缀，如果没有，则不能 Set
	FAffixCategory* TunerAffixesManager = CategorizedAffixes.Find(WeaverGameplayTags::Shared_Projectile_Affix_Tuner);

	if (!TunerAffixesManager)
	{
		Debug::Print(TEXT("Tuner Affixes Category not found."), FColor::Red, 5.f);
		return;
	}

	TArray<TObjectPtr<UDataAsset_AffixBase>> AcquiredAffixes = TunerAffixesManager->AcquiredAffixes;

	const int32 FoundIndex = AcquiredAffixes.Find(InTuner);
	if (FoundIndex != INDEX_NONE)
	{
		TunerAffixesManager->SelectedIndex = FoundIndex;

		GetOwner<AWeaverPlayerCharacter>()->GetPlayerUIComponent()->OnTunerChanged.Broadcast(InTuner);
	}
	else
	{
		const FString DebugMessage = FString::Printf(
			TEXT("Player does not own the Tuner affix: %s"),
			*InTuner->GetName()
		);
		Debug::Print(DebugMessage, FColor::Red, 5.f);
	}
}

void UPlayerCombatComponent::SetSelectedElement(UDataAsset_ElementBase* InElement)
{
	if (InElement == nullptr)
	{
		Debug::Print(TEXT("InElement is null, cannot set selected element."), FColor::Red, 5.f);
		return;
	}
	
	// Set 的前提是玩家已经拥有当前词缀，如果没有，则不能 Set
	FAffixCategory* ElementAffixesManager = CategorizedAffixes.Find(WeaverGameplayTags::Shared_Projectile_Affix_Element);

	if (!ElementAffixesManager)
	{
		Debug::Print(TEXT("Element Affixes Category not found."), FColor::Red, 5.f);
		return;
	}

	TArray<TObjectPtr<UDataAsset_AffixBase>> AcquiredAffixes = ElementAffixesManager->AcquiredAffixes;

	const int32 FoundIndex = AcquiredAffixes.Find(InElement);
	if (FoundIndex != INDEX_NONE)
	{
		ElementAffixesManager->SelectedIndex = FoundIndex;

		GetOwner<AWeaverPlayerCharacter>()->GetPlayerUIComponent()->OnElementChanged.Broadcast(InElement);
	}
	else
	{
		const FString DebugMessage = FString::Printf(
			TEXT("Player does not own the element affix: %s"),
			*InElement->GetName()
		);
		Debug::Print(DebugMessage, FColor::Red, 5.f);
	}
}

void UPlayerCombatComponent::SetSelectedEffect(UDataAsset_EffectBase* InEffect)
{
	if (InEffect == nullptr)
	{
		Debug::Print(TEXT("InEffect is null, cannot set selected effect."), FColor::Red, 5.f);
		return;
	}
	
	// Set 的前提是玩家已经拥有当前词缀，如果没有，则不能 Set
	FAffixCategory* EffectAffixesManager = CategorizedAffixes.Find(WeaverGameplayTags::Shared_Projectile_Affix_Effect);

	if (!EffectAffixesManager)
	{
		Debug::Print(TEXT("Effect Affixes Category not found."), FColor::Red, 5.f);
		return;
	}

	TArray<TObjectPtr<UDataAsset_AffixBase>> AcquiredAffixes = EffectAffixesManager->AcquiredAffixes;

	const int32 FoundIndex = AcquiredAffixes.Find(InEffect);
	if (FoundIndex != INDEX_NONE)
	{
		EffectAffixesManager->SelectedIndex = FoundIndex;

		GetOwner<AWeaverPlayerCharacter>()->GetPlayerUIComponent()->OnEffectChanged.Broadcast(InEffect);
	}
	else
	{
		const FString DebugMessage = FString::Printf(
			TEXT("Player does not own the effect affix: %s"),
			*InEffect->GetName()
		);
		Debug::Print(DebugMessage, FColor::Red, 5.f);
	}
}

void UPlayerCombatComponent::AddAffix(UDataAsset_AffixBase* InAffixData)
{
	if (!InAffixData)
	{
		Debug::Print(TEXT("Affix data is null, cannot add."), FColor::Red, 5.f);
		return;
	}

	if (InAffixData->AffixTag.MatchesTag(WeaverGameplayTags::Shared_Projectile_Affix_Tuner))
	{
		CategorizedAffixes[WeaverGameplayTags::Shared_Projectile_Affix_Tuner].AcquiredAffixes.AddUnique(InAffixData);
	}
	else if (InAffixData->AffixTag.MatchesTag(WeaverGameplayTags::Shared_Projectile_Affix_Element))
	{
		CategorizedAffixes[WeaverGameplayTags::Shared_Projectile_Affix_Element].AcquiredAffixes.AddUnique(InAffixData);
	}
	else if (InAffixData->AffixTag.MatchesTag(WeaverGameplayTags::Shared_Projectile_Affix_Effect))
	{
		CategorizedAffixes[WeaverGameplayTags::Shared_Projectile_Affix_Effect].AcquiredAffixes.AddUnique(InAffixData);
	}

	GetOwner<AWeaverPlayerCharacter>()->GetPlayerUIComponent()->OnAddANewAffix.Broadcast(InAffixData);
}

void UPlayerCombatComponent::AddAndSetTuner(UDataAsset_TunerBase* InTuner)
{
	AddAffix(InTuner);
	SetSelectedTuner(InTuner);
}

void UPlayerCombatComponent::AddAndSetElement(UDataAsset_ElementBase* InElement)
{
	AddAffix(InElement);
	SetSelectedElement(InElement);
}

void UPlayerCombatComponent::AddAndSetEffect(UDataAsset_EffectBase* InEffect)
{
	AddAffix(InEffect);
	SetSelectedEffect(InEffect);
}

UDataAsset_AffixBase* UPlayerCombatComponent::SwitchToNextAffixInCurrentCategory(FGameplayTag InCategoryTag)
{
	FAffixCategory* AffixesManager = CategorizedAffixes.Find(InCategoryTag);

	if (!AffixesManager)
	{
		Debug::Print(TEXT("Affixes Category not found."), FColor::Red, 5.f);
		return nullptr;
	}

	TArray<TObjectPtr<UDataAsset_AffixBase>> AcquiredAffixes = AffixesManager->AcquiredAffixes;

	if (AcquiredAffixes.IsEmpty())
	{
		const FString DebugMessage = FString::Printf(
			TEXT("Don't have any affixes under this category: %s"), 
			*InCategoryTag.GetTagName().ToString()
		);
		Debug::Print(DebugMessage, FColor::Red, 5.f);
		return nullptr;
	}

	if (AcquiredAffixes.Num() == 1)
	{
		return AcquiredAffixes[0].Get();
	}

	int CurrentIndex = AffixesManager->SelectedIndex;
	int NextIndex = (CurrentIndex + 1) % AcquiredAffixes.Num();
	UDataAsset_AffixBase* NextAffix = AcquiredAffixes[NextIndex].Get();

	if (InCategoryTag.MatchesTag(WeaverGameplayTags::Shared_Projectile_Affix_Tuner))
	{
		SetSelectedTuner(Cast<UDataAsset_TunerBase>(NextAffix));
	}
	else if (InCategoryTag.MatchesTag(WeaverGameplayTags::Shared_Projectile_Affix_Element))
	{
		SetSelectedElement(Cast<UDataAsset_ElementBase>(NextAffix));
	}
	else if (InCategoryTag.MatchesTag(WeaverGameplayTags::Shared_Projectile_Affix_Effect))
	{
		SetSelectedEffect(Cast<UDataAsset_EffectBase>(NextAffix));
	}

	return AcquiredAffixes[NextIndex].Get();
}
