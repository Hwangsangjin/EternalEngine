#pragma once

struct ENGINE_API FColor32
{
	FORCEINLINE constexpr FColor32()
		: R(0)
		, G(0)
		, B(0)
		, A(0)
	{}

	FORCEINLINE explicit constexpr FColor32(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255)
		: B(InB)
		, G(InG)
		, R(InR)
		, A(InA)
	{}
	
	FORCEINLINE explicit constexpr FColor32(UINT InColor)
		: ColorValue(InColor)
	{}

	FORCEINLINE constexpr const UINT& GetColorRef() const
	{
		return ColorValue;
	}

	FORCEINLINE constexpr UINT& GetColorRef()
	{
		return ColorValue;
	}

	FORCEINLINE constexpr WORD ToConsoleColorAttribute() const
	{
		// LinearColor에서 RGB 값을 0~255 범위로 변환
		int Red = static_cast<int>(FMath::Clamp(R * 255.0f, 0.0f, 255.0f));
		int Green = static_cast<int>(FMath::Clamp(G * 255.0f, 0.0f, 255.0f));
		int Blue = static_cast<int>(FMath::Clamp(B * 255.0f, 0.0f, 255.0f));

		// RGB 값을 다시 콘솔 색상 인덱스로 매핑
		int ConsoleColor = 0;

		if (Red > 128) ConsoleColor |= 4;
		if (Green > 128) ConsoleColor |= 2;
		if (Blue > 128) ConsoleColor |= 1;

		// 색상 인덱스 반환
		return static_cast<WORD>(ConsoleColor);
	}

	FORCEINLINE constexpr bool operator==(const FColor32& InColor) const
	{
		return GetColorRef() == InColor.GetColorRef();
	}

	FORCEINLINE constexpr bool operator!=(const FColor32& InColor) const
	{
		return GetColorRef() != InColor.GetColorRef();
	}

	FORCEINLINE constexpr void operator+=(const FColor32& InColor)
	{
		R = (BYTE)FMath::Clamp((BYTE)R + (BYTE)InColor.R, 0, 255);
		G = (BYTE)FMath::Clamp((BYTE)G + (BYTE)InColor.G, 0, 255);
		B = (BYTE)FMath::Clamp((BYTE)B + (BYTE)InColor.B, 0, 255);
		A = (BYTE)FMath::Clamp((BYTE)A + (BYTE)InColor.A, 0, 255);
	}

	static const FColor32 Error;

	union
	{
		struct
		{
			BYTE B, G, R, A;
		};

		UINT ColorValue;
	};
};
