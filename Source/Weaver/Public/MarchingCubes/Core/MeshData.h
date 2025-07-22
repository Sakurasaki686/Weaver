// Sakurasaki All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class WEAVER_API FMCMesh
{
public:
	FMCMesh();
	TArray<FVector> Vertices;
	TArray<FVector> Normals;
	TArray<FLinearColor> Colors;
	TArray<int> Triangles;
};
