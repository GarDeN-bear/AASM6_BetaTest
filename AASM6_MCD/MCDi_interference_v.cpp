#include "pch.h"
#include "MCADINCL.H"
#include "..\AASM6_Library\AASM6\AASM6.h"
#include "ErrorMessages.h"
#include "Extensions.h"

// Исполняемая функция (возвращаемое значение объявляется как первый аргумент, затем - входные аргументы)
LRESULT MCDi_interference_v(COMPLEXARRAY* const retVal,	// Возвращаемый массив
	LPCCOMPLEXSCALAR    zeta_c,							// 1-й аргумент
	LPCCOMPLEXSCALAR    D,								// 2-й аргумент
	LPCCOMPLEXSCALAR    l,								// 3-й аргумент
	LPCCOMPLEXSCALAR    y_v,							// 4-й аргумент
	LPCCOMPLEXSCALAR    z_v)							// 5-й аргумент
{

	// Проверка: все аргументы должны быть действительными числами (мнимая часть = 0),
	// иначе вовзращаем ошибку №1 для i-ого аргумента
	if (zeta_c->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 1);
	if (D->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 2);
	if (l->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 3);
	if (y_v->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 4);
	if (z_v->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 5);

	float result;
	AASM6::ErrorCode* ErrC; //Указатель на структуру для получения кода ошибки, возвращаемого из функции
	AASM6::InputComplex x_1, x_2, x_3, x_4; //Переменные для получения значений и границ входных комплексов, рассчитанных в функции
	//Вызываем функцию интерполяции графика
	ErrC = AASM6::get_interference_v(result, zeta_c->real, D->real, l->real, y_v->real, z_v->real, x_4, x_3, x_2, x_1);

	//Проверка не вернула ли функция ошибку
	if (ErrC->Code != 0) //Есть ошибка
	{
		return MAKELRESULT(ErrC->Code, ErrC->ArgNumber);
	}

	//Обработка входных комплексов под запись в комплексное число для маткада
	COMPLEXSCALAR x_1_mcd = InputComplexToComplexScalar(x_1);
	COMPLEXSCALAR x_2_mcd = InputComplexToComplexScalar(x_2);
	COMPLEXSCALAR x_3_mcd = InputComplexToComplexScalar(x_3);
	COMPLEXSCALAR x_4_mcd = InputComplexToComplexScalar(x_4);

	// Выделение памяти под возвращаемый массив (длина массива = 1 (результат) + количество входных комплексов)
	if (!MathcadArrayAllocate(retVal, (unsigned int)5, (unsigned int)1, TRUE, TRUE))
	{
		// При неудачном выделении возвращаем ошибку
		return MAKELRESULT(ErrMsg::ErrC_MemAlloc, 0);
	}

	// При успешном выделении заполняем элементы массива
	// 0 элемент, действительная часть - результат
	retVal->hReal[0][0] = result;	retVal->hImag[0][0] = 0;

	// следующие элементы - входные комплексы. Действительная часть - текущее значение,
	// мнимая часть - граничное значение (верхняя или нижняя граница по данному входному комплексу)
	retVal->hReal[0][1] = x_4_mcd.real;		retVal->hImag[0][1] = x_4_mcd.imag;
	retVal->hReal[0][2] = x_3_mcd.real;		retVal->hImag[0][2] = x_3_mcd.imag;
	retVal->hReal[0][3] = x_2_mcd.real;		retVal->hImag[0][3] = x_2_mcd.imag;
	retVal->hReal[0][4] = x_1_mcd.real;		retVal->hImag[0][4] = x_1_mcd.imag;

	return 0;
}

FUNCTIONINFO AASM6_interference_v = {
	"AASM6_interference_v",					// Имя по которому функция будет вызываться в Mathcad
	"\n1: zeta_c - обратное сужение консолей, -; \n2: D - диаметр фюзеляжа, м; \n3: l - размах несущей поверхности, м; \n4: y_v - нормальная координата вихря, м; \n5: z_v - поперечная координата вихря, м",			// Список входных параметров функции
	"\n\nФункция для определения коэффициента интерференции вихрей и задней несущей поверхности, -", // Описание функции
	(LPCFUNCTION)MCDi_interference_v,		// Ссылка на исполняемый код

	// 1) Тип возвращаемых в Mathcad данных - массив комплексных чисел
	// 2) Количество входных аргументов функции
	COMPLEX_ARRAY, 5,

	// Тип для каждого входного аргумента, для всех - комплексное число (скаляр)
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};