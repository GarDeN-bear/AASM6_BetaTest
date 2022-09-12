#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Sigma_chi(float chi_0, InputComplex& x_1)
	{
		static unsigned int Length_1_1 = 17; static float Matrix_1_1[][2] = { {0.00000f, 1.00000f}, {5.00000f, 0.98120f}, {10.00000f, 0.94577f}, {15.00000f, 0.89539f}, {20.00000f, 0.82578f}, {25.00000f, 0.73201f}, {30.00000f, 0.62439f}, {35.00000f, 0.51699f}, {40.00000f, 0.42221f}, {45.00000f, 0.34407f}, {50.00000f, 0.27732f}, {55.00000f, 0.21878f}, {60.00000f, 0.16811f}, {65.00000f, 0.12684f}, {70.00000f, 0.09803f}, {75.00000f, 0.07685f}, {80.00000f, 0.06335f} };

		//Входной комплекс x1
		const float x1_min = 0.0f;
		const float x1_max = 80.0f;

		//Координата по оси х графика
		float x1 = chi_0 * deg;

		x_1.Min = x1_min;
		x_1.Value = x1;
		x_1.Max = x1_max;

		//Ограничение по диапазону оси x
		if (x1 < x1_min)
			x1 = x1_min;
		else if (x1 > x1_max)
			x1 = x1_max;

		//Вычисление
		float y = Linterp(Matrix_1_1, Length_1_1, x1);

		return y;
	}

	ErrorCode* get_Sigma_chi(float& Result, float chi_0, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (chi_0 < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		
		// Проверка: некоторые аргументы не должны быть больше 90 градусов	
		if (chi_0 > 90.0f / deg)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_AngleMustBeLT90deg;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = Sigma_chi(chi_0, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}