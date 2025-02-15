#pragma once

class FRHI;
class FDrawCommand;
class FCommandQueue;
class FVertexBuffer;
class FIndexBuffer;
class FStaticMesh;
class FMaterial;

class ENGINE_API CRenderSystem
{
public:
    CRenderSystem();
    ~CRenderSystem();

	void Render();

    void EnqueueCommand(FDrawCommand* RenderCommand);

	FVertexBuffer* CreateVertexBuffer(UINT Size, const void* Data = nullptr);
	FIndexBuffer* CreateIndexBuffer(UINT Size, const void* Data = nullptr);
	void SetVertexBuffer(FVertexBuffer* VertexBuffer, UINT Stride, UINT Offset);
	void SetIndexBuffer(FIndexBuffer* IndexBuffer);

	void DrawPoint(const FVector2& InPosition, const FLinearColor& InColor);
	void DrawPoint(const FScreenPoint& InPosition, const FLinearColor& InColor);
	void DrawLine(const FVector2& InStartPosition, const FVector2& InEndPosition, const FLinearColor& InColor);
#undef DrawText
	void DrawText(const FVector2& InPosition, const FString& InText, const FLinearColor& InColor);
	void DrawStaticMesh(FStaticMesh* InStaticMesh, const std::vector<FMaterial*>& InMaterials);

	FORCEINLINE FRHI* GetRHI() const { return RHI; }

private:
	// RHI
	FRHI* RHI;

	// 커맨드 큐
	FCommandQueue* CommandQueue;
};
