#pragma once

#include "RHI.h"

class ENGINE_API FConsoleRHI : public FRHI
{
	RTTI_DECL(FConsoleRHI, FRHI)

public:
	FConsoleRHI();
	virtual ~FConsoleRHI();

	virtual void Clear() override;
	virtual void Present() override;

	// 커서 설정 함수
	void SetCursorType(const ECursorType& InCursorType);

	// 화면에 그리는 함수
	virtual void DrawPoint(const FVector2& InPosition, const FLinearColor& InColor) override {}
	virtual void DrawPoint(const FScreenPoint& InPosition, const FLinearColor& InColor) override {}
	virtual void DrawLine(const FVector2& InStartPosition, const FVector2& InEndPosition, const FLinearColor& InColor) override {}
	virtual void DrawText(const FVector2& InPosition, const FString& InText, const FLinearColor& InColor) override;
	virtual void DrawStaticMesh(FStaticMesh* InStaticMesh, const std::vector<FMaterial*>& InMaterials) override {}

protected:
	virtual FVertexBuffer* CreateVertexBuffer(UINT Size, const void* Data) override { return nullptr; }
	virtual FIndexBuffer* CreateIndexBuffer(UINT Size, const void* Data) override { return nullptr; }
	virtual void SetVertexBuffer(FVertexBuffer* VertexBuffer, UINT Stride, UINT Offset) override {}
	virtual void SetIndexBuffer(FIndexBuffer* IndexBuffer) override {}

	FORCEINLINE virtual void* GetRawDevice() const override { return nullptr; }
	FORCEINLINE virtual void* GetRawDeviceContext() const override { return nullptr; }

private:
	// 표준 디바이스 핸들
	HANDLE StdHandle;

	// 더블 버퍼링 변수
	HANDLE FrontBuffer;
	HANDLE BackBuffer;
	COORD BufferSize;
	CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
};
