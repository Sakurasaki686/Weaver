// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "WeaverGameInstance.generated.h"

class AAmbientSound;
/**
 * 
 */
UCLASS()
class WEAVER_API UWeaverGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Managers")
	void RegisterBGMManager(AAmbientSound* InBGMManager);

	UFUNCTION(BlueprintPure, Category = "Managers", meta = (WorldContext = "WorldContextObject"))
	AAmbientSound* GetBGMManager() const;

protected:
	UPROPERTY()
	TObjectPtr<AAmbientSound> BGMManagerInstance;
};
