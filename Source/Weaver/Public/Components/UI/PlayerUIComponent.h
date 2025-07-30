// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/UI/PawnUIComponent.h"
#include "PlayerUIComponent.generated.h"

class UDataAsset_AffixBase;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOverlapInteractableActor, AActor*, OverlappedActor, const FText&, InteractionPrompt);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverlapInteractableActorEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionWarningFeedback, const FText&, WarningFeedbackMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAetherAmountChanged, float, NewAetherAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChestOpened, const TArray<UDataAsset_AffixBase*>&, SelectableAffixes);

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

	UPROPERTY(BlueprintAssignable)
	FOnChestOpened OnChestOpened;

public:
	UFUNCTION(BlueprintCallable, Category = "UI|Broadcasting")
	void BroadcastChestOpened(const TArray<UDataAsset_AffixBase*>& OfferedAffixes);
};
