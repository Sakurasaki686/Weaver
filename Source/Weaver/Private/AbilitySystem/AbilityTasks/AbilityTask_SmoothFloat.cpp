// Sakurasaki All Rights Reserved.


#include "AbilitySystem/AbilityTasks/AbilityTask_SmoothFloat.h"

UAbilityTask_SmoothFloat::UAbilityTask_SmoothFloat()
{
	bTickingTask = true;
}

UAbilityTask_SmoothFloat* UAbilityTask_SmoothFloat::SmoothFloat(
	UGameplayAbility* OwningAbility,
	float From,
	float To,
	float Duration)
{
	UAbilityTask_SmoothFloat* MyObj = NewAbilityTask<UAbilityTask_SmoothFloat>(OwningAbility);
	MyObj->StartValue = From;
	MyObj->EndValue = To;
	MyObj->Duration = Duration;
	return MyObj;
}

void UAbilityTask_SmoothFloat::Activate()
{
	Super::Activate();

	SetWaitingOnAvatar();
}

void UAbilityTask_SmoothFloat::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	ElapsedTime += DeltaTime;
	float Alpha = FMath::Clamp(ElapsedTime / Duration, 0.0f, 1.0f);
	float CurrentValue = FMath::Lerp(StartValue, EndValue, Alpha);

	OnUpdate.Broadcast(CurrentValue);

	if (Alpha >= 1.0f)
	{
		OnComplete.Broadcast();
		EndTask();
	}
}
