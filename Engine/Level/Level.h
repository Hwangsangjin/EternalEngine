#pragma once

#include "Core.h"
#include "RTTI.h"
#include "Container/Array.h"

class CActor;

class ENGINE_API CLevel : public RTTI
{
	RTTI_DECL(CLevel, RTTI)

public:
	CLevel();
	virtual ~CLevel();

	// 액터 추가 함수
	void AddActor(CActor* NewActor);

	// 루프 처리 함수
	virtual void Update(float DeltaTime);
	virtual void Render();

protected:
	// 게임 공간에 배치되는 액터의 배열
	TArray<CActor*> ActorArray;
};
