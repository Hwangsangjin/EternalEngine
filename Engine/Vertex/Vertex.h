#pragma once

struct ENGINE_API FVertex
{
	FVertex(const FVector3& InPosition, const FVector3& InColor, const FVector2& InTexCoord);

	FVector3 Position;
	FVector3 Color;
	FVector2 TexCoord;
};
