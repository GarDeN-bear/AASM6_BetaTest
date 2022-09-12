#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Cyalf_OgiCil(float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1)
	{
		static unsigned int Length_1_1 = 16; static float Matrix_1_1[][2] = { {-0.80000f, 0.03523f}, {-0.60000f, 0.03523f}, {-0.40000f, 0.03523f}, {-0.20000f, 0.03534f}, {0.00000f, 0.03617f}, {0.20000f, 0.03779f}, {0.40000f, 0.03829f}, {0.60000f, 0.03827f}, {0.80000f, 0.03769f}, {1.00000f, 0.03670f}, {1.20000f, 0.03533f}, {1.40000f, 0.03391f}, {1.60000f, 0.03272f}, {1.80000f, 0.03177f}, {2.00000f, 0.03092f}, {2.20000f, 0.03014f} };
		static unsigned int Length_1_2 = 16; static float Matrix_1_2[][2] = { {-0.80000f, 0.03523f}, {-0.60000f, 0.03523f}, {-0.40000f, 0.03523f}, {-0.20000f, 0.03559f}, {0.00000f, 0.03743f}, {0.20000f, 0.04085f}, {0.40000f, 0.04440f}, {0.60000f, 0.04738f}, {0.80000f, 0.04880f}, {1.00000f, 0.04804f}, {1.20000f, 0.04615f}, {1.40000f, 0.04368f}, {1.60000f, 0.04134f}, {1.80000f, 0.03936f}, {2.00000f, 0.03771f}, {2.20000f, 0.03637f} };
		static unsigned int Length_1_3 = 16; static float Matrix_1_3[][2] = { {-0.80000f, 0.03523f}, {-0.60000f, 0.03523f}, {-0.40000f, 0.03523f}, {-0.20000f, 0.03559f}, {0.00000f, 0.03743f}, {0.20000f, 0.04104f}, {0.40000f, 0.04573f}, {0.60000f, 0.04929f}, {0.80000f, 0.05148f}, {1.00000f, 0.05219f}, {1.20000f, 0.05135f}, {1.40000f, 0.04917f}, {1.60000f, 0.04662f}, {1.80000f, 0.04443f}, {2.00000f, 0.04256f}, {2.20000f, 0.04107f} };
		static unsigned int Length_1_4 = 16; static float Matrix_1_4[][2] = { {-0.80000f, 0.03523f}, {-0.60000f, 0.03523f}, {-0.40000f, 0.03523f}, {-0.20000f, 0.03559f}, {0.00000f, 0.03743f}, {0.20000f, 0.04104f}, {0.40000f, 0.04605f}, {0.60000f, 0.05061f}, {0.80000f, 0.05410f}, {1.00000f, 0.05604f}, {1.20000f, 0.05573f}, {1.40000f, 0.05376f}, {1.60000f, 0.05151f}, {1.80000f, 0.04942f}, {2.00000f, 0.04753f}, {2.20000f, 0.04598f} };
		static unsigned int Length_1_5 = 16; static float Matrix_1_5[][2] = { {-0.80000f, 0.03523f}, {-0.60000f, 0.03523f}, {-0.40000f, 0.03523f}, {-0.20000f, 0.03559f}, {0.00000f, 0.03743f}, {0.20000f, 0.04104f}, {0.40000f, 0.04619f}, {0.60000f, 0.05123f}, {0.80000f, 0.05495f}, {1.00000f, 0.05703f}, {1.20000f, 0.05713f}, {1.40000f, 0.05609f}, {1.60000f, 0.05437f}, {1.80000f, 0.05260f}, {2.00000f, 0.05068f}, {2.20000f, 0.04877f} };

		//Значения по комплексу x2
		const float x2_min = 0.0f;
		const float x2_2 = 0.5f;
		const float x2_3 = 1.0f;
		const float x2_4 = 2.0f;
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
		const float x1_max = +2.2f;

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
		else if (x2_4 <= x2 && x2 < x2_max) {
			float y1 = Linterp(Matrix_1_4, Length_1_4, x1);
			float y2 = Linterp(Matrix_1_5, Length_1_5, x1);

			return LinterpOnce(x2_4, y1, x2_max, y2, x2) * deg;
		}
		else if (x2 == x2_max) {
			float y = Linterp(Matrix_1_5, Length_1_5, x1);

			return y * deg;
		}
		else
			return NAN;
	}

	ErrorCode* get_Cyalf_OgiCil(float& Result, float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1)
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
		Result = Cyalf_OgiCil(M, lambda_nos, lambda_cil, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}
