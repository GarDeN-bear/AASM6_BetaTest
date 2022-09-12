#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Cyalf_ConCil(float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1)
	{
		static unsigned int Length_1_1 = 18; static float Matrix_1_1[][2] = { {-0.80000f, 0.03526f}, {-0.60000f, 0.03526f}, {-0.40000f, 0.03520f}, {-0.20000f, 0.03473f}, {0.00000f, 0.03415f}, {0.20000f, 0.03378f}, {0.40000f, 0.03356f}, {0.60000f, 0.03301f}, {0.80000f, 0.03270f}, {1.00000f, 0.03251f}, {1.20000f, 0.03244f}, {1.40000f, 0.03241f}, {1.60000f, 0.03243f}, {1.80000f, 0.03238f}, {2.00000f, 0.03238f}, {2.20000f, 0.03233f}, {2.40000f, 0.03229f}, {2.60000f, 0.03230f} };
		static unsigned int Length_1_2 = 18; static float Matrix_1_2[][2] = { {-0.80000f, 0.03526f}, {-0.60000f, 0.03526f}, {-0.40000f, 0.03538f}, {-0.20000f, 0.03593f}, {0.00000f, 0.03837f}, {0.20000f, 0.04247f}, {0.40000f, 0.04557f}, {0.60000f, 0.04666f}, {0.80000f, 0.04620f}, {1.00000f, 0.04507f}, {1.20000f, 0.04380f}, {1.40000f, 0.04284f}, {1.60000f, 0.04190f}, {1.80000f, 0.04109f}, {2.00000f, 0.04046f}, {2.20000f, 0.04008f}, {2.40000f, 0.03979f}, {2.60000f, 0.03952f} };
		static unsigned int Length_1_3 = 18; static float Matrix_1_3[][2] = { {-0.80000f, 0.03526f}, {-0.60000f, 0.03526f}, {-0.40000f, 0.03538f}, {-0.20000f, 0.03593f}, {0.00000f, 0.03837f}, {0.20000f, 0.04314f}, {0.40000f, 0.04790f}, {0.60000f, 0.05067f}, {0.80000f, 0.05156f}, {1.00000f, 0.05097f}, {1.20000f, 0.05014f}, {1.40000f, 0.04918f}, {1.60000f, 0.04830f}, {1.80000f, 0.04745f}, {2.00000f, 0.04674f}, {2.20000f, 0.04605f}, {2.40000f, 0.04549f}, {2.60000f, 0.04517f} };
		static unsigned int Length_1_4 = 18; static float Matrix_1_4[][2] = { {-0.80000f, 0.03526f}, {-0.60000f, 0.03526f}, {-0.40000f, 0.03538f}, {-0.20000f, 0.03593f}, {0.00000f, 0.03837f}, {0.20000f, 0.04314f}, {0.40000f, 0.04813f}, {0.60000f, 0.05190f}, {0.80000f, 0.05456f}, {1.00000f, 0.05599f}, {1.20000f, 0.05658f}, {1.40000f, 0.05642f}, {1.60000f, 0.05591f}, {1.80000f, 0.05523f}, {2.00000f, 0.05463f}, {2.20000f, 0.05409f}, {2.40000f, 0.05338f}, {2.60000f, 0.05267f} };
		static unsigned int Length_1_5 = 18; static float Matrix_1_5[][2] = { {-0.80000f, 0.03526f}, {-0.60000f, 0.03526f}, {-0.40000f, 0.03538f}, {-0.20000f, 0.03593f}, {0.00000f, 0.03837f}, {0.20000f, 0.04314f}, {0.40000f, 0.04813f}, {0.60000f, 0.05199f}, {0.80000f, 0.05504f}, {1.00000f, 0.05720f}, {1.20000f, 0.05817f}, {1.40000f, 0.05883f}, {1.60000f, 0.05901f}, {1.80000f, 0.05893f}, {2.00000f, 0.05868f}, {2.20000f, 0.05837f}, {2.40000f, 0.05803f}, {2.60000f, 0.05751f} };
		static unsigned int Length_1_6 = 18; static float Matrix_1_6[][2] = { {-0.80000f, 0.03526f}, {-0.60000f, 0.03526f}, {-0.40000f, 0.03538f}, {-0.20000f, 0.03593f}, {0.00000f, 0.03837f}, {0.20000f, 0.04314f}, {0.40000f, 0.04813f}, {0.60000f, 0.05199f}, {0.80000f, 0.05504f}, {1.00000f, 0.05733f}, {1.20000f, 0.05877f}, {1.40000f, 0.05978f}, {1.60000f, 0.06026f}, {1.80000f, 0.06000f}, {2.00000f, 0.06000f}, {2.20000f, 0.06000f}, {2.40000f, 0.06000f}, {2.60000f, 0.06000f} };

		//Значения по комплексу x2
		const float x2_min = 0.0f;
		const float x2_2 = 0.5f;
		const float x2_3 = 1.0f;
		const float x2_4 = 2.0f;
		const float x2_5 = 3.0f;
		const float x2_max = 4.0f;

		//Входной комплекс x2
		float x2 = lambda_cil / lambda_nos;

		x_2.Min = x2_min;
		x_2.Value = x2;
		x_2.Max = x2_max;

		//Ограничение по диапазону x2
		if (x2 < x2_min)
			x2 = x2_min;
		else if (x2 > x2_max)
			x2 = x2_max;

		//Входной комплекс x1
		const float x1_min = -0.8f;
		const float x1_max = +2.6f;

		//Координата по оси х графика
		float x1;

		if (M >= 1)
			x1 = +sqrt(sqr(M) - 1.0f) / lambda_nos;
		else
			x1 = -sqrt(1.0f - sqr(M)) / lambda_nos;

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

			return y * deg;

		}
		else if (x2_min <= x2 && x2 < x2_2) {
			float y1 = Linterp(Matrix_1_1, Length_1_1, x1);
			float y2 = Linterp(Matrix_1_2, Length_1_2, x1);

			return LinterpOnce(x2_min, y1, x2_2, y2, x2) * deg;

		}
		else if (x2_2 <= x2 && x2 < x2_3) {
			float y1 = Linterp(Matrix_1_2, Length_1_2, x1);
			float y2 = Linterp(Matrix_1_3, Length_1_3, x1);

			return LinterpOnce(x2_2, y1, x2_3, y2, x2) * deg;

		}
		else if (x2_3 <= x2 && x2 < x2_4) {
			float y1 = Linterp(Matrix_1_3, Length_1_3, x1);
			float y2 = Linterp(Matrix_1_4, Length_1_4, x1);

			return LinterpOnce(x2_3, y1, x2_4, y2, x2) * deg;

		}
		else if (x2_4 <= x2 && x2 < x2_5) {
			float y1 = Linterp(Matrix_1_4, Length_1_4, x1);
			float y2 = Linterp(Matrix_1_5, Length_1_5, x1);

			return LinterpOnce(x2_4, y1, x2_5, y2, x2) * deg;

		}
		else if (x2_5 <= x2 && x2 < x2_max) {
			float y1 = Linterp(Matrix_1_5, Length_1_5, x1);
			float y2 = Linterp(Matrix_1_6, Length_1_6, x1);

			return LinterpOnce(x2_5, y1, x2_max, y2, x2) * deg;

		}
		else if (x2 == x2_max) {
			float y = Linterp(Matrix_1_6, Length_1_6, x1);

			return y * deg;
		}
		else
			return NAN;
	}


	ErrorCode* get_Cyalf_ConCil(float& Result, float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1)
	{		
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (M < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}			
		if (lambda_nos < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}			
		if (lambda_cil < 0.0f)
		{
			ErrC.ArgNumber = 3;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}			
		
		// Вызываем функцию интерполяции графика
		Result = Cyalf_ConCil(M, lambda_nos, lambda_cil, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}