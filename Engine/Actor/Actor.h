#pragma once

#include "Object/Object.h"

class CActorComponent;
class CBoxComponent;
class CTextComponent;
class CMoveComponent;

class ENGINE_API CActor : public CObject
{
	RTTI_DECL(CActor, CObject)

public:
	enum class EState
	{
		Active,
		Paused,
		Expired
	};

public:
	CActor(const FVector2& InPosition, const FVector2& InSize, const FString& InText);
	virtual ~CActor();

	// 루프 처리 함수
	virtual void Update(float DeltaTime);
	virtual void Render();

	// 상태 관련 함수
	FORCEINLINE EState GetState() const { return State; }
	FORCEINLINE void SetState(EState InState) { State = InState; }

	// 변환 관련 함수
	FORCEINLINE FVector2 GetPosition() const { return Position; }
	FORCEINLINE void SetPosition(const FVector2& InPosition) { Position = InPosition; }
	FORCEINLINE float GetScale() const { return Scale; }
	FORCEINLINE void SetScale(float InScale) { Scale = InScale; }
	FORCEINLINE float GetRotation() const { return Rotation; }
	FORCEINLINE void SetRotation(float InRotation) { Rotation = InRotation; }

	// 전방 벡터 반환 함수
	FORCEINLINE FVector2 GetForwardVector() const
	{
		// 회전 각도를 라디안 단위로 변환
		const float Radian = FMath::ToRadian(Rotation);

		// 라디안 값을 이용한 전방 벡터 계산
		return FVector2(FMath::Cos(Radian), -FMath::Sin(Radian));
	}

	// 우측 벡터 반환 함수
	FORCEINLINE FVector2 GetRightVector() const
	{
		// 회전 각도를 라디안 단위로 변환
		const float Radians = FMath::ToRadian(Rotation);

		// 라디안 값을 이용한 우측 벡터 계산
		return FVector2(FMath::Sin(Radians), FMath::Cos(Radians));
	}

	// 컴포넌트 추가 함수
	template <typename T>
	T* AddComponent(const FString& InName);

	// 컴포넌트 삭제 함수
	template <typename T>
	void RemoveComponent();

	//  컴포넌트 검색 함수
	template <typename T>
	T* GetComponent() const;

	// 컴포넌트 배열 반환 함수
	template<typename T>
	FORCEINLINE void GetComponents(std::vector<T*>& OutComponents) const;

	// 컴포넌트 객체 반환 함수
	FORCEINLINE CBoxComponent* GetBoxComponent() const { return BoxComponent; }
	FORCEINLINE CTextComponent* GetTextComponent() const { return TextComponent; }
	FORCEINLINE CMoveComponent* GetMoveComponent() const { return MoveComponent; }

protected:
	// 액터의 상태
	EState State;

	// 변환
	FVector2 Position;
	float Scale;
	float Rotation;

	// 컴포넌트 배열
	std::vector<CActorComponent*> Components;

	// 박스 컴포넌트
	CBoxComponent* BoxComponent;

	// 텍스트 컴포넌트
	CTextComponent* TextComponent;

	// 이동 컴포넌트
	CMoveComponent* MoveComponent;
};

template<typename T>
FORCEINLINE T* CActor::AddComponent(const FString& InName)
{
	// 같은 타입의 컴포넌트가 이미 존재하는지 확인
	for (const auto& Component : Components)
	{
		if (auto TypedComponent = Component->As<T>())
		{
			if (TypedComponent->GetName() == InName)
				return nullptr;
		}
	}

	// 새로운 컴포넌트를 생성하고, 추가
	T* NewComponent = new T(this, InName);
	Components.emplace_back(NewComponent);
	return NewComponent;
}

template<typename T>
FORCEINLINE void CActor::RemoveComponent()
{
	// 지정된 타입의 컴포넌트를 찾고 메모리를 해제한 후, 삭제
	for (auto Iter = Components.begin(); Iter != Components.end();)
	{
		if (auto TypedComponent = Iter->As<T>())
		{
			delete TypedComponent;
			Iter = Components.erase(Iter);
			break;
		}
		else
		{
			++Iter;
		}
	}
}

template<typename T>
FORCEINLINE T* CActor::GetComponent() const
{
	// 첫 번째로 찾은 해당 타입의 컴포넌트 반환
	for (const auto& Component : Components)
	{
		if (auto TypedComponent = Component->As<T>())
			return TypedComponent;
	}

	// 컴포넌트를 찾지 못한 경우
	return nullptr;
}

template<typename T>
FORCEINLINE void CActor::GetComponents(std::vector<T*>& OutComponents) const
{
	// 해당 타입의 모든 컴포넌트를 전달된 배열에 추가
	for (const auto& Component : Components)
	{
		if (auto TypedComponent = Component->As<T>())
			OutComponents.emplace_back(TypedComponent);
	}
}
