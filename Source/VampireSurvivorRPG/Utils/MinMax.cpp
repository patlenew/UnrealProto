#include "MinMax.h"

float FMinMax::GetRandomValue() const
{
	return FMath::RandRange(min, max);
}
