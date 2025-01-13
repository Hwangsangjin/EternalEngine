#include "Precompiled.h"
#include "Level.h"
#include "Actor/Actor.h"

CLevel::CLevel()
	: bUpdatingActors(false)
{
}

CLevel::~CLevel()
{
	// 메모리 해제
	for (auto const& Actor : Actors)
		delete Actor;
}

void CLevel::AddActor(CActor* NewActor)
{
	// 액터를 업데이트 중인 경우 대기 배열에 추가
	if (bUpdatingActors)
		PendingActors.emplace_back(NewActor);
	else
		Actors.emplace_back(NewActor);
}

void CLevel::RemoveActor(CActor* TargetActor)
{
	// 액터 배열과 대기 배열을 탐색한 후 존재하면 삭제
	RemoveActorFromArray(Actors, TargetActor);
	RemoveActorFromArray(PendingActors, TargetActor);
}

void CLevel::RemoveActorFromArray(std::vector<CActor*>& ActorArray, CActor* TargetActor)
{
	// 타겟 액터를 찾아서 마지막 요소와 교환한 후 제거
	auto Iter = std::find(ActorArray.begin(), ActorArray.end(), TargetActor);
	if (Iter != ActorArray.end())
	{
		std::iter_swap(Iter, ActorArray.end() - 1);
		ActorArray.pop_back();
	}
}

void CLevel::Update(float DeltaTime)
{
	// 모든 액터 업데이트
	bUpdatingActors = true;

	for (auto const& Actor : Actors)
		Actor->Update(DeltaTime);

	bUpdatingActors = false;

	// 대기 중인 액터 이동
	for (auto const& PendingActor : PendingActors)
		Actors.emplace_back(PendingActor);

	PendingActors.clear();

	// 만료된 액터 처리
	for (auto Iter = Actors.begin(); Iter != Actors.end(); )
	{
		if ((*Iter)->GetState() == CActor::EState::Expired)
		{
			delete* Iter;
			Iter = Actors.erase(Iter); // 삭제 후 자동으로 다음 요소로 이동
		}
		else
		{
			++Iter;
		}
	}
}

void CLevel::Render()
{
	// 액터 렌더
	for (auto const& Actor : Actors)
		Actor->Render();
}
