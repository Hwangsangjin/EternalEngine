#include "Precompiled.h"
#include "Vertex.h"

FVertex::FVertex(const FVector3& InPosition, const FVector3& InColor, const FVector2& InTexCoord)
	: Position(InPosition)
	, Color(InColor)
	, TexCoord(InTexCoord)
{
}
