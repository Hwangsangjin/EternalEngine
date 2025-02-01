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

protected:
	// 싱글톤 구현을 위한 정적 인스턴스
	static CCore* Instance;

	// 실행 플래그
	bool bRunning;

	// 델타 타임
	float DeltaTime;

	// 시스템
	CTimerSystem* TimerSystem;
	CInputSystem* InputSystem;
	CAudioSystem* AudioSystem;
	CRenderSystem* RenderSystem;

	// 월드
	CWorld* World;
};
