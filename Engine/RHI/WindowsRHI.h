#pragma once

#include "RHI.h"

class CWindow;

class ENGINE_API FWindowsRHI : public FRHI
{
    RTTI_DECL(FWindowsRHI, FRHI)

public:
    FWindowsRHI();
    virtual ~FWindowsRHI();

    virtual void Clear() override;
    virtual void Present() override;

    void FillBuffer();

    FORCEINLINE bool IsInScreen(const FScreenPoint& InPosition) const
    {
        if ((InPosition.X < 0 || InPosition.X >= ScreenSize.X) || (InPosition.Y < 0 || InPosition.Y >= ScreenSize.Y))
            return false;

        return true;
    }

    FORCEINLINE int GetScreenBufferIndex(const FScreenPoint& InPosition) const
    {
        return InPosition.Y * ScreenSize.X + InPosition.X;
    }

    FORCEINLINE void SetPixel(const FScreenPoint& InPosition, const FLinearColor& InColor)
    {
        if (!IsInScreen(InPosition))
            return;

        FColor32* Dest = ScreenBuffer;
        *(Dest + GetScreenBufferIndex(InPosition)) = InColor.ToColor32();
    }

    virtual void DrawPoint(const FVector2& InPosition, const FLinearColor& InColor) override;
    virtual void DrawPoint(const FScreenPoint& InPoint, const FLinearColor& InColor) override;
    virtual void DrawLine(const FVector2& InStartPosition, const FVector2& InEndPosition, const FLinearColor& InColor) override {}
    virtual void DrawText(const FVector2& InPosition, const FString& InText, const FLinearColor& InColor) override {}
    virtual void DrawStaticMesh(FStaticMesh* InStaticMesh, const std::vector<FMaterial*>& InMaterials) override {}

protected:
    virtual FVertexBuffer* CreateVertexBuffer(UINT Size, const void* Data) override { return nullptr; }
    virtual FIndexBuffer* CreateIndexBuffer(UINT Size, const void* Data) override { return nullptr; }
    virtual void SetVertexBuffer(FVertexBuffer* VertexBuffer, UINT Stride, UINT Offset) override {}
    virtual void SetIndexBuffer(FIndexBuffer* IndexBuffer) override {}

    FORCEINLINE virtual void* GetRawDevice() const override { return nullptr; }
    FORCEINLINE virtual void* GetRawDeviceContext() const override { return nullptr; }

private:
    template <typename T>
    T* CopyBuffer(T* InDest, T* InSrc, int InCount)
    {
        if (InCount == 0)
            return nullptr;

        if (InCount == 1)
        {
            memcpy(InDest, InSrc, sizeof(T));
        }
        else
        {
            int Half = FMath::FloorToInt(InCount * 0.5f);
            CopyBuffer<T>(InDest, InSrc, Half);
            memcpy(InDest + Half, InDest, Half * sizeof(T));

            if (InCount % 2)
                memcpy(InDest + (InCount - 1), InSrc, sizeof(T));
        }

        return InDest;
    }

    void CreateDepthBuffer();
    void ClearDepthBuffer();

private:
    // 윈도우
    CWindow& Window;

    // 윈도우 핸들
    HWND WindowHandle;

    // 클라이언트 영역
    RECT Rect;

    // 화면 크기
    FScreenPoint ScreenSize;

    // 디바이스 컨텍스트
    HDC ScreenDC;
    HDC MemoryDC;

    // 버퍼
    FColor32* ScreenBuffer;
    float* DepthBuffer;

    // 비트맵
    HBITMAP DefaultBitmap;
    HBITMAP DIBitmap;
};
