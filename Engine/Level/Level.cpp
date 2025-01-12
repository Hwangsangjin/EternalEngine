#include "Precompiled.h"
#include "Level.h"
#include "Actor/Actor.h"

CLevel::CLevel()
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
	// 액터 추가
	Actors.push_back(NewActor);
}

void CLevel::DestroyActor()
{
	// 액터 삭제
	for (size_t i = 0; i < Actors.size();)
	{
		if (Actors[i]->HasExpired())
		{
			delete Actors[i];
			Actors.erase(Actors.begin() + i);
		}
		else
		{
			++i;
		}
	}
}

void CLevel::Update(float DeltaTime)
{
	// 액터 업데이트
	for (auto const& Actor : Actors)
	{
		// 액터가 비활성화 상태이거나, 삭제 요청된 경우 제외
		if (!Actor->IsAcive() || Actor->HasExpired())
			continue;

		Actor->Update(DeltaTime);
	}
}

void CLevel::Render()
{
	// 액터 렌더
	for (auto const& Actor : Actors)
	{
		// 액터가 비활성화 상태이거나, 삭제 요청된 경우 제외
		if (!Actor->IsAcive() || Actor->HasExpired())
			continue;

		Actor->Render();
	}
}
