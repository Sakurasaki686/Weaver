// Sakurasaki All Rights Reserved.


#include "WeaverGameInstance.h"

void UWeaverGameInstance::RegisterBGMManager(AAmbientSound* InBGMManager)
{
	if (BGMManagerInstance && BGMManagerInstance != InBGMManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("A BGMManager was already registered. Overwriting."));
	}
	
	BGMManagerInstance = InBGMManager;
}

AAmbientSound* UWeaverGameInstance::GetBGMManager() const
{
	return BGMManagerInstance;
}
