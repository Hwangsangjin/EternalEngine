#include "Precompiled.h"
#include "Level.h"
#include "Actor/Actor.h"

CLevel::CLevel()
{
}

CLevel::~CLevel()
{
	// 메모리 해제
	for (auto const& Actor : ActorArray)
		delete Actor;
}

void CLevel::AddActor(CActor* NewActor)
{
	// 액터 추가
	ActorArray.Add(NewActor);
}

void CLevel::Update(float DeltaTime)
{
	// 액터 업데이트
	for (auto const& Actor : ActorArray)
		Actor->Update(DeltaTime);
}

void CLevel::Render()
{
	// 액터 렌더
	for (auto const& Actor : ActorArray)
		Actor->Render();
}
