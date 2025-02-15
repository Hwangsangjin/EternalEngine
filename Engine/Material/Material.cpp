#include "Precompiled.h"
#include "Material.h"

FString FMaterial::GetShaderPath(const FString& FileName)
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
			return FString(CurrentPath.wstring().c_str()) + TEXT("/Resource/Shader/") + FileName;
	}

	// 리소스 폴더를 찾지 못한 경우 빈 문자열 반환
	return FString();
}
