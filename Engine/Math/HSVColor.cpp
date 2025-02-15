#include "Precompiled.h"
#include "HSVColor.h"

constexpr FLinearColor FHSVColor::ToLinearColor() const
{
	float R = 0.0f, G = 0.0f, B = 0.0f;

	int I = FMath::FloorToInt(H * 6.0f);
	float F = H * 6.0f - I;
	float P = V * (1.0f - S);
	float Q = V * (1.0f - F * S);
	float T = V * (1.0f - (1.0f - F) * S);

	switch (I % 6)
	{
	case 0: R = V, G = T, B = P; break;
	case 1: R = Q, G = V, B = P; break;
	case 2: R = P, G = V, B = T; break;
	case 3: R = P, G = Q, B = V; break;
	case 4: R = T, G = P, B = V; break;
	case 5: R = V, G = P, B = Q; break;
	}

	return FLinearColor(R, G, B);
}
