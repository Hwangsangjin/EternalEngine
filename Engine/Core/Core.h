#pragma once

class CLevel;
class CActor;
class CTimer;
class CInput;
class CWorld;
class CRenderer;

class ENGINE_API CCore
{
public:
	CCore();
	virtual ~CCore();

	// 싱글톤 객체 접근 함수
	static CCore& Get();

	// 게임 실행 함수
	void Run();

	// 게임 종료 함수
	void QuitGame();

	// 레벨 추가 함수
	void LoadLevel(CLevel* InLevel);

	// 액터 추가, 삭제 함수
	void AddActor(CActor* InActor);
	void RemoveActor(CActor* InActor);

	FORCEINLINE CTimer* GetTimer() const { return Timer; }
	FORCEINLINE CInput* GetInput() const { return Input; }
	FORCEINLINE CWorld* GetWorld() const { return World; }
	FORCEINLINE CRenderer* GetRenderer() const { return Renderer; }

protected:
	// 싱글톤 구현을 위한 정적 인스턴스
	static CCore* Instance;

	// 게임 실행 플래그
	bool bRunning;

	// 타이머
	CTimer* Timer;

	// 입력
	CInput* Input;

	// 월드
	CWorld* World;

	// 렌더러
	CRenderer* Renderer;
};
