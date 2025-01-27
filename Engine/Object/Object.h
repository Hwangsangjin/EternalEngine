#pragma once

#include "RTTI/RTTI.h"

class ENGINE_API CObject : public RTTI
{
	RTTI_DECL(CObject, RTTI)

public:
	CObject() = default;
	virtual ~CObject() = default;
};
