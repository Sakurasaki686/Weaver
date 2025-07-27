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
	
	CurrentGait = CharacterDefaultGait;

	switch (CurrentGait)
	{
	case EWeaverCharacterGait::Run:
		GetCharacterMovement()->MaxWalkSpeed = WeaverAttributeSet->GetMaxRunSpeed() * WeaverAttributeSet->GetMovementSpeedMultiplier();
		break;
	case EWeaverCharacterGait::Walk:
		GetCharacterMovement()->MaxWalkSpeed = WeaverAttributeSet->GetMaxWalkSpeed() * WeaverAttributeSet->GetMovementSpeedMultiplier();
		break;
	default:
		break;
	}
}

void AWeaverBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	WeaverAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WeaverAttributeSet->GetMovementSpeedMultiplierAttribute()).AddUObject(this, &ThisClass::OnMovementAttributesChanged);
	WeaverAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WeaverAttributeSet->GetMaxRunSpeedAttribute()).AddUObject(this, &ThisClass::OnMovementAttributesChanged);
	WeaverAbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(WeaverAttributeSet->GetMaxWalkSpeedAttribute()).AddUObject(this, &ThisClass::OnMovementAttributesChanged);
	
	GetCharacterMovement()->MaxWalkSpeed = WeaverAttributeSet->GetMaxRunSpeed() * WeaverAttributeSet->GetMovementSpeedMultiplier();
	GetMesh()->GlobalAnimRateScale = WeaverAttributeSet->GetMovementSpeedMultiplier();
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

UAbilitySystemComponent* AWeaverBaseCharacter::GetAbilitySystemComponent() const
{
	return GetWeaverAbilitySystemComponent();
}

UPawnCombatComponent* AWeaverBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

UPawnUIComponent* AWeaverBaseCharacter::GetPawnUIComponent() const
{
	return nullptr;
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

void AWeaverBaseCharacter::OnMovementAttributesChanged(const FOnAttributeChangeData& Data)
{
	if (WeaverAttributeSet)
	{
		switch (CurrentGait)
		{
		case EWeaverCharacterGait::Run:
			GetCharacterMovement()->MaxWalkSpeed = WeaverAttributeSet->GetMaxRunSpeed() * WeaverAttributeSet->GetMovementSpeedMultiplier();
			break;
		case EWeaverCharacterGait::Walk:
			GetCharacterMovement()->MaxWalkSpeed = WeaverAttributeSet->GetMaxWalkSpeed() * WeaverAttributeSet->GetMovementSpeedMultiplier();
			break;
		default:
			break;
		}
		
		GetMesh()->GlobalAnimRateScale = WeaverAttributeSet->GetMovementSpeedMultiplier();
	}
}
