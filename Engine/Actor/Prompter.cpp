#include "Precompiled.h"
#include "Prompter.h"
#include "Engine/Engine.h"

CPrompter::CPrompter(char Image)
	: Image(Image)
{
}

CPrompter::~CPrompter()
{
}

void CPrompter::Render()
{
	Super::Render();

	// #1 콘솔 좌표 옮기기
	CEngine::Get().SetCursorPosition(Position);

	// #2 콘솔 출력
	Log("%c", Image);
}

void CPrompter::SetPosition(const FVector2& NewPosition)
{
	// 이전의 위치를 먼저 지우기
	CEngine::Get().SetCursorPosition(Position);
	Log(" ");

	// 새로운 위치로 옮기기
	Super::SetPosition(NewPosition);
}
