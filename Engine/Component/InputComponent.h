#pragma once

#include "MoveComponent.h"

class ENGINE_API CInputComponent : public CMoveComponent
{
	RTTI_DECL(CInputComponent, CMoveComponent)

public:
	CInputComponent(CActor* InActor, const FString& InName);
	virtual ~CInputComponent() = default;

	virtual void Update(float DeltaTime) override;

	FORCEINLINE float GetAngularAcceleration() const { return AngularAcceleration; }
	FORCEINLINE void SetAngularAcceleration(float InAngularAcceleration) { AngularAcceleration = InAngularAcceleration; }

	FORCEINLINE int GetClockwiseKey() const { return ClockwiseKey; }
	FORCEINLINE void SetClockwiseKey(int InClockwiseKey) { ClockwiseKey = InClockwiseKey; }

	FORCEINLINE int GetCounterClockwiseKey() const { return CounterClockwiseKey; }
	FORCEINLINE void SetCounterClockwiseKey(int InCounterClockwiseKey) { CounterClockwiseKey = InCounterClockwiseKey; }

	FORCEINLINE float GetForwardAcceleration() const { return ForwardAcceleration; }
	FORCEINLINE void SetForwardAcceleration(float InForwardAcceleration) { ForwardAcceleration = InForwardAcceleration; }

	FORCEINLINE float GetRightAcceleration() const { return RightAcceleration; }
	FORCEINLINE void SetRightAcceleration(float InRightAcceleration) { RightAcceleration = InRightAcceleration; }

	FORCEINLINE int GetForwardKey() const { return ForwardKey; }
	FORCEINLINE void SetForwardKey(int InForwardKey) { ForwardKey = InForwardKey; }

	FORCEINLINE int GetBackwardKey() const { return BackwardKey; }
	FORCEINLINE void SetBackwardKey(int InBackwardKey) { BackwardKey = InBackwardKey; }

	FORCEINLINE int GetLeftKey() const { return LeftKey; }
	FORCEINLINE void SetLeftKey(int InLeftKey) { LeftKey = InLeftKey; }

	FORCEINLINE int GetRightKey() const { return RightKey; }
	FORCEINLINE void SetRightKey(int InRightKey) { RightKey = InRightKey; }

private:
	// 회전 가속도
	float AngularAcceleration;

	// 회전을 위한 키
	int ClockwiseKey;
	int CounterClockwiseKey;

	// 전방 가속도
	float ForwardAcceleration;

	// 우측 가속도
	float RightAcceleration;

	// 이동을 위한 키
	int ForwardKey;
	int BackwardKey;
	int LeftKey;
	int RightKey;
};
