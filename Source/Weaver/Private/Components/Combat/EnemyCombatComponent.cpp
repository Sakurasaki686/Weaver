// Sakurasaki All Rights Reserved.


#include "Components/Combat/EnemyCombatComponent.h"

void UEnemyCombatComponent::SetSelectedElement(UDataAsset_ElementBase* InElement)
{
	SelectedElement = InElement;
}

void UEnemyCombatComponent::SetSelectedEffect(UDataAsset_EffectBase* InEffect)
{
	SelectedEffect = InEffect;
}

