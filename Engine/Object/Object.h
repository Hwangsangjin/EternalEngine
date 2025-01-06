#pragma once

#include "Core.h"
#include "RTTI.h"

// 오브젝트 클래스
class ENGINE_API CObject : public RTTI
{
	RTTI_DECL(CObject, RTTI);

public:
	CObject();
	virtual ~CObject();
};
