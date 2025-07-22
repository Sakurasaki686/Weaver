// Sakurasaki All Rights Reserved.


#include "AbilitySystem/Abilities/WeaverPlayerGA_SculptBase.h"

#include "EngineUtils.h"
#include "Characters/WeaverPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "MarchingCubes/VoxelWorld.h"
#include "MarchingCubes/VoxelBrush/SphereShape.h"
#include "MarchingCubes/VoxelBrush/VoxelBrush.h"


void UWeaverPlayerGA_SculptBase::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	
	UWorld* World = ActorInfo->OwnerActor->GetWorld();
	if (!World)
	{
		UE_LOG(LogTemp, Error, TEXT("OnGiveAbility FAILED: Could not get World from ActorInfo."));
		return;
	}

	VoxelWorld = Cast<AVoxelWorld>(UGameplayStatics::GetActorOfClass(World, AVoxelWorld::StaticClass()));

	if(AWeaverPlayerCharacter* PlayerCharacter = Cast<AWeaverPlayerCharacter>(ActorInfo->AvatarActor.Get()))
	{
		VoxelBrush = NewObject<UVoxelBrush>(PlayerCharacter);
		SphereShape = NewObject<USphereShape>(PlayerCharacter);
		SphereShape->Radius = SphereRadius;
		VoxelBrush->Shape = SphereShape;
	}
}
