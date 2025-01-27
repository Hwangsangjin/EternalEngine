#pragma once

class ENGINE_API CInput
{
public:
	CInput();

	// 키 상태 갱신
	void ProcessInput();

	// 키가 눌린 상태인지 확인
	bool GetKey(size_t InIndex) const;

	// 키가 방금 눌린 상태인지 확인
	bool GetKeyDown(size_t InIndex) const;

	// 키가 방금 떼어진 상태인지 확인
	bool GetKeyUp(size_t InIndex) const;

private:
	// 키 상태 배열
	std::array<EKeyState, 256> KeyStates;
};
