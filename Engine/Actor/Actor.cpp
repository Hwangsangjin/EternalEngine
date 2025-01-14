#include "Precompiled.h"
#include "Actor.h"
#include "Engine/Engine.h"

CActor::CActor(const FVector2& Position, const WORD& Color, const std::string& Text)
	: Position(Position)
	, Color(Color)
	, Text(Text)
{
}

CActor::~CActor()
{
}

void CActor::Update(float DeltaTime)
{
	SetPosition(Position);
}

void CActor::Render()
{
	CEngine::Get().PrintText(Position, Color, Text);
}
