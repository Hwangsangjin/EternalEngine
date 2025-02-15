#pragma once

#include "DrawCommand.h"

class ENGINE_API FDrawTextCommand : public FDrawCommand
{
public:
    FDrawTextCommand(const FVector2& InPosition, const FString& InText, const FLinearColor& InColor);
    virtual ~FDrawTextCommand() = default;

    virtual void Execute() override;

private:
    FVector2 Position;
    FString Text;
    FLinearColor Color;
};
