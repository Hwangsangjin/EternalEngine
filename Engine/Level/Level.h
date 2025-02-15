#pragma once

#include "RTTI/RTTI.h"

class CActor;

class ENGINE_API CLevel : public RTTI
{
	RTTI_DECL(CLevel, RTTI)

public:
	CLevel();
	virtual ~CLevel();

	// 루프 처리 함수
	virtual void Update(float DeltaTime);
	virtual void Render();

	// 액터 추가, 삭제 함수
	void AddActor(CActor* InActor);
	void RemoveActor(CActor* InActor);
	void RemoveActorFromArray(std::vector<CActor*>& OutActors, CActor* InActor);

	// 액터 반환 함수
	const std::vector<CActor*>& GetActors() const { return Actors; }

protected:
	// 활성화된 액터의 동적 배열
	std::vector<CActor*> Actors;

	// 대기 중인 액터의 동적 배열
	std::vector<CActor*> PendingActors;

private:
	bool bUpdatingActors;
};
