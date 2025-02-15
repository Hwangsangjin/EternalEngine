#include "Precompiled.h"
#include "DrawPointCommand.h"
#include "Core/Core.h"
#include "System/RenderSystem.h"

FDrawPointCommand::FDrawPointCommand(const FVector2 InPosition, const FLinearColor& InColor)
	: Position(InPosition)
	, Color(InColor)
{
}

void FDrawPointCommand::Execute()
{
	CCore::Get().GetRenderSystem()->DrawPoint(Position, Color);
}
