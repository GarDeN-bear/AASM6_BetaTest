#include "pch.h"
#include "MCADINCL.H"
#include "..\AASM6_Library\AASM6\AASM6.h"
#include "ErrorMessages.h"
#include "Extensions.h"

// Исполняемая функция (возвращаемое значение объявляется как первый аргумент, затем - входные аргументы)
LRESULT MCDi_Sigma_Cxinos(COMPLEXARRAY* const retVal,	// Возвращаемый массив
	LPCCOMPLEXSCALAR    M,						// 1-й аргумент
	LPCCOMPLEXSCALAR    lambda_nos,				// 2-й аргумент
	LPCCOMPLEXSCALAR    nos_typ)				// 3-й аргумент
{

	// Проверка: все аргументы должны быть действительными числами (мнимая часть = 0),
	// иначе вовзращаем ошибку №1 для i-ого аргумента
	if (M->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 1);
	if (lambda_nos->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 2);
	if (nos_typ->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 3);

	float result;
	AASM6::ErrorCode* ErrC; //Указатель на структуру для получения кода ошибки, возвращаемого из функции
	AASM6::InputComplex x_1, x_2; //Переменные для получения значений и границ входных комплексов, рассчитанных в функции
	//Вызываем функцию интерполяции графика
	ErrC = AASM6::get_Sigma_Cxinos(result, M->real, lambda_nos->real, nos_typ->real, x_2, x_1);

	//Проверка не вернула ли функция ошибку
	if (ErrC->Code != 0) //Есть ошибка
	{
		return MAKELRESULT(ErrC->Code, ErrC->ArgNumber);
	}

	//Обработка входных комплексов под запись в комплексное число для маткада
	COMPLEXSCALAR x_1_mcd = InputComplexToComplexScalar(x_1);
	COMPLEXSCALAR x_2_mcd = InputComplexToComplexScalar(x_2);

	// Выделение памяти под возвращаемый массив (длина массива = 1 (результат) + количество входных комплексов)
	if (!MathcadArrayAllocate(retVal, (unsigned int)3, (unsigned int)1, TRUE, TRUE))
	{
		// При неудачном выделении возвращаем ошибку
		return MAKELRESULT(ErrMsg::ErrC_MemAlloc, 0);
	}

	// При успешном выделении заполняем элементы массива
	// 0 элемент, действительная часть - результат
	retVal->hReal[0][0] = result;	retVal->hImag[0][0] = 0;

	// следующие элементы - входные комплексы. Действительная часть - текущее значение,
	// мнимая часть - граничное значение (верхняя или нижняя граница по данному входному комплексу)
	retVal->hReal[0][1] = x_2_mcd.real;		retVal->hImag[0][1] = x_2_mcd.imag;
	retVal->hReal[0][2] = x_1_mcd.real;		retVal->hImag[0][2] = x_1_mcd.imag;

	return 0;
}

FUNCTIONINFO AASM6_Sigma_Cxinos = {
	"AASM6_Sigma_Cxinos",					// Имя по которому функция будет вызываться в Mathcad
	"\n1: M  - число Маха, -; \n2: lambda_nos - удлинение носовой части фюзеляжа, -; \n3: nos_typ - тип носовой части (0: коническая, 1: оживальная), -",			// Список входных параметров функции
	"\n\nФункция для определения множителя, учитывающего форму носовой части и число Маха при расчёте коэффициента тангенциальной силы, индуцированной перераспределением давления на носовой части при ненулевых углах атаки, -", // Описание функции
	(LPCFUNCTION)MCDi_Sigma_Cxinos,		// Ссылка на исполняемый код

	// 1) Тип возвращаемых в Mathcad данных - массив комплексных чисел
	// 2) Количество входных аргументов функции
	COMPLEX_ARRAY, 3,

	// Тип для каждого входного аргумента, для всех - комплексное число (скаляр)
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};