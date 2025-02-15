#include "Precompiled.h"
#include "StaticMesh.h"
#include "Vertex/Vertex.h"
#include "Material/Material.h"
#include "Material/DirectX11Material.h"
#include "Buffer/DirectX11VertexBuffer.h"
#include "Buffer/DirectX11IndexBuffer.h"
#include "Buffer/VertexBuffer.h"
#include "Buffer/IndexBuffer.h"
#include "Core/Core.h"
#include "System/RenderSystem.h"

FStaticMesh::FStaticMesh(const std::vector<FVertex>& InVertices, const std::vector<UINT>& InIndices)
	: Vertices(InVertices)
	, Indices(InIndices)
	, VertexBuffer(nullptr)
	, IndexBuffer(nullptr)
{
	Vertices.assign(InVertices.begin(), InVertices.end());
	Indices.assign(InIndices.begin(), InIndices.end());

	VertexBuffer = CCore::Get().GetRenderSystem()->CreateVertexBuffer(sizeof(FVertex) * static_cast<UINT>(Vertices.size()), Vertices.data());
	IndexBuffer = CCore::Get().GetRenderSystem()->CreateIndexBuffer(sizeof(UINT) * static_cast<UINT>(Indices.size()), Indices.data());
}

FStaticMesh::~FStaticMesh()
{
	if (VertexBuffer)
	{
		delete VertexBuffer;
		VertexBuffer = nullptr;
	}

	if (IndexBuffer)
	{
		delete IndexBuffer;
		IndexBuffer = nullptr;
	}
}

void FStaticMesh::Bind()
{
	UINT Stride = sizeof(FVertex);
	UINT Offset = 0;

	CCore::Get().GetRenderSystem()->SetVertexBuffer(VertexBuffer, Stride, Offset);
	CCore::Get().GetRenderSystem()->SetIndexBuffer(IndexBuffer);
}
