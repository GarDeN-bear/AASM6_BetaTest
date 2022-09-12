#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float nn_Eff1(float l_r, float l_c, float zeta_c, InputComplex& x_2, InputComplex& x_1)
	{
		//zeta = 0, eta = inf
		static unsigned int Length_1_1 = 11; static float Matrix_1_1[][2] = { {0.0f,0.0f}, {0.1f,0.0269898795279352f}, {0.2f,0.0718952074951651f}, {0.3f,0.131756294282945f}, {0.4f,0.213541862517768f}, {0.5f,0.310621637375314f}, {0.6f,0.424967872760713f}, {0.7f,0.549184330212724f}, {0.8f,0.689496731155627f}, {0.9f,0.84144169539779f}, {1.0f,1.0f} };
		//zeta = 0.2, eta = 5
		static unsigned int Length_1_2 = 11; static float Matrix_1_2[][2] = { {0.0f,0.0f}, {0.1f,0.0411571781073742f}, {0.2f,0.0966513822230605f}, {0.3f,0.166576569054374f}, {0.4f,0.252551924790159f}, {0.5f,0.348853653850367f}, {0.6f,0.457587920034089f}, {0.7f,0.58030909430641f}, {0.8f,0.712612220552619f}, {0.9f,0.850710266795272f}, {1.0f,1.0f} };
		//zeta = 1, eta = 1
		static unsigned int Length_1_3 = 11; static float Matrix_1_3[][2] = { {0.0f,0.0f}, {0.1f,0.0593029256970759f}, {0.2f,0.138473331764551f}, {0.3f,0.222947915376712f}, {0.4f,0.313246991324852f}, {0.5f,0.411039928327273f}, {0.6f,0.51744039122788f}, {0.7f,0.632039132604963f}, {0.8f,0.75126498224765f}, {0.9f,0.875853879538199f}, {1.0f,1.0f} };

		//Значения по комплексу x2
		const float x2_min = 0.0f;
		const float x2_2 = 0.2f;
		const float x2_max = 1.0f;

		//Входной комплекс x2
		float x2 = zeta_c;

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
		const float x1_max = 1.0f;

		//Координата по оси х графика
		float x1;
		x1 = l_r / l_c;

		x_1.Min = x1_min;
		x_1.Value = x1;
		x_1.Max = x1_max;

		//Ограничение по диапазону оси x
		if (x1 < x1_min)
			x1 = x1_min;
		else if (x1 > x1_max)
			x1 = x1_max;

		//Вычисление
		if (x2 == x2_min)
		{
			float y = Linterp(Matrix_1_1, Length_1_1, x1);

			return y;
		}
		else if (x2_min <= x2 && x2 < x2_2)
		{
			float y1 = Linterp(Matrix_1_1, Length_1_1, x1);
			float y2 = Linterp(Matrix_1_2, Length_1_2, x1);

			return LinterpOnce(x2_min, y1, x2_2, y2, x2);
		}
		else if (x2_2 <= x2 && x2 < x2_max)
		{
			float y1 = Linterp(Matrix_1_2, Length_1_2, x1);
			float y2 = Linterp(Matrix_1_3, Length_1_3, x1);

			return LinterpOnce(x2_2, y1, x2_max, y2, x2);
		}
		else if (x2 == x2_max)
		{
			float y = Linterp(Matrix_1_3, Length_1_3, x1);

			return y;
		}
		else
			return NAN;
	}

	ErrorCode* get_nn_Eff1(float& Result, float l_r, float l_c, float zeta_c, InputComplex& x_2, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (l_r < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (l_c < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (zeta_c < 0.0f)
		{
			ErrC.ArgNumber = 3;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Проверка: некоторые аргументы не должны быть больше 1	
		if (zeta_c > 1.0f)
		{
			ErrC.ArgNumber = 3;
			ErrC.Code = ErrC_ArgMustNotBeGT1;
			return &ErrC;
		}

		// Проверка: некоторые аргументы не должны быть больше других	
		if (l_r > l_c)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_ArgMustNotBeGTNextArg;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = nn_Eff1(l_r, l_c, zeta_c, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}