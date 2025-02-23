#pragma once

#include "Material.h"

class FDirectX11Texture;

class ENGINE_API FDirectX11Material : public FMaterial
{
public:
	FDirectX11Material(const FString& ShaderName);
	virtual ~FDirectX11Material();

	virtual void Bind() override;

	void SetTexture(const FString& TextureName);

private:
	ID3D11InputLayout* InputLayout;

	ID3D11VertexShader* VertexShader;
	ID3D11PixelShader* PixelShader;

	ID3DBlob* VertexBlob;
	ID3DBlob* PixelBlob;

	ID3D11Texture2D* DefaultTexture;
	ID3D11ShaderResourceView* DefaultShaderResourceView;
	ID3D11SamplerState* DefaultSamplerState;

	FDirectX11Texture* Texture;
	bool bHasTexture;
};
