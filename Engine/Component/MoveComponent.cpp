#include "Precompiled.h"
#include "MoveComponent.h"
#include "Actor/Actor.h"

CMoveComponent::CMoveComponent(CActor* InActor, const FString& InName)
	: Super(InActor, InName)
	, AngularSpeed(0.0f)
	, ForwardSpeed(0.0f)
	, RightSpeed(0.0f)
{
}

void CMoveComponent::Update(float DeltaTime)
{
	Super::Update(DeltaTime);

	// 예외 처리
	if (Owner->GetState() == CActor::EState::Paused)
		return;

	// 회전 처리
	if (!FMath::IsNearlyZero(AngularSpeed))
	{
		float Rotation = Owner->GetRotation();
		Rotation += AngularSpeed * DeltaTime;
		Owner->SetRotation(Rotation);
	}

	// 상하 이동 처리
	if (!FMath::IsNearlyZero(ForwardSpeed))
	{
		FVector2 Position = Owner->GetPosition();
		Position += Owner->GetForwardVector() * ForwardSpeed * DeltaTime;
		Owner->SetPosition(Position);
	}

	// 좌우 이동 처리
	if (!FMath::IsNearlyZero(RightSpeed))
	{
		FVector2 Position = Owner->GetPosition();
		Position += Owner->GetRightVector() * RightSpeed * DeltaTime;
		Owner->SetPosition(Position);
	}
}
