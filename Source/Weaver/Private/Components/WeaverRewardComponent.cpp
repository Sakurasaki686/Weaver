// Sakurasaki All Rights Reserved.


#include "Components/WeaverRewardComponent.h"

#include "Blueprint/UserWidget.h"
#include "Widgets/WeaverWidgetBase.h"

UWeaverRewardComponent::UWeaverRewardComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UWeaverRewardComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UWeaverRewardComponent::StartRewardSelection()
{
	OnRewardSelectionStarted.Broadcast();
}

TArray<UDataAsset_AffixBase*> UWeaverRewardComponent::GetRandomUniqueAffixes(int32 Count)
{
	// 从池子中随机不重复抽取 N 个 Affix
	TArray<UDataAsset_AffixBase*> Result;
	TArray<UDataAsset_AffixBase*> TempPool = AllAffixesPool;
	
	Count = FMath::Min(Count, TempPool.Num());
	for (int32 i = 0; i < Count; ++i)
	{
		if (TempPool.Num() == 0) break;
		
		int32 RandomIndex = FMath::RandRange(0, TempPool.Num() - 1);
		Result.Add(TempPool[RandomIndex]);
		
		TempPool.RemoveAt(RandomIndex);
	}
	
	return Result;
}
