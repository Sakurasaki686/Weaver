// Sakurasaki All Rights Reserved.


#include "MarchingCubes/VoxelBrush/SphereShape.h"

float USphereShape::SignedDistance(FVector& VoxelPosition, FVector& BrushPosition)
{
	const float Dist = FVector::Distance(VoxelPosition, BrushPosition);
	return Dist - Radius;
}
