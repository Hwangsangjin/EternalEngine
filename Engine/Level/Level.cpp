#include "PreCompiledHeader.h"
#include "Level.h"
#include "Object/Object.h"

CLevel::CLevel()
	: ObjectArray{nullptr}
	, Capacity{4}
	, Count{0}
{
	// 동적 배열 생성
	ObjectArray = new CObject*[Capacity];

	// 초기화
	memset(ObjectArray, 0, sizeof(CObject*) * Capacity);
}

CLevel::~CLevel()
{
	// 메모리 해제
	for (size_t i = 0; i < Count; ++i)
	{
		// 오브젝트 삭제
		delete ObjectArray[i];
		ObjectArray[i] = nullptr;
	}

	// 동적 배열 해제
	delete[] ObjectArray;
	ObjectArray = nullptr;
}

void CLevel::AddObject(CObject* NewObject)
{
	// 할당된 공간이 부족하면 크기 변경
	if (Count == Capacity)
		ResizeObjectArray();

	// 오브젝트 추가
	ObjectArray[Count++] = NewObject;
}

void CLevel::Update(float DeltaTime)
{
	// 오브젝트 업데이트
	for (size_t i = 0; i < Count; ++i)
		ObjectArray[i]->Update(DeltaTime);
}

void CLevel::Render()
{
	// 오브젝트 렌더
	for (size_t i = 0; i < Count; ++i)
		ObjectArray[i]->Render();
}

void CLevel::ResizeObjectArray()
{
	// 새로운 크기
	size_t NewCapacity = Capacity * 2;

	// 임시 공간
	CObject** TempArray = new CObject*[NewCapacity];

	// 기존 값 복사
	memcpy_s(TempArray, sizeof(CObject*) * NewCapacity, ObjectArray, sizeof(CObject*) * Capacity);

	// 기존 배열 삭제
	delete[] ObjectArray;

	// 배열 교체
	ObjectArray = TempArray;

	// 크기 변경
	Capacity = NewCapacity;
}
