#pragma once

#include "Object/Object.h"
#include "Math/Vector2.h"

// 액터 클래스
class ENGINE_API CActor : public CObject
{
	RTTI_DECL(CActor, CObject);

public:
	CActor();
	virtual ~CActor();

	// 루프 처리 함수
	virtual void Update(float DeltaTime);
	virtual void Render();

	// 위치 관련 함수
	FORCEINLINE virtual void SetPosition(const FVector2& NewPosition) { Position = NewPosition; }
	FORCEINLINE FVector2 GetPositon() const { return Position; }

	// 상태 관련 함수
	FORCEINLINE bool IsAcive() const { return bActive; }
	FORCEINLINE void SetActive(bool bIsActive) { bActive = bIsActive; }
	FORCEINLINE bool HasExpired() const { return bExpired; }
	FORCEINLINE void Destroy() { bExpired = true; }

protected:
	// 활성화 상태인지 나타내는 변수
	bool bActive;

	// 제거 요청이 됐는지 여부를 나타내는 변수
	bool bExpired;

	// 액터의 위치
	FVector2 Position;
};
