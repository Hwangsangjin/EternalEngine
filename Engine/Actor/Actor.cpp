#include "PreCompiledHeader.h"
#include "Actor.h"

CActor::CActor()
	: bActive{true}
	, bExpired{false}
{
}

CActor::~CActor()
{
}

void CActor::Update(float DeltaTime)
{
}

void CActor::Render()
{
}
