#pragma once

#include "Object/Object.h"
#include "Math/Vector2.h"

// 액터 클래스
class ENGINE_API CActor : public CObject
{
	RTTI_DECL(CActor, CObject);

public:
	enum class EState
	{
		EActive,
		EPaused,
		Expired
	};

public:
	CActor(const FVector2& Position, const WORD& Color, const std::string& Text);
	virtual ~CActor();

	// 루프 처리 함수
	virtual void Update(float DeltaTime);
	virtual void Render();

	// 위치 관련 함수
	FORCEINLINE FVector2 GetPositon() const { return Position; }
	FORCEINLINE void SetPosition(const FVector2& NewPosition) { Position = NewPosition; }

	// 상태 관련 함수
	FORCEINLINE EState GetState() const { return State; }
	FORCEINLINE void SetState(EState NewState) { State = NewState; }

	// 텍스트 관련 함수
	FORCEINLINE std::string GetText() { return Text; }
	FORCEINLINE void SetText(const std::string& NewText) { Text = NewText; }

protected:
	// 액터의 상태
	EState State = EState::EActive;

	// 액터의 위치
	FVector2 Position;

	// 액터의 텍스트 색상
	WORD Color;

	// 액터의 텍스트 이미지
	std::string Text;
};
