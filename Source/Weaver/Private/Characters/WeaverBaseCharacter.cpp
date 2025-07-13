// Sakurasaki All Rights Reserved.


#include "Characters/WeaverBaseCharacter.h"

#include "AbilitySystem/WeaverAbilitySystemComponent.h"
#include "AbilitySystem/WeaverAttributeSet.h"
#include "MotionWarpingComponent.h"
#include "WeaverGameplayTags.h"
#include "GameFramework/CharacterMovementComponent.h"

AWeaverBaseCharacter::AWeaverBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	WeaverAbilitySystemComponent = CreateDefaultSubobject<UWeaverAbilitySystemComponent>(TEXT("WeaverAbilitySystemComponent"));
	WeaverAttributeSet = CreateDefaultSubobject<UWeaverAttributeSet>(TEXT("WeaverAttributeSet"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComponent"));

	switch (CharacterDefaultGait)
	{
	case EWeaverCharacterGait::Run:
		GetCharacterMovement()->MaxWalkSpeed = MaxRunSpeed;
		break;
	case EWeaverCharacterGait::Walk:
		GetCharacterMovement()->MaxWalkSpeed = MaxWalSpeed;
		break;
	default:
		break;
	}
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

	if (WeaverAbilitySystemComponent)
	{
		WeaverAbilitySystemComponent->InitAbilityActorInfo(this, this);

		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}

void AWeaverBaseCharacter::OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode)
{
	Super::OnMovementModeChanged(PrevMovementMode, PreviousCustomMode);

	if (!WeaverAbilitySystemComponent) return;

	if (GetCharacterMovement() && GetCharacterMovement()->IsFalling())
	{
		WeaverAbilitySystemComponent->AddLooseGameplayTag(WeaverGameplayTags::Player_State_InAir);
	}
	else
	{
		WeaverAbilitySystemComponent->RemoveLooseGameplayTag(WeaverGameplayTags::Player_State_InAir);
	}
}
