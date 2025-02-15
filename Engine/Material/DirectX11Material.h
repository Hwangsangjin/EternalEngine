#pragma once

#include "Material.h"

class ENGINE_API FDirectX11Material : public FMaterial
{
public:
	FDirectX11Material(const FString& ShaderName);
	virtual ~FDirectX11Material();

	virtual void Bind() override;

private:
	ID3D11InputLayout* InputLayout;

	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;

	ID3DBlob* VertexBlob;
	ID3DBlob* PixelBlob;
};

