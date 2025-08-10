// Sakurasaki All Rights Reserved.


#include "Components/WeaverRewardComponent.h"
#include "DataAssets/Affixes/DataAsset_AffixBase.h"


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
	TArray<UDataAsset_AffixBase*> Result;
    
	TArray<TSoftObjectPtr<UDataAsset_AffixBase>> TempPool = AllAffixesPool;
    
	Count = FMath::Min(Count, TempPool.Num());
	for (int32 i = 0; i < Count; ++i)
	{
		if (TempPool.Num() == 0) break;
        
		int32 RandomIndex = FMath::RandRange(0, TempPool.Num() - 1);
        
		TSoftObjectPtr<UDataAsset_AffixBase> SelectedSoftPtr = TempPool[RandomIndex];
        
		UDataAsset_AffixBase* LoadedAffix = SelectedSoftPtr.LoadSynchronous();

		if (LoadedAffix)
		{
			Result.Add(LoadedAffix);
		}
        
		TempPool.RemoveAt(RandomIndex);
	}
    
	return Result;
}
