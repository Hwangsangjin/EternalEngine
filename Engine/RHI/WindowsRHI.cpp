#include "Precompiled.h"
#include "WindowsRHI.h"
#include "Window/Window.h"

FWindowsRHI::FWindowsRHI()
	: Window(CWindow::Get())
	, WindowHandle(Window.GetWindowHandle())
	, ScreenSize(Window.GetScreenSize())
{
	// 윈도우의 클라이언트 영역 크기 얻기
	GetClientRect(WindowHandle, &Rect);

	ScreenDC = GetDC(WindowHandle);
	MemoryDC = CreateCompatibleDC(ScreenDC);

	// 색상 & 비트맵 설정
	BITMAPINFO BitmapInfo;
	memset(&BitmapInfo, 0, sizeof(BITMAPINFO));
	BitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	BitmapInfo.bmiHeader.biWidth = ScreenSize.X;
	BitmapInfo.bmiHeader.biHeight = -ScreenSize.Y;
	BitmapInfo.bmiHeader.biPlanes = 1;
	BitmapInfo.bmiHeader.biBitCount = 32;
	BitmapInfo.bmiHeader.biCompression = BI_RGB;

	DIBitmap = CreateDIBSection(MemoryDC, &BitmapInfo, DIB_RGB_COLORS, (void**)&ScreenBuffer, nullptr, 0);
	DefaultBitmap = reinterpret_cast<HBITMAP>(SelectObject(MemoryDC, DIBitmap));

	// 깊이 버퍼 생성
	CreateDepthBuffer();
}

FWindowsRHI::~FWindowsRHI()
{
	// 깊이 버퍼 해제
	if (DepthBuffer)
	{
		delete[] DepthBuffer;
		DepthBuffer = nullptr;
	}

	// 비트맵 해제
	SelectObject(MemoryDC, DIBitmap);
	DeleteObject(DefaultBitmap);

	// 디바이스 컨텍스트 해제
	DeleteDC(MemoryDC);
	ReleaseDC(WindowHandle, ScreenDC);
}

void FWindowsRHI::Clear()
{
	FillBuffer();
	HBRUSH BrushHandle = (HBRUSH)GetStockObject(WHITE_BRUSH);
	FillRect(MemoryDC, &Rect, BrushHandle);
	ClearDepthBuffer();
}

void FWindowsRHI::Present()
{
	BitBlt(ScreenDC, 0, 0, ScreenSize.X, ScreenSize.Y, MemoryDC, 0, 0, SRCCOPY);
}

void FWindowsRHI::FillBuffer()
{
	if (!ScreenBuffer)
		return;

	FColor32* Dest = ScreenBuffer;
	UINT TotalCount = ScreenSize.X * ScreenSize.Y;
	FColor32 Color = FLinearColor::White.ToColor32();
	CopyBuffer<FColor32>(ScreenBuffer, &Color, TotalCount);
}

void FWindowsRHI::CreateDepthBuffer()
{
	DepthBuffer = new float[ScreenSize.X * ScreenSize.Y];
}

void FWindowsRHI::ClearDepthBuffer()
{
	if (DepthBuffer)
	{
		float* Dest = DepthBuffer;
		static float DefValue = INFINITY;
		UINT TotalCount = ScreenSize.X * ScreenSize.Y;
		CopyBuffer<float>(DepthBuffer, &DefValue, TotalCount);
	}
}

void FWindowsRHI::DrawPoint(const FScreenPoint& InPoint, const FLinearColor& InColor)
{
	SetPixel(InPoint, InColor);
}

void FWindowsRHI::DrawPoint(const FVector2& InPosition, const FLinearColor& InColor)
{
	SetPixel(FScreenPoint::ToScreenCoordinate(ScreenSize, InPosition), InColor);
}
