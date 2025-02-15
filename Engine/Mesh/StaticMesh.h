#pragma once

#include "Vertex/Vertex.h"

class FVertexBuffer;
class FIndexBuffer;

class ENGINE_API FStaticMesh
{
public:
	FStaticMesh(const std::vector<FVertex>& InVertices, const std::vector<UINT>& InIndices);
	~FStaticMesh();

	void Bind();

	FORCEINLINE UINT GetIndexCount() const { return static_cast<UINT>(Indices.size()); }

private:
	// 정점 데이터
	std::vector<FVertex> Vertices;

	// 정점 버퍼
	FVertexBuffer* VertexBuffer;

	// 인덱스 데이터
	std::vector<UINT> Indices;

	// 인덱스 버퍼
	FIndexBuffer* IndexBuffer;
};
