#pragma once

#include "IndexBuffer.h"

class ENGINE_API FDirectX11IndexBuffer : public FIndexBuffer
{
public:
    FDirectX11IndexBuffer(ID3D11Buffer* InIndexBuffer);
    virtual ~FDirectX11IndexBuffer();

    virtual void* GetBuffer() const override { return static_cast<void*>(IndexBuffer); }

private:
    ID3D11Buffer* IndexBuffer;
};
