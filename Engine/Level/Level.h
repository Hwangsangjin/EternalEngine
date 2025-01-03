#pragma once

class CObject;

// 레벨 클래스
class ENGINE_API CLevel
{
public:
	CLevel();
	virtual ~CLevel();

	// 오브젝트 추가 함수
	void AddObject(CObject* NewObeject);

	// 루프 처리 함수
	virtual void Update(float DeltaTime);
	virtual void Render();

protected:
	// 오브젝트 배열 크기 변경 함수
	void ResizeObjectArray();

protected:
	// 게임 공간에 배치되는 오브젝트 배열
	CObject** ObjectArray;

	// 저장할 수 있는 공간의 크기
	size_t Capacity;

	// 오브젝트의 수
	size_t Count;
};

