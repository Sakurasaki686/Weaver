// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VoxelShape.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class WEAVER_API UVoxelShape : public UObject
{
	GENERATED_BODY()
public:
	virtual float SignedDistance(FVector& VoxelPosition, FVector& BrushPosition);
};
