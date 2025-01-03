#pragma once

// 디버깅 매크로
#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
// Replace _NORMAL_BLOCK with _CLIENT_BLOCK if you want the
// allocations to be of _CLIENT_BLOCK type
#else
#define DBG_NEW new
#endif

// 라이브러리 링크
#pragma comment(lib, "winmm.lib")

// 미리 컴파일된 헤더
#include <stdlib.h>
#include <crtdbg.h>
#include <Windows.h>
#include <iostream>

// 메모리 삭제 함수
template <typename T>
void SafeDelete(T* Pointer)
{
	if (Pointer)
	{
		delete Pointer;
		Pointer = nullptr;
	}
}


