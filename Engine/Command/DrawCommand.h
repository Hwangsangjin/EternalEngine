#pragma once

class ENGINE_API FDrawCommand
{
public:
    virtual ~FDrawCommand() = default;

    virtual void Execute() = 0;
};
