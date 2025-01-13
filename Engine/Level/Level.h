#pragma once

#include "Core.h"
#include "RTTI.h"

class CActor;

class ENGINE_API CLevel : public RTTI
{
	RTTI_DECL(CLevel, RTTI)

public:
	CLevel();
	virtual ~CLevel();

	// 액터 추가, 삭제 함수
	void AddActor(CActor* NewActor);
	void RemoveActor(CActor* NewActor);
	void RemoveActorFromArray(std::vector<CActor*>& ActorArray, CActor* TargetActor);

	// 루프 처리 함수
	virtual void Update(float DeltaTime);
	virtual void Render();

protected:
	// 활성화된 액터의 동적 배열
	std::vector<CActor*> Actors;

	// 대기 중인 액터의 동적 배열
	std::vector<CActor*> PendingActors;

private:
	bool bUpdatingActors;
};
