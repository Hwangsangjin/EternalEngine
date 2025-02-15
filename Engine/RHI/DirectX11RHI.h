#pragma once

#include "RHI.h"

class CWindow;

class ENGINE_API FDirectX11RHI : public FRHI
{
	RTTI_DECL(FDirectX11RHI, FRHI)

public:
    FDirectX11RHI();
    virtual ~FDirectX11RHI();

	virtual void Clear() override;
	virtual void Present() override;

	virtual FVertexBuffer* CreateVertexBuffer(UINT Size, const void* Data = nullptr) override;
	virtual FIndexBuffer* CreateIndexBuffer(UINT Size, const void* Data = nullptr) override;
	virtual void SetVertexBuffer(FVertexBuffer* VertexBuffer, UINT Stride, UINT Offset);
	virtual void SetIndexBuffer(FIndexBuffer* IndexBuffer);

	virtual void DrawPoint(const FScreenPoint& InPosition, const FLinearColor& InColor) override {}
	virtual void DrawPoint(const FVector2& InPosition, const FLinearColor& InColor) override {}
	virtual void DrawLine(const FVector2& InStartPosition, const FVector2& InEndPosition, const FLinearColor& InColor) override {}
	virtual void DrawText(const FVector2& InPosition, const FString& InText, const FLinearColor& InColor) override {}
	virtual void DrawStaticMesh(FStaticMesh* InStaticMesh, const std::vector<FMaterial*>& InMaterials) override;

protected:
	FORCEINLINE virtual void* GetRawDevice() const override { return Device; }
	FORCEINLINE virtual void* GetRawDeviceContext() const override { return DeviceContext; }

private:
	// 윈도우
	CWindow& Window;

	// 뷰포트
	D3D11_VIEWPORT ViewPort;

	// 장치
	ID3D11Device* Device;
	ID3D11DeviceContext* DeviceContext;
	IDXGISwapChain* SwapChain;

	// 버퍼
	ID3D11Texture2D* BackBuffer;
	ID3D11RenderTargetView* RenderTargetView;
	ID3D11DepthStencilView* DepthStencilView = nullptr;
};
