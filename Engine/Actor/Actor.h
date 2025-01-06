﻿#pragma once

#include "Object/Object.h"

// 액터 클래스
class ENGINE_API CActor : public CObject
{
	RTTI_DECL(CActor, RTTI);

public:
	CActor();
	virtual ~CActor();

	// 루프 처리 함수
	virtual void Update(float DeltaTime);
	virtual void Render();

protected:
	// 활성화 상태인지 나타내는 변수
	bool bActive;

	// 제거 요청이 됐는지 여부를 나타내는 변수
	bool bExpired;
};
