#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float DELTA_Mcr0_lambda(float Mcr_pr0, float lambda_c, InputComplex& x_2, InputComplex& x_1)
	{
		static unsigned int Length_1_1 = 13; static float Matrix_1_1[][2] = { {0.70000f, 0.074182f}, {0.73153f, 0.071007f}, {0.79680f, 0.063225f}, {0.84840f, 0.054858f}, {0.87500f, 0.049526f}, {0.89928f, 0.043588f}, {0.93341f, 0.032934f}, {0.95254f, 0.025538f}, {0.96604f, 0.019333f}, {0.97512f, 0.014816f}, {0.98373f, 0.009947f}, {0.99293f, 0.004411f}, {1.00000f, 0.000000f} };
		static unsigned int Length_1_2 = 12; static float Matrix_1_2[][2] = { {0.70000f, 0.031507f}, {0.73082f, 0.031050f}, {0.75855f, 0.030502f}, {0.79741f, 0.029100f}, {0.84695f, 0.026113f}, {0.89232f, 0.022090f}, {0.93366f, 0.016666f}, {0.95998f, 0.011667f}, {0.97484f, 0.008226f}, {0.98446f, 0.005700f}, {0.98967f, 0.003895f}, {1.00000f, 0.000000f} };
		static unsigned int Length_1_3 = 7; static float Matrix_1_3[][2] = { {0.70000f, 0.008044f}, {0.74953f, 0.008044f}, {0.89960f, 0.007090f}, {0.94156f, 0.005749f}, {0.96128f, 0.004585f}, {0.98373f, 0.002675f}, {1.00000f, 0.000000f} };

		//Значения по комплексу x2
		const float x2_min = 0.5f;
		const float x2_2 = 1.0f;
		const float x2_3 = 2.0f;
		const float x2_max = 100.0f;

		//Входной комплекс x2
		float x2 = lambda_c;

		x_2.Min = x2_min;
		x_2.Value = x2;
		x_2.Max = x2_max;

		//Ограничение по диапазону x2
		if (x2 < x2_min)
			x2 = x2_min;
		else if (x2 > x2_max)
			x2 = x2_max;

		//Входной комплекс x1
		const float x1_min = 0.7f;
		const float x1_max = 1.0f;

		//Координата по оси х графика
		float x1 = Mcr_pr0;

		x_1.Min = x1_min;
		x_1.Value = x1;
		x_1.Max = x1_max;

		//Ограничение по диапазону оси x
		if (x1 < x1_min)
			x1 = x1_min;
		else if (x1 > x1_max)
			x1 = x1_max;

		//Вычисление
		if (x2 == x2_min) {
			float y = Linterp(Matrix_1_1, Length_1_1, x1);

			return y;
		}
		else if (x2_min <= x2 && x2 < x2_2) {
			float y1 = Linterp(Matrix_1_1, Length_1_1, x1);
			float y2 = Linterp(Matrix_1_2, Length_1_2, x1);

			return LinterpOnce(x2_min, y1, x2_2, y2, x2);
		}
		else if (x2_2 <= x2 && x2 < x2_3) {
			float y1 = Linterp(Matrix_1_2, Length_1_2, x1);
			float y2 = Linterp(Matrix_1_3, Length_1_3, x1);

			return LinterpOnce(x2_2, y1, x2_3, y2, x2);
		}
		else if (x2_3 <= x2 && x2 < x2_max) {
			float y1 = Linterp(Matrix_1_3, Length_1_3, x1);
			float y2 = 0.0f;

			return LinterpOnce(x2_2, y1, x2_max, y2, x2);
		}
		else if (x2 == x2_max) {
			float y = 0.0f;

			return y;
		}
		else
			return NAN;
	}

	ErrorCode* get_DELTA_Mcr0_lambda(float& Result, float Mcr_pr0, float lambda_c, InputComplex& x_2, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (Mcr_pr0 < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (lambda_c < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Проверка: некоторые аргументы не должны быть больше 1		
		if (Mcr_pr0 > 1.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_ArgMustNotBeGT1;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = DELTA_Mcr0_lambda(Mcr_pr0, lambda_c, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}