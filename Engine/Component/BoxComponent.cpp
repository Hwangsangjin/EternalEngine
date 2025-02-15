#include "Precompiled.h"
#include "BoxComponent.h"
#include "Actor/Actor.h"

CBoxComponent::CBoxComponent(CActor* InActor, const FString& InName)
    : Super(InActor, InName)
    , Position(FVector2::Zero)
    , Size(FVector2::One)
{
}

void CBoxComponent::Update(float DeltaTime)
{
    Super::Update(DeltaTime);

    SetPosition(Owner->GetPosition());
}

bool CBoxComponent::IsOverlappingComponent(const CBoxComponent* InBoxComponent) const
{
    // 현재 컴포넌트의 좌측 상단과 우측 하단 좌표
    const FVector2 TopLeft = Position;
    const FVector2 BottomRight = Position + Size;

    // 다른 컴포넌트의 좌측 상단과 우측 하단 좌표
    const FVector2 OtherTopLeft = InBoxComponent->Position;
    const FVector2 OtherBottomRight = InBoxComponent->Position + InBoxComponent->Size;

    // X축, Y축에서 겹치는 범위가 없으면 충돌 없음
    const bool bNoOverlapX = (BottomRight.X <= OtherTopLeft.X) || (TopLeft.X >= OtherBottomRight.X);
    const bool bNoOverlapY = (BottomRight.Y <= OtherTopLeft.Y) || (TopLeft.Y >= OtherBottomRight.Y);

    // 겹치는 경우 충돌 발생
    return !(bNoOverlapX || bNoOverlapY);
}

bool CBoxComponent::IsOverlappingForward(const CBoxComponent* InBoxComponent) const
{
    // 방향 벡터 계산
    const FVector2 Center = Position + Size * 0.5f;
    const FVector2 OtherCenter = InBoxComponent->Position + InBoxComponent->Size * 0.5f;
    FVector2 ToOther = OtherCenter - Center;

    // 방향 벡터 정규화 (크기를 1로 설정)
    ToOther.Normalize();

    // 전방 벡터와의 내적
    const float DotProduct = Owner->GetForwardVector().DotProduct(ToOther);

    // 내적 값이 음수일 경우 전방으로 겹치지 않음
    if (DotProduct < 0.0f)
        return false;

    // 내적 값이 0에 매우 가까운 경우(수직인 경우) 또는 내적 값이 양수일 경우
    return IsOverlappingComponent(InBoxComponent); // AABB 충돌 판정
}

bool CBoxComponent::IsOverlappingActor(const CActor* InActor) const
{
    // 액터가 널인 경우, 충돌 없음
    if (!InActor)
        return false;

    // 액터의 기본 박스 컴포넌트와 충돌 검사
    if (CBoxComponent* BoxComponent = InActor->GetBoxComponent())
    {
        if (IsOverlappingForward(BoxComponent))
            return true;
    }

    // 기본 박스 컴포넌트가 없을 경우, 다른 박스 컴포넌트 찾기
    std::vector<CBoxComponent*> BoxComponents;
    InActor->GetComponents(BoxComponents);

    // 모든 박스 컴포넌트에 대해 순차적으로 충돌 검사
    for (CBoxComponent* BoxComponent : BoxComponents)
    {
        if (IsOverlappingForward(BoxComponent))
            return true;
    }

    // 모든 박스 컴포넌트와 충돌 없음
    return false;
}
