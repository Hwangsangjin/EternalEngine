#pragma once

#include "Core.h"
#include "RTTI.h"

class ENGINE_API CObject : public RTTI
{
	RTTI_DECL(CObject, RTTI)

public:
	CObject();
	virtual ~CObject();
};
