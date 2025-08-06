// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "AmbientSoundSubsystem.generated.h"

class AAmbientSound;
/**
 * 
 */
UCLASS()
class WEAVER_API UAmbientSoundSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Managers")
	void RegisterBGMManager(AAmbientSound* InBGMManager);

	UFUNCTION(BlueprintPure, Category = "Managers")
	AAmbientSound* GetBGMManager() const;

protected:
	UPROPERTY()
	TObjectPtr<AAmbientSound> BGMManagerInstance;
};
