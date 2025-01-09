#pragma once

#include "Core.h"

struct ENGINE_API FVector2
{
	FORCEINLINE constexpr FVector2()
	{}

	FORCEINLINE explicit constexpr FVector2(int X, int Y)
		: X(static_cast<float>(X)), Y(static_cast<float>(Y))
	{}

	FORCEINLINE explicit constexpr FVector2(float X, float Y)
		: X(X), Y(Y)
	{}

	FORCEINLINE constexpr float operator[](unsigned char Index) const
	{
		assert(Index < Dimension);
		return Scalars[Index];
	}

	FORCEINLINE constexpr float& operator[](unsigned char Index)
	{
		assert(Index < Dimension);
		return Scalars[Index];
	}

	FORCEINLINE constexpr FVector2 operator-() const
	{
		return FVector2(-X, -Y);
	}

	FORCEINLINE constexpr FVector2 operator*(float Scalar) const
	{
		return FVector2(X * Scalar, Y * Scalar);
	}

	FORCEINLINE constexpr FVector2 operator/(float Scalar) const
	{
		return FVector2(X / Scalar, Y / Scalar);
	}

	FORCEINLINE constexpr FVector2 operator+(const FVector2& TArray) const
	{
		return FVector2(X + TArray.X, Y + TArray.Y);
	}

	FORCEINLINE constexpr FVector2 operator-(const FVector2& Other) const
	{
		return FVector2(X - Other.X, Y - Other.Y);
	}

	FORCEINLINE constexpr FVector2 operator*(const FVector2& Other) const
	{
		return FVector2(X * Other.X, Y * Other.Y);
	}

	FORCEINLINE constexpr FVector2& operator*=(float Scale)
	{
		X *= Scale;
		Y *= Scale;
		return *this;
	}

	FORCEINLINE constexpr FVector2& operator/=(float Scale)
	{
		X /= Scale;
		Y /= Scale;
		return *this;
	}

	FORCEINLINE constexpr FVector2& operator+=(const FVector2& Other)
	{
		X += Other.X;
		Y += Other.Y;
		return *this;
	}

	FORCEINLINE constexpr FVector2& operator-=(const FVector2& Other)
	{
		X -= Other.X;
		Y -= Other.Y;
		return *this;
	}

	static const FVector2 UnitX;
	static const FVector2 UnitY;
	static const FVector2 One;
	static const FVector2 Zero;
	static constexpr unsigned char Dimension = 2;

	union
	{
		struct
		{
			float X, Y;
		};

		float Scalars[Dimension] = { 0.0f, 0.0f };
	};
};
