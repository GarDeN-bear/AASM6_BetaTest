#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Sigma_M(float M, float xx_t, InputComplex& x_2, InputComplex& x_1)
	{		
		static unsigned int Length_1_1 = 27; static float Matrix_1_1[][2] = { {0.00000f, 1.00000f}, {0.49399f, 0.96952f}, {0.69322f, 0.95396f}, {0.87954f, 0.93476f}, {1.04726f, 0.91363f}, {1.20648f, 0.89073f}, {1.36025f, 0.86701f}, {1.50002f, 0.84586f}, {1.64844f, 0.82182f}, {1.78423f, 0.80066f}, {1.93787f, 0.77837f}, {2.11636f, 0.75216f}, {2.31868f, 0.72227f}, {2.54054f, 0.69141f}, {2.74352f, 0.66424f}, {2.96375f, 0.63703f}, {3.18995f, 0.60945f}, {3.41240f, 0.58234f}, {3.63695f, 0.55628f}, {3.86864f, 0.52933f}, {4.14096f, 0.50088f}, {4.41781f, 0.47307f}, {4.68827f, 0.44893f}, {4.97398f, 0.42498f}, {5.30835f, 0.40369f}, {5.54674f, 0.38999f}, {6.00000f, 0.36873f} };
		static unsigned int Length_1_2 = 19; static float Matrix_1_2[][2] = { {0.00000f, 1.00000f}, {0.56989f, 0.96826f}, {0.77123f, 0.95103f}, {0.96313f, 0.92997f}, {1.13984f, 0.90737f}, {1.39912f, 0.86821f}, {1.65871f, 0.83053f}, {1.97949f, 0.78320f}, {2.28613f, 0.74058f}, {2.59020f, 0.69656f}, {2.97076f, 0.64758f}, {3.27033f, 0.61106f}, {3.66954f, 0.56399f}, {3.98925f, 0.52683f}, {4.41781f, 0.48561f}, {4.80866f, 0.45202f}, {5.22265f, 0.42009f}, {5.53122f, 0.40266f}, {6.00000f, 0.37970f} };
		static unsigned int Length_1_3 = 20; static float Matrix_1_3[][2] = { {0.00000f, 1.00000f}, {0.37680f, 0.98332f}, {0.60011f, 0.96952f}, {0.82623f, 0.95103f}, {1.09647f, 0.92042f}, {1.35517f, 0.88566f}, {1.63014f, 0.84876f}, {1.84099f, 0.82117f}, {2.11636f, 0.78103f}, {2.37928f, 0.74655f}, {2.67049f, 0.70863f}, {2.93984f, 0.67530f}, {3.34869f, 0.62708f}, {3.69992f, 0.58656f}, {4.06326f, 0.54991f}, {4.43354f, 0.51663f}, {4.79919f, 0.48732f}, {5.19184f, 0.46151f}, {5.52124f, 0.44396f}, {6.00000f, 0.42225f} };
		static unsigned int Length_1_4 = 18; static float Matrix_1_4[][2] = { {0.00000f, 1.00000f}, {0.28623f, 0.98993f}, {0.52010f, 0.97736f}, {0.80616f, 0.95802f}, {1.05880f, 0.93169f}, {1.30761f, 0.90269f}, {1.54943f, 0.87125f}, {1.82116f, 0.83821f}, {2.09036f, 0.80066f}, {2.37000f, 0.76514f}, {2.63977f, 0.73175f}, {2.95143f, 0.69286f}, {3.43521f, 0.63682f}, {3.85944f, 0.59209f}, {4.37286f, 0.54766f}, {4.82003f, 0.51440f}, {5.28674f, 0.48732f}, {6.00000f, 0.46203f} };
		static unsigned int Length_1_5 = 19; static float Matrix_1_5[][2] = { {0.00000f, 1.00000f}, {0.42174f, 0.98819f}, {0.66653f, 0.97535f}, {0.92635f, 0.95697f}, {1.19152f, 0.93356f}, {1.46830f, 0.90737f}, {1.70701f, 0.87945f}, {1.93907f, 0.85503f}, {2.22964f, 0.82182f}, {2.48678f, 0.79141f}, {2.78249f, 0.76215f}, {3.07370f, 0.73136f}, {3.41441f, 0.69752f}, {3.73969f, 0.67054f}, {4.07075f, 0.64535f}, {4.51560f, 0.61622f}, {4.88213f, 0.59202f}, {5.43477f, 0.55886f}, {6.00000f, 0.53446f} };
		static unsigned int Length_1_6 = 13; static float Matrix_1_6[][2] = { {0.00000f, 1.00000f}, {0.73137f, 0.99391f}, {1.26364f, 0.98627f}, {1.68974f, 0.97867f}, {2.18295f, 0.96416f}, {2.60841f, 0.95030f}, {3.16716f, 0.92854f}, {3.59816f, 0.91139f}, {4.10915f, 0.88809f}, {4.57126f, 0.86610f}, {5.13779f, 0.84258f}, {5.60545f, 0.82653f}, {6.00000f, 0.81268f} };

		//Значения по комплексу x2
		const float x2_min = 0.0f;
		const float x2_2 = 0.2f;
		const float x2_3 = 0.5f;
		const float x2_4 = 0.6f;
		const float x2_5 = 0.8f;
		const float x2_max = 1.0f;

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
		const float x1_max = 6.0f;

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
		else if (x2_4 <= x2 && x2 < x2_5) {
			float y1 = Linterp(Matrix_1_4, Length_1_4, x1);
			float y2 = Linterp(Matrix_1_5, Length_1_5, x1);

			return LinterpOnce(x2_4, y1, x2_5, y2, x2);
		}
		else if (x2_5 <= x2 && x2 < x2_max) {
			float y1 = Linterp(Matrix_1_5, Length_1_5, x1);
			float y2 = Linterp(Matrix_1_6, Length_1_6, x1);

			return LinterpOnce(x2_5, y1, x2_max, y2, x2);
		}
		else if (x2 == x2_max) {
			float y = Linterp(Matrix_1_6, Length_1_6, x1);

			return y;
		}
		else
			return NAN;
	}

	ErrorCode* get_Sigma_M(float& Result, float M, float xx_t, InputComplex& x_2, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (M < 0.0f)
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
		Result = Sigma_M(M, xx_t, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}