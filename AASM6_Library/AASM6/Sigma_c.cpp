#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Sigma_c(float cc, float xx_t, InputComplex& x_2, InputComplex& x_1) 
	{
		static unsigned int Length_1_1 = 9; static float Matrix_1_1[][2] = { {0.00000f, 1.00000f}, {0.01564f, 1.03821f}, {0.03437f, 1.08642f}, {0.05091f, 1.13161f}, {0.06614f, 1.17552f}, {0.08268f, 1.22545f}, {0.09914f, 1.28011f}, {0.11191f, 1.32789f}, {0.12000f, 1.36252f} };
		static unsigned int Length_1_2 = 9; static float Matrix_1_2[][2] = { {0.00000f, 1.00000f}, {0.01626f, 1.03180f}, {0.02943f, 1.05957f}, {0.04009f, 1.08255f}, {0.06021f, 1.12760f}, {0.07035f, 1.15211f}, {0.08986f, 1.20173f}, {0.09850f, 1.22534f}, {0.12000f, 1.29104f} };
		static unsigned int Length_1_3 = 9; static float Matrix_1_3[][2] = { {0.00000f, 1.00000f}, {0.01953f, 1.02460f}, {0.03582f, 1.04627f}, {0.05363f, 1.07300f}, {0.06977f, 1.09756f}, {0.08588f, 1.12386f}, {0.09803f, 1.14539f}, {0.10928f, 1.16631f}, {0.12000f, 1.18873f} };

		//Значения по комплексу x2
		const float x2_min = 0.0f;
		const float x2_2 = 0.2f;
		const float x2_max = 0.4f;

		//Входной комплекс x2
		float x2 = xx_t;

		x_2.Min = x2_min;
		x_2.Value = x2;
		x_2.Max = x2_max;

		//Ограничение по диапазону x2
		if (x2 < x2_min)
			x2 = x2_min;
		else if (x2 > x2_max)
			x2 = x2_max;

		//Входной комплекс x1
		const float x1_min = 0.0f;
		const float x1_max = 1.2f;

		//Координата по оси х графика
		float x1 = cc;

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
		else if (x2_2 <= x2 && x2 < x2_max) {
			float y1 = Linterp(Matrix_1_2, Length_1_2, x1);
			float y2 = Linterp(Matrix_1_3, Length_1_3, x1);

			return LinterpOnce(x2_2, y1, x2_max, y2, x2);
		}
		else if (x2 == x2_max) {
			float y = Linterp(Matrix_1_3, Length_1_3, x1);

			return y;
		}
		else
			return NAN;
	}

	ErrorCode* get_Sigma_c(float& Result, float cc, float xx_t, InputComplex& x_2, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (cc < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (xx_t < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Проверка: некоторые аргументы не должны быть больше 1		
		if (xx_t > 1.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_ArgMustNotBeGT1;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = Sigma_c(cc, xx_t, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}