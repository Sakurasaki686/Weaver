// Sakurasaki All Rights Reserved.


#include "MarchingCubes/VoxelGenerator.h"

#include "MarchingCubes/VoxelBrush/VoxelBrush.h"

FastNoiseLite FVoxelGenerator::Noise = FastNoiseLite();

void FVoxelGenerator::Sculpt(FVoxel* Data, const int Size, UVoxelBrush* VoxelBrush)
{
	for(int x = 0; x < Size; x++)
	{
		for(int y = 0; y < Size; y++)
		{
			for(int z = 0; z < Size; z++)
			{
				const int Index = x + Size * (y + Size * z);
				FVector Position = FVector(x, y, z);
				// FVector Location = VoxelWorldLocation / 100.f + Position;
				VoxelBrush->Sculpt(Data[Index], Position);
			}
		}
	}
}

void FVoxelGenerator::Paint(FVoxel* Data, const int Size, UVoxelBrush* VoxelBrush, const int MaterialId)
{
	for(int x = 0; x < Size; x++)
	{
		for(int y = 0; y < Size; y++)
		{
			for(int z = 0; z < Size; z++)
			{
				const int Index = x + Size * (y + Size * z);
				FVector Position = FVector(x, y, z);
				VoxelBrush->Paint(Data[Index], Position, MaterialId);
			}
		}
	}
}

void FVoxelGenerator::Generate(const FVector Origin, const int Size, FVoxel* Data)
{
	for(int x = 0; x < Size; x++)
	{
		for(int y = 0; y < Size; y++)
		{
			for(int z = 0; z < Size; z++)
			{
				const int Index = x + Size * (y + Size * z);
				Data[Index] = GetVoxel(Origin + FVector(x, y, z));
			}
		}
	}
}

FVoxel FVoxelGenerator::GetVoxel(const FVector Position)
{
	FVoxel VoxelData;
	const float Scale = 7;
	const float Height = Noise.GetNoise(Position.X * Scale, Position.Y * Scale) * 4.0 + 8;
	VoxelData.Density = Position.Z - Height;
	if(Position.Z < -8) VoxelData.Id = 1;
	return VoxelData;
}

void FVoxelGenerator::Clear(FVoxel* Data, int Size)
{
	for(int i = 0; i < Size * Size * Size; ++i)
	{
		Data[i].Density = 1.0f; 
		Data[i].Id = 0;
	}
}
