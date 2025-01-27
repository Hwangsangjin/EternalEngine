#include "Precompiled.h"
#include "World.h"
#include "Level/Level.h"

CWorld::CWorld()
	: PersistentLevel(nullptr)
{
}

CWorld::~CWorld()
{
	if (PersistentLevel)
		delete PersistentLevel;
}

void CWorld::Update(float DeltaTime)
{
	PersistentLevel->Update(DeltaTime);
}

void CWorld::Render()
{
	PersistentLevel->Render();
}

void CWorld::LoadLevel(CLevel* InLevel)
{
	// 로드한 레벨이 널인 경우 리턴
	if (!InLevel)
		return;

	// 퍼시스턴트 레벨과 로드한 레벨이 같은 경우 리턴
	if (PersistentLevel == InLevel)
		return;

	// 기존 레벨이 있다면 삭제
	if (PersistentLevel)
		delete PersistentLevel;

	// 로드한 레벨을 퍼시스턴트 레벨로 설정
	PersistentLevel = InLevel;
}
