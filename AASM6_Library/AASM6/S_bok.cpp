#include "Extensions.h"
#include "AASM6.h"

namespace AASM6
{	
	// класс, содержащий атрибуты и методы для винтовой линии и образующей кормовой части
	class VintAndKon {
	public:
		float d, M, b_b, L_hv, lambda_cor, eta_cor, L_vint;

		VintAndKon(float di, float Mi, float b_bi, float L_hvi, float lambda_cori, float eta_cori)
		{
			d = di;											// калибр
			M = Mi;											// число Маха
			b_b = b_bi;										// длина бортовой хорды
			L_hv = L_hvi;									// длина от конца бортовой хорды до донного среза ракеты
			lambda_cor = lambda_cori;						// удлинение кормовой части
			eta_cor = eta_cori;							// сужение кормовой части
#pragma warning(push)
#pragma warning(disable:4244)
			L_vint = M_PI_4 * d * sqrtf(sqr(M) - 1.0f);		// четверть шага винтовой линии
#pragma warning(pop)
		}

		// уравнение образующей кормовой части
		// x_dop = b_b для первой (левой) винтовой линии и 0 для второй (правой) винтовой линии
		float z_kon(float x, float x_dop = 0.0f)
		{
			return d / 2.0f - (x - (L_hv + x_dop - d * lambda_cor)) / (2.0f * lambda_cor) * (1.0f - eta_cor);
		}

		// уравнение проекции винтовой линии
		float z_vint(float x)
		{
			return d / 2.0f * cosf(2.0f * x / (d * sqrtf(sqr(M) - 1.0f)));
		}

		// Уравнение разности винтовой линии и образующей кормовой части
		float vint_and_korm(float x, float x_dop)
		{
			return z_vint(x) - z_kon(x, x_dop);
		}

		// площадь под проекцией винтовой линии, ограниченная x1 и x2
		float S_vint(float x1, float x2)
		{
			return sqr(d) * sqrtf(sqr(M) - 1.0f) / 2.0f * (sinf(2.0f * x2 / (d * sqrtf(sqr(M) - 1.0f))) - sinf(2.0f * x1 / (d * sqrtf(sqr(M) - 1.0f))));
		}

		// функция поиска одного корня в интервале (a, b) методом половинного деления. Необходима для поиска корня с кормовой частью ракеты
		float one_root(float a, float b, float x_dop)
		{
			float c = -1.0f;
			//если при а или b функция равна нулю, то это и есть корень
			if (abs(vint_and_korm(a, x_dop)) < 1e-7f)
				return a;
			else if (abs(vint_and_korm(b, x_dop)) < 1e-7f)
				return b;
			while ((b - a) / 2.0f > 1e-5f) {
				c = (a + b) / 2.0f;
				if ((vint_and_korm(a, x_dop) * vint_and_korm(c, x_dop)) > 0.0f) a = c;
				else b = c;
			}
			return c;
		}
	};

	//Функция поиска корней пересечения с кормовой частью
	std::vector<float> find_roots(VintAndKon np, float x_dop = 0.0f)
	{
		// пределы поиска корней
		float a = np.L_hv - np.d * np.lambda_cor + x_dop;	// расстояние от начала винтовой линии до начала кормовой части
		float b = fmin(np.L_hv + x_dop, np.L_vint);			// правая граница: или донный срез или четверть шага винтовой линии
		std::vector<float> results;

		// следим, чтобы левая граница была меньше четверти шага (иначе получается, что винтовая линия находится до
		// кормовой части и не имеет пересечений с ней)
		if (a < np.L_vint)
		{
			float fa = np.vint_and_korm(a, x_dop);
			float fb = np.vint_and_korm(b, x_dop);

			// у функции один корень в диапазоне
			if (fa * fb < 0)
				results.push_back(np.one_root(a, b, x_dop));
			else
			{
				// иначе исследуем наличие экстремума функции
				// максимальное значение Маха, при котором будет экстремум
				float M_extr_max = sqrtf(sqr(2.0f * np.lambda_cor / (1.0f - np.eta_cor)) + 1.0f);
				float extr = -1.0f;
				
				// если Мах меньше максиального, то рассчитываем экстремум
				if (np.M <= M_extr_max)
					extr = np.d * sqrtf(sqr(np.M) - 1.0f) / 2.0f * asinf(sqrtf(sqr(np.M) - 1.0f) / (2.0f * np.lambda_cor) * (1.0f - np.eta_cor));
				float fextr = np.vint_and_korm(extr, x_dop);

				// проверяем, что экстремум в диапазоне (a,b)
				if (a < extr && extr < b)
				{
					// поиск корня в диапазоне [a,extr]
					if (fa * fextr <= 0)
						results.push_back(np.one_root(a, extr, x_dop));
					// поиск корня в диапазоне [extr,b]
					if (fextr * fb <= 0)
						results.push_back(np.one_root(extr, b, x_dop));
				}
				// если экстремум вне диапазона, но а - корень (когда a == 0)
				else if (a < 1e-7f)
					results.push_back(a);
			}
		}
		return results;
	}

	// Площадь между проекцией винтовой линии и образующей кормовой части Sн
	float S_nar_for_one_vint(VintAndKon np, float x_dop = 0)
	{
		float S_nar = 0.0f;
		// Проверяем налаичие кормовой части
		if (np.eta_cor < 1.0f && np.d * np.lambda_cor > 0.0f)
		{
			// находим точки пересечения с кормовой частью
			std::vector<float> roots = find_roots(np, x_dop);

			// расчет площади
			switch (roots.size())
			{
			// один корень	
			case 1:
			{
				float x1 = roots[0];
				float x2 = np.L_hv + x_dop;
				float S_trap = (x2 - x1) * (np.z_kon(x1, x_dop) + np.z_kon(x2, x_dop));
				S_nar = np.S_vint(x1, x2) - S_trap;
				break;
			}
			// два корня
			case 2:
			{
				float x1 = roots[0];
				float x2 = roots[1];
				float S_trap = (x2 - x1) * (np.z_kon(x1, x_dop) + np.z_kon(x2, x_dop));
				S_nar = np.S_vint(x1, x2) - S_trap;
				break;
			}
			}
		}
		return S_nar;
	}

	float S_bok(float D, float S_nos, float lambda_cil, float lambda_cor, float eta_cor, vector<float>& M, vector<float>& b_b, vector<float>& L_hv)
	{
		// площадь корпуса
		float S_bok = S_nos + sqr(D) * (lambda_cil + 1.0f / 2.0f * (1.0f + eta_cor) * lambda_cor);

		for (size_t i = 0; i < M.size(); i++)
		{
			float S_nar = 0.0f;			// площадь области, выходящей за кормовую часть ракеты
			float S_vn = 0.0f;			// площадь области, выходящей за донный срез ракеты
			float S_peres = 0.0f;		// площадь пересечения областей затенения соседних несущих поверхностей

			if (M[i] > 1.0f)
			{
				// создаем класс для текущей несущей поверхности
				VintAndKon np(D, M[i], b_b[i], L_hv[i], lambda_cor, eta_cor);

				//проевряем возможность пересечения винтовой линии с кормовой частью
				S_nar = S_nar_for_one_vint(np) - S_nar_for_one_vint(np, np.b_b);

				//проверяем возможность выхода винтовой линии за ракету
				if (np.L_hv < np.L_vint)
				{
					S_vn = np.S_vint(np.L_hv, np.L_vint);
					//если первая винтовая линия тоже заходит за ракету
					if (np.L_hv + np.b_b < np.L_vint)
						S_vn -= np.S_vint(np.L_hv + np.b_b, np.L_vint);
				}
			}
			
			// проверяем наличие пересечений между граничными винтовыми линиями несущих поверхностей
			// или винтовая линия - прямая (при околозвуке)
			if (i > 0 && M[i - 1] > 1.0f)
			{
				// создаем класс для предыдущей несущей поверхности
				VintAndKon np_pred(D, M[i - 1], b_b[i - 1], L_hv[i - 1], lambda_cor, eta_cor);

				// расстояние между несущими поверхностями
				float x12 = np_pred.L_hv - (b_b[i] + L_hv[i]);
				if (M[i] <= 1.0f)
				{
					// проверяем условие пересечения винтовой линии и прямой
					if (x12 < np_pred.L_vint)
					{
						//проверяем чтобы первая кривая не вышла за ракету
						float x2_pred = fmin(np_pred.L_hv, np_pred.L_vint);
						S_peres = np_pred.S_vint(x12, x2_pred);
					}
				}
				else
				{
					// создаем класс для текущей несущей поверхности
					VintAndKon np(D, M[i], b_b[i], L_hv[i], lambda_cor, eta_cor);

					// проверяем условие пересечения винтовых линий
					if (x12 + np.L_vint < np_pred.L_vint)
					{

						// точка пересечения несущих поверхностей
						float x_peres = x12 * sqrtf(sqr(np.M) - 1) / (sqrtf(sqr(np_pred.M) - 1) - sqrtf(sqr(np.M) - 1));

						//проверяем, чтобы точка пересечения не была за ракетой
						if (np.b_b + np.L_hv > x_peres)
						{
							//правая граница для расчета площади для предыдущей несущей поверхности
							float x2_pred = fmin(np_pred.L_hv, np_pred.L_vint);

							//правая граница для расчета площади для текущей несущей поверхности
							float x2 = fmin(np.b_b + np.L_hv, np.L_vint);

							S_peres = np_pred.S_vint(x_peres + x12, x2_pred) - np.S_vint(x_peres, x2);
						}
					}
				}
			}
			
			// площадь затененной области текущей несущей поверхности
			float S_ten = D * b_b[i] - S_vn - S_nar;

			// отнимаем полученную площадь от площади корпуса
			S_bok -= S_ten - S_peres;
		}
		return S_bok;
	}

	ErrorCode* get_S_bok(float& Result, float D, float S_nos, float lambda_cil, float lambda_cor, float eta_cor, vector<float>& M, vector<float>& b_b, vector<float>& L_hv)
	{
		static ErrorCode ErrC;

		// Проверка: все аргументы не должны быть меньше 0		
		if (D < 0.0f)
		{
			ErrC.ArgNumber = 1;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (S_nos < 0.0f)
		{
			ErrC.ArgNumber = 2;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (lambda_cil < 0.0f)
		{
			ErrC.ArgNumber = 3;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (lambda_cor < 0.0f)
		{
			ErrC.ArgNumber = 4;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}
		if (eta_cor < 0.0f)
		{
			ErrC.ArgNumber = 5;
			ErrC.Code = ErrC_NumberMustNotBeNeg;
			return &ErrC;
		}

		// Проверка: количество элементов во всех массивах должно совпадать c кол-вом элементов в массиве M
		if (M.size() != b_b.size())
		{
			ErrC.ArgNumber = 7;
			ErrC.Code = ErrC_RowCountMustBeTheSame;
			return &ErrC;
		}
		if (M.size() != L_hv.size())
		{
			ErrC.ArgNumber = 8;
			ErrC.Code = ErrC_RowCountMustBeTheSame;
			return &ErrC;
		}

		// Проверки для массивов
		for (size_t i = 0; i < M.size(); i++)
		{
			// Проверка: все аргументы массивов не должны быть меньше 0
			if (M[i] < 0.0f)
			{
				ErrC.ArgNumber = 6;
				ErrC.Code = ErrC_NumberMustNotBeNeg;
				return &ErrC;
			}
			if (b_b[i] < 0.0f)
			{
				ErrC.ArgNumber = 7;
				ErrC.Code = ErrC_NumberMustNotBeNeg;
				return &ErrC;
			}
			if (L_hv[i] < 0.0f)
			{
				ErrC.ArgNumber = 8;
				ErrC.Code = ErrC_NumberMustNotBeNeg;
				return &ErrC;
			}
			// Проверка: не должно быть пересечения несущих поверхностей (когда L_хв несущей поверхности
			// меньше суммы L_хв и b_б следующей за ней несущей поверхности)
			if (i < M.size() - 1)
			{
				if (L_hv[i] < L_hv[i + 1] + b_b[i + 1])
				{
					ErrC.ArgNumber = 8;
					ErrC.Code = ErrC_PlaneMustNotIntersect;
					return &ErrC;
				}
			}

			//Проверка: несущая поверхность не должна заходить на кормовую часть
			if (L_hv[i] < D * lambda_cor)
			{
				ErrC.ArgNumber = 8;
				ErrC.Code = ErrC_PlaneMustNotBeOverTheCilPart;
				return &ErrC;
			}

			//Проверка: НП не должна заходить на носовую часть
			//т.е. расстояние от конца ракеты до начала бортовой хорды НП должно быть меньше, чем сумма длин цилиндрической и кормовой частей
			if (L_hv[i] + b_b[i] > D * (lambda_cil + lambda_cor))
			{
				ErrC.ArgNumber = 8;
				ErrC.Code = ErrC_PlaneMustNotBeOverTheNosPart;
				return &ErrC;
			}
		}

		// Вызываем функцию
		Result = S_bok(D, S_nos, lambda_cil, lambda_cor, eta_cor, M, b_b, L_hv);
		ErrC.ArgNumber = ErrC_OK;
		ErrC.Code = ErrC_OK;

		return &ErrC;
	}
}