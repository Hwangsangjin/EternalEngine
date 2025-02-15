#pragma once

#include "DrawCommand.h"

class ENGINE_API FDrawPointCommand : public FDrawCommand
{
public:
	FDrawPointCommand(const FVector2 InPosition, const FLinearColor& InColor);
	virtual ~FDrawPointCommand() = default;

	virtual void Execute() override;

private:
	FVector2 Position;
	FLinearColor Color;
};
