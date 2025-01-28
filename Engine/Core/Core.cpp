#include "Precompiled.h"
#include "Core.h"
#include "Level/Level.h"
#include "Actor/Actor.h"
#include "Timer/Timer.h"
#include "Input/Input.h"
#include "World/World.h"
#include "Renderer/Renderer.h"

// 스태틱 변수 초기화
CCore* CCore::Instance = nullptr;

CCore::CCore()
	: bRunning(true)
	, DeltaTime(0.0f)
	, Timer(new CTimer)
	, Input(new CInput)
	, World(new CWorld)
	, Renderer(new CRenderer)
{
	// 싱글톤 객체 설정
	Instance = this;

	// 랜덤 시드 설정
	srand((unsigned int)time(nullptr));
}

CCore::~CCore()
{
	delete Timer;
	Timer = nullptr;

	delete Input;
	Input = nullptr;

	delete World;
	World = nullptr;

	delete Renderer;
	Renderer = nullptr;
}

CCore& CCore::Get()
{
	return *Instance;
}

void CCore::Run()
{
	// 퍼시스턴트 레벨이 없는 경우 종료
	if (!World->GetPersistentLevel())
		return;

	// 목표 프레임 설정
	Timer->SetTargetFPS(60.0f);

	// 게임 루프
	while (bRunning)
	{
		// 델타 타임 계산
		DeltaTime = Timer->CalculateDeltaTime();
		
		// 입력 처리
		Input->ProcessInput();

		// 업데이트
		World->Update(DeltaTime);

		// 렌더
		Renderer->Render();
	}
}

void CCore::QuitGame()
{
	// 실행 플래그 설정
	bRunning = false;
}

void CCore::LoadLevel(CLevel* InLevel)
{
	World->LoadLevel(InLevel);
}

void CCore::AddActor(CActor* InActor)
{
	World->GetPersistentLevel()->AddActor(InActor);
}

void CCore::RemoveActor(CActor* InActor)
{
	World->GetPersistentLevel()->RemoveActor(InActor);
}
