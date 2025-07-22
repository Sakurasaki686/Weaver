// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_OnTick.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTickTaskDelegate, float, DeltaTime);

/**
 * 
 */
UCLASS()
class WEAVER_API UAbilityTask_OnTick : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks", meta = (DisplayName = "ExecuteOnTick", HidePin = "OwningAbility", DefaultToSelf = "OwningAbility"))
	static UAbilityTask_OnTick* AbilityTaskOnTick(UGameplayAbility* OwningAbility, FName TaskInstanceName);

	UPROPERTY(BlueprintAssignable)
	FOnTickTaskDelegate OnTick;

	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;

private:
	UAbilityTask_OnTick(const FObjectInitializer& ObjectInitializer);
};
