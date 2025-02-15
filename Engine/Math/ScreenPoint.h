#pragma once

struct ENGINE_API FScreenPoint
{
	FORCEINLINE constexpr FScreenPoint() = default;

	FORCEINLINE explicit constexpr FScreenPoint(int InX, int InY)
		: X(InX), Y(InY)
	{}

	FORCEINLINE explicit constexpr FScreenPoint(float InX, float InY)
		: X(FMath::FloorToInt(InX))
		, Y(FMath::FloorToInt(InY))
	{}

	FORCEINLINE explicit constexpr FScreenPoint(const FVector2& InPosition)
		: FScreenPoint(InPosition.X, InPosition.Y)
	{}

	constexpr FScreenPoint GetHalf() const
	{
		return FScreenPoint(FMath::FloorToInt(0.5f * X), FMath::FloorToInt(0.5f * Y));
	}

	constexpr float AspectRatio() const
	{
		return static_cast<float>(X) / static_cast<float>(Y);
	}

	FORCEINLINE constexpr bool HasZero() const
	{
		return (X == 0 || Y == 0);
	}

	FORCEINLINE static constexpr FScreenPoint ToScreenCoordinate(const FScreenPoint& InPoint, const FVector2& InPosition)
	{
		return FScreenPoint(InPosition.X + InPoint.X * 0.5f, -InPosition.Y + InPoint.Y * 0.5f);
	}

	FORCEINLINE constexpr FVector2 ToCartesianCoordinate(const FScreenPoint& InPoint)
	{
		return FVector2(X - InPoint.X * 0.5f + 0.5f, -(Y + 0.5f) + InPoint.Y * 0.5f);
	}

	FORCEINLINE constexpr FScreenPoint operator-(const FScreenPoint& InPoint) const
	{
		return FScreenPoint(X - InPoint.X, Y - InPoint.Y);
	}

	FORCEINLINE constexpr FScreenPoint operator+(const FScreenPoint& InPoint) const
	{
		return FScreenPoint(X + InPoint.X, Y + InPoint.Y);
	}

	int X = 0;
	int Y = 0;
};
