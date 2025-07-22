// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FastNoiseLite.h"
#include "Core/VoxelData.h"

class UVoxelBrush;

class WEAVER_API FVoxelGenerator
{
private:
	static FastNoiseLite Noise;
public:
	static void Sculpt(FVoxel* Data, int Size, UVoxelBrush* VoxelBrush);
	// static void Sculpt(FVoxel* Data, int Size, UVoxelBrush* VoxelBrush, FVector VoxelWorldLocation);
	static void Paint(FVoxel* Data, int Size, UVoxelBrush* VoxelBrush, int MaterialId);
	static void Generate(FVector Origin, int Size, FVoxel* Data);
	static FVoxel GetVoxel(FVector Position);
	static void Clear(FVoxel* Data, int Size);
};
