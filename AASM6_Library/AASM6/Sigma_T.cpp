#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Sigma_T(float M, float TT_s, InputComplex& x_1)
	{
		static unsigned int Length_1_1 = 21; static float Matrix_1_1[][2] = { {-0.05f,3.0f}, {-0.0475f,2.74692897438938f}, {-0.045f,2.55618515009959f}, {-0.0425f,2.39408280138465f}, {-0.04f,2.2483795253478f}, {-0.0375f,2.11818082711569f}, {-0.035f,1.99146072005772f}, {-0.0325f,1.87497760988365f}, {-0.03f,1.76654495356973f}, {-0.0275f,1.66248538330331f}, {-0.025f,1.56786770336669f}, {-0.0225f,1.47831882771239f}, {-0.02f,1.3951308044908f}, {-0.0175f,1.3206889533642f}, {-0.015f,1.25151468315844f}, {-0.0125f,1.18820432378908f}, {-0.00999999999999999f,1.13383891315323f}, {-0.00749999999999999f,1.08921355780498f}, {-0.00499999999999999f,1.05323498623244f}, {-0.00249999999999999f,1.02471053860449f}, {0.0f,1.0f} };
		const float x1_min = -0.05f;
		const float x1_max = 0.0f;

		//Координата по оси х графика
		float x1 = (TT_s - 1) / powf(M, 2);

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

	ErrorCode* get_Sigma_T(float& Result, float M, float TT_s, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (M < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (TT_s < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}		

		// Вызываем функцию интерполяции графика
		Result = Sigma_T(M, TT_s, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}