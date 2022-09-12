#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Sigma_pw(float M, float chi_c, InputComplex& x_1)
	{
		static unsigned int Length_1_1 = 25; static float Matrix_1_1[][2] = { {0.00000f, 0.00000f}, {0.25000f, 0.05897f}, {0.50000f, 0.20000f}, {0.75000f, 0.37650f}, {1.00000f, 0.54180f}, {1.25000f, 0.66795f}, {1.50000f, 0.77216f}, {1.75000f, 0.85230f}, {2.00000f, 0.91325f}, {2.25000f, 0.95542f}, {2.50000f, 0.97966f}, {2.75000f, 0.98634f}, {3.00000f, 0.98937f}, {3.25000f, 0.99149f}, {3.50000f, 0.99301f}, {3.75000f, 0.99467f}, {4.00000f, 0.99651f}, {4.25000f, 0.99704f}, {4.50000f, 0.99767f}, {4.75000f, 0.99767f}, {5.00000f, 0.99807f}, {5.25000f, 0.99807f}, {5.50000f, 0.99857f}, {5.75000f, 0.99857f}, {6.00000f, 1.00000f} };

		//Входной комплекс x1
		const float x1_min = 0.0f;
		const float x1_max = 6.0f;

		//Координата по оси х графика
		float x1;

		if (M < 1.0) {
			x1 = 0.0f;
		}
		else {
			x1 = sqrt(sqr(M) - 1.0f) - tan(chi_c);
		}

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

	ErrorCode* get_Sigma_pw(float& Result, float M, float chi_c, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (M < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (chi_c < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Проверка: некоторые аргументы не должны быть меньше 1	
		if (M < 1.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_ArgMustNotBeLT1;
			return &ErrC;
		}

		// Проверка: некоторые аргументы не должны быть больше 90 градусов	
		if (chi_c > 90.0f / deg)
		{
			ErrC.ArgNumber = 4;
			ErrC.Code = ErrC_AngleMustBeLT90deg;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = Sigma_pw(M, chi_c, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}