// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_SmoothFloat.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValueUpdate, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComplete);

/**
 * 
 */
UCLASS()
class WEAVER_API UAbilityTask_SmoothFloat : public UAbilityTask
{
	GENERATED_BODY()

public:
	UAbilityTask_SmoothFloat();
	
	UPROPERTY(BlueprintAssignable)
	FOnValueUpdate OnUpdate;

	UPROPERTY(BlueprintAssignable) 
	FOnComplete OnComplete;

	UFUNCTION(BlueprintCallable, Category = "Ability|Tasks")
	static UAbilityTask_SmoothFloat* SmoothFloat(
		UGameplayAbility* OwningAbility,
		float From,
		float To, 
		float Duration
	);

protected:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;

private:
	float StartValue;
	float EndValue;
	float Duration;
	float ElapsedTime = 0.0f;
};
