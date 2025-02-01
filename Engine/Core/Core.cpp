#include "Precompiled.h"
#include "Core.h"
#include "World/World.h"
#include "Level/Level.h"
#include "Actor/Actor.h"
#include "System/TimerSystem.h"
#include "System/InputSystem.h"
#include "System/AudioSystem.h"
#include "System/RenderSystem.h"

// 스태틱 변수 초기화
CCore* CCore::Instance = nullptr;

CCore::CCore()
	: bRunning(true)
	, DeltaTime(0.0f)
	, World(new CWorld)
	, TimerSystem(new CTimerSystem)
	, InputSystem(new CInputSystem)
	, AudioSystem(new CAudioSystem)
	, RenderSystem(new CRenderSystem)
{
	// 싱글톤 객체 설정
	Instance = this;

	// 랜덤 시드 설정
	srand((unsigned int)time(nullptr));
}

CCore::~CCore()
{
	// 월드 메모리 해제
	delete World;
	World = nullptr;

	// 타이머 시스템 메모리 해제
	delete TimerSystem;
	TimerSystem = nullptr;

	// 입력 시스템 메모리 해제
	delete InputSystem;
	InputSystem = nullptr;

	// 오디오 시스템 메모리 해제
	delete AudioSystem;
	AudioSystem = nullptr;

	// 렌더 시스템 메모리 해제
	delete RenderSystem;
	RenderSystem = nullptr;
}

void CCore::Run()
{
	// 퍼시스턴트 레벨이 없는 경우 종료
	if (!World->GetPersistentLevel())
		return;

	// 목표 프레임 설정
	TimerSystem->SetTargetFPS(60.0f);

	// 게임 루프
	while (bRunning)
	{
		// 델타 타임 계산
		DeltaTime = TimerSystem->CalculateDeltaTime();
		
		// 입력 처리
		InputSystem->ProcessInput();

		// 업데이트
		World->Update(DeltaTime);

		// 렌더
		RenderSystem->Render();
	}
}

void CCore::Quit()
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
