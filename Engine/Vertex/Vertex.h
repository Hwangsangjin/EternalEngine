#pragma once

struct ENGINE_API FVertex
{
	FVertex(const FVector3& InPosition, const FVector3& InColor);

	FVector3 Position;
	FVector3 Color;
};
