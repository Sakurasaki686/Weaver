// Sakurasaki All Rights Reserved.


#include "Components/WeaverEffectComponentBase.h"

UWeaverEffectComponentBase::UWeaverEffectComponentBase()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UWeaverEffectComponentBase::BeginPlay()
{
	Super::BeginPlay();

}

void UWeaverEffectComponentBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

