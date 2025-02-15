#pragma once

struct ENGINE_API FLinearColor
{
	FORCEINLINE constexpr FLinearColor() = default;

	FORCEINLINE explicit constexpr FLinearColor(float InR, float InG, float InB, float InA = 1.0f)
		: R(InR)
		, G(InG)
		, B(InB)
		, A(InA)
	{}
	
	FORCEINLINE explicit constexpr FLinearColor(const FColor32& InColor32)
	{
		R = float(InColor32.R) * OneOver255;
		G = float(InColor32.G) * OneOver255;
		B = float(InColor32.B) * OneOver255;
		A = float(InColor32.A) * OneOver255;
	}

	FORCEINLINE constexpr FColor32 ToColor32(const bool bSRGB = false) const
	{
		float FloatR = FMath::Clamp(R, 0.0f, 1.0f);
		float FloatG = FMath::Clamp(G, 0.0f, 1.0f);
		float FloatB = FMath::Clamp(B, 0.0f, 1.0f);
		float FloatA = FMath::Clamp(A, 0.0f, 1.0f);

		return FColor32(
			(int)(FloatR * 255.999f),
			(int)(FloatG * 255.999f),
			(int)(FloatB * 255.999f),
			(int)(FloatA * 255.999f)
		);
	}

	FORCEINLINE FLinearColor ToHSVColor() const
	{
		const float RGBMin = FMath::Min3(R, G, B);
		const float RGBMax = FMath::Max3(R, G, B);
		const float RGBRange = RGBMax - RGBMin;

		const float Hue = (RGBMax == RGBMin ? 0.0f :
			RGBMax == R ? FMath::FMod((((G - B) / RGBRange) * 60.0f) + 360.0f, 360.0f) :
			RGBMax == G ? (((B - R) / RGBRange) * 60.0f) + 120.0f :
			RGBMax == B ? (((R - G) / RGBRange) * 60.0f) + 240.0f :
			0.0f);

		const float Saturation = (RGBMax == 0.0f ? 0.0f : RGBRange / RGBMax);
		const float Value = RGBMax;

		return FLinearColor(Hue, Saturation, Value, A);
	}

	FORCEINLINE constexpr FLinearColor operator+(const FLinearColor& InColor) const
	{
		return FLinearColor(
			R + InColor.R,
			G + InColor.G,
			B + InColor.B,
			A + InColor.A
		);
	}

	FORCEINLINE constexpr FLinearColor operator-(const FLinearColor& InColor) const
	{
		return FLinearColor(
			R - InColor.R,
			G - InColor.G,
			B - InColor.B,
			A - InColor.A
		);
	}

	FORCEINLINE constexpr FLinearColor operator*(const FLinearColor& InColor) const
	{
		return FLinearColor(
			R * InColor.R,
			G * InColor.G,
			B * InColor.B,
			A * InColor.A
		);
	}

	FORCEINLINE constexpr FLinearColor operator*(float InScalar) const
	{
		return FLinearColor(
			R * InScalar,
			G * InScalar,
			B * InScalar,
			A * InScalar
		);
	}

	FORCEINLINE constexpr FLinearColor& operator*=(float InScale)
	{
		R *= InScale;
		G *= InScale;
		B *= InScale;
		A *= InScale;
		return *this;
	}

	FORCEINLINE constexpr FLinearColor& operator/=(float InScale)
	{
		R /= InScale;
		G /= InScale;
		B /= InScale;
		A /= InScale;
		return *this;
	}

	FORCEINLINE constexpr FLinearColor& operator+=(const FLinearColor& InColor)
	{
		R += InColor.R;
		G += InColor.G;
		B += InColor.B;
		A += InColor.A;
		return *this;

	}
	FORCEINLINE constexpr FLinearColor& operator-=(const FLinearColor& InColor)
	{
		R -= InColor.R;
		G -= InColor.G;
		B -= InColor.B;
		A -= InColor.A;
		return *this;
	}

	FORCEINLINE constexpr bool operator==(const FLinearColor& InColor) const
	{
		return R == InColor.R && G == InColor.G && B == InColor.B && A == InColor.A;
	}

	FORCEINLINE constexpr bool operator!=(const FLinearColor& InColor) const
	{
		return R != InColor.R || G != InColor.G || B != InColor.B || A != InColor.A;
	}

	FORCEINLINE constexpr bool IsNearlyEqual(const FLinearColor& InColor, float InTolerance = FMath::Epsilon) const
	{
		return (FMath::Abs(R - InColor.R) < InTolerance) &&
			(FMath::Abs(G - InColor.G) < InTolerance) &&
			(FMath::Abs(B - InColor.B) < InTolerance) &&
			(FMath::Abs(A - InColor.A) < InTolerance);
	}

	static constexpr float OneOver255 = { 1.0f / 255.0f };
	static const FLinearColor Error;
	static const FLinearColor White;
	static const FLinearColor Black;
	static const FLinearColor Gray;
	static const FLinearColor Silver;
	static const FLinearColor WhiteSmoke;
	static const FLinearColor LightGray;
	static const FLinearColor DimGray;
	static const FLinearColor Red;
	static const FLinearColor Green;
	static const FLinearColor Blue;
	static const FLinearColor Yellow;
	static const FLinearColor Cyan;
	static const FLinearColor Magenta;

	float R = 0.0f;
	float G = 0.0f;
	float B = 0.0f;
	float A = 1.0f;
};
