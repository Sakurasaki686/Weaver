// Sakurasaki All Rights Reserved.


#include "Components/Combat/PlayerCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WeaverGameplayTags.h"
#include "AbilitySystem/WeaverAbilitySystemComponent.h"
#include "Characters/WeaverPlayerCharacter.h"
#include "Items/Weapons/WeaverPlayerWeapon.h"

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

void UPlayerCombatComponent::SetSelectedTuner(const FGameplayTag& InTunerTag)
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
	SelectedElement = InElement;
}

void UPlayerCombatComponent::SetSelectedEffect(UDataAsset_EffectBase* InEffect)
{
	SelectedEffect = InEffect;
}
