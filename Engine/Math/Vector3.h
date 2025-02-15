#pragma once

class FString;

struct ENGINE_API FVector3
{
	FORCEINLINE constexpr FVector3() = default;

	FORCEINLINE explicit constexpr FVector3(const FVector2& InVector, bool IsPoint = true)
		: X(InVector.X)
		, Y(InVector.Y)
		, Z(IsPoint ? 1.0f : 0.0f)
	{}

	FORCEINLINE explicit constexpr FVector3(float InX, float InY, float InZ)
		: X(InX)
		, Y(InY)
		, Z(InZ)
	{}

	FORCEINLINE constexpr float operator[](BYTE InIndex) const
	{
		assert(InIndex < Dimension);
		return Scalars[InIndex];
	}

	FORCEINLINE constexpr float& operator[](BYTE InIndex)
	{
		assert(InIndex < Dimension);
		return Scalars[InIndex];
	}

	FORCEINLINE constexpr FVector3 operator-() const
	{
		return FVector3(-X, -Y, -Z);
	}

	FORCEINLINE constexpr FVector3 operator*(float InScale) const
	{
		return FVector3(X * InScale, Y * InScale, Z * InScale);
	}

	FORCEINLINE constexpr FVector3 operator/(float InScale) const
	{
		return FVector3(X / InScale, Y / InScale, Z / InScale);
	}

	FORCEINLINE constexpr FVector3 operator*(const FVector3& InVector) const
	{
		return FVector3(X * InVector.X, Y * InVector.Y, Z * InVector.Z);
	}

	FORCEINLINE constexpr FVector3 operator+(const FVector3& InVector) const
	{
		return FVector3(X + InVector.X, Y + InVector.Y, Z + InVector.Z);
	}

	FORCEINLINE constexpr FVector3 operator-(const FVector3& InVector) const
	{
		return FVector3(X - InVector.X, Y - InVector.Y, Z - InVector.Z);
	}

	FORCEINLINE constexpr FVector3& operator*=(float InScale)
	{
		X *= InScale;
		Y *= InScale;
		Z *= InScale;
		return *this;
	}

	FORCEINLINE constexpr FVector3& operator/=(float InScale)
	{
		X /= InScale;
		Y /= InScale;
		Z /= InScale;
		return *this;
	}

	FORCEINLINE constexpr FVector3& operator+=(const FVector3& InVector)
	{
		X += InVector.X;
		Y += InVector.Y;
		Z += InVector.Z;
		return *this;
	}

	FORCEINLINE constexpr FVector3& operator-=(const FVector3& InVector)
	{
		X -= InVector.X;
		Y -= InVector.Y;
		Z -= InVector.Z;
		return *this;
	}

	FORCEINLINE constexpr FVector2 ToVector2() const
	{
		return FVector2(X, Y);
	}

	FORCEINLINE float Size() const
	{
		return sqrtf(SizeSquared());
	}

	FORCEINLINE constexpr float SizeSquared() const
	{
		return X * X + Y * Y + Z * Z;
	}

	void Normalize()
	{
		*this = GetNormalize();
	}

	[[nodiscard]] FVector3 GetNormalize() const
	{
		float SquareSum = SizeSquared();
		if (SquareSum == 1.0f)
			return *this;
		else if (SquareSum == 0.0f)
			return FVector3::Zero;

		float InvLength = FMath::InvSqrt(SquareSum);
		return FVector3(X * InvLength, Y * InvLength, Z * InvLength);
	}

	FORCEINLINE constexpr bool IsNearlyEqual(const FVector3& InVector, float InTolerance = FMath::Epsilon) const
	{
		return (FMath::Abs(X - InVector.X) <= InTolerance) &&
			(FMath::Abs(Y - InVector.Y) < InTolerance) &&
			(FMath::Abs(Z - InVector.Z) < InTolerance);
	}

	FORCEINLINE constexpr float Max() const
	{
		float Max = FMath::Max(X, Y);
		return FMath::Max(Max, Z);
	}

	FORCEINLINE constexpr float DotProduct(const FVector3& InVector) const
	{
		return X * InVector.X + Y * InVector.Y + Z * InVector.Z;
	}

	FORCEINLINE constexpr FVector3 CrossProduct(const FVector3& InVector) const
	{
		return FVector3(
			Y * InVector.Z - Z * InVector.Y,
			Z * InVector.X - X * InVector.Z,
			X * InVector.Y - Y * InVector.X);
	}

	FString ToString() const;

	friend FString& operator<<(FString& InString, const FVector3& InVector);

	static const FVector3 UnitX;
	static const FVector3 UnitY;
	static const FVector3 UnitZ;
	static const FVector3 One;
	static const FVector3 Zero;
	static constexpr BYTE Dimension = 3;

	union
	{
		struct
		{
			float X, Y, Z;
		};

		std::array<float, Dimension> Scalars = { 0.0f, 0.0f, 0.0f };
	};
};
