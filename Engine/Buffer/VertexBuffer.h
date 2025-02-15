#pragma once

class ENGINE_API FVertexBuffer
{
public:
    virtual ~FVertexBuffer() = default;

    virtual void* GetBuffer() const = 0;
};
