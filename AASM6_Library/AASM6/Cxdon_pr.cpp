#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Cxdon_pr(float M, InputComplex& x_1)
	{		
		static unsigned int Length_1_1 = 24; static float Matrix_1_1[][2] = { {1.00000f, 0.35000f}, {1.22476f, 0.34952f}, {1.34501f, 0.34322f}, {1.43137f, 0.33223f}, {1.50234f, 0.31819f}, {1.58419f, 0.29944f}, {1.65661f, 0.27747f}, {1.74312f, 0.25666f}, {1.83606f, 0.23719f}, {1.97887f, 0.21462f}, {2.11715f, 0.19448f}, {2.31210f, 0.17346f}, {2.55691f, 0.15089f}, {2.81306f, 0.13408f}, {3.15762f, 0.11483f}, {3.55753f, 0.09670f}, {3.78043f, 0.08832f}, {4.05623f, 0.07855f}, {4.40192f, 0.06914f}, {4.82128f, 0.05826f}, {5.21420f, 0.05089f}, {5.72612f, 0.04388f}, {6.09448f, 0.04001f}, {6.50000f, 0.03669f} };

		//Входной комплекс x1
		const float x1_min = 1.0f;
		const float x1_max = 6.5f;

		//Координата по оси х графика
		float x1 = M;

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

	ErrorCode* get_Cxdon_pr(float& Result, float M, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (M < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = Cxdon_pr(M, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}