#include "Precompiled.h"
#include "Actor.h"
#include "Component/BoxComponent.h"
#include "Component/TextComponent.h"
#include "Component/MoveComponent.h"

CActor::CActor()
	: State(EState::Active)
	, Position(FVector2::Zero)
	, Scale(1.0f)
	, Rotation(0.0f)
{
	BoxComponent = AddComponent<CBoxComponent>(TEXT("BoxComponent"));
	TextComponent = AddComponent<CTextComponent>(TEXT("TextComponent"));
	MoveComponent = AddComponent<CMoveComponent>(TEXT("MoveComponent"));
}

CActor::~CActor()
{
	for (const auto& Component : Components)
		delete Component;
	
	Components.clear();
}

void CActor::Update(float DeltaTime)
{
    for (const auto& Component : Components)
        Component->Update(DeltaTime);
}

void CActor::Render()
{
    for (const auto& Component : Components)
        Component->Render();
}
