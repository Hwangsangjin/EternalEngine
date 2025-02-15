#pragma once

class ENGINE_API CWindow
{
public:
    CWindow(FScreenPoint InScreenSize, const FString& InWindowName, HINSTANCE InInstanceHandle, ERHIType InRHIType = ERHIType::GDI);
    ~CWindow();

    FORCEINLINE static CWindow& Get() { return *Instance; }
    FORCEINLINE FScreenPoint GetScreenSize() const { return ScreenSize; }
    FORCEINLINE HWND GetWindowHandle() const { return WindowHandle; }
    FORCEINLINE ERHIType GetRHIType() const { return RHIType; }

private:
    static LRESULT CALLBACK WindowProc(HWND HWnd, UINT Message, WPARAM WParam, LPARAM LParam);

private:
    static CWindow* Instance;
    FScreenPoint ScreenSize;
    FString WindowName;
    HWND WindowHandle;
    HINSTANCE InstanceHandle;
    ERHIType RHIType;
};
