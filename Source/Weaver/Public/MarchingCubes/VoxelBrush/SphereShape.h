// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MarchingCubes/VoxelBrush/VoxelShape.h"
#include "SphereShape.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class WEAVER_API USphereShape : public UVoxelShape
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadWrite)
	float Radius = 2.0;
	virtual float SignedDistance(FVector& VoxelPosition, FVector& BrushPosition) override;
};