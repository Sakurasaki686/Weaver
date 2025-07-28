// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "PlayerUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOverlapInteractableActor, AActor*, OverlappedActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverlapInteractableActorEnd);

/**
 * 
 */
UCLASS()
class WEAVER_API UPlayerUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnOverlapInteractableActor OnOverlapInteractableActor;

	UPROPERTY(BlueprintAssignable)
	FOnOverlapInteractableActorEnd OnOverlapInteractableActorEnd;
};
