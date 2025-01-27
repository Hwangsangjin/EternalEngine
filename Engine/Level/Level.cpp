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

	for (auto const& PendingActor : PendingActors)
		delete PendingActor;

	Actors.clear();
	PendingActors.clear();
}

void CLevel::AddActor(CActor* InActor)
{
	// 추가할 액터가 널인 경우 리턴
	if (!InActor)
		return;

	// 액터를 업데이트 중인 경우 대기 배열에 추가
	if (bUpdatingActors)
		PendingActors.emplace_back(InActor);
	else
		Actors.emplace_back(InActor);
}

void CLevel::RemoveActor(CActor* InActor)
{
	// 삭제할 액터가 널인 경우 리턴
	if (!InActor)
		return;

	// 액터 배열과 대기 배열을 탐색한 후 존재하면 삭제
	RemoveActorFromArray(Actors, InActor);
	RemoveActorFromArray(PendingActors, InActor);
}

void CLevel::RemoveActorFromArray(std::vector<CActor*>& OutActors, CActor* InActor)
{
	// 액터를 찾아서 마지막 요소와 교환한 후 제거
	auto Iter = std::find(OutActors.begin(), OutActors.end(), InActor);
	if (Iter != OutActors.end())
	{
		std::iter_swap(Iter, OutActors.end() - 1);
		OutActors.pop_back();
	}
}

void CLevel::Update(float DeltaTime)
{
	bUpdatingActors = true;

	// 모든 액터 업데이트
	for (auto const& Actor : Actors)
		Actor->Update(DeltaTime);

	bUpdatingActors = false;

	// 대기 중인 액터 이동
	for (auto const& PendingActor : PendingActors)
		Actors.emplace_back(PendingActor);

	PendingActors.clear();

	// 만료된 액터 처리
	for (auto Iter = Actors.begin(); Iter != Actors.end();)
	{
		if ((*Iter)->GetState() == CActor::EState::Expired)
		{
			delete* Iter; // 현재 위치의 액터 객체 삭제
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
