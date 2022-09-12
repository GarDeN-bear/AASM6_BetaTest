#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Sigma_CF(float M, float chi_0, float alpha, InputComplex& x_2, InputComplex& x_1)
	{		
		static unsigned int Length_1_2 = 18; static float Matrix_1_2[][2] = { {-0.6f,0.908202552504843f}, {-0.5f,0.907400517761241f}, {-0.4f,0.908418787258174f}, {-0.3f,0.908794430023942f}, {-0.2f,0.909116577491481f}, {-0.1f,0.910093473449499f}, {0.0f,0.90885321282492f}, {0.1f,0.906939098886949f}, {0.2f,0.901153226030429f}, {0.3f,0.889474445143502f}, {0.4f,0.872860725861395f}, {0.5f,0.848537402892214f}, {0.6f,0.814603916600993f}, {0.7f,0.767011526571256f}, {0.8f,0.698007718958332f}, {0.9f,0.588935919291693f}, {0.95f,0.475645299639008f}, {1.0f,0.0f} };
		static unsigned int Length_1_3 = 18; static float Matrix_1_3[][2] = { {-0.6f,0.851340229670292f}, {-0.5f,0.849926448159835f}, {-0.4f,0.840194519531771f}, {-0.3f,0.828778720972405f}, {-0.2f,0.814860565213651f}, {-0.1f,0.796287543092863f}, {0.0f,0.769549150777549f}, {0.1f,0.739905252045609f}, {0.2f,0.704963844871659f}, {0.3f,0.667013140842031f}, {0.4f,0.621193190045201f}, {0.5f,0.570342649088079f}, {0.6f,0.50660925187195f}, {0.7f,0.433284628568485f}, {0.8f,0.339485810455382f}, {0.9f,0.211003961495886f}, {0.95f,0.125323360179927f}, {1.0f,0.0f} };
		static unsigned int Length_1_4 = 18; static float Matrix_1_4[][2] = { {-0.6f,0.776525746961148f}, {-0.5f,0.764466931592258f}, {-0.4f,0.740856140270571f}, {-0.3f,0.711379385474099f}, {-0.2f,0.675995056634584f}, {-0.1f,0.627947058222896f}, {0.0f,0.58273325643954f}, {0.1f,0.527029028240254f}, {0.2f,0.469915225617277f}, {0.3f,0.410080097102079f}, {0.4f,0.348207367850318f}, {0.5f,0.286841644882276f}, {0.6f,0.226919812184005f}, {0.7f,0.168745751859121f}, {0.8f,0.112552706824908f}, {0.9f,0.057073123155578f}, {0.95f,0.0268578700432418f}, {1.0f,0.0f} };
		static unsigned int Length_1_5 = 18; static float Matrix_1_5[][2] = { {-0.6f,0.649936688623266f}, {-0.5f,0.637354242972013f}, {-0.4f,0.605404543348229f}, {-0.3f,0.558750344080467f}, {-0.2f,0.497297114171111f}, {-0.1f,0.427344219259617f}, {0.0f,0.360472065280488f}, {0.1f,0.283280552095914f}, {0.2f,0.209534830211047f}, {0.3f,0.149052197188504f}, {0.4f,0.094599109911483f}, {0.5f,0.0545064017702292f}, {0.6f,0.0260342876292814f}, {0.7f,0.00609660653201279f}, {0.8f,0.00253434808430575f}, {0.9f,0.0f}, {0.95f,0.0f}, {1.0f,0.0f} };

		//Значения по комплексу x2
		const float x2_min = 0.0f;
		const float x2_2 = 2.0f;
		const float x2_3 = 4.0f;
		const float x2_4 = 6.0f;
		const float x2_max = 8.0f;

		//Входной комплекс x2
		float x2 = alpha * deg;

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
		const float x1_max = 1.0f;

		//Координата по оси х графика
		float x1;

		if (M >= 1)
			x1 = +sqrt(sqr(M) - 1.0f) / tan(chi_0);
		else
			x1 = -sqrt(1.0f - sqr(M)) / tan(chi_0);

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
			float y = 1.0f;
			if (x1 >= 1.0f)
				y = 0.0f;
			
			return y;
		}
		else if (x2_min <= x2 && x2 < x2_2)
		{
			float y1 = 1.0f;
			if (x1 >= 1.0f)
				y1 = 0.0f;
			float y2 = Linterp(Matrix_1_2, Length_1_2, x1);
			float y = LinterpOnce(x2_min, y1, x2_2, y2, x2);

			if (x1 < 0.0f)
				return y;
			else
				return LinterpOnce(0.0, y, 1.0, y2, powf(x1, LinterpOnce(x2_min, 100.0f, x2_2, 1.0f, x2)));
		}
		else if (x2_2 <= x2 && x2 < x2_3)
		{
			float y1 = Linterp(Matrix_1_2, Length_1_3, x1);
			float y2 = Linterp(Matrix_1_3, Length_1_3, x1);

			return LinterpOnce(x2_2, y1, x2_3, y2, x2);
		}
		else if (x2_3 <= x2 && x2 < x2_4)
		{
			float y1 = Linterp(Matrix_1_3, Length_1_3, x1);
			float y2 = Linterp(Matrix_1_4, Length_1_4, x1);

			return LinterpOnce(x2_3, y1, x2_4, y2, x2);
		}
		else if (x2_4 <= x2 && x2 < x2_max)
		{
			float y1 = Linterp(Matrix_1_4, Length_1_4, x1);
			float y2 = Linterp(Matrix_1_5, Length_1_5, x1);

			return LinterpOnce(x2_4, y1, x2_max, y2, x2);
		}
		else if (x2 == x2_max)
		{
			float y = Linterp(Matrix_1_5, Length_1_5, x1);

			return y;
		}
		else
			return NAN;
	}

	ErrorCode* get_Sigma_CF(float& Result, float M, float chi_0, float alpha, InputComplex& x_2, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (M < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (chi_0 < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (alpha < 0.0f)
		{
			ErrC.ArgNumber = 3;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Проверка: некоторые аргументы не должны быть больше 90 градусов	
		if (chi_0 > 90.0f / deg)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_AngleMustBeLT90deg;
			return &ErrC;
		}		
		if (alpha > 90.0f / deg)
		{
			ErrC.ArgNumber = 3;
			ErrC.Code = ErrC_AngleMustBeLT90deg;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = Sigma_CF(M, chi_0, alpha, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}