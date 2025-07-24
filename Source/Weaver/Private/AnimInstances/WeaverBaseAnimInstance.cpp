// Sakurasaki All Rights Reserved.


#include "AnimInstances/WeaverBaseAnimInstance.h"

#include "GameplayTagContainer.h"
#include "WeaverFunctionLibrary.h"

bool UWeaverBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UWeaverFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
	}
	
	return false;
}
