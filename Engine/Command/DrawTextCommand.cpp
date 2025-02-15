#include "Precompiled.h"
#include "DrawTextCommand.h"
#include "Core/Core.h"
#include "System/RenderSystem.h"

FDrawTextCommand::FDrawTextCommand(const FVector2& InPosition, const FString& InText, const FLinearColor& InColor)
    : Position(InPosition)
    , Text(InText)
    , Color(InColor)
{
}

void FDrawTextCommand::Execute()
{
    CCore::Get().GetRenderSystem()->DrawText(Position, Text, Color);
}
