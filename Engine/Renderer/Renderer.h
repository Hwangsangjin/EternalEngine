#pragma once

class CLevel;

class ENGINE_API CRenderer
{
public:
    CRenderer();
    ~CRenderer();

	void Render();

	// 화면 크기 반환 함수
	FORCEINLINE COORD GetBufferSize() const { return BufferSize; }

	// 커서 설정 함수
	void SetCursorType(const ECursorType& InCursorType);

	// 텍스트 출력 함수
	void PrintText(const FVector2& InPosition, const FString& InText, const EColor& InColor = EColor::White);

protected:
	void Clear();
	void Present();

private:
	// 표준 디바이스 핸들
	HANDLE StdHandle;

	// 더블 버퍼링 변수
	HANDLE FrontBuffer;
	HANDLE BackBuffer;
	COORD BufferSize;
	CONSOLE_SCREEN_BUFFER_INFO BufferInfo;
};
