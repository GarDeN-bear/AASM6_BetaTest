#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float xi_D(float DD, InputComplex& x_1)
	{
		static unsigned int Length_1_1 = 17; static float Matrix_1_1[][2] = { {0.00000f, 0.00000f}, {0.00940f, 0.01601f}, {0.03395f, 0.02297f}, {0.05964f, 0.02725f}, {0.08891f, 0.03022f}, {0.13212f, 0.03226f}, {0.18733f, 0.03313f}, {0.24014f, 0.03313f}, {0.30735f, 0.03163f}, {0.38337f, 0.02923f}, {0.45010f, 0.02670f}, {0.51511f, 0.02348f}, {0.57051f, 0.02057f}, {0.65239f, 0.01651f}, {0.74759f, 0.01175f}, {0.84417f, 0.00708f}, {1.00000f, 0.00000f} };
				
		//Входной комплекс x1
		const float x1_min = 0.0f;
		const float x1_max = +1.0f;

		//Координата по оси х графика
		float x1 = DD;

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

	ErrorCode* get_xi_D(float& Result, float DD, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (DD < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Проверка: некоторые аргументы не должны быть больше 1		
		if (DD > 1.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_ArgMustNotBeGT1;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = xi_D(DD, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}