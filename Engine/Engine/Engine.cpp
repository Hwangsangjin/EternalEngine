#include "Precompiled.h"
#include "Engine.h"
#include "Level/Level.h"
#include "Actor/Actor.h"
#include "Math/Vector2.h"

// 스태틱 변수 초기화
CEngine* CEngine::Instance = nullptr;

CEngine::CEngine()
	: TargetFrameRate(60.0f)
	, OneFrameTime(0.0f)
	, bShouldUpdate(true)
	, bQuit(false)
	, MainLevel(nullptr)
{
	// 싱글톤 객체 설정
	Instance = this;

	// 기본 타겟 프레임 속도 설정
	SetTargetFrameRate(60.0f);
}

CEngine::~CEngine()
{
	// 메인 레벨 메모리 해제
	if (MainLevel)
	{
		delete MainLevel;
		MainLevel = nullptr;
	}
}

void CEngine::Run()
{
	// 메인 레벨이 없는 경우 리턴
	if (!MainLevel)
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

			if (bShouldUpdate)
			{
				// 업데이트
				Update(DeltaTime);

				// 렌더
				Render();
			}

			// 키 상태 저장
			SavePreviousKeyStates();

			// 이전 프레임 시간 저장
			PreviousTime = CurrentTime;

			// 삭제 요청된 액터 정리
			MainLevel->DestroyActor();

			// 프레임 업데이트 활성화
			bShouldUpdate = true;
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
	if (MainLevel == NewLevel)
		return;

	// 기존 레벨이 있다면 삭제
	if (MainLevel)
		delete MainLevel;

	// 메인 레벨 설정
	MainLevel = NewLevel;
}

void CEngine::AddActor(CActor* NewActor)
{
	if (!NewActor)
		return;

	bShouldUpdate = false;
	MainLevel->AddActor(NewActor);
}

void CEngine::DestroyActor(CActor* TargetActor)
{
	if (!TargetActor)
		return;

	bShouldUpdate = false;
	TargetActor->Destroy();
}

void CEngine::SetCursorType(ECursorType CursorType)
{
	// #1 커서 속성 구조체 설정
	CONSOLE_CURSOR_INFO Info = {};

	// 타입 별로 구조체 값 설정
	switch (CursorType)
	{
	case ECursorType::NoCursor:
		Info.dwSize = 1;
		Info.bVisible = FALSE;
		break;
	case ECursorType::SolidCursor:
		Info.dwSize = 100;
		Info.bVisible = TRUE;
		break;
	case ECursorType::NormalCursor:
		Info.dwSize = 20;
		Info.bVisible = TRUE;
		break;
	}

	// #2 설정
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

void CEngine::SetCursorPosition(const FVector2& Position)
{
	SetCursorPosition(static_cast<int>(Position.X), static_cast<int>(Position.Y));
}

void CEngine::SetCursorPosition(int X, int Y)
{
	static const HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	const COORD Coord = {static_cast<short>(X), static_cast<short>(Y)};
	SetConsoleCursorPosition(Handle, Coord);
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
	MainLevel->Update(DeltaTime);

	// 종료키 입력 확인
	if (GetKeyDown(VK_ESCAPE))
		QuitGame();
}

void CEngine::Clear()
{
	SetCursorPosition(0, 0);

	constexpr size_t Height = 25;
	for (size_t i = 0; i < Height; ++i)
		std::cout << "                               \n";

	SetCursorPosition(0, 0);
}

void CEngine::Render()
{
	// 화면 지우기
	Clear();

	// 레벨 렌더
	MainLevel->Render();
}

void CEngine::SavePreviousKeyStates()
{
	for (size_t i = 0; i < 255; ++i)
		KeyState[i].bWasKeyDown = KeyState[i].bIsKeyDown;
}
