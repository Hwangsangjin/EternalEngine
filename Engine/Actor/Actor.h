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
	CActor();
	CActor(const std::string& Text);
	virtual ~CActor();

	// 루프 처리 함수
	virtual void Update(float DeltaTime);
	virtual void Render();

	// 위치 관련 함수
	FORCEINLINE virtual void SetPosition(const FVector2& NewPosition) { Position = NewPosition; }
	FORCEINLINE FVector2 GetPositon() const { return Position; }

	// 상태 관련 함수
	FORCEINLINE EState GetState() const { return State; }

protected:
	// 액터의 상태
	EState State;

	// 액터의 위치
	FVector2 Position;

	// 액터의 텍스트 이미지
	std::string Text;
};
