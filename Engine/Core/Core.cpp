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

// 게임이 실행 중인지 체크
std::atomic<bool> CCore::bRunning(true);

CCore::CCore()
	: DeltaTime(0.0f)
	, bUpdateCompleted(false)
	, TimerSystem(new CTimerSystem)
	, InputSystem(new CInputSystem)
	, AudioSystem(new CAudioSystem)
	, RenderSystem(new CRenderSystem)
	, World(new CWorld)
{
	// 싱글톤 객체 설정
	Instance = this;

	// 랜덤 시드 설정
	srand((unsigned int)time(nullptr));

	// 콘솔 입력 모드 설정
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_PROCESSED_INPUT | ENABLE_EXTENDED_FLAGS);
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

	// 스레드 시작
	GameThreadHandle = std::thread(&CCore::GameThread, this);
	RenderThreadHandle = std::thread(&CCore::RenderThread, this);
	ConsoleInputThreadHandle = std::thread(&CCore::ConsoleInputThread, this);

	// 메시지 루프
	MSG Msg = {};
	while (bRunning)
	{
		// 메시지 큐에서 메시지를 가져와 처리
		if (PeekMessage(&Msg, nullptr, 0, 0, PM_REMOVE))
		{
			// 메시지 변역
			TranslateMessage(&Msg);

			// 메시지를 윈도우 프로시저로 전달
			DispatchMessage(&Msg);

			// 종료 요청 메시지인 경우
			if (Msg.message == WM_QUIT)
				Quit();
		}
	}

	// 스레드가 종료될 때까지 기다리기
	if (GameThreadHandle.joinable())
		GameThreadHandle.join();
	if (RenderThreadHandle.joinable())
		RenderThreadHandle.join();
	if (ConsoleInputThreadHandle.joinable())
		ConsoleInputThreadHandle.join();
}

void CCore::GameThread()
{
	while (bRunning.load(std::memory_order_acquire))
	{
		// 델타 타임 계산
		DeltaTime = TimerSystem->CalculateDeltaTime();

		// 입력 처리
		InputSystem->ProcessInput();

		// 월드 업데이트
		World->Update(DeltaTime);

		// 게임 스레드 완료 처리
		bUpdateCompleted.store(true, std::memory_order_release);

		// 렌더 스레드에 알림
		UpdateCondition.notify_one();

		// 렌더 스레드가 작업을 완료했는지 확인
		std::unique_lock<std::mutex> Lock(SyncMutex);
		UpdateCondition.wait(Lock, [this] { return !bUpdateCompleted.load() || !bRunning.load(); });
	}
}

void CCore::RenderThread()
{
	while (bRunning.load(std::memory_order_acquire))
	{
		// 게임 스레드가 업데이트 완료될 때까지 대기
		std::unique_lock<std::mutex> Lock(SyncMutex);
		UpdateCondition.wait(Lock, [this] { return bUpdateCompleted.load() || !bRunning.load(); });

		// 렌더링
		RenderSystem->Render();

		// 게임 스레드가 다음 업데이트를 할 수 있도록 상태 초기화
		bUpdateCompleted.store(false, std::memory_order_release);

		// 게임 스레드에 업데이트 완료 알림
		UpdateCondition.notify_one();
	}
}

void CCore::ConsoleInputThread()
{
	static HANDLE StdHandle = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD InputRecord;
	DWORD Event;

	while (bRunning.load(std::memory_order_acquire))
	{
		if (ReadConsoleInput(StdHandle, &InputRecord, 1, &Event))
		{
			if (!bRunning.load(std::memory_order_acquire))
				break;

			switch (InputRecord.EventType)
			{
			case MOUSE_EVENT:
				InputSystem->SetMousePosition(InputRecord.Event.MouseEvent.dwMousePosition);
				break;
			}
		}
	}
}

void CCore::Quit()
{
	// 플래그를 설정하고 대기 중인 스레드들 깨우기
	{
		std::lock_guard<std::mutex> Lock(SyncMutex);
		bRunning.store(false, std::memory_order_release);
		bUpdateCompleted.store(true, std::memory_order_release);
		UpdateCondition.notify_all();
	}

	// 콘솔 종료
	FreeConsole();

	// 현재 스레드의 ID 가져오기
	std::thread::id ThisThreadId = std::this_thread::get_id();

	// 게임 스레드가 실행 중이고, 현재 스레드가 게임 스레드가 아닌 경우
	if (GameThreadHandle.joinable() && GameThreadHandle.get_id() != ThisThreadId)
		GameThreadHandle.join();

	// 렌더 스레드가 실행 중이고, 현재 스레드가 렌더 스레드가 아닌 경우
	if (RenderThreadHandle.joinable() && RenderThreadHandle.get_id() != ThisThreadId)
		RenderThreadHandle.join();

	// 콘솔 입력 스레드가 실행 중이고, 현재 스레드가 콘솔 입력 스레드가 아닌 경우
	if (ConsoleInputThreadHandle.joinable() && ConsoleInputThreadHandle.get_id() != ThisThreadId)
		ConsoleInputThreadHandle.join();
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
