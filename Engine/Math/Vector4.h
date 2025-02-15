#pragma once

class FString;

struct ENGINE_API FVector4
{
	FORCEINLINE constexpr FVector4() = default;

	FORCEINLINE explicit constexpr FVector4(const FVector2& InV, bool IsPoint = true)
		: X(InV.X)
		, Y(InV.Y)
		, Z(0.0f)
		, W(IsPoint ? 1.0f : 0.0f)
	{}

	FORCEINLINE explicit constexpr FVector4(const FVector3& InV, bool IsPoint = true)
		: X(InV.X)
		, Y(InV.Y)
		, Z(InV.Z)
		, W(IsPoint ? 1.0f : 0.0f)
	{}

	FORCEINLINE explicit constexpr FVector4(float InX, float InY, float InZ, float InW)
		: X(InX)
		, Y(InY)
		, Z(InZ)
		, W(InW)
	{}

	FORCEINLINE explicit constexpr FVector4(float InX, float InY, float InZ, bool IsPoint = true)
		: X(InX)
		, Y(InY)
		, Z(InZ)
		, W(IsPoint ? 1.0f : 0.0f)
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

	FORCEINLINE constexpr FVector4 operator-() const
	{
		return FVector4(-X, -Y, -Z, -W);
	}

	FORCEINLINE constexpr FVector4 operator*(float InScale) const
	{
		return FVector4(X * InScale, Y * InScale, Z * InScale, W * InScale);
	}

	FORCEINLINE constexpr FVector4 operator/(float InScale) const
	{
		return FVector4(X / InScale, Y / InScale, Z / InScale, W / InScale);
	}

	FORCEINLINE constexpr FVector4 operator*(const FVector4& InVector) const
	{
		return FVector4(X * InVector.X, Y * InVector.Y, Z * InVector.Z, W * InVector.W);
	}

	FORCEINLINE constexpr FVector4 operator+(const FVector4& InVector) const
	{
		return FVector4(X + InVector.X, Y + InVector.Y, Z + InVector.Z, W + InVector.W);
	}

	FORCEINLINE constexpr FVector4 operator-(const FVector4& InVector) const
	{
		return FVector4(X - InVector.X, Y - InVector.Y, Z - InVector.Z, W - InVector.W);
	}

	FORCEINLINE constexpr FVector4& operator*=(float InScale)
	{
		X *= InScale;
		Y *= InScale;
		Z *= InScale;
		W *= InScale;
		return *this;
	}

	FORCEINLINE constexpr FVector4& operator/=(float InScale)
	{
		X /= InScale;
		Y /= InScale;
		Z /= InScale;
		W /= InScale;
		return *this;
	}

	FORCEINLINE constexpr FVector4& operator+=(const FVector4& InVector)
	{
		X += InVector.X;
		Y += InVector.Y;
		Z += InVector.Z;
		W += InVector.W;
		return *this;
	}

	FORCEINLINE constexpr FVector4& operator-=(const FVector4& InVector)
	{
		X -= InVector.X;
		Y -= InVector.Y;
		Z -= InVector.Z;
		W -= InVector.W;
		return *this;
	}

	FORCEINLINE constexpr FVector2 ToVector2() const
	{
		return FVector2(X, Y);
	}

	FORCEINLINE constexpr FVector3 ToVector3() const
	{
		return FVector3(X, Y, Z);
	}

	FORCEINLINE float Size() const
	{
		return sqrtf(SizeSquared());
	}

	FORCEINLINE constexpr float SizeSquared() const
	{
		return X * X + Y * Y + Z * Z + W * W;
	}

	void Normalize()
	{
		*this = GetNormalize();
	}

	[[nodiscard]] FVector4 GetNormalize() const
	{
		float SquareSum = SizeSquared();
		if (SquareSum == 1.0f)
			return *this;
		else if (SquareSum == 0.0f)
			return FVector4::Zero;

		float InvLength = FMath::InvSqrt(SquareSum);
		return FVector4(X * InvLength, Y * InvLength, Z * InvLength, W * InvLength);
	}

	FORCEINLINE constexpr bool IsNearlyEqual(const FVector4& InVector, float InTolerance = FMath::Epsilon) const
	{
		return (FMath::Abs(X - InVector.X) <= InTolerance) &&
			(FMath::Abs(Y - InVector.Y) < InTolerance) &&
			(FMath::Abs(Z - InVector.Z) < InTolerance) &&
			(FMath::Abs(W - InVector.W) < InTolerance);
	}

	FORCEINLINE constexpr float Max() const
	{
		float Max = FMath::Max(X, Y);
		Max = FMath::Max(Max, Z);
		return FMath::Max(Max, W);
	}

	FORCEINLINE constexpr float DotProduct(const FVector4& InVector) const
	{
		return X * InVector.X + Y * InVector.Y + Z * InVector.Z + W * InVector.W;
	}

	FString ToString() const;

	friend FString& operator<<(FString& InString, const FVector4& InVector);

	static const FVector4 UnitX;
	static const FVector4 UnitY;
	static const FVector4 UnitZ;
	static const FVector4 UnitW;
	static const FVector4 One;
	static const FVector4 Zero;
	static constexpr BYTE Dimension = 4;

	union
	{
		struct
		{
			float X, Y, Z, W;
		};

		std::array<float, Dimension> Scalars = { 0.0f, 0.0f, 0.0f, 0.0f };
	};
};
