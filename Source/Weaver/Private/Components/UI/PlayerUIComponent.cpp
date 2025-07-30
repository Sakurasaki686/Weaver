// Sakurasaki All Rights Reserved.


#include "Components/UI/PlayerUIComponent.h"

void UPlayerUIComponent::BroadcastChestOpened(const TArray<UDataAsset_AffixBase*>& OfferedAffixes)
{
	OnChestOpened.Broadcast(OfferedAffixes);
}

void UPlayerUIComponent::BroadcastRewardSelectionFinished()
{
	OnRewardSelectionFinished.Broadcast();
}
