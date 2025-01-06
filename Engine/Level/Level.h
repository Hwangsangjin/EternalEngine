#pragma once

class CActor;

// 레벨 클래스
class ENGINE_API CLevel
{
public:
	CLevel();
	virtual ~CLevel();

	// 액터 추가 함수
	void AddActor(CActor* NewActor);

	// 루프 처리 함수
	virtual void Update(float DeltaTime);
	virtual void Render();

protected:
	// 액터 배열의 크기 변경 함수
	void ResizeActorArray();

protected:
	// 게임 공간에 배치되는 액터의 배열
	CActor** ActorArray;

	// 액터를 저장할 수 있는 배열의 크기
	size_t Capacity;

	// 배열에 저장된 액터의 수
	size_t Count;
};
