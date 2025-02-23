#include "Precompiled.h"
#include "DirectX11Material.h"
#include "Texture/DirectX11Texture.h"
#include "Core/Core.h"
#include "System/RenderSystem.h"
#include "RHI/RHI.h"

FDirectX11Material::FDirectX11Material(const FString& ShaderName)
	: DefaultTexture(nullptr)
	, DefaultShaderResourceView(nullptr)
	, DefaultSamplerState(nullptr)
	, Texture(nullptr)
	, bHasTexture(false)
{
	// 정점 셰이더 리드
	FString FileName = ShaderName + TEXT("_VS_5_0.cso");
	HRESULT Result = D3DReadFileToBlob(GetShaderPath(FileName).GetWideString().c_str(), &VertexBlob);
	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to read vertex shader object", "Error", MB_OK);
		__debugbreak();
	}

	// 정점 셰이더 생성
	ID3D11Device* Device = CCore::Get().GetRenderSystem()->GetRHI()->GetDevice<ID3D11Device>();
	Result = Device->CreateVertexShader(VertexBlob->GetBufferPointer(), VertexBlob->GetBufferSize(), nullptr, &VertexShader);
	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to create vertex shader", "Error", MB_OK);
		__debugbreak();
	}

	// 입력 레이아웃 정보
	constexpr D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// 입력 레이아웃 생성
	Result = Device->CreateInputLayout(InputElementDesc, _countof(InputElementDesc), VertexBlob->GetBufferPointer(), VertexBlob->GetBufferSize(), &InputLayout);
	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to create input layout", "Error", MB_OK);
		__debugbreak();
	}

	// 픽셀 셰이더 리드
	FileName = ShaderName + TEXT("_PS_5_0.cso");
	Result = D3DReadFileToBlob(GetShaderPath(FileName).GetWideString().c_str(), &PixelBlob);
	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to read pixel shader object", "Error", MB_OK);
		__debugbreak();
	}

	// 픽셀 셰이더 생성
	Result = Device->CreatePixelShader(PixelBlob->GetBufferPointer(), PixelBlob->GetBufferSize(), nullptr, &PixelShader);
	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to create pixel shader", "Error", MB_OK);
		__debugbreak();
	}
}

FDirectX11Material::~FDirectX11Material()
{
	if (InputLayout)
		InputLayout->Release();

	if (VertexShader)
		VertexShader->Release();

	if (PixelShader)
		PixelShader->Release();

	if (VertexBlob)
		VertexBlob->Release();

	if (PixelBlob)
		PixelBlob->Release();

	if (Texture)
	{
		delete Texture;
		Texture = nullptr;
	}
}

void FDirectX11Material::Bind()
{
	// 디바이스 컨텍스트 얻기
	static ID3D11DeviceContext* DeviceContext = CCore::Get().GetRenderSystem()->GetRHI()->GetDeviceContext<ID3D11DeviceContext>();

	// 프리미티브 토폴로지 설정
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	// 입력 레이아웃 설정
	DeviceContext->IASetInputLayout(InputLayout);

	// 셰이더 설정
	DeviceContext->VSSetShader(VertexShader, nullptr, 0);
	DeviceContext->PSSetShader(PixelShader, nullptr, 0);

	// 텍스처 설정
	if (bHasTexture)
		Texture->Bind();
	else
	{
		D3D11_TEXTURE2D_DESC TextureDesc = {};
		TextureDesc.Width = 1;
		TextureDesc.Height = 1;
		TextureDesc.MipLevels = 1;
		TextureDesc.ArraySize = 1;
		TextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		TextureDesc.SampleDesc.Count = 1;
		TextureDesc.Usage = D3D11_USAGE_DEFAULT;
		TextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		TextureDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA InitData = {};
		unsigned char DefaultColor[4] = { 255, 255, 255, 255 };
		InitData.pSysMem = DefaultColor;
		InitData.SysMemPitch = 4;
		InitData.SysMemSlicePitch = 4;

		static ID3D11Device* Device = CCore::Get().GetRenderSystem()->GetRHI()->GetDevice<ID3D11Device>();

		HRESULT Result = Device->CreateTexture2D(&TextureDesc, &InitData, &DefaultTexture);
		if (FAILED(Result))
		{
			MessageBoxA(nullptr, "Failed to create default texture", "Error", MB_OK);
			__debugbreak();
		}

		Result = Device->CreateShaderResourceView(DefaultTexture, nullptr, &DefaultShaderResourceView);
		if (FAILED(Result))
		{
			MessageBoxA(nullptr, "Failed to create shader resource view for default texture", "Error", MB_OK);
			__debugbreak();
		}

		D3D11_SAMPLER_DESC SamplerDesc = {};
		SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		SamplerDesc.BorderColor[0] = 0.0f;
		SamplerDesc.BorderColor[1] = 0.0f;
		SamplerDesc.BorderColor[2] = 0.0f;
		SamplerDesc.BorderColor[3] = 0.0f;
		SamplerDesc.MipLODBias = 0.0f;
		SamplerDesc.MaxAnisotropy = 1;
		SamplerDesc.MinLOD = 0;
		SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		Result = Device->CreateSamplerState(&SamplerDesc, &DefaultSamplerState);
		if (FAILED(Result))
		{
			MessageBoxA(nullptr, "Failed to create sampler state", "Error", MB_OK);
			__debugbreak();
		}

		DeviceContext->PSSetSamplers(0, 1, &DefaultSamplerState);
		DeviceContext->PSSetShaderResources(0, 1, &DefaultShaderResourceView);
	}
}

void FDirectX11Material::SetTexture(const FString& TextureName)
{
	Texture = new FDirectX11Texture(TextureName);
	bHasTexture = true;
}
