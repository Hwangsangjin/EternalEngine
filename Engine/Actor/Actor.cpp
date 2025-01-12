#include "Precompiled.h"
#include "Actor.h"

CActor::CActor()
	: bActive(true)
	, bExpired(false)
	, Position(FVector2())
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
