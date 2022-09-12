#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Ms_Con(float M, float teta_Con, InputComplex& x_2, InputComplex& x_1)
	{
		static unsigned int Length_1_1 = 11; static float Matrix_1_1[][2] = { {0.00000f, 0.00000f}, {0.62500f, 0.62500f}, {1.25000f, 1.25000f}, {2.50000f, 2.50000f}, {3.75000f, 3.75000f}, {5.00000f, 5.00000f}, {6.25000f, 6.25000f}, {7.50000f, 7.50000f}, {8.75000f, 8.75000f}, {9.37500f, 9.37500f}, {10.00000f, 10.00000f} };
		static unsigned int Length_1_2 = 11; static float Matrix_1_2[][2] = { {0.00000f, 0.00000f}, {1.86758f, 1.73904f}, {2.69765f, 2.56208f}, {3.19710f, 3.07208f}, {3.87551f, 3.71138f}, {4.62004f, 4.43059f}, {5.26835f, 5.03331f}, {6.34716f, 5.97537f}, {7.09676f, 6.59834f}, {8.66686f, 7.83417f}, {10.00000f, 8.69013f} };
		static unsigned int Length_1_3 = 11; static float Matrix_1_3[][2] = { {0.00000f, 0.00000f}, {1.26934f, 1.14311f}, {1.96211f, 1.75000f}, {2.76228f, 2.48276f}, {4.21399f, 3.72703f}, {4.79644f, 4.19299f}, {5.37890f, 4.65896f}, {6.60966f, 5.54024f}, {7.77458f, 6.21893f}, {9.02560f, 6.84191f}, {10.00000f, 7.25723f} };
		static unsigned int Length_1_4 = 11; static float Matrix_1_4[][2] = { {0.00000f, 0.00000f}, {1.27561f, 1.09487f}, {2.03955f, 1.68999f}, {3.03142f, 2.47926f}, {4.01907f, 3.21789f}, {4.96029f, 3.88476f}, {6.00280f, 4.52208f}, {7.12129f, 5.09610f}, {7.96543f, 5.43798f}, {8.92775f, 5.70810f}, {10.00000f, 5.90648f} };
		static unsigned int Length_1_5 = 11; static float Matrix_1_5[][2] = { {0.00000f, 0.00000f}, {1.31083f, 1.06231f}, {2.10094f, 1.59715f}, {3.01869f, 2.21101f}, {3.83920f, 2.71547f}, {4.87243f, 3.24424f}, {5.97252f, 3.70616f}, {7.16377f, 4.08298f}, {8.23954f, 4.36256f}, {9.18161f, 4.49020f}, {10.00000f, 4.54490f} };
		static unsigned int Length_1_6 = 11; static float Matrix_1_6[][2] = { {0.00000f, 0.00000f}, {1.31083f, 0.97439f}, {2.03290f, 1.43866f}, {2.84327f, 1.90408f}, {3.73807f, 2.34612f}, {4.63708f, 2.70488f}, {5.81888f, 3.03409f}, {6.96775f, 3.24836f}, {8.08802f, 3.37089f}, {9.00699f, 3.42340f}, {10.00000f, 3.45841f} };

		//Значения по комплексу x2
		const float x2_min = 0.0f;
		const float x2_2 = 5.0f;
		const float x2_3 = 10.0f;
		const float x2_4 = 15.0f;
		const float x2_5 = 20.0f;
		const float x2_max = 25.0f;

		//Входной комплекс x2
		float x2 = teta_Con * deg;

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
		const float x1_max = 10.0f;

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

	ErrorCode* get_Ms_Con(float& Result, float M, float teta_Con, InputComplex& x_2, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (M < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (teta_Con < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Проверка: некоторые аргументы не должны быть больше 90 градусов	
		if (teta_Con > 90.0f / deg)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_AngleMustBeLT90deg;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = Ms_Con(M, teta_Con, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}