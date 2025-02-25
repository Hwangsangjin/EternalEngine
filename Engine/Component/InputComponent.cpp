﻿#include "Precompiled.h"
#include "InputComponent.h"
#include "Core/Core.h"
#include "System/InputSystem.h"

CInputComponent::CInputComponent(CActor* InActor, const FString& InName)
	: Super(InActor, InName)
	, ForwardAcceleration(0.0f)
	, RightAcceleration(0.0f)
	, AngularAcceleration(0.0f)
	, ForwardKey(0)
	, BackwardKey(0)
	, LeftKey(0)
	, RightKey(0)
	, ClockwiseKey(0)
	, CounterClockwiseKey(0)
{
}

void CInputComponent::Update(float DeltaTime)
{
    Super::Update(DeltaTime);

	// 각 속도 계산
	float AngularSpeed = 0.0f;

	if (CCore::Get().GetInputSystem()->GetKey(ClockwiseKey))
		AngularSpeed += AngularAcceleration * DeltaTime;

	if (CCore::Get().GetInputSystem()->GetKey(CounterClockwiseKey))
		AngularSpeed -= AngularAcceleration * DeltaTime;

	SetAngularSpeed(AngularSpeed);

	// 전방 속도 계산
	float ForwardSpeed = 0.0f;

	if (CCore::Get().GetInputSystem()->GetKey(ForwardKey))
		ForwardSpeed += ForwardAcceleration * DeltaTime;

	if (CCore::Get().GetInputSystem()->GetKey(BackwardKey))
		ForwardSpeed -= ForwardAcceleration * DeltaTime;

	SetForwardSpeed(ForwardSpeed);

	// 우측 속도 계산
	float RightSpeed = 0.0f;

	if (CCore::Get().GetInputSystem()->GetKey(LeftKey))
		RightSpeed -= RightAcceleration * DeltaTime;

	if (CCore::Get().GetInputSystem()->GetKey(RightKey))
		RightSpeed += RightAcceleration * DeltaTime;

	SetRightSpeed(RightSpeed);
}
