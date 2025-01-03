#include "PreCompiledHeader.h"
#include "Engine.h"
#include "Level/Level.h"

// 스태틱 변수 초기화
CEngine* CEngine::Instance = nullptr;

CEngine::CEngine()
	: bQuit{false}
	, MainLevel{nullptr}
{
	// 싱글톤 객체 설정
	Instance = this;
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

CEngine& CEngine::GetInstance()
{
	// 싱글톤 객체 반환
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
	// 메인 레벨과 새로운 레벨이 같은 경우 리턴
	if (MainLevel == NewLevel)
		return;

	// 기존 레벨이 있다면 삭제
	if (MainLevel)
		delete MainLevel;

	// 메인 레벨 설정
	MainLevel = NewLevel;
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
	if (MainLevel)
		MainLevel->Update(DeltaTime);

	// 종료키 입력 확인
	if (GetKeyDown(VK_ESCAPE))
		QuitGame();

	// 프레임 확인
	std::cout << "DeltaTime: " << DeltaTime << ", FPS: " << (1.0f / DeltaTime) << "\n";
}

void CEngine::Render()
{
	// 레벨 렌더
	if (MainLevel)
		MainLevel->Render();
}

void CEngine::SavePreviousKeyStates()
{
	for (size_t i = 0; i < 255; ++i)
		KeyState[i].bWasKeyDown = KeyState[i].bIsKeyDown;
}
