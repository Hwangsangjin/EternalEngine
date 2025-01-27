#include "Precompiled.h"
#include "Input.h"

CInput::CInput()
{
	KeyStates.fill(EKeyState::None);
}

void CInput::ProcessInput()
{
	for (SHORT i = 0; i < KeyStates.size(); ++i)
	{
		if (GetAsyncKeyState(i) & 0x8000)
		{
			if (KeyStates[i] == EKeyState::None || KeyStates[i] == EKeyState::Up)
				KeyStates[i] = EKeyState::Down;
			else
				KeyStates[i] = EKeyState::Hold;
		}
		else
		{
			if (KeyStates[i] == EKeyState::Down || KeyStates[i] == EKeyState::Hold)
				KeyStates[i] = EKeyState::Up;
			else
				KeyStates[i] = EKeyState::None;
		}
	}
}

bool CInput::GetKey(size_t InIndex) const
{
	return KeyStates[InIndex] == EKeyState::Down || KeyStates[InIndex] == EKeyState::Hold;
}

bool CInput::GetKeyDown(size_t InIndex) const
{
	return KeyStates[InIndex] == EKeyState::Down;
}

bool CInput::GetKeyUp(size_t InIndex) const
{
	return KeyStates[InIndex] == EKeyState::Up;
}
