// Sakurasaki All Rights Reserved.


#include "AbilitySystem/AbilityTasks/AbilityTask_OnTick.h"

UAbilityTask_OnTick::UAbilityTask_OnTick(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bTickingTask = true;
}

void UAbilityTask_OnTick::Activate()
{
	Super::Activate();
}

void UAbilityTask_OnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);
	
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnTick.Broadcast(DeltaTime);
	}
}

UAbilityTask_OnTick* UAbilityTask_OnTick::AbilityTaskOnTick(UGameplayAbility* OwningAbility, FName TaskInstanceName)
{
	UAbilityTask_OnTick* MyObj = NewAbilityTask<UAbilityTask_OnTick>(OwningAbility, TaskInstanceName);
	return MyObj;
}