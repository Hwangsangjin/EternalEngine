#include "Precompiled.h"
#include "Window.h"

CWindow* CWindow::Instance = nullptr;

CWindow::CWindow(FScreenPoint InScreenSize, const FString& InWindowName, HINSTANCE InInstanceHandle, ERHIType InRHIType)
    : ScreenSize(InScreenSize)
    , WindowName(InWindowName)
    , InstanceHandle(InInstanceHandle)
    , RHIType(InRHIType)
{
    // 싱글톤 객체 설정
    Instance = this;

    // 윈도우 클래스 등록
    WNDCLASS WindowClass = {};
    WindowClass.lpfnWndProc = WindowProc;
    WindowClass.hInstance = InstanceHandle;
    WindowClass.lpszClassName = WindowName.GetWideString().c_str();

    // 실패 시 오류 메시지 출력
    if (!RegisterClass(&WindowClass))
    {
        MessageBoxA(nullptr, "Failed to register a window", "Error", MB_OK);
        __debugbreak();
    }

    // 화면 가운데 위치 설정
    unsigned int PositionX = (GetSystemMetrics(SM_CXSCREEN) - ScreenSize.X) / 2;
    unsigned int PositionY = (GetSystemMetrics(SM_CYSCREEN) - ScreenSize.Y) / 2;

    // 창 크기 조정
    RECT Rect = { 0, 0, static_cast<long>(ScreenSize.X), static_cast<long>(ScreenSize.Y) };
    AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, FALSE);

    // 창 크기 재설정
    unsigned int WindowWidthAdjusted = Rect.right - Rect.left;
    unsigned int WindowHeightAdjusted = Rect.bottom - Rect.top;

    // 윈도우 생성
    WindowHandle = CreateWindow(
        WindowName.GetWideString().c_str(),
        WindowName.GetWideString().c_str(),
        WS_OVERLAPPEDWINDOW,
        PositionX,
        PositionY,
        WindowWidthAdjusted,
        WindowHeightAdjusted,
        nullptr,
        nullptr,
        InstanceHandle,
        nullptr
    );

    // 실패 시 오류 메시지 출력
    if (!WindowHandle)
    {
        MessageBoxA(nullptr, "Failed to create a window", "Error", MB_OK);
        __debugbreak();
    }

    // 윈도우 보이기
    ShowWindow(WindowHandle, SW_SHOW);

    // 윈도우 메시지 업데이트
    UpdateWindow(WindowHandle);
}

CWindow::~CWindow()
{
    // 클래스 등록 해제
    UnregisterClass(WindowName.GetWideString().c_str(), InstanceHandle);
}

// 창에 관련된 메시지를 처리하는 콜백 함수
LRESULT CALLBACK CWindow::WindowProc(
    HWND   WindowHandle,
    UINT   Message,
    WPARAM WParam,
    LPARAM LParam
)
{
    // 메시지 처리
    switch (Message)
    {
        // 창이 삭제되면 실행
    case WM_DESTROY:
        // 이때 프로그램 종료 메시지를 발행
        PostQuitMessage(Message);
        break;
    }

    // 기본 메시지 처리
    return DefWindowProc(WindowHandle, Message, WParam, LParam);
}
