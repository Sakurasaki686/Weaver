// Sakurasaki All Rights Reserved.


#include "DataAssets/StartUpData/DataAsset_PlayerStartUpData.h"

#include "AbilitySystem/WeaverAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WeaverGameplayAbility.h"


void UDataAsset_PlayerStartUpData::GiveToAbilitySystemComponent(UWeaverAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FWeaverPlayerAbilitySet& AbilitySet : PlayerStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilitySet.InputTag);

		InASCToGive->GiveAbility(AbilitySpec);
	}
}
