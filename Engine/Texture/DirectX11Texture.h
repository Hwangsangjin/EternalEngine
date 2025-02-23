#pragma once

#include "Texture.h"

class ENGINE_API FDirectX11Texture : public FTexture
{
public:
	FDirectX11Texture(const FString& InTextureName, EBindType InBindType = EBindType::PS, UINT InIndex = 0u);
	virtual ~FDirectX11Texture();

	virtual void Bind() override;

private:
	ID3D11Texture2D* Texture;
	ID3D11ShaderResourceView* ShaderResourceView;
	ID3D11SamplerState* SamplerState;
};
