// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/WeaverRewardComponent.h"
#include "Components/UI/PawnUIComponent.h"
#include "DataAssets/Affixes/DataAsset_TunerBase.h"
#include "DataAssets/Affixes/DataAsset_ElementBase.h"
#include "DataAssets/Affixes/DataAsset_EffectBase.h"
#include "PlayerUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnOverlapInteractableActor, AActor*, OverlappedActor, const FText&, InteractionPrompt);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOverlapInteractableActorEnd);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractionWarningFeedback, const FText&, WarningFeedbackMessage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAetherAmountChanged, float, NewAetherAmount);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChestOpened, const TArray<UDataAsset_AffixBase*>&, SelectableAffixes);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTunerChanged, UDataAsset_TunerBase*, NewTuner);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnElementChanged, UDataAsset_ElementBase*, NewElement);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEffectChanged, UDataAsset_EffectBase*, NewEffect);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddANewAffix, UDataAsset_AffixBase*, NewAffix);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRewardSelectionFinished);

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

	UPROPERTY(BlueprintAssignable)
	FOnTunerChanged OnTunerChanged;

	UPROPERTY(BlueprintAssignable)
	FOnElementChanged OnElementChanged;

	UPROPERTY(BlueprintAssignable)
	FOnEffectChanged OnEffectChanged;

	UPROPERTY(BlueprintAssignable)
	FOnRewardSelectionFinished OnRewardSelectionFinished;

	UPROPERTY(BlueprintAssignable)
	FOnAddANewAffix OnAddANewAffix;

public:
	UFUNCTION(BlueprintCallable, Category = "UI|Broadcasting")
	void BroadcastChestOpened(const TArray<UDataAsset_AffixBase*>& OfferedAffixes);
	
	UFUNCTION(BlueprintCallable, Category = "UI|Broadcasting")
    void BroadcastRewardSelectionFinished();
};
