﻿#include "Precompiled.h"
#include "Vector2.h"

const FVector2 FVector2::UnitX(1.0f, 0.0f);
const FVector2 FVector2::UnitY(0.0f, 1.0f);
const FVector2 FVector2::Zero(0.0f, 0.0f);
const FVector2 FVector2::One(1.0f, 1.0f);

FString FVector2::ToString() const
{
	return FString::Printf(TEXT("(%f, %f)"), X, Y);
}

FString& operator<<(FString& InString, const FVector2& InVector)
{
	InString = InVector.ToString();
	return InString;
}
