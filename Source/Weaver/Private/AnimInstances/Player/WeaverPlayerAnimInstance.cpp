// Sakurasaki All Rights Reserved.


#include "AnimInstances/Player/WeaverPlayerAnimInstance.h"

#include "Characters/WeaverPlayerCharacter.h"

void UWeaverPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningPlayerCharacter = Cast<AWeaverPlayerCharacter>(OwningCharacter);
	}
}

void UWeaverPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
}
