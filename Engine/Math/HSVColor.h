#pragma once

struct FLinearColor;

struct ENGINE_API FHSVColor
{
	FORCEINLINE constexpr FHSVColor() = default;

	FORCEINLINE constexpr FHSVColor(float InH, float InS, float InV)
		: H(InH)
		, S(InS)
		, V(InV)
	{}

	FORCEINLINE constexpr FLinearColor ToLinearColor() const;

	float H = 0.0f;
	float S = 1.0f;
	float V = 1.0f;
};
