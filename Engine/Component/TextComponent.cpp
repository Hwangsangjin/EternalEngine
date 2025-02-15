#include "Precompiled.h"
#include "TextComponent.h"
#include "Actor/Actor.h"
#include "Command/DrawTextCommand.h"
#include "Core/Core.h"
#include "System/RenderSystem.h"

CTextComponent::CTextComponent(CActor* InActor, const FString& InName)
	: Super(InActor, InName)
	, String(TEXT(""))
	, Color(FLinearColor::White)
{
}

void CTextComponent::Render()
{
	Super::Render();

	FDrawTextCommand* DrawTextCommand = new FDrawTextCommand(Owner->GetPosition(), String, Color);
	CCore::Get().GetRenderSystem()->EnqueueCommand(DrawTextCommand);
}
