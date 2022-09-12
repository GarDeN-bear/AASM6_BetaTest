#include "pch.h"
#include "MCADINCL.H"
#include "..\AASM6_Library\AASM6\AASM6.h"
#include "ErrorMessages.h"
#include "Extensions.h"

// Исполняемая функция (возвращаемое значение объявляется как первый аргумент, затем - входные аргументы)
LRESULT MCDi_S_bok(COMPLEXSCALAR* const retVal,	// Возвращаемое значение
	LPCCOMPLEXSCALAR    D,					// 1-й аргумент
	LPCCOMPLEXSCALAR    S_nos,				// 2-й аргумент
	LPCCOMPLEXSCALAR    lambda_cil,			// 3-й аргумент
	LPCCOMPLEXSCALAR    lambda_cor,			// 4-й аргумент
	LPCCOMPLEXSCALAR    eta_cor,			// 5-й аргумент
	LPCCOMPLEXARRAY     M,			   		// 6-й аргумент
	LPCCOMPLEXARRAY     b_b,			   	// 7-й аргумент
	LPCCOMPLEXARRAY     L_hv)			   	// 8-й аргумент
{

	// Проверка: все аргументы должны быть действительными числами (мнимая часть = 0),
	// иначе вовзращаем ошибку №1 для i-ого аргумента
	if (D->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 1);
	if (S_nos->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 2);
	if (lambda_cil->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 3);
	if (lambda_cor->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 4);
	if (eta_cor->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 5);
	if (M->hImag != NULL)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 6);
	if (b_b->hImag != NULL)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 7);
	if (L_hv->hImag != NULL)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 8);

	// Проверка: количество элементов во всех массивах должно совпадать,
	// иначе вовзращаем ошибку №12 для i-ого аргумента
	if (M->rows != b_b->rows)
		return MAKELRESULT(ErrMsg::ErrC_RowCountMustBeTheSame, 7);
	if (M->rows != L_hv->rows)
		return MAKELRESULT(ErrMsg::ErrC_RowCountMustBeTheSame, 8);

	//переводим const double const* const* в vector<float>
	std::vector<float> Ms(M->rows);
	std::vector<float> b_bs(b_b->rows);
	std::vector<float> L_hvs(L_hv->rows);
	for (int i = 0; i < M->rows; i++)
	{
		Ms[i] = M->hReal[0][i];
		b_bs[i] = b_b->hReal[0][i];
		L_hvs[i] = L_hv->hReal[0][i];
	}

	float result;
	AASM6::ErrorCode* ErrC; //Указатель на структуру для получения кода ошибки, возвращаемого из функции
	ErrC = AASM6::get_S_bok(result, D->real, S_nos->real, lambda_cil->real, lambda_cor->real, eta_cor->real, Ms, b_bs, L_hvs);

	//Проверка не вернула ли функция ошибку
	if (ErrC->Code != 0) //Есть ошибка
	{
		return MAKELRESULT(ErrC->Code, ErrC->ArgNumber);
	}

	retVal->real = result;
	retVal->imag = NULL;

	if (retVal->real == NULL)
		return MAKELRESULT(ErrMsg::ErrC_MemAlloc, 0);

	return 0;
}

FUNCTIONINFO AASM6_S_bok = {
	"AASM6_S_bok",							// Имя по которому функция будет вызываться в Mathcad
	"\n1: D - диаметр фюзеляжа, м; \n2: S_nos - площадь боковой проекции носовой части, м2;\n3: lambda_cil - удлинение цилиндрической части, -; \n4: lambda_cor - удлинение кормовой части, -; \n5: eta_cor - сужение кормовой части, -; \n6: M - массив чисел Маха набегающего потока на каждую несущую поверхность, -; \n7: b_b - массив длин бортовой хорды несущих поверхностей, м; \n8: L_hv - массив расстояний от конца бортовой хорды до донного среза фюзеляжа, м",			    // Список входных параметров функции
	"\n\nФункция для расчёта незатенённой площади боковой проекции фюзеляжа, м2",							// Описание функции
	(LPCFUNCTION)MCDi_S_bok,			// Ссылка на исполняемый код

	// 1) Тип возвращаемых в Mathcad данных - массив комплексных чисел
	// 2) Количество входных аргументов функции
	COMPLEX_SCALAR, 8,

	// Тип для каждого входного аргумента, для всех - комплексное число (скаляр) и матрица
	{
		COMPLEX_SCALAR,		//D
		COMPLEX_SCALAR,		//S_nos
		COMPLEX_SCALAR,		//lambda_cil
		COMPLEX_SCALAR,		//lambda_cor
		COMPLEX_SCALAR,		//eta_cor
		COMPLEX_ARRAY,		//M
		COMPLEX_ARRAY,		//b_b
		COMPLEX_ARRAY		//L_hv
	}
};