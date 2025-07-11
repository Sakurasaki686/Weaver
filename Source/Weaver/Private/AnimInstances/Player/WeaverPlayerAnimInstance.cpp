// Sakurasaki All Rights Reserved.


#include "AnimInstances/Player/WeaverPlayerAnimInstance.h"

#include "Characters/WeaverPlayerCharacter.h"

void UWeaverPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<AWeaverPlayerCharacter>(OwningCharacter);
	}
}

void UWeaverPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
