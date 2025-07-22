// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MarchingCubes/Core/VoxelData.h"
#include "UObject/NoExportTypes.h"
#include "VoxelBrush.generated.h"

class UVoxelShape;
/**
 * 
 */
UCLASS(Blueprintable)
class WEAVER_API UVoxelBrush : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	FVector Location;
	UPROPERTY(BlueprintReadWrite)
	UVoxelShape* Shape;
	UPROPERTY(BlueprintReadWrite)
	float Strength = 1.0;
	
	UVoxelBrush();
	UVoxelBrush(UVoxelShape* Shape);
	
	void Paint(FVoxel& Voxel, FVector& VoxelPosition, int MaterialId);
	void Sculpt(FVoxel& Voxel, FVector& VoxelPosition);
};