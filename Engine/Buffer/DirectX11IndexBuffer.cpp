#include "Precompiled.h"
#include "DirectX11IndexBuffer.h"

FDirectX11IndexBuffer::FDirectX11IndexBuffer(ID3D11Buffer* InIndexBuffer)
	: IndexBuffer(InIndexBuffer)
{
}

FDirectX11IndexBuffer::~FDirectX11IndexBuffer()
{
    if (IndexBuffer)
    {
        IndexBuffer->Release();
        IndexBuffer = nullptr;
    }
}
