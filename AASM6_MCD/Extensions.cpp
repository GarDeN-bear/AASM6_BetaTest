#include "pch.h"
#include "Extensions.h"
#include <cmath>

COMPLEXSCALAR InputComplexToComplexScalar(const AASM6::InputComplex& x)
{
	COMPLEXSCALAR x_mcd;
	if (fabs(x.Value - x.Min) < fabs(x.Value - x.Max))
	{
		//значение комплекса ближе к левой границе или выходит за неё
		x_mcd.real = x.Min;
		x_mcd.imag = x.Value;
		// Если x_mcd.real > x_mcd.imag то это Выход за левую границу		
	}
	else
	{
		//значение комплекса ближе к правой границе или выходит за неё
		x_mcd.real = x.Value;
		x_mcd.imag = x.Max;
		// Если x_mcd.real > x_mcd.imag то это Выход за правую границу	
	}
    return x_mcd;
}
