#pragma once

#include "RTTI/RTTI.h"

class FVertexBuffer;
class FIndexBuffer;
class FStaticMesh;
class FMaterial;

class ENGINE_API FRHI : public RTTI
{
    RTTI_DECL(FRHI, RTTI)

public:
    virtual ~FRHI() = default;

    virtual void Clear() = 0;
    virtual void Present() = 0;

    virtual FVertexBuffer* CreateVertexBuffer(UINT InSize, const void* InData = nullptr) = 0;
    virtual FIndexBuffer* CreateIndexBuffer(UINT InSize, const void* InData = nullptr) = 0;
    virtual void SetVertexBuffer(FVertexBuffer* InVertexBuffer, UINT InStride, UINT InOffset) = 0;
    virtual void SetIndexBuffer(FIndexBuffer* InIndexBuffer) = 0;

    virtual void DrawPoint(const FVector2& InPosition, const FLinearColor& InColor) = 0;
    virtual void DrawPoint(const FScreenPoint& InPosition, const FLinearColor& InColor) = 0;
    virtual void DrawLine(const FVector2& InStartPosition, const FVector2& InEndPosition, const FLinearColor& InColor) = 0;
#undef DrawText
    virtual void DrawText(const FVector2& InPosition, const FString& InText, const FLinearColor& InColor) = 0;

    virtual void DrawStaticMesh(FStaticMesh* InStaticMesh, const std::vector<FMaterial*>& InMaterials) = 0;

    template <typename T>
    FORCEINLINE T* GetDevice() const
    {
        return static_cast<T*>(GetRawDevice());
    }

    template <typename T>
    FORCEINLINE T* GetDeviceContext() const
    {
        return static_cast<T*>(GetRawDeviceContext());
    }

protected:
    virtual void* GetRawDevice() const = 0;
    virtual void* GetRawDeviceContext() const = 0;
};
