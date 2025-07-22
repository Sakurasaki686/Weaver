// Sakurasaki All Rights Reserved.


#include "MarchingCubes/Core/MeshBuilder.h"

#include "MarchingCubes/Core/VoxelMaterial.h"

FMCMesh FMCMeshBuilder::Build(FVoxel* Data, int Size)
{
	FMCMesh Mesh;
	TArray<FVector> NewTriangles;

	// 重置内部状态
	IndexToVertex.Empty();
	IndexToNormal.Empty();
	VertexToIndex.Empty();
	Triangles.Empty();

	const float VoxelSize = 100.0;

	for (int z = 0; z < Size - 1; z++) 
	{
		for (int y = 0; y < Size - 1; y++) 
		{
			for (int x = 0; x < Size - 1; x++) 
			{
				W[0] = Data[GetIndex(x,     y,     z,     Size)].Density;
				W[1] = Data[GetIndex(x,     y,     z + 1, Size)].Density;
				W[2] = Data[GetIndex(x + 1, y,     z + 1, Size)].Density;
				W[3] = Data[GetIndex(x + 1, y,     z,     Size)].Density;
				W[4] = Data[GetIndex(x,     y + 1, z,     Size)].Density;
				W[5] = Data[GetIndex(x,     y + 1, z + 1, Size)].Density;
				W[6] = Data[GetIndex(x + 1, y + 1, z + 1, Size)].Density;
				W[7] = Data[GetIndex(x + 1, y + 1, z,     Size)].Density;

				SetVectors(Pos, x, y, z);
				MarchingCubes.InsertTrianglesOfCube(Pos, W, NewTriangles);
			}
		}
	}

	for (int i = 0; i < NewTriangles.Num(); i += 3)
	{
		AddTriangle(NewTriangles[i], NewTriangles[i + 1], NewTriangles[i + 2]);
	}

	for (int i = 0; i < IndexToVertex.Num(); i++)
	{
		const FVector* v = IndexToVertex.Find(i);

		const int x_idx = FMath::Clamp(FMath::RoundToInt(v->X), 0, Size - 1);
		const int y_idx = FMath::Clamp(FMath::RoundToInt(v->Y), 0, Size - 1);
		const int z_idx = FMath::Clamp(FMath::RoundToInt(v->Z), 0, Size - 1);

		// Material
		const FVoxel Voxel = Data[GetIndex(x_idx, y_idx, z_idx, Size)];
		Mesh.Colors.Add(UVoxelMaterial::Encode(Voxel.Id));

		const int x_minus = FMath::Max(0, x_idx - 1);
		const int x_plus = FMath::Min(Size - 1, x_idx + 1);
		const int y_minus = FMath::Max(0, y_idx - 1);
		const int y_plus = FMath::Min(Size - 1, y_idx + 1);
		const int z_minus = FMath::Max(0, z_idx - 1);
		const int z_plus = FMath::Min(Size - 1, z_idx + 1);
		
		FVector Grad;
		Grad.X = Data[GetIndex(x_minus, y_idx, z_idx, Size)].Density - Data[GetIndex(x_plus, y_idx, z_idx, Size)].Density;
		Grad.Y = Data[GetIndex(x_idx, y_minus, z_idx, Size)].Density - Data[GetIndex(x_idx, y_plus, z_idx, Size)].Density;
		Grad.Z = Data[GetIndex(x_idx, z_idx, z_minus, Size)].Density - Data[GetIndex(x_idx, z_idx, z_plus, Size)].Density;
		Mesh.Normals.Add(-Grad.GetSafeNormal());
		
		// Vertex
		Mesh.Vertices.Add(FVector(v->X * VoxelSize, v->Y * VoxelSize, v->Z * VoxelSize));
	}
	
	for (int i = 0; i < Triangles.Num(); i++)
	{
		Mesh.Triangles.Add(Triangles[i]);
	}

	return Mesh;
}

void FMCMeshBuilder::SetVectors(FVector* V, const float X, const float Y, const float Z)
{
	V[4].X = V[5].X = V[0].X = V[1].X = X;
	V[7].X = V[6].X = V[3].X = V[2].X = X + 1;

	V[0].Y = V[1].Y = V[2].Y = V[3].Y = Y;
	V[4].Y = V[5].Y = V[6].Y = V[7].Y = Y + 1;

	V[0].Z = V[3].Z = V[4].Z = V[7].Z = Z;
	V[1].Z = V[2].Z = V[5].Z = V[6].Z = Z + 1;
}

void FMCMeshBuilder::AddTriangle(const FVector V1, const FVector V2, const FVector V3)
{
	const FVector Normal = ComputeNormal(V1, V2, V3);

	Triangles.Add(InsertVertex(V1, Normal));
	Triangles.Add(InsertVertex(V2, Normal));
	Triangles.Add(InsertVertex(V3, Normal));
}

int FMCMeshBuilder::InsertVertex(const FVector V, const FVector Normal)
{
	int i = 0;
	if (!VertexToIndex.Contains(V)) {
		i = IndexToVertex.Num();
		IndexToVertex.Add(i, V);
		VertexToIndex.Add(V, i);
		IndexToNormal.Add(i, FVector());
	}
	else {
		i = *VertexToIndex.Find(V);
	}

	IndexToNormal.Add(i, *IndexToNormal.Find(i) + Normal);

	return i;
}

FVector FMCMeshBuilder::ComputeNormal(const FVector V1, const FVector V2, const FVector V3)
{
	FVector E1 = FVector(V2.X, V2.Y, V2.Z);
	FVector E2 = FVector(V3.X, V3.Y, V3.Z);
	E1 = E1 - V1;
	E2 = E2 - V1;
	return FVector::CrossProduct(E1, E2).GetSafeNormal();
}

int FMCMeshBuilder::GetIndex(const int X, const int Y, const int Z, const int Size) {
	return ((Z * Size * Size) + (Y * Size) + X);
}
