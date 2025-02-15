#include "Precompiled.h"
#include "Vector4.h"

const FVector4 FVector4::UnitX(1.0f, 0.0f, 0.0f, 0.0f);
const FVector4 FVector4::UnitY(0.0f, 1.0f, 0.0f, 0.0f);
const FVector4 FVector4::UnitZ(0.0f, 0.0f, 1.0f, 0.0f);
const FVector4 FVector4::UnitW(0.0f, 0.0f, 0.0f, 1.0f);
const FVector4 FVector4::Zero(0.0f, 0.0f, 0.0f, 0.0f);
const FVector4 FVector4::One(1.0f, 1.0f, 1.0f, 1.0f);

FString FVector4::ToString() const
{
	return FString::Printf(TEXT("(%f, %f, %f, %f)"), X, Y, Z, W);
}

FString& operator<<(FString& InString, const FVector4& InVector)
{
	InString = InVector.ToString();
	return InString;
}
