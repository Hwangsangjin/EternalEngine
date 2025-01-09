#include "Precompiled.h"
#include "Actor.h"

CActor::CActor()
	: bActive(true)
	, bExpired(false)
	, Position(FVector2(0.0f, 0.0f))
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

void CActor::SetPosition(const FVector2& NewPosition)
{
	Position = NewPosition;
}
