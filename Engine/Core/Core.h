#pragma once

class CWorld;
class CLevel;
class CActor;
class CTimerSystem;
class CInputSystem;
class CAudioSystem;
class CRenderSystem;

class ENGINE_API CCore
{
public:
	CCore();
	virtual ~CCore();

	// 실행, 종료 함수
	void Run();
	void Quit();

	// 레벨 추가 함수
	void LoadLevel(CLevel* InLevel);

	// 액터 추가, 삭제 함수
	void AddActor(CActor* InActor);
	void RemoveActor(CActor* InActor);

	// 싱글톤 객체 접근 함수
	FORCEINLINE static CCore& Get() { return *Instance; }

	// 월드 반환 함수
	FORCEINLINE CWorld* GetWorld() const { return World; }

	// 시스템 반환 함수
	FORCEINLINE CTimerSystem* GetTimerSystem() const { return TimerSystem; }
	FORCEINLINE CInputSystem* GetInputSystem() const { return InputSystem; }
	FORCEINLINE CAudioSystem* GetAudioSystem() const { return AudioSystem; }
	FORCEINLINE CRenderSystem* GetRenderSystem() const { return RenderSystem; }

private:
	// 게임 로직을 처리하는 함수
	void GameThread();

	// 렌더링을 처리하는 함수
	void RenderThread();

	// 콘솔 입력을 처리하는 함수
	void ConsoleInputThread();

private:
	// 싱글톤 구현을 위한 정적 인스턴스
	static CCore* Instance;

	// 델타 타임
	float DeltaTime;

	// 실행 플래그
	static std::atomic<bool> bRunning;

	// 업데이트 완료 플래그
	std::atomic<bool> bUpdateCompleted;

	// 스레드 동기화를 위한 조건 변수
	std::condition_variable UpdateCondition;

	// 스레드 동기화를 위한 뮤텍스
	std::mutex SyncMutex;

	// 게임 스레드 핸들
	std::thread GameThreadHandle;

	// 렌더 스레드 핸들
	std::thread RenderThreadHandle;

	// 콘솔 입력 스레드 핸들
	std::thread ConsoleInputThreadHandle;

	// 시스템
	CTimerSystem* TimerSystem;
	CInputSystem* InputSystem;
	CAudioSystem* AudioSystem;
	CRenderSystem* RenderSystem;

	// 월드
	CWorld* World;
};
