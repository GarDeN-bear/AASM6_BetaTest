#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float TTr_TTsl(float M, float key, InputComplex& x_1)
	{
		static unsigned int Length_1_1 = 14; static float Matrix_1_1[][2] = { {0.00000f, 1.00000f}, {0.19895f, 1.04663f}, {0.51622f, 1.07884f}, {0.82727f, 1.14853f}, {1.08638f, 1.24251f}, {1.34549f, 1.34824f}, {1.83181f, 1.60243f}, {2.29696f, 1.92625f}, {2.84095f, 2.38908f}, {3.29869f, 2.84235f}, {3.74151f, 3.35091f}, {4.16723f, 3.88963f}, {4.62634f, 4.51927f}, {5.00000f, 5.08574f} };
		static unsigned int Length_1_2 = 15; static float Matrix_1_2[][2] = { {0.00000f, 0.00000f}, {1.00000f, 0.00000f}, {1.04281f, 0.28550f}, {1.12896f, 0.56007f}, {1.25854f, 0.76465f}, {1.43364f, 0.96358f}, {1.62802f, 1.11870f}, {1.83004f, 1.23792f}, {2.20260f, 1.41451f}, {2.54186f, 1.54606f}, {3.00338f, 1.69432f}, {3.57451f, 1.84487f}, {3.88698f, 1.91426f}, {4.46280f, 2.00966f}, {5.00000f, 2.08772f} };

		//Входной комплекс x1
		const float x1_min = 0.0f;
		const float x1_max = 5.0f;

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
		if (abs(key - 0.0f) < 1e-5)
			return Linterp(Matrix_1_2, Length_1_2, x1) / Linterp(Matrix_1_1, Length_1_1, x1);		
		else if (abs(key - 1.0f) < 1e-5)
			return Linterp(Matrix_1_1, Length_1_1, x1);		
		else if (abs(key - 2.0f) < 1e-5)
			return Linterp(Matrix_1_2, Length_1_2, x1);
		else
			return NAN;
	}

	ErrorCode* get_TTr_TTsl(float& Result, float M, float key, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (M < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (key < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Проверка: некоторые аргументы должны быть 0, 1 или 2	
		if (!(abs(key - 0.0f) < 1e-5) && !(abs(key - 1.0f) < 1e-5) && !(abs(key - 2.0f) < 1e-5))
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_ArgMustBe01or2;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = TTr_TTsl(M, key, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}