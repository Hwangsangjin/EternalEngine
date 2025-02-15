#include "Precompiled.h"
#include "DirectX11RHI.h"
#include "Window/Window.h"
#include "Buffer/DirectX11VertexBuffer.h"
#include "Buffer/DirectX11IndexBuffer.h"
#include "Mesh/StaticMesh.h"
#include "Material/Material.h"

FDirectX11RHI::FDirectX11RHI()
	: Window(CWindow::Get())
	, ViewPort()
	, Device(nullptr)
	, DeviceContext(nullptr)
	, SwapChain(nullptr)
	, BackBuffer(nullptr)
	, RenderTargetView(nullptr)
{
	// 장치 디버깅 플래그
	UINT Flag = 0u;

#if _DEBUG
	Flag |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	// 장치 기능 수준
	D3D_FEATURE_LEVEL FeatureLevel[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
	};

	// 스왑 체인 정보
	DXGI_SWAP_CHAIN_DESC SwapChainDesc = {};
	SwapChainDesc.Windowed = true; // 창 모드 여부
	SwapChainDesc.OutputWindow = Window.GetWindowHandle();
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferCount = 1; // 백 버퍼 개수
	SwapChainDesc.SampleDesc.Count = 1; // 멀티 샘플링 개수
	SwapChainDesc.SampleDesc.Quality = 0; // 멀티 샘플링 수준
	SwapChainDesc.BufferDesc.Width = Window.GetScreenSize().X;
	SwapChainDesc.BufferDesc.Height = Window.GetScreenSize().Y;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// 장치 생성
	HRESULT Result = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		Flag,
		FeatureLevel,
		_countof(FeatureLevel),
		D3D11_SDK_VERSION,
		&SwapChainDesc,
		&SwapChain,
		&Device,
		nullptr,
		&DeviceContext
	);

	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to create devices.", "Error", MB_OK);
		__debugbreak();
	}

	// 백 버퍼 얻기
	Result = SwapChain->GetBuffer(0, IID_PPV_ARGS(&BackBuffer));
	/*SwapChain->GetBuffer(
		0,
		__uuidof(BackBuffer),
		reinterpret_cast<void**>(&BackBuffer)
	);*/

	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to get back buffer", "Error", MB_OK);
		__debugbreak();
	}

	// 렌더 타겟 뷰 정보
	D3D11_RENDER_TARGET_VIEW_DESC RenderTargetViewDesc = {};
	RenderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	RenderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	// 렌더 타겟 뷰 생성
	Result = Device->CreateRenderTargetView(
		BackBuffer,
		nullptr,
		&RenderTargetView
	);

	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to create render target view", "Error", MB_OK);
		__debugbreak();
	}

	// 렌더 타겟 뷰 설정
	DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);

	// 뷰포트 정보
	ViewPort.TopLeftX = 0.0f;
	ViewPort.TopLeftY = 0.0f;
	ViewPort.Width = static_cast<float>(Window.GetScreenSize().X);
	ViewPort.Height = static_cast<float>(Window.GetScreenSize().Y);
	ViewPort.MaxDepth = 1.0f;
	ViewPort.MinDepth = 0.0f;

	// 뷰포트 설정
	DeviceContext->RSSetViewports(1, &ViewPort);
}

FDirectX11RHI::~FDirectX11RHI()
{
	if (BackBuffer)
	{
		BackBuffer->Release();
		BackBuffer = nullptr;
	}

	if (RenderTargetView)
	{
		RenderTargetView->Release();
		RenderTargetView = nullptr;
	}

	if (SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}

	if (DeviceContext)
	{
		DeviceContext->Release();
		DeviceContext = nullptr;
	}

	if (Device)
	{
		Device->Release();
		Device = nullptr;
	}
}

void FDirectX11RHI::Clear()
{
	constexpr float Color[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	DeviceContext->ClearRenderTargetView(RenderTargetView, Color);
}

void FDirectX11RHI::Present()
{
	SwapChain->Present(1u, 0u);
}

FVertexBuffer* FDirectX11RHI::CreateVertexBuffer(UINT InSize, const void* InData)
{
	// 정점 버퍼 정보
	D3D11_BUFFER_DESC VertexBufferDesc = {};
	VertexBufferDesc.ByteWidth = InSize;
	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// 정점 데이터
	D3D11_SUBRESOURCE_DATA VertexData = {};
	VertexData.pSysMem = InData;

	// 정점 버퍼 생성
	ID3D11Buffer* VertexBuffer = nullptr;
	HRESULT Result = Device->CreateBuffer(
		&VertexBufferDesc,
		&VertexData,
		&VertexBuffer
	);

	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to create vertex buffer", "Error", MB_OK);
		__debugbreak();
	}

	// 정점 버퍼 반환
	return new FDirectX11VertexBuffer(VertexBuffer);
}

FIndexBuffer* FDirectX11RHI::CreateIndexBuffer(UINT InSize, const void* InData)
{
	// 인덱스 버퍼 정보
	D3D11_BUFFER_DESC IndexBufferDesc = {};
	IndexBufferDesc.ByteWidth = InSize;
	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// 인덱스 데이터
	D3D11_SUBRESOURCE_DATA IndexData = {};
	IndexData.pSysMem = InData;

	// 인덱스 버퍼 생성
	ID3D11Buffer* IndexBuffer = nullptr;
	HRESULT Result = Device->CreateBuffer(
		&IndexBufferDesc,
		&IndexData,
		&IndexBuffer
	);

	if (FAILED(Result))
	{
		MessageBoxA(nullptr, "Failed to create index buffer", "Error", MB_OK);
		__debugbreak();
	}

	return new FDirectX11IndexBuffer(IndexBuffer);
}

void FDirectX11RHI::SetVertexBuffer(FVertexBuffer* InVertexBuffer, UINT InStride, UINT InOffset)
{
	ID3D11Buffer* D3D11Buffer = static_cast<ID3D11Buffer*>(InVertexBuffer->GetBuffer());
	DeviceContext->IASetVertexBuffers(0, 1, &D3D11Buffer, &InStride, &InOffset);
}

void FDirectX11RHI::SetIndexBuffer(FIndexBuffer* IndexBuffer)
{
	ID3D11Buffer* D3D11Buffer = static_cast<ID3D11Buffer*>(IndexBuffer->GetBuffer());
	DeviceContext->IASetIndexBuffer(D3D11Buffer, DXGI_FORMAT_R32_UINT, 0);
}

void FDirectX11RHI::DrawStaticMesh(FStaticMesh* InStaticMesh, const std::vector<FMaterial*>& InMaterials)
{
	InStaticMesh->Bind();

	for (size_t i = 0; i < InMaterials.size(); ++i)
		InMaterials[i]->Bind();

	DeviceContext->DrawIndexed(InStaticMesh->GetIndexCount(), 0, 0);
}
