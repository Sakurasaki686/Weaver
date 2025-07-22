// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WeaverPlayerGameplayAbility.h"
#include "WeaverPlayerGA_SculptBase.generated.h"

class USphereShape;
class UVoxelBrush;
class AVoxelWorld;
/**
 * 
 */
UCLASS()
class WEAVER_API UWeaverPlayerGA_SculptBase : public UWeaverPlayerGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MarchingCubes")
	AVoxelWorld* VoxelWorld;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MarchingCubes")
	UVoxelBrush* VoxelBrush;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MarchingCubes")
	USphereShape* SphereShape;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MarchingCubes")
	float SphereRadius = 1.5f;
};
