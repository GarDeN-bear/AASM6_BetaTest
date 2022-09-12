#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Sigma_Con(float M, float lambda_nos, InputComplex& x_2, InputComplex& x_1)
	{
		static unsigned int Length_1_1 = 21; static float Matrix_1_1[][2] = { {0.00000f, 1.00000f}, {0.25000f, 1.00183f}, {0.50000f, 1.00557f}, {0.75000f, 1.01254f}, {1.00000f, 1.02412f}, {1.25000f, 1.04169f}, {1.50000f, 1.06714f}, {1.75000f, 1.10361f}, {2.00000f, 1.15568f}, {2.25000f, 1.23011f}, {2.50000f, 1.32923f}, {2.75000f, 1.44842f}, {3.00000f, 1.57809f}, {3.50000f, 1.83370f}, {4.00000f, 2.09544f}, {5.00000f, 2.72620f}, {6.00000f, 3.50120f}, {7.00000f, 4.33876f}, {8.00000f, 5.23089f}, {9.00000f, 6.23280f}, {10.00000f, 7.23590f} };
		static unsigned int Length_1_2 = 21; static float Matrix_1_2[][2] = { {0.00000f, 1.00000f}, {0.25000f, 1.00135f}, {0.50000f, 1.00417f}, {0.75000f, 1.00943f}, {1.00000f, 1.01809f}, {1.25000f, 1.03112f}, {1.50000f, 1.05004f}, {1.75000f, 1.07745f}, {2.00000f, 1.11666f}, {2.25000f, 1.17132f}, {2.50000f, 1.24065f}, {2.75000f, 1.32085f}, {3.00000f, 1.40686f}, {3.50000f, 1.58141f}, {4.00000f, 1.76722f}, {5.00000f, 2.21584f}, {6.00000f, 2.74387f}, {7.00000f, 3.34751f}, {8.00000f, 3.99352f}, {9.00000f, 4.68894f}, {10.00000f, 5.44624f} };
		static unsigned int Length_1_3 = 21; static float Matrix_1_3[][2] = { {0.00000f, 1.00000f}, {0.25000f, 1.00097f}, {0.50000f, 1.00278f}, {0.75000f, 1.00622f}, {1.00000f, 1.01206f}, {1.25000f, 1.02114f}, {1.50000f, 1.03441f}, {1.75000f, 1.05290f}, {2.00000f, 1.07765f}, {2.25000f, 1.10935f}, {2.50000f, 1.14721f}, {2.75000f, 1.19011f}, {3.00000f, 1.23690f}, {3.50000f, 1.33861f}, {4.00000f, 1.44870f}, {5.00000f, 1.69404f}, {6.00000f, 1.99763f}, {7.00000f, 2.32945f}, {8.00000f, 2.67187f}, {9.00000f, 3.06547f}, {10.00000f, 3.46613f} };
		static unsigned int Length_1_4 = 21; static float Matrix_1_4[][2] = { {0.00000f, 1.00000f}, {0.25000f, 1.00046f}, {0.50000f, 1.00139f}, {0.75000f, 1.00313f}, {1.00000f, 1.00603f}, {1.25000f, 1.01043f}, {1.50000f, 1.01681f}, {1.75000f, 1.02595f}, {2.00000f, 1.03864f}, {2.25000f, 1.05549f}, {2.50000f, 1.07602f}, {2.75000f, 1.09945f}, {3.00000f, 1.12495f}, {3.50000f, 1.18057f}, {4.00000f, 1.24533f}, {5.00000f, 1.40594f}, {6.00000f, 1.58598f}, {7.00000f, 1.79955f}, {8.00000f, 2.01664f}, {9.00000f, 2.25139f}, {10.00000f, 2.50026f} };
		static unsigned int Length_1_5 = 21; static float Matrix_1_5[][2] = { {0.00000f, 1.00000f}, {0.25000f, 1.00000f}, {0.50000f, 1.00000f}, {0.75000f, 1.00000f}, {1.00000f, 1.00000f}, {1.25000f, 1.00184f}, {1.50000f, 1.00549f}, {1.75000f, 1.01065f}, {2.00000f, 1.01699f}, {2.25000f, 1.02429f}, {2.50000f, 1.03284f}, {2.75000f, 1.04306f}, {3.00000f, 1.05538f}, {3.50000f, 1.08790f}, {4.00000f, 1.13310f}, {5.00000f, 1.26027f}, {6.00000f, 1.40243f}, {7.00000f, 1.54534f}, {8.00000f, 1.69170f}, {9.00000f, 1.85937f}, {10.00000f, 2.02568f} };

		//Значения по комплексу x2
		const float x2_min = 1.5f;
		const float x2_2 = 2.0f;
		const float x2_3 = 3.0f;
		const float x2_4 = 4.0f;
		const float x2_max = 5.0f;

		//Входной комплекс x2
		float x2 = lambda_nos;

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

	ErrorCode* get_Sigma_Con(float& Result, float M, float lambda_nos, InputComplex& x_2, InputComplex& x_1)
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

		// Вызываем функцию интерполяции графика
		Result = Sigma_Con(M, lambda_nos, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}