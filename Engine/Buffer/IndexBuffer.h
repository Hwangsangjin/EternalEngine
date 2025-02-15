#pragma once

class ENGINE_API FIndexBuffer
{
public:
    virtual ~FIndexBuffer() = default;

    virtual void* GetBuffer() const = 0;
};
