#include "pch.h"
#include "MCADINCL.H"
#include "..\AASM6_Library\AASM6\AASM6.h"
#include "ErrorMessages.h"
#include "Extensions.h"

// Исполняемая функция (возвращаемое значение объявляется как первый аргумент, затем - входные аргументы)
LRESULT MCDi_Sigma_T(COMPLEXARRAY* const retVal,	// Возвращаемый массив
	LPCCOMPLEXSCALAR    M,							// 1-й аргумент
	LPCCOMPLEXSCALAR    TT_s)						// 2-й аргумент	
{
	// Проверка: все аргументы должны быть действительными числами (мнимая часть = 0),
	// иначе вовзращаем ошибку №1 для i-ого аргумента
	if (M->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 1);
	if (TT_s->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 2);

	float result;
	AASM6::ErrorCode* ErrC; //Указатель на структуру для получения кода ошибки, возвращаемого из функции
	AASM6::InputComplex x_1; //Переменные для получения значений и границ входных комплексов, рассчитанных в функции
	//Вызываем функцию интерполяции графика
	ErrC = AASM6::get_Sigma_T(result, M->real, TT_s->real, x_1);

	//Проверка не вернула ли функция ошибку
	if (ErrC->Code != 0) //Есть ошибка
	{
		return MAKELRESULT(ErrC->Code, ErrC->ArgNumber);
	}

	//Обработка входных комплексов под запись в комплексное число для маткада
	COMPLEXSCALAR x_1_mcd = InputComplexToComplexScalar(x_1);

	// Выделение памяти под возвращаемый массив (длина массива = 1 (результат) + количество входных комплексов)
	if (!MathcadArrayAllocate(retVal, (unsigned int)2, (unsigned int)1, TRUE, TRUE))
	{
		// При неудачном выделении возвращаем ошибку
		return MAKELRESULT(ErrMsg::ErrC_MemAlloc, 0);
	}

	// При успешном выделении заполняем элементы массива
	// 0 элемент, действительная часть - результат
	retVal->hReal[0][0] = result;	retVal->hImag[0][0] = 0;

	// следующие элементы - входные комплексы. Действительная часть - текущее значение,
	// мнимая часть - граничное значение (верхняя или нижняя граница по данному входному комплексу)		
	retVal->hReal[0][1] = x_1_mcd.real;		retVal->hImag[0][1] = x_1_mcd.imag;

	return 0;
}

FUNCTIONINFO AASM6_Sigma_T = {
	"AASM6_Sigma_T",					// Имя по которому функция будет вызываться в Mathcad
	"\n1: M  - число Маха, -; \n2: TT_s - относительная температура поверхности тела (Ts/Tr), -",				// Список входных параметров функции
	"\n\nФункция для определения поправочного множителя, учитывающего влияние температуры поверхности тела на критическое число Рейнольдса, -", // Описание функции
	(LPCFUNCTION)MCDi_Sigma_T,			// Ссылка на исполняемый код

	// 1) Тип возвращаемых в Mathcad данных - массив комплексных чисел
	// 2) Количество входных аргументов функции
	COMPLEX_ARRAY, 2,

	// Тип для каждого входного аргумента, для всех - комплексное число (скаляр)
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};