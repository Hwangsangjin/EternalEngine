#include "Precompiled.h"
#include "RHIFactory.h"
#include "RHI.h"
#include "ConsoleRHI.h"
#include "DirectX11RHI.h"
#include "WindowsRHI.h"
#include "Window/Window.h"

FRHI* FRHIFactory::CreateRHI()
{
    FRHI* RHI = nullptr;

    CWindow* Window = &CWindow::Get();
    if (Window)
    {
        ERHIType RHIType = CWindow::Get().GetRHIType();

        switch (RHIType)
        {
        case ERHIType::GDI:
            RHI = new FWindowsRHI;
            break;
        case ERHIType::DX11:
            RHI = new FDirectX11RHI;
            break;
        }
    }
    else
    {
        RHI = new FConsoleRHI;
    }

    return RHI;
}
