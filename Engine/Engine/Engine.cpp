#pragma comment(lib, "winmm.lib")

#include "Engine.h"
#include <iostream>
#include <windows.h>

CEngine::CEngine()
	: bQuit{false}
{
}

CEngine::~CEngine()
{
}

void CEngine::Run()
{
	// CPU 시계 사용
	LARGE_INTEGER Frequency;
	QueryPerformanceFrequency(&Frequency);

	// 시작 시간 및 이전 시간을 위한 변수
	LARGE_INTEGER Time;
	QueryPerformanceCounter(&Time);

	int64_t CurrentTime = Time.QuadPart;
	int64_t PreviousTime = 0;

	// 프레임 제한
	constexpr float TargetFrameRate = 60.0f;

	// 프레임 시간 계산
	constexpr float TargetOneFrameTime = 1.0f / TargetFrameRate;

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
		if (DeltaTime >= TargetOneFrameTime)
		{
			// 입력 처리 (현재 키의 눌림 상태 확인)
			ProcessInput();

			Update(DeltaTime);
			Render();

			// 키 상태 저장
			SavePreviousKeyStates();

			// 이전 프레임 시간 저장
			PreviousTime = CurrentTime;
		}
	}
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

void CEngine::QuitGame()
{
	bQuit = true;
}

void CEngine::ProcessInput()
{
	for (size_t i = 0; i < 255; ++i)
		KeyState[i].bIsKeyDown = GetAsyncKeyState(i) & 0x8000 ? true : false;
}

void CEngine::Update(float DeltaTime)
{
	if (GetKeyDown(VK_ESCAPE))
		QuitGame();

	std::cout << "DeltaTime: " << DeltaTime << ", FPS: " << (1.0f / DeltaTime) << "\n";
}

void CEngine::Render()
{
}

void CEngine::SavePreviousKeyStates()
{
	for (size_t i = 0; i < 255; ++i)
		KeyState[i].bWasKeyDown = KeyState[i].bIsKeyDown;
}
