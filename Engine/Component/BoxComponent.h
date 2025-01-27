#pragma once

#include "ActorComponent.h"

class ENGINE_API CBoxComponent : public CActorComponent
{
	RTTI_DECL(CBoxComponent, CActorComponent)

public:
	CBoxComponent(CActor* InActor, const FString& InName);
	virtual ~CBoxComponent() = default;

	virtual void Update(float DeltaTime) override;

	// 충돌 검사 함수
    bool IsOverlappingComponent(const CBoxComponent* InBoxComponent) const;
	bool IsOverlappingForward(const CBoxComponent* InBoxComponent) const;
    bool IsOverlappingActor(const CActor* InActor) const;

	// 박스의 크기 관련 함수
	FORCEINLINE FVector2 GetSize() const { return Size; }
	FORCEINLINE void SetSize(const FVector2& InSize) { Size = InSize; }

	// 박스의 위치 관련 함수
	FORCEINLINE FVector2 GetPosition() const { return Position; }
	FORCEINLINE void SetPosition(const FVector2& InPosition) { Position = InPosition; }

private:
	// 박스의 위치
	FVector2 Position;

	// 박스의 크기 (폭과 높이)
	FVector2 Size;
};
