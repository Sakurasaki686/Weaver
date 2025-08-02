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
