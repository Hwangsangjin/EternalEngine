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

	// 액터 추가 함수
	void AddActor(CActor* NewActor);

	// 삭제 요청이 된 액터를 정리하는 함수
	void DestroyActor();

	// 루프 처리 함수
	virtual void Update(float DeltaTime);
	virtual void Render();

protected:
	// 게임 내 배치된 액터의 동적 배열
	std::vector<CActor*> Actors;
};
