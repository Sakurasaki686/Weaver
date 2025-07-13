// Sakurasaki All Rights Reserved.


#include "AnimInstances/WeaverCharacterAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "Characters/WeaverBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWeaverCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AWeaverBaseCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UWeaverCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
	IsInAir = OwningMovementComponent->IsFalling();
}
