#pragma once

class ENGINE_API CTimerSystem
{
public:
	CTimerSystem();

	float CalculateDeltaTime();

	FORCEINLINE float GetDeltaTime() const { return DeltaTime; }
	FORCEINLINE float GetFPS() const { return FPS; }
	FORCEINLINE void SetTargetFPS(float InFPS) { TargetDeltaTime = 1.0f / InFPS; }

private:
	LARGE_INTEGER Frequency;
	LARGE_INTEGER CurrentTime;
	LARGE_INTEGER PreviousTime;
	float TargetDeltaTime;
	float DeltaTime;
	float FPS;
};
