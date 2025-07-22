// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "VoxelMaterial.generated.h"

class UTexture2D;
/**
 * 
 */
UCLASS(Blueprintable)
class WEAVER_API UVoxelMaterial : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int32 Id;
	UPROPERTY(BlueprintReadWrite)
	UTexture2D* Texture;
	
	static FColor Encode(const int Id);
};
