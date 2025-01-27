#include "Precompiled.h"
#include "Timer.h"
#include <chrono>

CTimer::CTimer()
	: Frequency()
	, CurrentTime()
	, PreviousTime()
	, TargetDeltaTime(0.0f)
	, DeltaTime(0.0f)
	, FPS(0.0f)
{
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&PreviousTime);
}

float CTimer::CalculateDeltaTime()
{
	do
	{
		// 현재 시간 측정
		QueryPerformanceCounter(&CurrentTime);

		// 델타 타임 계산 (현재 시간과 이전 시간 차이를 주파수로 나누기)
		DeltaTime = static_cast<float>(CurrentTime.QuadPart - PreviousTime.QuadPart) / static_cast<float>(Frequency.QuadPart);

	} while (DeltaTime < TargetDeltaTime); // 프레임이 너무 빠르게 진행되지 않도록 제한

	// 이전 시간을 현재 시간으로 업데이트
	PreviousTime = CurrentTime;

	// 초당 프레임 계산
	FPS = 1.0f / DeltaTime;
	 
	// 델타 타임 반환
	return DeltaTime;
}
