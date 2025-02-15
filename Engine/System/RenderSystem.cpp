#include "Precompiled.h"
#include "RenderSystem.h"
#include "Core/Core.h"
#include "World/World.h"
#include "Level/Level.h"
#include "RHI/RHIFactory.h"
#include "RHI/RHI.h"
#include "Command/DrawCommand.h"
#include "Command/CommandQueue.h"

CRenderSystem::CRenderSystem()
	: RHI(FRHIFactory::CreateRHI())
	, CommandQueue(new FCommandQueue)
{
}

CRenderSystem::~CRenderSystem()
{
	// RHI 리소스 해제
	if (RHI)
	{
		delete RHI;
		RHI = nullptr;
	}

	// 커맨드 큐 해제
	if (CommandQueue)
	{
		delete CommandQueue;
		CommandQueue = nullptr;
	}
}

void CRenderSystem::Render()
{
	// 화면 지우기
	RHI->Clear();

	// 레벨의 렌더 함수 호출하기
	CCore::Get().GetWorld()->GetPersistentLevel()->Render();

	// 커맨드 큐에 있는 명령 실행하기
	CommandQueue->ExecuteAll();

	// 버퍼 변경하기
	RHI->Present();
}

void CRenderSystem::EnqueueCommand(FDrawCommand* DrawCommand)
{
	if (CommandQueue)
		CommandQueue->Enqueue(DrawCommand);
}

FVertexBuffer* CRenderSystem::CreateVertexBuffer(UINT Size, const void* Data)
{
	FVertexBuffer* VertexBuffer = nullptr;

	if (RHI)
		VertexBuffer = RHI->CreateVertexBuffer(Size, Data);

	return VertexBuffer;
}

FIndexBuffer* CRenderSystem::CreateIndexBuffer(UINT Size, const void* Data)
{
	FIndexBuffer* IndexBuffer = nullptr;

	if (RHI)
		IndexBuffer = RHI->CreateIndexBuffer(Size, Data);

	return IndexBuffer;
}

void CRenderSystem::SetVertexBuffer(FVertexBuffer* VertexBuffer, UINT Stride, UINT Offset)
{
	if (RHI)
		RHI->SetVertexBuffer(VertexBuffer, Stride, Offset);
}

void CRenderSystem::SetIndexBuffer(FIndexBuffer* IndexBuffer)
{
	if (RHI)
		RHI->SetIndexBuffer(IndexBuffer);
}

void CRenderSystem::DrawPoint(const FVector2& InPosition, const FLinearColor& InColor)
{
	if (RHI)
		RHI->DrawPoint(InPosition, InColor);
}

void CRenderSystem::DrawPoint(const FScreenPoint& InPosition, const FLinearColor& InColor)
{
	if (RHI)
		RHI->DrawPoint(InPosition, InColor);
}

void CRenderSystem::DrawLine(const FVector2& InStartPosition, const FVector2& InEndPosition, const FLinearColor& InColor)
{
	if (RHI)
		RHI->DrawLine(InStartPosition, InEndPosition, InColor);
}

void CRenderSystem::DrawText(const FVector2& InPosition, const FString& InText, const FLinearColor& InColor)
{
	if (RHI)
		RHI->DrawText(InPosition, InText, InColor);
}

void CRenderSystem::DrawStaticMesh(FStaticMesh* InStaticMesh, const std::vector<FMaterial*>& InMaterials)
{
	if (RHI)
		RHI->DrawStaticMesh(InStaticMesh, InMaterials);
}
