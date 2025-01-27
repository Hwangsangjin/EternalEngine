#pragma once

#include "ActorComponent.h"

class ENGINE_API CMoveComponent : public CActorComponent
{
	RTTI_DECL(CMoveComponent, CActorComponent)

public:
	CMoveComponent(CActor* InActor, const FString& InName);
	virtual ~CMoveComponent() = default;

	virtual void Update(float DeltaTime) override;

	FORCEINLINE float GetAngularSpeed() const { return AngularSpeed; }
	FORCEINLINE void SetAngularSpeed(float InAngularSpeed) { AngularSpeed = InAngularSpeed; }

	FORCEINLINE float GetForwardSpeed() const { return ForwardSpeed; }
	FORCEINLINE void SetForwardSpeed(float InForwardSpeed) { ForwardSpeed = InForwardSpeed; }

	FORCEINLINE float GetRightSpeed() const { return RightSpeed; }
	FORCEINLINE void SetRightSpeed(float InRightSpeed) { RightSpeed = InRightSpeed; }

private:
	// 회전 속도
	float AngularSpeed;

	// 전방 속도
	float ForwardSpeed;

	// 우측 속도
	float RightSpeed;
};
