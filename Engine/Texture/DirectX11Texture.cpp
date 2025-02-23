#include "Precompiled.h"
#include "DirectX11Texture.h"
#include "Core/Core.h"
#include "System/RenderSystem.h"
#include "RHI/RHI.h"

FDirectX11Texture::FDirectX11Texture(const FString& InTextureName, EBindType InBindType, UINT InIndex)
{
	// 텍스처 로드
	LoadTexture(InTextureName);

	// 텍스처 정보
	D3D11_TEXTURE2D_DESC TextureDesc = {};
	TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	TextureDesc.ArraySize = 1;
	TextureDesc.MipLevels = 1;
	TextureDesc.SampleDesc.Count = 1;
	TextureDesc.SampleDesc.Quality = 0;
	TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	TextureDesc.Width = Width;
	TextureDesc.Height = Height;

	// 서브리소스 데이터
	D3D11_SUBRESOURCE_DATA SubResourceData = {};
	SubResourceData.pSysMem = Data;
	SubResourceData.SysMemPitch = Width * ChannelCount;

	// 텍스처 생성
	static ID3D11Device* Device = CCore::Get().GetRenderSystem()->GetRHI()->GetDevice<ID3D11Device>();
	HRESULT Result = Device->CreateTexture2D(&TextureDesc, &SubResourceData, &Texture);
	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to create texture 2d", "Error", MB_OK);
		__debugbreak();
	}

	// 셰이더 리소스 뷰 생성
	Result = Device->CreateShaderResourceView(Texture, nullptr, &ShaderResourceView);
	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to create shader resource view", "Error", MB_OK);
		__debugbreak();
	}

	// 샘플러 정보
	D3D11_SAMPLER_DESC SamplerDesc = {};
	SamplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	SamplerDesc.MaxLOD = FLT_MAX;
	SamplerDesc.MinLOD = -FLT_MAX;
	SamplerDesc.MaxAnisotropy = 3;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;

	// 샘플러 생성
	Result = Device->CreateSamplerState(&SamplerDesc, &SamplerState);
	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to create sampler state", "Error", MB_OK);
		__debugbreak();
	}
}

FDirectX11Texture::~FDirectX11Texture()
{
	if (Texture)
	{
		Texture->Release();
		Texture = nullptr;
	}

	if (ShaderResourceView)
	{
		ShaderResourceView->Release();
		ShaderResourceView = nullptr;
	}

	if (SamplerState)
	{
		SamplerState->Release();
		SamplerState = nullptr;
	}
}

void FDirectX11Texture::Bind()
{
	if (!ShaderResourceView)
		return;
	if (!SamplerState)
		return;

	static ID3D11DeviceContext* DeviceContext = CCore::Get().GetRenderSystem()->GetRHI()-> GetDeviceContext<ID3D11DeviceContext>();

	if (BindType == EBindType::VS)
	{
		DeviceContext->VSSetShaderResources(Index, 1, &ShaderResourceView);
		DeviceContext->VSSetSamplers(Index, 1, &SamplerState);
	}
	else if (BindType == EBindType::PS)
	{
		DeviceContext->PSSetShaderResources(Index, 1, &ShaderResourceView);
		DeviceContext->PSSetSamplers(Index, 1, &SamplerState);
	}
}
