#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float DELTA_Mcr0_chi(float Mcr_pr0, float chi_c, InputComplex& x_2, InputComplex& x_1)
	{		
		static unsigned int Length_1_1 = 7; static float Matrix_1_1[][2] = { {0.70000f, 0.01272f}, {0.75239f, 0.01260f}, {0.80215f, 0.01260f}, {0.85080f, 0.01183f}, {0.90122f, 0.01012f}, {0.94854f, 0.00654f}, {1.00000f, 0.00000f} };
		static unsigned int Length_1_2 = 10; static float Matrix_1_2[][2] = { {0.70000f, 0.04512f}, {0.75121f, 0.04365f}, {0.80086f, 0.04064f}, {0.85492f, 0.03575f}, {0.89106f, 0.03023f}, {0.91868f, 0.02563f}, {0.94564f, 0.01929f}, {0.96539f, 0.01349f}, {0.97998f, 0.00873f}, {1.00000f, 0.00000f} };
		static unsigned int Length_1_3 = 16; static float Matrix_1_3[][2] = { {0.70000f, 0.09231f}, {0.72417f, 0.08981f}, {0.75156f, 0.08638f}, {0.78190f, 0.08183f}, {0.80781f, 0.07699f}, {0.83557f, 0.07157f}, {0.85832f, 0.06603f}, {0.87664f, 0.06102f}, {0.89696f, 0.05507f}, {0.91542f, 0.04813f}, {0.93131f, 0.04206f}, {0.94862f, 0.03361f}, {0.96050f, 0.02702f}, {0.97267f, 0.01929f}, {0.98342f, 0.01180f}, {1.00000f, 0.00000f} };
		static unsigned int Length_1_4 = 19; static float Matrix_1_4[][2] = { {0.70000f, 0.15696f}, {0.73632f, 0.14430f}, {0.76533f, 0.13398f}, {0.78932f, 0.12511f}, {0.81034f, 0.11746f}, {0.83359f, 0.10839f}, {0.85691f, 0.09825f}, {0.87983f, 0.08834f}, {0.89517f, 0.08127f}, {0.91075f, 0.07286f}, {0.92037f, 0.06741f}, {0.92816f, 0.06258f}, {0.93746f, 0.05669f}, {0.95005f, 0.04813f}, {0.96015f, 0.04131f}, {0.96974f, 0.03361f}, {0.97878f, 0.02465f}, {0.98711f, 0.01605f}, {1.00000f, 0.00000f} };

		//Значения по комплексу x2
		const float x2_min = 0.0f;
		const float x2_2 = 15.0f;
		const float x2_3 = 30.0f;
		const float x2_4 = 45.0f;
		const float x2_max = 60.0f;

		//Входной комплекс x2
		float x2 = chi_c * deg;

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
			return 0.0f;
		}
		else if (x2_min <= x2 && x2 < x2_2) {
			float y1 = 0.0f;
			float y2 = Linterp(Matrix_1_1, Length_1_1, x1);

			return LinterpOnce(x2_min, y1, x2_2, y2, x2);
		}
		else if (x2_2 <= x2 && x2 < x2_3) {
			float y1 = Linterp(Matrix_1_1, Length_1_1, x1);
			float y2 = Linterp(Matrix_1_2, Length_1_2, x1);

			return LinterpOnce(x2_2, y1, x2_3, y2, x2);
		}
		else if (x2_3 <= x2 && x2 < x2_4) {
			float y1 = Linterp(Matrix_1_2, Length_1_2, x1);
			float y2 = Linterp(Matrix_1_3, Length_1_3, x1);

			return LinterpOnce(x2_3, y1, x2_4, y2, x2);
		}
		else if (x2_4 <= x2 && x2 < x2_max) {
			float y1 = Linterp(Matrix_1_3, Length_1_3, x1);
			float y2 = Linterp(Matrix_1_4, Length_1_4, x1);

			return LinterpOnce(x2_4, y1, x2_max, y2, x2);
		}
		else if (x2 == x2_max) {
			float y = Linterp(Matrix_1_4, Length_1_4, x1);

			return y;
		}
		else
			return NAN;
	}

	ErrorCode* get_DELTA_Mcr0_chi(float& Result, float Mcr_pr0, float chi_c, InputComplex& x_2, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (Mcr_pr0 < 0.0f)
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

		// Проверка: некоторые аргументы не должны быть больше 1		
		if (Mcr_pr0 > 1.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_ArgMustNotBeGT1;
			return &ErrC;
		}

		// Проверка: некоторые аргументы не должны быть больше 90 градусов	
		if (chi_c > 90.0f / deg)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_AngleMustBeLT90deg;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = DELTA_Mcr0_chi(Mcr_pr0, chi_c, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}