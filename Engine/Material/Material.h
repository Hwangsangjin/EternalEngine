#pragma once

class ENGINE_API FMaterial
{
public:
    virtual ~FMaterial() = default;

    virtual void Bind() = 0;

	FString GetShaderPath(const FString& FileName);
};
