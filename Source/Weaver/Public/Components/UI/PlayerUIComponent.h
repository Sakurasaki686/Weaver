// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "PlayerUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOverlapInteractableActor, AActor*, OverlappedActor, const FText&, InteractionPrompt);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverlapInteractableActorEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionWarningFeedback, const FText&, WarningFeedbackMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAetherAmountChanged, float, NewAetherAmount);

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

	UPROPERTY(BlueprintAssignable)
	FOnInteractionWarningFeedback OnInteractionWarningFeedback;

	UPROPERTY(BlueprintAssignable)
	FOnAetherAmountChanged OnAetherAmountChanged;
};
