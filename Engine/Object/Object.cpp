#include "PreCompiledHeader.h"
#include "Object.h"

CObject::CObject()
	: bActive{true}
	, bExpired{false}
{
}

CObject::~CObject()
{
}

void CObject::Update(float DeltaTime)
{
}

void CObject::Render()
{
}
