@echo off
setlocal enabledelayedexpansion

rem 셰이더 소스 폴더와 출력 폴더, FXC 경로 설정
set "SHADER_DIR=%SHADER_DIR%"  rem 빌드 이벤트에서 설정한 환경 변수를 사용
set "FXC_PATH=C:\Program Files (x86)\Windows Kits\10\bin\10.0.22621.0\x64\fxc.exe"

rem FXC 실행 파일 존재 여부 확인
if not exist "%FXC_PATH%" (
    echo [ERROR] FXC compiler not found: "%FXC_PATH%"
    exit /b 1
)

rem 셰이더 폴더 존재 여부 확인
if not exist "%SHADER_DIR%" (
    echo [ERROR] Shader directory not found: "%SHADER_DIR%"
    exit /b 1
)

rem SHADER_DIR 폴더 내의 모든 .hlsl 파일에 대해 루프 실행
for %%f in ("%SHADER_DIR%\*.hlsl") do (
    rem 파일명만 추출
    set "FILENAME=%%~nf"
    echo Compiling %%f...

    rem FXC 경로 출력 확인
    echo Calling FXC with the following command:
    echo "%FXC_PATH%" /T vs_5_0 /E VS_Main /Fo "%SHADER_DIR%\!FILENAME!_VS_5_0.cso" "%%f"

    rem 정점 셰이더 컴파일
    "%FXC_PATH%" /T vs_5_0 /E VS_Main /Fo "%SHADER_DIR%\!FILENAME!_VS_5_0.cso" "%%f"
    if errorlevel 1 (
        echo [ERROR] Vertex shader compilation failed for %%f
        exit /b 1
    )
    
    rem 픽셀 셰이더 컴파일
    echo Calling FXC with the following command:
    echo "%FXC_PATH%" /T ps_5_0 /E PS_Main /Fo "%SHADER_DIR%\!FILENAME!_PS_5_0.cso" "%%f"
    "%FXC_PATH%" /T ps_5_0 /E PS_Main /Fo "%SHADER_DIR%\!FILENAME!_PS_5_0.cso" "%%f"
    if errorlevel 1 (
        echo [ERROR] Pixel shader compilation failed for %%f
        exit /b 1
    )
)

echo Shaders compiled successfully.
