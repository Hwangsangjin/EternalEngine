#pragma once

struct FMath
{
	template <typename T>
	FORCEINLINE static T Random(T InMin, T InMax)
	{
		if constexpr (std::is_integral<T>::value)
		{
			T RangeDiff = (InMax - InMin) + 1;
			return ((RangeDiff * rand()) / (RAND_MAX + 1)) + InMin;
		}
		else if constexpr (std::is_floating_point<T>::value)
		{
			T RandomValue = static_cast<T>(rand()) / static_cast<T>(RAND_MAX);
			return RandomValue * (InMax - InMin) + InMin;
		}
	}

	FORCEINLINE static constexpr int TruncToInt(float InFloat)
	{
		return static_cast<int>(InFloat);
	}

	FORCEINLINE static constexpr int RoundToInt(float InFloat)
	{
		return TruncToInt(roundf(InFloat));
	}

	FORCEINLINE static constexpr int FloorToInt(float InFloat)
	{
		return TruncToInt(floorf(InFloat));
	}

	FORCEINLINE static int CeilToInt(float InFloat)
	{
		return TruncToInt(ceilf(InFloat));
	}

	template< class T>
	FORCEINLINE static constexpr T Lerp(const T& InSrc, const T& InDest, float InAlpha)
	{
		return (T)(InSrc + InAlpha * (InDest - InSrc));
	}

	template<class T>
	FORCEINLINE static constexpr T Square(const T InNum)
	{
		return InNum * InNum;
	}

	FORCEINLINE static constexpr float ToRadian(float InDegree)
	{
		return InDegree * Pi / 180.0f;
	}

	FORCEINLINE static constexpr float ToDegree(float InRadian)
	{
		return InRadian * 180.0f / Pi;
	}

	FORCEINLINE static constexpr bool IsNearlyZero(float InFloat, float InTolerance = Epsilon)
	{
		return FMath::Abs(InFloat) <= InTolerance;
	}

	FORCEINLINE static constexpr bool IsNearlyEqual(const float InFloat1, const float InFloat2, float InTolerance = Epsilon)
	{
		return FMath::Abs(InFloat1 - InFloat2) <= InTolerance;
	}

	template<class T>
	FORCEINLINE static constexpr T Max(const T InA, const T InB)
	{
		return (InA >= InB) ? InA : InB;
	}

	template<class T>
	FORCEINLINE static constexpr T Min(const T InA, const T InB)
	{
		return (InA <= InB) ? InA : InB;
	}

	template<class T>
	FORCEINLINE static constexpr T Abs(const T InA)
	{
		return (InA >= (T)0) ? InA : -InA;
	}

	template<class T>
	FORCEINLINE static constexpr T Clamp(const T InX, const T InMin, const T InMax)
	{
		return InX < InMin ? InMin : InX < InMax ? InX : InMax;
	}

	FORCEINLINE static float Cos(float InAngle)
	{
		return cosf(InAngle);
	}

	FORCEINLINE static float Sin(float InAngle)
	{
		return sinf(InAngle);
	}

	FORCEINLINE static float Tan(float InAngle)
	{
		return tanf(InAngle);
	}

	FORCEINLINE static float Acos(float InValue)
	{
		return acosf(InValue);
	}

	FORCEINLINE static float Atan2(float InY, float InX)
	{
		return atan2f(InY, InX);
	}

	FORCEINLINE static float Cot(float InAngle)
	{
		return 1.0f / Tan(InAngle);
	}

	FORCEINLINE static float Sqrt(float InValue)
	{
		return sqrtf(InValue);
	}

	FORCEINLINE static constexpr void GetSinCosRad(float& OutSin, float& OutCos, float InRadians)
	{
		float Quotient = (InvPi * 0.5f) * InRadians;

		if (InRadians >= 0.0f)
			Quotient = (static_cast<float>(static_cast<int>(Quotient + 0.5f)));
		else
			Quotient = (static_cast<float>(static_cast<int>(Quotient - 0.5f)));

		float Y = InRadians - (2.0f * Pi) * Quotient;

		float Sign = 0.0f;

		if (Y > HalfPi)
		{
			Y = Pi - Y;
			Sign = -1.0f;
		}
		else if (Y < -HalfPi)
		{
			Y = -Pi - Y;
			Sign = -1.0f;
		}
		else
		{
			Sign = +1.0f;
		}

		float Y2 = Y * Y;

		OutSin = (((((-2.3889859e-08f * Y2 + 2.7525562e-06f) * Y2 - 0.00019840874f) * Y2 + 0.0083333310f) * Y2 - 0.16666667f) * Y2 + 1.0f) * Y;

		float P = ((((-2.6051615e-07f * Y2 + 2.4760495e-05f) * Y2 - 0.0013888378f) * Y2 + 0.041666638f) * Y2 - 0.5f) * Y2 + 1.0f;
		OutCos = Sign * P;
	}

	FORCEINLINE static constexpr void GetSinCos(float& OutSin, float& OutCos, float InDegree)
	{
		if (InDegree == 0.0f)
		{
			OutSin = 0.0f;
			OutCos = 1.0f;
		}
		else if (InDegree == 90.0f)
		{
			OutSin = 1.0f;
			OutCos = 0.0f;
		}
		else if (InDegree == 180.0f)
		{
			OutSin = 0.0f;
			OutCos = -1.0f;
		}
		else if (InDegree == 270.0f)
		{
			OutSin = -1.0f;
			OutCos = 0.0f;
		}
		else
		{
			GetSinCosRad(OutSin, OutCos, FMath::ToRadian(InDegree));
		}
	}

	FORCEINLINE static float FMod(float InX, float InY)
	{
		if (fabsf(InY) <= Epsilon)
			return 0.0f;

		const float Quotient = static_cast<float>(TruncToInt(InX / InY));

		float IntPortion = InY * Quotient;

		if (fabsf(IntPortion) > fabsf(InX))
			IntPortion = InX;

		return (InX - IntPortion);
	}

	FORCEINLINE static float InvSqrt(float InFloat)
	{
		const __m128 OneHalf = _mm_set_ss(0.5f);
		__m128 Y0, X0, X1, X2, FOver2;
		float Temp;

		Y0 = _mm_set_ss(InFloat);
		X0 = _mm_rsqrt_ss(Y0);
		FOver2 = _mm_mul_ss(Y0, OneHalf);

		X1 = _mm_mul_ss(X0, X0);
		X1 = _mm_sub_ss(OneHalf, _mm_mul_ss(FOver2, X1));
		X1 = _mm_add_ss(X0, _mm_mul_ss(X0, X1));

		X2 = _mm_mul_ss(X1, X1);
		X2 = _mm_sub_ss(OneHalf, _mm_mul_ss(FOver2, X2));
		X2 = _mm_add_ss(X1, _mm_mul_ss(X1, X2));

		_mm_store_ss(&Temp, X2);
		return Temp;
	}

	static constexpr float Pi = { 3.14159265358979323846f };
	static constexpr float TwoPi = { 2.0f * Pi };
	static constexpr float HalfPi = { 1.57079632679f };
	static constexpr float InvPi = { 0.31830988618f };
	static constexpr float Epsilon = { 1.e-8f };
};
