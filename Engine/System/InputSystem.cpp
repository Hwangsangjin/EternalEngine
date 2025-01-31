#include "Precompiled.h"
#include "InputSystem.h"

CInputSystem::CInputSystem()
{
	KeyStates.fill(EKeyState::None);
}

void CInputSystem::ProcessInput()
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

bool CInputSystem::GetKey(size_t InIndex) const
{
	return KeyStates[InIndex] == EKeyState::Down || KeyStates[InIndex] == EKeyState::Hold;
}

bool CInputSystem::GetKeyDown(size_t InIndex) const
{
	return KeyStates[InIndex] == EKeyState::Down;
}

bool CInputSystem::GetKeyUp(size_t InIndex) const
{
	return KeyStates[InIndex] == EKeyState::Up;
}
