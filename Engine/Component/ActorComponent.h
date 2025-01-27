#pragma once

#include "Object/Object.h"

class CActor;

class ENGINE_API CActorComponent : public CObject
{
    RTTI_DECL(CActorComponent, CObject)

public:
    // 생성자에서 소유자 액터와 컴포넌트 이름 초기화
    CActorComponent(CActor* InActor, const FString& InName);
    virtual ~CActorComponent() = default;

    // 가상 함수로, 실제 동작은 컴포넌트 별로 구현
    virtual void Update(float DeltaTime) {}
    virtual void Render() {}

    // 소유자 액터 관련 함수
    FORCEINLINE CActor* GetOwner() const { return Owner; }
    FORCEINLINE void SetOwner(CActor* InActor) { Owner = InActor; }

    // 컴포넌트 이름 관련 함수
    FORCEINLINE const FString& GetName() const { return Name; }
    FORCEINLINE void SetName(const FString& InName) { Name = InName; }

protected:
    // 소유자 액터
    CActor* Owner;

    // 컴포넌트 이름
    FString Name;
};
