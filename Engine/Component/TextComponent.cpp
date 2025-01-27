#include "Precompiled.h"
#include "TextComponent.h"
#include "Actor/Actor.h"
#include "Core/Core.h"
#include "Renderer/Renderer.h"

CTextComponent::CTextComponent(CActor* InActor, const FString& InName)
	: Super(InActor, InName)
	, String(TEXT(""))
	, Color(EColor::White)
{
}

void CTextComponent::Render()
{
	Super::Render();

	CCore::Get().GetRenderer()->PrintText(Owner->GetPosition(), String, Color);
}
