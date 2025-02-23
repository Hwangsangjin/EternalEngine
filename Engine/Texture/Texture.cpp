#include "Precompiled.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Stb/stb_image.h"
#include "Core/Core.h"
#include "System/RenderSystem.h"
#include "RHI/RHI.h"

FTexture::~FTexture()
{
	free(Data);
	Data = nullptr;
}

void FTexture::LoadTexture(const FString& InTextureName)
{
	// 파일 로드
	Data = stbi_load(GetTexturePath(InTextureName).ToString().c_str(), &Width, &Height, &ChannelCount, 0);

	// 예외 처리
	if (!Data)
	{
		// "Failed to load texture file :"
		MessageBoxA(nullptr, ("Failed to load texture file :" + Name).ToString().c_str(), "Error", MB_OK);
		__debugbreak();
	}
}

FString FTexture::GetTexturePath(const FString& InFileName)
{
	// 현재 실행 파일 경로
	std::filesystem::path CurrentPath = std::filesystem::current_path();

	// 상위 경로로 올라가면서 리소스 폴더 찾기
	while (CurrentPath.has_parent_path())
	{
		// 현재 경로를 상위 경로로 변경
		CurrentPath = CurrentPath.parent_path();

		// 리소스 폴더를 찾았다면 경로 결합 후 반환
		if (std::filesystem::exists(CurrentPath / "Resource"))
			return FString(CurrentPath.wstring().c_str()) + TEXT("/Resource/Texture/") + InFileName;
	}

	// 리소스 폴더를 찾지 못한 경우 빈 문자열 반환
	return FString();
}
