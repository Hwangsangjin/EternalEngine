#include "Precompiled.h"
#include "Actor.h"
#include "Component/BoxComponent.h"
#include "Component/TextComponent.h"
#include "Component/MoveComponent.h"

CActor::CActor(const FVector2& InPosition, const FVector2& InSize, const FString& InText)
	: State(EState::Active)
	, Position(InPosition)
	, Scale(0.0f)
	, Rotation(0.0f)
{
	BoxComponent = AddComponent<CBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetPosition(InPosition);
	BoxComponent->SetSize(InSize);

	TextComponent = AddComponent<CTextComponent>(TEXT("TextComponent"));
	TextComponent->SetString(InText);

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
