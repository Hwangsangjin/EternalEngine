#pragma once

#include "VertexBuffer.h"

class ENGINE_API FDirectX11VertexBuffer : public FVertexBuffer
{
public:
    FDirectX11VertexBuffer(ID3D11Buffer* InVertexBuffer);
    virtual ~FDirectX11VertexBuffer();

    virtual void* GetBuffer() const override { return static_cast<void*>(VertexBuffer); }

private:
    ID3D11Buffer* VertexBuffer;
};
