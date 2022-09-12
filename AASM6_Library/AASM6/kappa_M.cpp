#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float kappa_M(float M, InputComplex& x_1)
	{		
		static unsigned int Length_1_1 = 21; static float Matrix_1_1[][2] = { {0.00000f, 1.00000f}, {1.00000f, 1.00000f}, {1.20000f, 1.00000f}, {1.40000f, 1.00000f}, {1.53100f, 1.00000f}, {1.60000f, 0.99639f}, {1.80000f, 0.97909f}, {2.00000f, 0.95772f}, {2.20000f, 0.93558f}, {2.40000f, 0.91344f}, {2.60000f, 0.89487f}, {2.80000f, 0.88240f}, {3.00000f, 0.87324f}, {3.20000f, 0.86638f}, {3.40000f, 0.86100f}, {3.60000f, 0.85700f}, {3.80000f, 0.85400f}, {4.00000f, 0.85200f}, {4.20000f, 0.85100f}, {4.40000f, 0.8505f}, {4.60000f, 0.85000f} };

		//Входной комплекс x1
		const float x1_min = 0.0f;
		const float x1_max = 4.6f;

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

	ErrorCode* get_kappa_M(float& Result, float M, InputComplex& x_1)
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
		Result = kappa_M(M, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}