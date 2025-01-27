#pragma once

#pragma warning (disable : 4172)

#include <stdlib.h>
#include <crtdbg.h>
#include <Windows.h>
#include <intrin.h>
#include <cassert>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <deque>

#include "Math/Math.h"
#include "Math/Vector2.h"
#include "String/String.h"

// 인라인 매크로
#define FORCEINLINE __forceinline

// 디버깅 매크로
#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define new new
#endif

// 엔진 빌드 매크로
#if _ENGINE_BUILD
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

// 유니코드 빌드 여부를 확인하는 매크로
#ifdef TEXT
	#undef TEXT
#endif
#if defined(UNICODE) || defined(_UNICODE)
	// 유니코드 빌드: wchar_t 사용
#define TEXT(str) L##str
#else
	// ANSI 빌드: char 사용
#define TEXT(str) str
#endif

// 메모리 누수 확인 함수
FORCEINLINE void CheckMemoryLeak()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

enum class EKeyState
{
	None,
	Down,
	Hold,
	Up
};

enum class ECursorType
{
	Hidden,
	Solid,
	Normal
};

enum class EColor
{
	Black = NULL,
	Red = FOREGROUND_RED,
	Green = FOREGROUND_GREEN,
	Blue = FOREGROUND_BLUE,
	Yellow = FOREGROUND_RED | FOREGROUND_GREEN,
	Magenta = FOREGROUND_RED | FOREGROUND_BLUE,
	Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
	White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,

	Gray = FOREGROUND_INTENSITY,
	BrightRed = FOREGROUND_RED | FOREGROUND_INTENSITY,
	BrightGreen = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	BrightBlue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	BrightYellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	BrightMagenta = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	BrightCyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	BrightWhite = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY
};
