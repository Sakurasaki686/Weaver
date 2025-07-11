// Sakurasaki All Rights Reserved.


#include "WeaverTypes/WeaverStructTypes.h"

#include "AbilitySystem/Abilities/WeaverPlayerGameplayAbility.h"

bool FWeaverPlayerAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
