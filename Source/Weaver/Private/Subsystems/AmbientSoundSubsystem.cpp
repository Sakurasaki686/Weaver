// Sakurasaki All Rights Reserved.


#include "Subsystems/AmbientSoundSubsystem.h"

void UAmbientSoundSubsystem::RegisterBGMManager(AAmbientSound* InBGMManager)
{
	if (BGMManagerInstance && BGMManagerInstance != InBGMManager)
	{
		UE_LOG(LogTemp, Warning, TEXT("A BGMManager was already registered. Overwriting."));
	}
	
	BGMManagerInstance = InBGMManager;
}

AAmbientSound* UAmbientSoundSubsystem::GetBGMManager() const
{
	return BGMManagerInstance;
}
