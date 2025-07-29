// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PawnInteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPawnInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class WEAVER_API IPawnInteractionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void HighlightActor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void UnHighlightActor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void Interact(AActor* InInstigator);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void SetInteractionInfo(AActor* InInteractableTarget, const FText& InInteractionPrompt);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Interaction")
	void ShowInteractionWarningFeedback(const FText& InWarningFeedbackMessage);
};
