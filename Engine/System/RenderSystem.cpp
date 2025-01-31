#include "Precompiled.h"
#include "RenderSystem.h"
#include "Core/Core.h"
#include "World/World.h"

CRenderSystem::CRenderSystem()
	: StdHandle(GetStdHandle(STD_OUTPUT_HANDLE))
	, FrontBuffer(INVALID_HANDLE_VALUE)
	, BackBuffer(INVALID_HANDLE_VALUE)
	, BufferSize(COORD(50, 20))
	, BufferInfo()
{
	// 스크린 버퍼 생성
	FrontBuffer = CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	BackBuffer = CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	// 스크린 버퍼 크기 설정
	SetConsoleScreenBufferSize(FrontBuffer, BufferSize);
	SetConsoleScreenBufferSize(BackBuffer, BufferSize);

	// 창 크기 설정
	SMALL_RECT Rect = { 0, 0, BufferSize.X - 1, BufferSize.Y - 1 };
	SetConsoleWindowInfo(FrontBuffer, true, &Rect);
	SetConsoleWindowInfo(BackBuffer, true, &Rect);

	// 활성 버퍼 설정
	SetConsoleActiveScreenBuffer(FrontBuffer);

	// 커서 타입 설정
	SetCursorType(ECursorType::Hidden);
}

CRenderSystem::~CRenderSystem()
{
	// 스크린 버퍼 메모리 해제
	if (FrontBuffer != INVALID_HANDLE_VALUE)
		CloseHandle(FrontBuffer);
	if (BackBuffer != INVALID_HANDLE_VALUE)
		CloseHandle(BackBuffer);
}

void CRenderSystem::SetCursorType(const ECursorType& InCursorType)
{
	CONSOLE_CURSOR_INFO CursorInfo = {};

	// 타입 별로 구조체 값 설정
	switch (InCursorType)
	{
	case ECursorType::Hidden:
		CursorInfo.dwSize = 1;
		CursorInfo.bVisible = FALSE;
		break;
	case ECursorType::Solid:
		CursorInfo.dwSize = 100;
		CursorInfo.bVisible = TRUE;
		break;
	case ECursorType::Normal:
		CursorInfo.dwSize = 20;
		CursorInfo.bVisible = TRUE;
		break;
	}

	SetConsoleCursorInfo(FrontBuffer, &CursorInfo);
	SetConsoleCursorInfo(BackBuffer, &CursorInfo);
}

void CRenderSystem::PrintText(const FVector2& InPosition, const FString& InText, const EColor& InColor)
{
	// 텍스트 길이
	const DWORD Length = static_cast<DWORD>(InText.GetWideString().length());

	// 출력 위치
	const COORD Coord = { static_cast<SHORT>(InPosition.X), static_cast<SHORT>(InPosition.Y) };

	// 출력된 문자 또는 속성의 수
	DWORD Written = 0;

	// 콘솔 색상 설정
	FillConsoleOutputAttribute(BackBuffer, static_cast<WORD>(InColor), Length, Coord, &Written);

	// 문자열 전체를 한 번에 출력
	WriteConsoleOutputCharacterW(BackBuffer, InText.GetWideString().c_str(), Length, Coord, &Written);
}

void CRenderSystem::Render()
{
	// 화면 지우기
	Clear();

	// 월드 그리기
	CCore::Get().GetWorld()->Render();

	// 버퍼 변경하기
	Present();
}

void CRenderSystem::Clear()
{
	// 콘솔 버퍼 크기에 맞는 전체 문자 개수 계산
	const DWORD Length = BufferSize.X * BufferSize.Y;

	// 콘솔 좌표를 (0, 0)으로 설정 (시작 위치)
	constexpr COORD Coord = { 0, 0 };

	// 출력된 문자 또는 속성의 수
	DWORD Written = 0;

	// 백 버퍼를 공백 문자로 채우기 (콘솔에 출력된 내용을 비우기 위해)
	FillConsoleOutputCharacter(BackBuffer, ' ', Length, Coord, &Written);

	// 백 버퍼의 색상 속성 초기화 (기본 색상으로 설정)
	FillConsoleOutputAttribute(BackBuffer, BufferInfo.wAttributes, Length, Coord, &Written);
}

void CRenderSystem::Present()
{
	// 백 버퍼 활성화
	SetConsoleActiveScreenBuffer(BackBuffer);

	// 페이지 플리핑
	std::swap(FrontBuffer, BackBuffer);
}
