#pragma once

#include "String/String.h"

struct FVector2
{
	FORCEINLINE constexpr FVector2() = default;

	FORCEINLINE explicit constexpr FVector2(int InX, int InY)
		: X(static_cast<float>(InX)), Y(static_cast<float>(InY))
	{}

	FORCEINLINE explicit constexpr FVector2(float InX, float InY)
		: X(InX), Y(InY)
	{}

	FORCEINLINE constexpr float operator[](unsigned char InIndex) const
	{
		assert(InIndex < Dimension);
		return Scalars[InIndex];
	}

	FORCEINLINE constexpr float& operator[](unsigned char InIndex)
	{
		assert(InIndex < Dimension);
		return Scalars[InIndex];
	}

	FORCEINLINE constexpr FVector2 operator-() const
	{
		return FVector2(-X, -Y);
	}

	FORCEINLINE constexpr FVector2 operator*(float InScalar) const
	{
		return FVector2(X * InScalar, Y * InScalar);
	}

	FORCEINLINE constexpr FVector2 operator/(float InScalar) const
	{
		return FVector2(X / InScalar, Y / InScalar);
	}

	FORCEINLINE constexpr FVector2 operator+(const FVector2& InVector) const
	{
		return FVector2(X + InVector.X, Y + InVector.Y);
	}

	FORCEINLINE constexpr FVector2 operator-(const FVector2& InVector) const
	{
		return FVector2(X - InVector.X, Y - InVector.Y);
	}

	FORCEINLINE constexpr FVector2 operator*(const FVector2& InVector) const
	{
		return FVector2(X * InVector.X, Y * InVector.Y);
	}

	FORCEINLINE constexpr FVector2& operator*=(float InScale)
	{
		X *= InScale;
		Y *= InScale;
		return *this;
	}

	FORCEINLINE constexpr FVector2& operator/=(float InScale)
	{
		X /= InScale;
		Y /= InScale;
		return *this;
	}

	FORCEINLINE constexpr FVector2& operator+=(const FVector2& InVector)
	{
		X += InVector.X;
		Y += InVector.Y;
		return *this;
	}

	FORCEINLINE constexpr FVector2& operator-=(const FVector2& InVector)
	{
		X -= InVector.X;
		Y -= InVector.Y;
		return *this;
	}

	FORCEINLINE constexpr bool operator==(const FVector2& InVector) const
	{
		return X == InVector.X && Y == InVector.Y;
	}

	FORCEINLINE constexpr bool operator!=(const FVector2& InVector) const
	{
		return !(*this == InVector);
	}

	FORCEINLINE constexpr bool operator<(const FVector2& InVector) const
	{
		return SizeSquared() < InVector.SizeSquared();
	}

	FORCEINLINE constexpr bool operator<=(const FVector2& InVector) const
	{
		return SizeSquared() <= InVector.SizeSquared();
	}

	FORCEINLINE constexpr bool operator>(const FVector2& InVector) const
	{
		return SizeSquared() > InVector.SizeSquared();
	}

	FORCEINLINE constexpr bool operator>=(const FVector2& InVector) const
	{
		return SizeSquared() >= InVector.SizeSquared();
	}

	FORCEINLINE float Size() const
	{
		return sqrtf(SizeSquared());
	}

	FORCEINLINE constexpr float SizeSquared() const
	{
		return X * X + Y * Y;
	}

	void Normalize()
	{
		*this = GetNormalize();
	}

	[[nodiscard]] FVector2 GetNormalize() const
	{
		float SquareSum = SizeSquared();
		if (SquareSum == 1.0f)
			return *this;
		else if (SquareSum == 0.0f)
			return FVector2(0.0f, 0.0f);

		float InvLength = FMath::InvSqrt(SquareSum);
		return FVector2(X, Y) * InvLength;
	}

	FORCEINLINE constexpr float Max() const
	{
		return FMath::Max(X, Y);
	}

	FORCEINLINE constexpr float DotProduct(const FVector2& InVector) const
	{
		return X * InVector.X + Y * InVector.Y;
	}

	FORCEINLINE float Angle() const
	{
		return atan2f(Y, X);
	}

	FORCEINLINE float AngleInDegree() const
	{
		return FMath::ToDegree(atan2f(Y, X));
	}

	FORCEINLINE FVector2 ToPolarCoordinate() const
	{
		return FVector2(Size(), Angle());
	}

	FORCEINLINE constexpr FVector2 ToCartesianCoordinate() const
	{
		float Sin = 0.0f, Cos = 0.0f;
		FMath::GetSinCosRad(Sin, Cos, Y);
		return FVector2(X * Cos, X * Sin);
	}

	FString ToString() const
	{
		return FString::Printf(TEXT("(%f, %f)"), X, Y);
	}

	friend FString& operator<<(FString& InString, const FVector2& InVector)
	{
		InString = InVector.ToString();
		return InString;
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
