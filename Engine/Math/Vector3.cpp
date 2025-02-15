#include "Precompiled.h"
#include "Vector3.h"

const FVector3 FVector3::UnitX(1.0f, 0.0f, 0.0f);
const FVector3 FVector3::UnitY(0.0f, 1.0f, 0.0f);
const FVector3 FVector3::UnitZ(0.0f, 0.0f, 1.0f);
const FVector3 FVector3::Zero(0.0f, 0.0f, 0.0f);
const FVector3 FVector3::One(1.0f, 1.0f, 1.0f);

FString FVector3::ToString() const
{
	return FString::Printf(TEXT("(%f, %f, %f)"), X, Y, Z);
}

FString& operator<<(FString& InString, const FVector3& InVector)
{
	InString = InVector.ToString();
	return InString;
}
