#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Sigma_eta(float M, float lambda_cor, float eta_cor, InputComplex& x_2, InputComplex& x_1)
	{
		static unsigned int Length_1_1 = 17; static float Matrix_1_1[][2] = { {0.0f,1.0f}, {0.025f,0.838057919453962f}, {0.05f,0.713704016315244f}, {0.075f,0.634719841051644f}, {0.1f,0.573005445344625f}, {0.125f,0.517522647220079f}, {0.15f,0.471196662097383f}, {0.2f,0.39169997162581f}, {0.25f,0.326503516798165f}, {0.3f,0.269765838619792f}, {0.35f,0.220854875902463f}, {0.4f,0.175746760156458f}, {0.45f,0.136234706373233f}, {0.5f,0.101150572088625f}, {0.55f,0.0719224910397638f}, {0.6f,0.0522266123924579f}, {0.65f,0.0422790713544172f} };
		static unsigned int Length_1_2 = 17; static float Matrix_1_2[][2] = { {0.0f,1.0f}, {0.025f,0.866082218725098f}, {0.05f,0.779842722466462f}, {0.075f,0.709805600872628f}, {0.1f,0.651744380258076f}, {0.125f,0.599018463794246f}, {0.15f,0.553822374566377f}, {0.2f,0.475937903465883f}, {0.25f,0.409351049614229f}, {0.3f,0.356089262416203f}, {0.35f,0.308924431705675f}, {0.4f,0.267791417128466f}, {0.45f,0.230585917472269f}, {0.5f,0.206132202809465f}, {0.55f,0.190055055455735f}, {0.6f,0.179992016806128f}, {0.65f,0.175005064226838f} };
		static unsigned int Length_1_3 = 17; static float Matrix_1_3[][2] = { {0.0f,1.0f}, {0.025f,0.881951720785904f}, {0.05f,0.805049476034688f}, {0.075f,0.74301848069343f}, {0.1f,0.688752781172883f}, {0.125f,0.644285352428739f}, {0.15f,0.605432542571875f}, {0.2f,0.541410499479033f}, {0.25f,0.484628714278352f}, {0.3f,0.439327596284032f}, {0.35f,0.399666988117971f}, {0.4f,0.366494265922524f}, {0.45f,0.334201933556732f}, {0.5f,0.31392687483607f}, {0.55f,0.300862685879194f}, {0.6f,0.292205757666534f}, {0.65f,0.288010420977612f} };
		static unsigned int Length_1_4 = 17; static float Matrix_1_4[][2] = { {0.0f,1.0f}, {0.025f,0.892283311351229f}, {0.05f,0.828377019288302f}, {0.075f,0.769630468276592f}, {0.1f,0.725500182853699f}, {0.125f,0.68735860257886f}, {0.15f,0.654422418857708f}, {0.2f,0.598860421693167f}, {0.25f,0.555966667659954f}, {0.3f,0.517631811786938f}, {0.35f,0.486523316614466f}, {0.4f,0.461450069910813f}, {0.45f,0.438980627408237f}, {0.5f,0.42392611631697f}, {0.55f,0.412421542961658f}, {0.6f,0.403705574301067f}, {0.65f,0.397526697429479f} };
		static unsigned int Length_1_5 = 17; static float Matrix_1_5[][2] = { {0.0f,1.0f}, {0.025f,0.908576251831605f}, {0.05f,0.850123191783481f}, {0.075f,0.80380299087197f}, {0.1f,0.762612818146621f}, {0.125f,0.728886688038982f}, {0.15f,0.70027560870279f}, {0.2f,0.655163880471925f}, {0.25f,0.621791313431838f}, {0.3f,0.593426654361231f}, {0.35f,0.573071741793307f}, {0.4f,0.557353349137001f}, {0.45f,0.545624435871716f}, {0.5f,0.535698252015276f}, {0.55f,0.527819679775371f}, {0.6f,0.521200649202936f}, {0.65f,0.514571636137421f} };

		//Значения по комплексу x2
		const float x2_min = 0.0f;
		const float x2_0 = 0.8f;
		const float x2_1 = 1.0f;
		const float x2_2 = 1.5f;
		const float x2_3 = 2.0f;
		const float x2_4 = 2.5f;
		const float x2_max = 3.0f;

		//Входной комплекс x2
		float x2 = M;

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
		const float x1_max = 0.65f;
		//Координата по оси х графика
		float x1;

		if (lambda_cor != 0 && eta_cor != 0) //проверяем условие чтобы избежать деления на ноль (нули обрабатываются отдельно в else)
		{
			x1 = (1.0f - eta_cor) / (2.0f * lambda_cor * eta_cor * eta_cor);

			x_1.Min = x1_min;
			x_1.Value = x1;
			x_1.Max = x1_max;

			//Ограничение по диапазону оси x	
			if (x1 < x1_min)
				x1 = x1_min;
			else if (x1 > x1_max)
				x1 = x1_max;

			//Ограничение по диапазону оси y
			if (x2 < x2_min)
				x2 = x2_min;
			else if (x2 > x2_max)
				x2 = x2_max;

			//Вычисление
			if (x2 < x2_0)
			{
				//Используем eta_k (при М<0.8 Sigma_eta = eta_cor)
				float y = eta_cor;

				return y;
			}
			else if (x2_0 <= x2 && x2 < x2_1)
			{
				//Интерполяция между eta_cor и кривой M=1	
				float y1 = eta_cor;
				float y2 = Linterp(Matrix_1_1, Length_1_1, x1);

				return LinterpOnce(x2_0, y1, x2_1, y2, x2);
			}
			else if (x2_1 <= x2 && x2 < x2_2)
			{
				//Интерполяция между кривыми 1 и 2		
				float y1 = Linterp(Matrix_1_1, Length_1_1, x1);
				float y2 = Linterp(Matrix_1_2, Length_1_2, x1);

				return LinterpOnce(x2_1, y1, x2_2, y2, x2);
			}
			else if (x2_2 <= x2 && x2 < x2_3)
			{
				//Интерполяция между кривыми 2 и 3		
				float y1 = Linterp(Matrix_1_2, Length_1_2, x1);
				float y2 = Linterp(Matrix_1_3, Length_1_3, x1);

				return LinterpOnce(x2_2, y1, x2_3, y2, x2);
			}
			else if (x2_3 <= x2 && x2 < x2_4)
			{
				//Интерполяция между кривыми 3 и 4			
				float y1 = Linterp(Matrix_1_3, Length_1_3, x1);
				float y2 = Linterp(Matrix_1_4, Length_1_4, x1);

				return LinterpOnce(x2_3, y1, x2_4, y2, x2);
			}
			else if (x2_4 <= x2 && x2 < x2_max)
			{
				//Интерполяция между кривыми 4 и 5		
				float y1 = Linterp(Matrix_1_4, Length_1_4, x1);
				float y2 = Linterp(Matrix_1_5, Length_1_5, x1);

				return LinterpOnce(x2_4, y1, x2_max, y2, x2);
			}
			else if (x2 == x2_max)
			{
				//Используем кривую 5		
				float y = Linterp(Matrix_1_5, Length_1_5, x1);

				return y;
			}
			else
				return NAN;
		}
		else if (lambda_cor != 0 && eta_cor == 0) //кормовая часть сужается в точку, донного среза нет поэтому можно принять Sigma_eta=1
		{
			x1 = 0.0f;
			x_1.Min = x1_min;
			x_1.Value = x1;
			x_1.Max = x1_max;
			return 1.0f;
		}
		else if (lambda_cor == 0) //кормовая часть нулевой длины (не существует) поэтому нужно принять Sigma_eta=1
		{
			x1 = 0.0f;
			x_1.Min = x1_min;
			x_1.Value = x1;
			x_1.Max = x1_max;
			return 1.0f;
		}
		else
		{
			return NAN;
		}
	}

	ErrorCode* get_Sigma_eta(float& Result, float M, float lambda_cor, float eta_cor, InputComplex& x_2, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (M < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (lambda_cor < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (eta_cor < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = Sigma_eta(M, lambda_cor, eta_cor, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}