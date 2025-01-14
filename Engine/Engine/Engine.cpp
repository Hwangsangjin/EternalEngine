﻿#include "Precompiled.h"
#include "Engine.h"
#include "Level/Level.h"
#include "Actor/Actor.h"

// 스태틱 변수 초기화
CEngine* CEngine::Instance = nullptr;

CEngine::CEngine()
	: StdHandle(GetStdHandle(STD_OUTPUT_HANDLE))
	, FrontBuffer(INVALID_HANDLE_VALUE)
	, BackBuffer(INVALID_HANDLE_VALUE)
	, BufferSize(COORD(1920, 1080))
	, TargetFrameRate(60.0f)
	, OneFrameTime(0.0f)
	, bQuit(false)
	, PersistentLevel(nullptr)
{
	// 싱글톤 객체 설정
	Instance = this;

	// 콘솔 화면 버퍼 설정
	FrontBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
	BackBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
	SetConsoleScreenBufferSize(FrontBuffer, BufferSize);
	SetConsoleScreenBufferSize(BackBuffer, BufferSize);
	SetConsoleActiveScreenBuffer(FrontBuffer);

	// 기본 타겟 프레임 속도 설정
	SetTargetFrameRate(TargetFrameRate);
}

CEngine::~CEngine()
{
	// 메인 레벨 메모리 해제
	if (PersistentLevel)
	{
		delete PersistentLevel;
		PersistentLevel = nullptr;
	}

	// 화면 버퍼 메모리 해제
	if (FrontBuffer != INVALID_HANDLE_VALUE)
		CloseHandle(FrontBuffer);
	if (BackBuffer != INVALID_HANDLE_VALUE)
		CloseHandle(BackBuffer);
}

void CEngine::Run()
{
	// 메인 레벨이 없는 경우 리턴
	if (!PersistentLevel)
		return;

	// CPU 시계 사용
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);

	// 시작 시간 및 이전 시간을 위한 변수
	LARGE_INTEGER Time;
	QueryPerformanceCounter(&Time);

	int64_t CurrentTime = Time.QuadPart;
	int64_t PreviousTime = 0;

	// 게임 루프
	while (true)
	{
		// 종료 조건
		if (bQuit)
			break;

		// 현재 프레임 시간 저장
		QueryPerformanceCounter(&Time);
		CurrentTime = Time.QuadPart;

		// 프레임 시간 계산
		const float DeltaTime = static_cast<float>(CurrentTime - PreviousTime) / static_cast<float>(Frequency.QuadPart);

		// 프레임 확인
		if (DeltaTime >= OneFrameTime)
		{
			// 입력 처리 (현재 키의 눌림 상태 확인)
			ProcessInput();

			// 업데이트
			Update(DeltaTime);

			// 렌더
			Render();

			// 키 상태 저장
			SavePreviousKeyStates();

			// 이전 프레임 시간 저장
			PreviousTime = CurrentTime;
		}
	}
}

CEngine& CEngine::Get()
{
	return *Instance;
}

bool CEngine::GetKey(int Key)
{
	return KeyState[Key].bIsKeyDown;
}

bool CEngine::GetKeyDown(int Key)
{
	return KeyState[Key].bIsKeyDown && !KeyState[Key].bWasKeyDown;
}

bool CEngine::GetKeyUp(int Key)
{
	return !KeyState[Key].bIsKeyDown && !KeyState[Key].bWasKeyDown;
}

void CEngine::LoadLevel(CLevel* NewLevel)
{
	// 새로운 레벨이 널인 경우 리턴
	if (!NewLevel)
		return;

	// 메인 레벨과 새로운 레벨이 같은 경우 리턴
	if (PersistentLevel == NewLevel)
		return;

	// 기존 레벨이 있다면 삭제
	if (PersistentLevel)
		delete PersistentLevel;

	// 메인 레벨 설정
	PersistentLevel = NewLevel;
}

void CEngine::AddActor(CActor* NewActor)
{
	if (!NewActor)
		return;

	PersistentLevel->AddActor(NewActor);
}

void CEngine::RemoveActor(CActor* TargetActor)
{
	if (!TargetActor)
		return;

	PersistentLevel->RemoveActor(TargetActor);
}

void CEngine::SetCursorType(const ECursorType& CursorType)
{
	CONSOLE_CURSOR_INFO CursorInfo = {};

	// 타입 별로 구조체 값 설정
	switch (CursorType)
	{
	case ECursorType::NoCursor:
		CursorInfo.dwSize = 1;
		CursorInfo.bVisible = FALSE;
		break;
	case ECursorType::SolidCursor:
		CursorInfo.dwSize = 100;
		CursorInfo.bVisible = TRUE;
		break;
	case ECursorType::NormalCursor:
		CursorInfo.dwSize = 20;
		CursorInfo.bVisible = TRUE;
		break;
	}

	SetConsoleCursorInfo(StdHandle, &CursorInfo);
}

void CEngine::SetCursorPosition(const FVector2& Position)
{
	const COORD Coord = { static_cast<SHORT>(Position.X), static_cast<SHORT>(Position.Y) };
	SetConsoleCursorPosition(StdHandle, Coord);
}

void CEngine::SetConsoleColor(WORD Color)
{
	SetConsoleTextAttribute(StdHandle, Color);
}

void CEngine::PrintText(const FVector2& Position, WORD Color, const std::string& Text)
{
	// 위치 설정
	COORD Coord = { static_cast<SHORT>(Position.X), static_cast<SHORT>(Position.Y) };

	// 텍스트 색상 설정
	DWORD Written = 0;
	FillConsoleOutputAttribute(BackBuffer, Color, static_cast<DWORD>(Text.size()), Coord, &Written);

	// 텍스트 출력
	WriteConsoleOutputCharacterA(BackBuffer, Text.c_str(), static_cast<DWORD>(Text.size()), Coord, &Written);

	// 커서를 다음 줄로 이동
	Coord.X = 0;
	Coord.Y += 1;
	SetConsoleCursorPosition(StdHandle, Coord);
}

void CEngine::SetTargetFrameRate(float FrameRate)
{
	TargetFrameRate = FrameRate;
	OneFrameTime = 1.0f / FrameRate;
}

void CEngine::QuitGame()
{
	// 종료 플래그 설정
	bQuit = true;
}

void CEngine::ProcessInput()
{
	for (int i = 0; i < 255; ++i)
		KeyState[i].bIsKeyDown = GetAsyncKeyState(i) & 0x8000 ? true : false;
}

void CEngine::Update(float DeltaTime)
{
	// 레벨 업데이트
	PersistentLevel->Update(DeltaTime);
}

void CEngine::Clear()
{
	// 백 버퍼 초기화
	DWORD Written = 0;
	COORD Coord = { 0, 0 };
	DWORD ConsoleSize = BufferSize.X * BufferSize.Y;

	// 화면을 지우는 대신 변경된 영역만 초기화
	FillConsoleOutputCharacter(BackBuffer, ' ', ConsoleSize, Coord, &Written);
	FillConsoleOutputAttribute(BackBuffer, 7, ConsoleSize, Coord, &Written);
}

void CEngine::Present()
{
	// 백 버퍼를 활성화하고 스왑
	SetConsoleActiveScreenBuffer(BackBuffer);

	// 현재 백 버퍼를 프론트 버퍼로 교체
	HANDLE TempBuffer = FrontBuffer;
	FrontBuffer = BackBuffer;
	BackBuffer = TempBuffer;
}

void CEngine::Render()
{
	// 화면 지우기
	Clear();

	// 레벨 렌더
	PersistentLevel->Render();

	// 버퍼 스왑
	Present();
}

void CEngine::SavePreviousKeyStates()
{
	for (size_t i = 0; i < 255; ++i)
		KeyState[i].bWasKeyDown = KeyState[i].bIsKeyDown;
}
