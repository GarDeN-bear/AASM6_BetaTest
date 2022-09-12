#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
	float Mcr_pr_1(float cc, float Cn, InputComplex& x_2, InputComplex& x_1)
	{		
		static unsigned int Length_1_1 = 17; static float Matrix_1_1[][2] = { {0.0f,0.873187494117647f}, {0.05f,0.838098363249595f}, {0.1f,0.786312548987352f}, {0.15f,0.705389691193309f}, {0.2f,0.616010241967913f}, {0.25f,0.55652829677413f}, {0.3f,0.509881929227426f}, {0.35f,0.47231438489451f}, {0.4f,0.441008097950414f}, {0.45f,0.41377162830905f}, {0.5f,0.390345583681345f}, {0.55f,0.369731926120245f}, {0.6f,0.351009347582304f}, {0.65f,0.334138436289345f}, {0.7f,0.319840579065841f}, {0.75f,0.306909277256463f}, {0.8f,0.296953877612648f} };
		static unsigned int Length_1_2 = 17; static float Matrix_1_2[][2] = { {0.0f,0.822330835294118f}, {0.05f,0.807491656866259f}, {0.1f,0.786312548987352f}, {0.15f,0.749523849196745f}, {0.2f,0.691366233054627f}, {0.25f,0.627579675940681f}, {0.3f,0.576837404535108f}, {0.35f,0.535617461696647f}, {0.4f,0.500397890284038f}, {0.45f,0.470004704583528f}, {0.5f,0.444039924057471f}, {0.55f,0.420265993188234f}, {0.6f,0.398416815494917f}, {0.65f,0.380218771037789f}, {0.7f,0.365836439862448f}, {0.75f,0.354239983632843f}, {0.8f,0.34589326428452f} };
		static unsigned int Length_1_3 = 17; static float Matrix_1_3[][2] = { {0.0f,0.758485564705882f}, {0.05f,0.75470981515816f}, {0.1f,0.747867273749566f}, {0.15f,0.733779444624723f}, {0.2f,0.709882307291762f}, {0.25f,0.673619193022483f}, {0.3f,0.628877293042762f}, {0.35f,0.588961778775139f}, {0.4f,0.552959550220028f}, {0.45f,0.522044593091183f}, {0.5f,0.492434064533175f}, {0.55f,0.465693278831009f}, {0.6f,0.440778693128015f}, {0.65f,0.418342521709613f}, {0.7f,0.394862807434541f}, {0.75f,0.377513907442404f}, {0.8f,0.363598666164333f} };
		static unsigned int Length_1_4 = 17; static float Matrix_1_4[][2] = { {0.0f,0.730348605882353f}, {0.05f,0.725404316097961f}, {0.1f,0.717734275796657f}, {0.15f,0.706456889170758f}, {0.2f,0.692682467602994f}, {0.25f,0.677102552716753f}, {0.3f,0.658099207330577f}, {0.35f,0.635793478769258f}, {0.4f,0.611791993065851f}, {0.45f,0.585181650220769f}, {0.5f,0.558310421661519f}, {0.55f,0.529743435960182f}, {0.6f,0.501176450258844f}, {0.65f,0.471174593129584f}, {0.7f,0.44267746632952f}, {0.75f,0.417347156816139f}, {0.8f,0.393454196721562f} };

		//Значения по комплексу x2
		const float x2_min = 0.04f;
		const float x2_2 = 0.06f;
		const float x2_3 = 0.09f;
		const float x2_max = 0.12f;

		//Входной комплекс x2
		float x2 = cc;

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
		const float x1_max = 0.8f;
		//Координата по оси х графика
		float x1 = Cn;

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
			//Используем кривую 1		
			float y = Linterp(Matrix_1_1, Length_1_1, x1);

			return y;
		}
		else if (x2_min <= x2 && x2 < x2_2)
		{
			//Интерполяция между кривыми 1 и 2		
			float y1 = Linterp(Matrix_1_1, Length_1_1, x1);
			float y2 = Linterp(Matrix_1_2, Length_1_2, x1);

			return LinterpOnce(x2_min, y1, x2_2, y2, x2);
		}
		else if (x2_2 <= x2 && x2 < x2_3)
		{
			//Интерполяция между кривыми 2 и 3
			float y1 = Linterp(Matrix_1_2, Length_1_2, x1);
			float y2 = Linterp(Matrix_1_3, Length_1_3, x1);

			return LinterpOnce(x2_2, y1, x2_3, y2, x2);
		}
		else if (x2_3 <= x2 && x2 < x2_max)
		{
			//Интерполяция между кривыми 3 и 4		
			float y1 = Linterp(Matrix_1_3, Length_1_3, x1);
			float y2 = Linterp(Matrix_1_4, Length_1_4, x1);

			return LinterpOnce(x2_3, y1, x2_max, y2, x2);
		}
		else if (x2 == x2_max)
		{
			//Используем кривую 4
			float y = Linterp(Matrix_1_4, Length_1_4, x1);

			return y;
		}
		else
			return NAN;
	}
	float Mcr_pr_2(float cc, float Cn, InputComplex& x_2, InputComplex& x_1)
	{		
		static unsigned int Length_2_1 = 17; static float Matrix_2_1[][2] = { {0.0f,0.8740481f}, {0.05f,0.83375942795258f}, {0.1f,0.750448121998178f}, {0.15f,0.664283022298611f}, {0.2f,0.599019931503765f}, {0.25f,0.549864710901472f}, {0.3f,0.507464738778463f}, {0.35f,0.470783981700956f}, {0.4f,0.438380863932779f}, {0.45f,0.411431736283997f}, {0.5f,0.384910372566148f}, {0.55f,0.363522176019497f}, {0.6f,0.342989507334711f}, {0.65f,0.325647675534065f}, {0.7f,0.310996760899608f}, {0.75f,0.298155383777703f}, {0.8f,0.286845988068543f} };
		static unsigned int Length_2_2 = 17; static float Matrix_2_2[][2] = { {0.0f,0.81404944f}, {0.05f,0.801668238509255f}, {0.1f,0.778568983485225f}, {0.15f,0.742023439415337f}, {0.2f,0.686253943682177f}, {0.25f,0.632975231789372f}, {0.3f,0.586028140369473f}, {0.35f,0.543465629241637f}, {0.4f,0.505822403319529f}, {0.45f,0.472242934741286f}, {0.5f,0.443888716102692f}, {0.55f,0.419489085345991f}, {0.6f,0.398292742311043f}, {0.65f,0.382765326429858f}, {0.7f,0.369938127858262f}, {0.75f,0.358850485446728f}, {0.8f,0.348317225155771f} };
		static unsigned int Length_2_3 = 17; static float Matrix_2_3[][2] = { {0.0f,0.76871502f}, {0.05f,0.761674735739829f}, {0.1f,0.750448121998178f}, {0.15f,0.738875510838557f}, {0.2f,0.715166696186046f}, {0.25f,0.682371462784345f}, {0.3f,0.639327718944612f}, {0.35f,0.598155442228348f}, {0.4f,0.560458747312805f}, {0.45f,0.526326751680059f}, {0.5f,0.495313867919755f}, {0.55f,0.469024210709152f}, {0.6f,0.447190427602042f}, {0.65f,0.42606958435149f}, {0.7f,0.410563142471339f}, {0.75f,0.397246936412357f}, {0.8f,0.388002764278842f} };
		static unsigned int Length_2_4 = 17; static float Matrix_2_4[][2] = { {0.0f,0.72863568f}, {0.05f,0.723861835783602f}, {0.1f,0.716932059551757f}, {0.15f,0.707692357909299f}, {0.2f,0.697528686102593f}, {0.25f,0.683791747642401f}, {0.3f,0.667581306435613f}, {0.35f,0.647192978198807f}, {0.4f,0.619248033664827f}, {0.45f,0.584134873996953f}, {0.5f,0.551302567491662f}, {0.55f,0.521804680926545f}, {0.6f,0.494891201341454f}, {0.65f,0.468868896577061f}, {0.7f,0.445876586203042f}, {0.75f,0.430034684225205f}, {0.8f,0.416549015780362f} };
		
		//Значения по комплексу x2
		const float x2_min = 0.04f;
		const float x2_2 = 0.06f;
		const float x2_3 = 0.09f;
		const float x2_max = 0.12f;

		//Входной комплекс x2
		float x2 = cc;

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
		const float x1_max = 0.8f;
		//Координата по оси х графика
		float x1 = Cn;

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
			//Используем кривую 1		
			float y = Linterp(Matrix_2_1, Length_2_1, x1);

			return y;
		}
		else if (x2_min <= x2 && x2 < x2_2)
		{
			//Интерполяция между кривыми 1 и 2		
			float y1 = Linterp(Matrix_2_1, Length_2_1, x1);
			float y2 = Linterp(Matrix_2_2, Length_2_2, x1);

			return LinterpOnce(x2_min, y1, x2_2, y2, x2);
		}
		else if (x2_2 <= x2 && x2 < x2_3)
		{
			//Интерполяция между кривыми 2 и 3
			float y1 = Linterp(Matrix_2_2, Length_2_2, x1);
			float y2 = Linterp(Matrix_2_3, Length_2_3, x1);

			return LinterpOnce(x2_2, y1, x2_3, y2, x2);
		}
		else if (x2_3 <= x2 && x2 < x2_max)
		{
			//Интерполяция между кривыми 3 и 4		
			float y1 = Linterp(Matrix_2_3, Length_2_3, x1);
			float y2 = Linterp(Matrix_2_4, Length_2_4, x1);

			return LinterpOnce(x2_3, y1, x2_max, y2, x2);
		}
		else if (x2 == x2_max)
		{
			//Используем кривую 4
			float y = Linterp(Matrix_2_4, Length_2_4, x1);

			return y;
		}
		else
			return NAN;
	}
	float Mcr_pr_3(float cc, float Cn, InputComplex& x_2, InputComplex& x_1)
	{		
		static unsigned int Length_3_1 = 19; static float Matrix_3_1[][2] = { {0.0f,0.895772379310345f}, {0.025f,0.871303098075173f}, {0.05f,0.812423895026362f}, {0.075f,0.744674578271496f}, {0.1f,0.690842164055439f}, {0.15f,0.608564212782036f}, {0.2f,0.547543947804176f}, {0.25f,0.500593518360061f}, {0.3f,0.464807197545978f}, {0.35f,0.431314871655875f}, {0.4f,0.402257602618798f}, {0.45f,0.374729663531044f}, {0.5f,0.351330915306452f}, {0.55f,0.329614430026111f}, {0.6f,0.309427274695089f}, {0.65f,0.293552834677899f}, {0.7f,0.280013760804491f}, {0.75f,0.267328884456647f}, {0.8f,0.256391688582726f} };
		static unsigned int Length_3_2 = 19; static float Matrix_3_2[][2] = { {0.0f,0.840468041379311f}, {0.025f,0.831842619352042f}, {0.05f,0.81717972528508f}, {0.075f,0.796215169526745f}, {0.1f,0.769146029423785f}, {0.15f,0.705067104547287f}, {0.2f,0.641141112665721f}, {0.25f,0.586544033475005f}, {0.3f,0.536993743117045f}, {0.35f,0.495548901490478f}, {0.4f,0.459150848696668f}, {0.45f,0.426117321791361f}, {0.5f,0.400271645647856f}, {0.55f,0.376872897423265f}, {0.6f,0.357909206051699f}, {0.65f,0.33940431366493f}, {0.7f,0.324111014171732f}, {0.75f,0.312029307572106f}, {0.8f,0.301323997926868f} };
		static unsigned int Length_3_3 = 17; static float Matrix_3_3[][2] = { {0.0f,0.78619955862069f}, {0.05f,0.776428839463169f}, {0.1f,0.762457823636279f}, {0.15f,0.740425866434192f}, {0.2f,0.713131577146737f}, {0.25f,0.677447214498548f}, {0.3f,0.633797592330673f}, {0.35f,0.584412983308625f}, {0.4f,0.540338547299701f}, {0.45f,0.501680487764163f}, {0.5f,0.465571311274922f}, {0.55f,0.432011017831983f}, {0.6f,0.400403824247893f}, {0.65f,0.369775790118176f}, {0.7f,0.345966615836538f}, {0.75f,0.328144033695288f}, {0.8f,0.314474646668195f} };
		static unsigned int Length_3_4 = 17; static float Matrix_3_4[][2] = { {0.0f,0.747525365517241f}, {0.05f,0.747789635159998f}, {0.1f,0.74572929521542f}, {0.15f,0.740425866434192f}, {0.2f,0.731276287296216f}, {0.25f,0.718868186507357f}, {0.3f,0.701981836325624f}, {0.35f,0.678829481988406f}, {0.4f,0.650366954638065f}, {0.45f,0.612452319324363f}, {0.5f,0.564448355285726f}, {0.55f,0.51984290197549f}, {0.6f,0.481715859741264f}, {0.65f,0.447305938616224f}, {0.7f,0.412896017491184f}, {0.75f,0.386880424005096f}, {0.8f,0.367328291816901f} };

		//Значения по комплексу x2
		const float x2_min = 0.04f;
		const float x2_2 = 0.06f;
		const float x2_3 = 0.09f;
		const float x2_max = 0.12f;

		//Входной комплекс x2
		float x2 = cc;

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
		const float x1_max = 0.8f;
		//Координата по оси х графика
		float x1 = Cn;

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
			//Используем кривую 1		
			float y = Linterp(Matrix_3_1, Length_3_1, x1);

			return y;
		}
		else if (x2_min <= x2 && x2 < x2_2)
		{
			//Интерполяция между кривыми 1 и 2		
			float y1 = Linterp(Matrix_3_1, Length_3_1, x1);
			float y2 = Linterp(Matrix_3_2, Length_3_2, x1);

			return LinterpOnce(x2_min, y1, x2_2, y2, x2);
		}
		else if (x2_2 <= x2 && x2 < x2_3)
		{
			//Интерполяция между кривыми 2 и 3
			float y1 = Linterp(Matrix_3_2, Length_3_2, x1);
			float y2 = Linterp(Matrix_3_3, Length_3_3, x1);

			return LinterpOnce(x2_2, y1, x2_3, y2, x2);
		}
		else if (x2_3 <= x2 && x2 < x2_max)
		{
			//Интерполяция между кривыми 3 и 4
			float y1 = Linterp(Matrix_3_3, Length_3_3, x1);
			float y2 = Linterp(Matrix_3_4, Length_3_4, x1);

			return LinterpOnce(x2_3, y1, x2_max, y2, x2);
		}
		else if (x2 == x2_max)
		{
			//Используем кривую 4		
			float y = Linterp(Matrix_3_4, Length_3_4, x1);

			return y;
		}
		else
			return NAN;
	}

	float Mcr_pr(float cc, float Cn, float xx_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
	{		
		//Значения по комплексу x3
		const float x3_min = 0.35f;
		const float x3_2 = 0.4f;
		const float x3_max = 0.5f;

		//Входной комплекс x3
		float x3 = xx_c;

		x_3.Min = x3_min;
		x_3.Value = x3;
		x_3.Max = x3_max;

		//Ограничение по диапазону x3	
		if (x3 < x3_min)
			x3 = x3_min;
		else if (x3 > x3_max)
			x3 = x3_max;

		//Вычисление
		if (x3 == x3_min)
		{
			//Используем 1-ый график
			float y = Mcr_pr_1(cc, Cn, x_2, x_1);

			return y;
		}
		else if (x3_min <= x3 && x3 < x3_2)
		{
			//Интерполяция между 1-м и 2-м графиком
			float y1 = Mcr_pr_1(cc, Cn, x_2, x_1);
			float y2 = Mcr_pr_2(cc, Cn, x_2, x_1);

			return LinterpOnce(x3_min, y1, x3_2, y2, x3);
		}
		else if (x3_2 <= x3 && x3 < x3_max)
		{
			//Интерполяция между 2-м и 3-м графиком
			float y1 = Mcr_pr_2(cc, Cn, x_2, x_1);
			float y2 = Mcr_pr_3(cc, Cn, x_2, x_1);

			return LinterpOnce(x3_2, y1, x3_max, y2, x3);
		}
		else if (x3 == x3_max)
		{
			//Используем 4-ий график
			float y = Mcr_pr_3(cc, Cn, x_2, x_1);

			return y;
		}
		else
			return NAN;
	}

	ErrorCode* get_Mcr_pr(float& Result, float cc, float Cn, float xx_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
	{
		static ErrorCode ErrC;
		// Проверка: некоторые аргументы не должны быть меньше 0		
		if (cc < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (Cn < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (xx_c < 0.0f)
		{
			ErrC.ArgNumber = 3;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Проверка: некоторые аргументы не должны быть больше 1		
		if (xx_c > 1.0f)
		{
			ErrC.ArgNumber = 3;
			ErrC.Code = ErrC_ArgMustNotBeGT1;
			return &ErrC;
		}

		// Вызываем функцию интерполяции графика
		Result = Mcr_pr(cc, Cn, xx_c, x_3, x_2, x_1);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}