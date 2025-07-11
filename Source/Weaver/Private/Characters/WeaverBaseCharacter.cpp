// Sakurasaki All Rights Reserved.


#include "Characters/WeaverBaseCharacter.h"

#include "AbilitySystem/WeaverAbilitySystemComponent.h"
#include "AbilitySystem/WeaverAttributeSet.h"
#include "MotionWarpingComponent.h"

AWeaverBaseCharacter::AWeaverBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	WeaverAbilitySystemComponent = CreateDefaultSubobject<UWeaverAbilitySystemComponent>(TEXT("WeaverAbilitySystemComponent"));
	
	WeaverAttributeSet = CreateDefaultSubobject<UWeaverAttributeSet>(TEXT("WeaverAttributeSet"));

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));
}

UAbilitySystemComponent* AWeaverBaseCharacter::GetAbilitySystemComponent() const
{
	return GetWeaverAbilitySystemComponent();
}

UPawnCombatComponent* AWeaverBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

void AWeaverBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	Super::PossessedBy(NewController);

	if (WeaverAbilitySystemComponent)
	{
		WeaverAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}
