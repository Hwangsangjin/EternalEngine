#pragma once

#include "ActorComponent.h"

class ENGINE_API CTextComponent : public CActorComponent
{
	RTTI_DECL(CTextComponent, CActorComponent)

public:
	CTextComponent(CActor* InActor, const FString& InName);
	virtual ~CTextComponent() = default;

	virtual void Render() override;

	FORCEINLINE const FString& GetString() const { return String; }
	FORCEINLINE void SetString(const FString& InString) { String = InString; }

	FORCEINLINE const EColor& GetColor() const { return Color; }
	FORCEINLINE void SetColor(const EColor& InColor) { Color = InColor; }

private:
	// 문자열
	FString String;

	// 색상
	EColor Color;
};
