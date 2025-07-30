// Sakurasaki All Rights Reserved.


#include "Components/Combat/PlayerCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WeaverDebugHelper.h"
#include "WeaverGameplayTags.h"
#include "AbilitySystem/WeaverAbilitySystemComponent.h"
#include "Characters/WeaverPlayerCharacter.h"
#include "DataAssets/Affixes/DataAsset_AffixBase.h"
#include "DataAssets/Affixes/DataAsset_EffectBase.h"
#include "DataAssets/Affixes/DataAsset_ElementBase.h"
#include "Items/Weapons/WeaverPlayerWeapon.h"

UPlayerCombatComponent::UPlayerCombatComponent()
{
	CategorizedAffixes.Add(WeaverGameplayTags::Shared_Projectile_Affix_Element, FAffixCategory());
	CategorizedAffixes.Add(WeaverGameplayTags::Shared_Projectile_Affix_Effect, FAffixCategory());
}

void UPlayerCombatComponent::BeginPlay()
{
	Super::BeginPlay();

	SetSelectedTuner(SelectedTunerTag);
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

void UPlayerCombatComponent::SetSelectedTuner(FGameplayTag InTunerTag)
{
	UWeaverAbilitySystemComponent* ASC = GetOwner<AWeaverPlayerCharacter>()->GetWeaverAbilitySystemComponent();
	if (!ASC)
	{
		UE_LOG(LogTemp, Error, TEXT("UPlayerCombatComponent::SetSelectedTuner: Owner does not have an AbilitySystemComponent."));
		return;
	}

	FGameplayTagContainer TagsToRemove;
	TagsToRemove.AddTag(WeaverGameplayTags::Shared_Projectile_Affix_Tuner_Focus);
	TagsToRemove.AddTag(WeaverGameplayTags::Shared_Projectile_Affix_Tuner_Diverge);
	TagsToRemove.AddTag(WeaverGameplayTags::Shared_Projectile_Affix_Tuner_Aegis);

	ASC->RemoveLooseGameplayTags(TagsToRemove);

	if (InTunerTag.IsValid())
	{
		ASC->AddLooseGameplayTag(InTunerTag);
	}

	SelectedTunerTag = InTunerTag;
}

void UPlayerCombatComponent::SetSelectedElement(UDataAsset_ElementBase* InElement)
{
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

	if (InAffixData->AffixTag.MatchesTag(WeaverGameplayTags::Shared_Projectile_Affix_Element))
	{
		CategorizedAffixes[WeaverGameplayTags::Shared_Projectile_Affix_Element].AcquiredAffixes.AddUnique(InAffixData);
	}
	else if (InAffixData->AffixTag.MatchesTag(WeaverGameplayTags::Shared_Projectile_Affix_Effect))
	{
		CategorizedAffixes[WeaverGameplayTags::Shared_Projectile_Affix_Effect].AcquiredAffixes.AddUnique(InAffixData);
	}
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

void UPlayerCombatComponent::SwitchToCurrentCategoryNextAffix(FGameplayTag InCategoryTag)
{
	FAffixCategory* AffixesManager = CategorizedAffixes.Find(InCategoryTag);

	if (!AffixesManager)
	{
		Debug::Print(TEXT("Affixes Category not found."), FColor::Red, 5.f);
		return;
	}

	TArray<TObjectPtr<UDataAsset_AffixBase>> AcquiredAffixes = AffixesManager->AcquiredAffixes;

	if (AcquiredAffixes.IsEmpty())
	{
		const FString DebugMessage = FString::Printf(
			TEXT("Don't have any affixes under this category: %s"), 
			*InCategoryTag.GetTagName().ToString()
		);
		Debug::Print(DebugMessage, FColor::Red, 5.f);
		return;
	}

	int CurrentIndex = AffixesManager->SelectedIndex;
	int NextIndex = (CurrentIndex + 1) % AcquiredAffixes.Num();
	AffixesManager->SelectedIndex = NextIndex;
}
