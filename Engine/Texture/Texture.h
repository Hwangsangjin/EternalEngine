#pragma once

struct ENGINE_API FTexture
{
	virtual ~FTexture();

	virtual void Bind() = 0;

	void LoadTexture(const FString& InTextureName);

	FString GetTexturePath(const FString& InFileName);

	int Width = 0;
	int Height = 0;
	int ChannelCount = 0;
	FString Name;
	UINT Index = 0u;
	EBindType BindType = EBindType::PS;
	void* Data = nullptr;
};
