// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaverRewardComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRewardSelectionStarted);

class UUserWidget;
class UDataAsset_AffixBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WEAVER_API UWeaverRewardComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UWeaverRewardComponent();

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintAssignable, Category = "Reward|Events")
	FOnRewardSelectionStarted OnRewardSelectionStarted;

	UFUNCTION(BlueprintCallable, Category = "Reward")
	void StartRewardSelection();

	UFUNCTION(BlueprintPure, Category = "Reward")
	TArray<UDataAsset_AffixBase*> GetRandomUniqueAffixes(int32 Count);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Affix Pool")
	TArray<TObjectPtr<UDataAsset_AffixBase>> AllAffixesPool;
};
