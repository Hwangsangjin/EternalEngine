#pragma once

class ENGINE_API FString
{
public:
    // 기본 생성자
    FString() = default;

    // wchar_t* 문자열을 변환하는 생성자
    FString(const wchar_t* InString)
        : WideString(InString)
    {}

    // char* 문자열을 변환하는 생성자
    FString(const char* InString)
        : WideString(InString, InString + strlen(InString))
    {}

    // 복사 생성자
    FString(const FString& InString)
        : WideString(InString.WideString)
    {}

    // 대입 연산자
    FORCEINLINE FString& operator=(const FString& InString)
    {
        if (this != &InString)
            WideString = InString.WideString;

        return *this;
    }

    // 문자열 비교 연산자
    FORCEINLINE bool operator==(const FString& InString) const
    {
        return WideString == InString.WideString;
    }

    // 문자열 비교 연산자
    FORCEINLINE bool operator<(const FString& InString) const
    {
        return WideString < InString.WideString;
    }

    // 문자열 덧셈 연산자
    FORCEINLINE FString operator+(const FString& InString)
    {
        FString Result = *this;
        Result.Append(InString);
        return Result;
    }

    // 문자열 덧셈 연산자
    FORCEINLINE friend FString operator+(const FString& InString1, const FString& InString2)
    {
        FString Result = InString1;
        Result.Append(InString2);
        return Result;
    }

    // 문자열을 출력하는 함수
    FORCEINLINE void Print() const
    {
        std::string String(WideString.begin(), WideString.end());
        std::cout << String << std::endl;
    }

    // 문자열을 추가하는 함수
    FORCEINLINE void Append(const FString& InString)
    {
        WideString.append(InString.WideString);
    }

    // 문자열 길이를 반환하는 함수
    FORCEINLINE size_t Length() const
    {
        return WideString.length();
    }

    // std::string으로 변환하여 반환하는 함수
    FORCEINLINE std::string ToString() const
    {
        std::string String(WideString.begin(), WideString.end());
        return String;
    }

    // 유니코드 문자열을 반환하는 함수
    FORCEINLINE const std::wstring& GetWideString() const { return WideString; }

    // std::wostream에 FString을 출력하는 연산자
    friend std::wostream& operator<<(std::wostream& OutStream, const FString& InString)
    {
        OutStream << InString.GetWideString();
        return OutStream;
    }

    // 포맷팅된 문자열을 생성하는 함수 (가변 인수)
    static FString Printf(const wchar_t* Format, ...)
    {
        // 가변 인수 리스트 처리
        va_list Args;
        va_start(Args, Format);

        // 가변 인수를 처리하여 버퍼에 저장
        wchar_t Buffer[1024];
        _vsnwprintf_s(Buffer, sizeof(Buffer) / sizeof(wchar_t), Format, Args);
        va_end(Args);

        return FString(Buffer);
    }

private:
    // 내부적으로 사용하는 유니코드 문자열
    std::wstring WideString;
};

// std::hash를 FString에 대해 특수화하여 해시 값을 계산하는 구조체
namespace std
{
    template <>
    struct hash<FString>
    {
        size_t operator()(const FString& InString) const
        {
            // 유니코드 문자열의 해시 값을 반환
            return std::hash<std::wstring>{}(InString.GetWideString());
        }
    };
}
