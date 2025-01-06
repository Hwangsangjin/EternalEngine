#include "PreCompiledHeader.h"
#include "Level.h"
#include "Actor/Actor.h"

CLevel::CLevel()
	: ActorArray{nullptr}
	, Capacity{4}
	, Count{0}
{
	// 동적 배열 생성
	ActorArray = new CActor*[Capacity];

	// 초기화
	memset(ActorArray, 0, sizeof(CActor*) * Capacity);
}

CLevel::~CLevel()
{
	// 메모리 해제
	for (size_t i = 0; i < Count; ++i)
	{
		// 액터 삭제
		delete ActorArray[i];
		ActorArray[i] = nullptr;
	}

	// 동적 배열 해제
	delete[] ActorArray;
	ActorArray = nullptr;
}

void CLevel::AddActor(CActor* NewActor)
{
	// 할당된 공간이 부족하면 크기 변경
	if (Count == Capacity)
		ResizeActorArray();

	// 액터 추가
	ActorArray[Count++] = NewActor;
}

void CLevel::Update(float DeltaTime)
{
	// 액터 업데이트
	for (size_t i = 0; i < Count; ++i)
		ActorArray[i]->Update(DeltaTime);
}

void CLevel::Render()
{
	// 액터 렌더
	for (size_t i = 0; i < Count; ++i)
		ActorArray[i]->Render();
}

void CLevel::ResizeActorArray()
{
	// 새로운 크기
	size_t NewCapacity = Capacity * 2;

	// 새로운 공간 할당
	CActor** NewArray = new CActor*[NewCapacity];

	// 기존 값 복사
	memcpy_s(NewArray, sizeof(CActor*) * NewCapacity, ActorArray, sizeof(CActor*) * Capacity);

	// 기존 배열 삭제
	delete[] ActorArray;

	// 배열 교체
	ActorArray = NewArray;

	// 크기 변경
	Capacity = NewCapacity;
}
