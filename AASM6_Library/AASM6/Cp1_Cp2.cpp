#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Cp1_Cp2(float M, float key, InputComplex& x_1)		
	{
		//1_1: C1, 1_2: C2
		static unsigned int Length_1_1 = 28; static float Matrix_1_1[][2] = { {1.4f,2.0f}, {1.5f,1.80443646004051f}, {1.6f,1.62539941084171f}, {1.7f,1.46734964438147f}, {1.8f,1.33935996549104f}, {1.9f,1.22832026639217f}, {2.0f,1.14529993083999f}, {2.1f,1.07381019744783f}, {2.2f,1.01039188556769f}, {2.3f,0.956198055415573f}, {2.4f,0.906616466127463f}, {2.5f,0.858187937055356f}, {2.6f,0.812757364544856f}, {2.8f,0.739653346850295f}, {3.0f,0.683845232395772f}, {3.2f,0.631035074502855f}, {3.4f,0.583067769517149f}, {3.6f,0.542018825827458f}, {3.8f,0.506735183217781f}, {4.0f,0.482059694595326f}, {4.25f,0.460257397543196f}, {4.5f,0.448394641282865f}, {4.75f,0.4424632631527f}, {5.0f,0.438756151821347f}, {5.25f,0.433566195957452f}, {5.5f,0.430600506892369f}, {5.75f,0.426893395561016f}, {6.0f,0.424421985040992f} };
		static unsigned int Length_1_2 = 28; static float Matrix_1_2[][2] = { {1.4f,2.8f}, {1.5f,2.38190701920698f}, {1.6f,2.04064488633723f}, {1.7f,1.79320607952607f}, {1.8f,1.64577776782179f}, {1.9f,1.55092305540825f}, {2.0f,1.49157005303229f}, {2.1f,1.44434318134974f}, {2.2f,1.4f}, {2.3f,1.38220733861319f}, {2.4f,1.35516064579986f}, {2.5f,1.33355410463107f}, {2.6f,1.318471219027f}, {2.8f,1.29401160117843f}, {3.0f,1.27496132189252f}, {3.2f,1.26085000390296f}, {3.4f,1.24885538361183f}, {3.6f,1.2403885928181f}, {3.8f,1.23497925425543f}, {4.0f,1.23380331108964f}, {4.25f,1.2305004747189f}, {4.5f,1.22814858864069f}, {4.75f,1.22701441872581f}, {5.0f,1.22623184471396f}, {5.25f,1.22614585246905f}, {5.5f,1.22603954565888f}, {5.75f,1.2260395328554f}, {6.0f,1.2260395328554f} };

		//Входной комплекс x1
		const float x1_min = 1.4f;
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
		if (abs(key - 0.0f) < 1e-5)
			return Linterp(Matrix_1_2, Length_1_2, x1) / Linterp(Matrix_1_1, Length_1_1, x1);
		else if (abs(key - 1.0f) < 1e-5)
			return Linterp(Matrix_1_1, Length_1_1, x1);
		else if(abs(key - 2.0f) < 1e-5)
			return Linterp(Matrix_1_2, Length_1_2, x1);
		else
			return NAN;
	}

	ErrorCode* get_Cp1_Cp2(float& Result, float M, float key, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (M < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (key < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Проверка: некоторые аргументы должны быть 0, 1 или 2	
		if (!(abs(key - 0.0f) < 1e-5) && !(abs(key - 1.0f) < 1e-5) && !(abs(key - 2.0f) < 1e-5))
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_ArgMustBe01or2;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = Cp1_Cp2(M, key, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}