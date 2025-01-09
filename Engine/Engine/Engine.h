﻿#pragma once

#include "Core.h"

// 입력 처리를 위한 구조체
struct SKeyState
{
	// 현재 프레임에 키가 눌렸는지 확인
	bool bIsKeyDown = false;

	// 이전 프레임에 키가 눌렸었는지 확인
	bool bWasKeyDown = false;
};

// 커서의 종류를 설정할 때 사용할 열거형
enum class ECursorType
{
	NoCursor,
	SolidCursor,
	NormalCursor
};

class CLevel;
struct FVector2;

// 엔진 클래스
class ENGINE_API CEngine
{
public:
	CEngine();
	virtual ~CEngine();

	// 엔진 실행 함수
	void Run();

	// 싱글톤 객체 접근 함수
	static CEngine& Get();

	// 입력 관련 함수
	bool GetKey(int Key);
	bool GetKeyDown(int Key);
	bool GetKeyUp(int Key);

	// 레벨 추가 함수
	void LoadLevel(CLevel* NewLevel);

	// 화면 좌표 관련 함수
	void SetCursorType(ECursorType CursorType);
	void SetCursorPosition(const FVector2& Position);
	void SetCursorPosition(int X, int Y);

	// 타겟 프레임 속도 설정 함수
	void SetTargetFrameRate(float TargetFrameRate);

	// 엔진 종료 함수
	void QuitGame();

protected:
	void ProcessInput();
	void Update(float DeltaTime);
	void Render();

	// 이전 프레임의 키 상태를 저장하는 함수
	void SavePreviousKeyStates();

protected:
	// 타겟 프레임 변수 (초당 프레임)
	float TargetFrameRate;

	// 한 프레임 시간 값 (단위: 초)
	float OneFrameTime;

	// 종료할 때 설정할 변수
	bool bQuit;

	// 키 상태를 저장하는 배열
	SKeyState KeyState[255];

	// 싱글톤 구현을 위한 스태틱 변수
	static CEngine* Instance;

	// 메인 레벨 변수
	CLevel* MainLevel;
};
