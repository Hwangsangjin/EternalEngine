#include "Precompiled.h"
#include "DirectX11Material.h"
#include "Core/Core.h"
#include "System/RenderSystem.h"
#include "RHI/RHI.h"

FDirectX11Material::FDirectX11Material(const FString& ShaderName)
{
	// 정점 셰이더 컴파일
	FString FileName = ShaderName + TEXT("VertexShader.hlsl");
	HRESULT Result = D3DCompileFromFile(
		GetShaderPath(FileName).GetWideString().c_str(),
		nullptr,
		nullptr,
		"main",
		"vs_5_0",
		0,
		0,
		&VertexBlob,
		nullptr
	);

	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to compile vertex shader", "Error", MB_OK);
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
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	// 입력 레이아웃 생성
	Result = Device->CreateInputLayout(
		InputElementDesc,
		_countof(InputElementDesc),
		VertexBlob->GetBufferPointer(),
		VertexBlob->GetBufferSize(),
		&InputLayout
	);

	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to create input layout", "Error", MB_OK);
		__debugbreak();
	}

	// 픽셀 셰이더 컴파일
	FileName = ShaderName + TEXT("PixelShader.hlsl");
	Result = D3DCompileFromFile(
		GetShaderPath(FileName).GetWideString().c_str(),
		nullptr,
		nullptr,
		"main",
		"ps_5_0",
		0,
		0,
		&PixelBlob,
		nullptr
	);

	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to compile pixel shader", "Error", MB_OK);
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
}
