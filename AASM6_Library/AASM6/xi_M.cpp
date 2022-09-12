#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float xi_M(float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1)
	{
		static unsigned int Length_1_1 = 17; static float Matrix_1_1[][2] = { {-0.80000f, 0.04416f}, {-0.60000f, 0.05000f}, {-0.40000f, 0.06136f}, {-0.20000f, 0.07502f}, {0.00000f, 0.09429f}, {0.20000f, 0.11450f}, {0.40000f, 0.12932f}, {0.60000f, 0.13638f}, {0.80000f, 0.13898f}, {1.00000f, 0.14084f}, {1.20000f, 0.14166f}, {1.40000f, 0.14195f}, {1.60000f, 0.13885f}, {1.80000f, 0.13279f}, {2.00000f, 0.12610f}, {2.20000f, 0.11865f}, {2.40000f, 0.11032f} };
		static unsigned int Length_1_2 = 17; static float Matrix_1_2[][2] = { {-0.80000f, 0.04416f}, {-0.60000f, 0.05000f}, {-0.40000f, 0.06136f}, {-0.20000f, 0.07502f}, {0.00000f, 0.09587f}, {0.20000f, 0.12995f}, {0.40000f, 0.17798f}, {0.60000f, 0.22655f}, {0.80000f, 0.25486f}, {1.00000f, 0.26683f}, {1.20000f, 0.27076f}, {1.40000f, 0.27117f}, {1.60000f, 0.27117f}, {1.80000f, 0.27117f}, {2.00000f, 0.27117f}, {2.20000f, 0.27117f}, {2.40000f, 0.27117f} };
		static unsigned int Length_1_3 = 17; static float Matrix_1_3[][2] = { {-0.80000f, 0.04416f}, {-0.60000f, 0.05000f}, {-0.40000f, 0.06136f}, {-0.20000f, 0.07502f}, {0.00000f, 0.09587f}, {0.20000f, 0.12995f}, {0.40000f, 0.17933f}, {0.60000f, 0.24920f}, {0.80000f, 0.32894f}, {1.00000f, 0.40313f}, {1.20000f, 0.45236f}, {1.40000f, 0.48477f}, {1.60000f, 0.50706f}, {1.80000f, 0.52532f}, {2.00000f, 0.53813f}, {2.20000f, 0.54707f}, {2.40000f, 0.55428f} };
		static unsigned int Length_1_4 = 17; static float Matrix_1_4[][2] = { {-0.80000f, 0.04416f}, {-0.60000f, 0.05000f}, {-0.40000f, 0.06136f}, {-0.20000f, 0.07502f}, {0.00000f, 0.09587f}, {0.20000f, 0.12995f}, {0.40000f, 0.17933f}, {0.60000f, 0.24920f}, {0.80000f, 0.32894f}, {1.00000f, 0.41086f}, {1.20000f, 0.48345f}, {1.40000f, 0.53997f}, {1.60000f, 0.57829f}, {1.80000f, 0.60605f}, {2.00000f, 0.62826f}, {2.20000f, 0.64724f}, {2.40000f, 0.66621f} };
		static unsigned int Length_1_5 = 17; static float Matrix_1_5[][2] = { {-0.80000f, 0.04416f}, {-0.60000f, 0.05000f}, {-0.40000f, 0.06136f}, {-0.20000f, 0.07502f}, {0.00000f, 0.09587f}, {0.20000f, 0.12995f}, {0.40000f, 0.17933f}, {0.60000f, 0.24920f}, {0.80000f, 0.32894f}, {1.00000f, 0.41231f}, {1.20000f, 0.49421f}, {1.40000f, 0.55993f}, {1.60000f, 0.61493f}, {1.80000f, 0.65809f}, {2.00000f, 0.69268f}, {2.20000f, 0.72007f}, {2.40000f, 0.74401f} };

		//Значения по комплексу x2
		const float x2_min = 0.5f;
		const float x2_2 = 1.0f;
		const float x2_3 = 2.0f;
		const float x2_4 = 3.0f;
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
		const float x1_min = -0.6f;
		const float x1_max = 2.4f;

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
		else if (x2_3 <= x2 && x2 < x2_4) {
			float y1 = Linterp(Matrix_1_3, Length_1_3, x1);
			float y2 = Linterp(Matrix_1_4, Length_1_4, x1);

			return LinterpOnce(x2_3, y1, x2_4, y2, x2);
		}
		else if (x2_4 <= x2 && x2 < x2_max) {
			float y1 = Linterp(Matrix_1_4, Length_1_4, x1);
			float y2 = Linterp(Matrix_1_5, Length_1_5, x1);

			return LinterpOnce(x2_4, y1, x2_max, y2, x2);
		}
		else if (x2 == x2_max) {
			float y = Linterp(Matrix_1_5, Length_1_5, x1);

			return y;
		}
		else
			return NAN;
	}

	ErrorCode* get_xi_M(float& Result, float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1)
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
		Result = xi_M(M, lambda_nos, lambda_cil, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}