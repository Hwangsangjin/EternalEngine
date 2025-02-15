#include "Precompiled.h"
#include "DirectX11VertexBuffer.h"

FDirectX11VertexBuffer::FDirectX11VertexBuffer(ID3D11Buffer* InVertexBuffer)
	: VertexBuffer(InVertexBuffer)
{
}

FDirectX11VertexBuffer::~FDirectX11VertexBuffer()
{
    if (VertexBuffer)
    {
        VertexBuffer->Release();
        VertexBuffer = nullptr;
    }
}
