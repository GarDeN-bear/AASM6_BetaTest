#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Sigma_Cxinos(float M, float lambda_nos, float nos_typ, InputComplex& x_2, InputComplex& x_1)
	{
		//1.2: оживальная, 1.1: коническая
		static unsigned int Length_1_2 = 23; static float Matrix_1_2[][2] = { {-0.8f,-0.318551647607295f}, {-0.6f,-0.313354823853946f}, {-0.4f,-0.282696271607436f}, {-0.3f,-0.242916998425321f}, {-0.2f,-0.172976337060557f}, {0.0f,0.0f}, {0.2f,0.181635594018662f}, {0.3f,0.256440704261703f}, {0.4f,0.318627233875661f}, {0.5f,0.375188738294666f}, {0.6f,0.42430075452159f}, {0.7f,0.470548326702914f}, {0.8f,0.509757043290433f}, {1.0f,0.570831730892878f}, {1.2f,0.615754797856703f}, {1.4f,0.652646560592735f}, {1.6f,0.679603838993079f}, {1.8f,0.700101572953447f}, {2.0f,0.717162098485064f}, {2.2f,0.732612717271171f}, {2.4f,0.745122136106876f}, {2.6f,0.751094135381642f}, {2.8f,0.75213461098955f} };
		static unsigned int Length_1_1 = 23; static float Matrix_1_1[][2] = { {-0.8f,-0.2f}, {-0.6f,-0.199f}, {-0.4f,-0.195545619306295f}, {-0.3f,-0.185402571638476f}, {-0.2f,-0.172976337060557f}, {0.0f,-0.153524421825331f}, {0.2f,-0.12367488154575f}, {0.3f,-0.106336777604422f}, {0.4f,-0.0848414990461009f}, {0.5f,-0.0640470254774944f}, {0.6f,-0.0418736962684829f}, {0.7f,-0.0196442471335864f}, {0.8f,0.00528672451651813f}, {1.0f,0.0583203737511138f}, {1.2f,0.110774420261834f}, {1.4f,0.162359062686741f}, {1.6f,0.211915095578085f}, {1.8f,0.254483102290623f}, {2.0f,0.294508483730324f}, {2.2f,0.331198963927386f}, {2.4f,0.363481207871492f}, {2.6f,0.389101253539788f}, {2.8f,0.4f} };

		//Входной комплекс x2
		const float x2_min = 0.0f;
		const float x2_max = 1.0f;

		//Входной комплекс x2
		float x2 = nos_typ;

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
		const float x1_max = 2.8f;

		//Координата по оси х графика
		float x1;
		if (M >= 1)
			x1 = sqrt(sqr(M) - 1.0f) / lambda_nos;
		else
			x1 = -sqrt(1.0f - sqr(M)) / lambda_nos;

		//Входной комплекс x1
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
		else if (x2_min < x2 && x2 < x2_max)
		{
			float y1 = Linterp(Matrix_1_1, Length_1_1, x1);
			float y2 = Linterp(Matrix_1_2, Length_1_2, x1);

			return LinterpOnce(x2_min, y1, x2_max, y2, x2);
		}
		else if (x2 == x2_max)
		{
			float y = Linterp(Matrix_1_2, Length_1_2, x1);

			return y;
		}
		else
			return NAN;
	}

	ErrorCode* get_Sigma_Cxinos(float& Result, float M, float lambda_nos, float nos_typ, InputComplex& x_2, InputComplex& x_1)
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
		if (nos_typ < 0.0f)
		{
			ErrC.ArgNumber = 3;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Проверка: некоторые аргументы не должны быть больше 1		
		if (nos_typ > 1.0f)
		{
			ErrC.ArgNumber = 3;
			ErrC.Code = ErrC_ArgMustNotBeGT1;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = Sigma_Cxinos(M, lambda_nos, nos_typ, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}