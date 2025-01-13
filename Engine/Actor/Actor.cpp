#include "Precompiled.h"
#include "Actor.h"
#include "Engine/Engine.h"

CActor::CActor()
	: State(EState::EActive)
	, Position(FVector2::Zero)
	, Text("")
{
}

CActor::CActor(const std::string& Text)
	: State(EState::EActive)
	, Position(FVector2::Zero)
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
	CEngine::Get().PrintText(Position, CEngine::EColorType::White, Text);
}
