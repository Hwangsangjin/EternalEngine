#pragma once

#pragma warning (disable : 4172)

#define FORCEINLINE __forceinline

#if _ENGINE_BUILD
#define ENGINE_API __declspec(dllexport)
#else
#define ENGINE_API __declspec(dllimport)
#endif

#define _CRTDBG_MAP_ALLOC
#ifdef _DEBUG
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define new new
#endif

#include <stdlib.h>
#include <crtdbg.h>
#include <Windows.h>
#include <intrin.h>
#include <cassert>
#include <sstream>
#include <iostream>
#include <filesystem>
#include <functional>
#include <mutex>
#include <atomic>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>

#include "Math/Math.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Color32.h"
#include "Math/HSVColor.h"
#include "Math/LinearColor.h"
#include "Math/ScreenPoint.h"

#include "String/String.h"

FORCEINLINE void CheckMemoryLeak()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

enum class ERHIType
{
	GDI,
	DX11
};

enum class EBindType
{
	VS,
	PS
};

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
