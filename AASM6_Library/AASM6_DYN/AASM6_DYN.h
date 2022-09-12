#pragma once

#include <iostream>

#ifdef _EXPORTING
#define DECLSPEC    __declspec(dllexport)
#include "AASM6.h"
#else
#define DECLSPEC    __declspec(dllimport)
#endif

namespace AASM6_DYN
{
#ifdef _EXPORTING
	using namespace AASM6;
#else
	struct ErrorCode
	{
		int Code;
		int ArgNumber;
	};

	struct InputComplex
	{
		float Min;
		float Value;
		float Max;
	};
#endif
	

	/// <summary>
	/// Функция для определения производной по углу атаки коэффициента подъёмной силы комбинации конус-цилиндр
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 153, Рис.3.2.)</para>
	/// </summary>
	/// <param name="Result"> - производная по углу атаки коэффициента подъёмной силы изолированного фюзеляжа, 1/рад</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_nos"> - удлинение носовой части фюзеляжа, -</param>
	/// <param name="lambda_cil"> - удлинение цилиндрической части фюзеляжа, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cyalf_ConCil(float& Result, float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения производной по углу атаки коэффициента подъёмной силы комбинации оживало-цилиндр
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 154, Рис.3.3.)</para>
	/// </summary>
	/// <param name="Result"> - производная по углу атаки коэффициента подъёмной силы изолированного фюзеляжа, 1/рад</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_nos"> - удлинение носовой части фюзеляжа, -</param>
	/// <param name="lambda_cil"> - удлинение цилиндрической части фюзеляжа, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cyalf_OgiCil(float& Result, float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения производной по углу атаки коэффициента подъёмной силы цилиндра со сферическим затуплением или с плоским торцом
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 154, Рис.3.4.)</para>
	/// </summary>
	/// <param name="Result"> - производная по углу атаки коэффициента подъёмной силы изолированного фюзеляжа, 1/рад</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_nos"> - удлинение носовой части фюзеляжа (0 - плоская, 0.5 - сферическая), -</param>
	/// <param name="lambda_cil"> - удлинение цилиндрической части фюзеляжа, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cyalf_SphCil(float& Result, float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения производной по углу атаки коэффициента подъёмной силы изолированной несущей поверхности
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 156, Рис.3.5.)</para>
	/// </summary>
	/// <param name="Result"> - производная по углу атаки коэффициента подъёмной силы изолированной несущей поверхности, 1/рад</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_c"> - удлинение консолей, -</param>
	/// <param name="cc"> - относительная толщина профиля, -</param>
	/// <param name="chi_05"> - угол стреловидности по линии середин хорд, рад</param>
	/// <param name="eta_c"> - сужение консолей, -</param>
	/// <param name="x_3"> - входной комплекс, обозначающий график</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cyalf_IsP(float& Result, float M, float lambda_c, float cc, float chi_05, float eta_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения поправочного множителя, учитывающего влияние числа Маха при расчёте коэффициентов интерференции фюзеляжа и несущей поверхности
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 162, Рис.3.13.)</para>
	/// </summary>
	/// <param name="Result"> - поправочный множитель, учитывающий влияние числа Маха при расчёте коэффициентов интерференции фюзеляжа и несущей поверхности, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_kappa_M(float& Result, float M, InputComplex& x_1);
	/// <summary>
	/// Функция для определения относительной поперечной координаты вихря, сбегающего с консоли несущей поверхности
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 168, Рис.3.16.)</para>
	/// </summary>
	/// <param name="Result"> - относительная поперечная координата вихря, сбегающего с консоли несущей поверхности, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_c"> - удлинение консолей, -</param>
	/// <param name="chi_05"> - угол стреловидности по линии середин хорд, рад</param>
	/// <param name="zeta_c"> - обратное сужение консолей, -</param> 
	/// <param name="x_3"> - входной комплекс, обозначающий график</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Coordinate_zz_v(float& Result, float M, float lambda_c, float chi_05, float zeta_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента интерференции вихрей и задней несущей поверхности
	/// <para>NACA Report 1307 (Chart 7)</para>
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 169, Рис.3.17.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент интерференции вихрей и задней несущей поверхности, -</param>
	/// <param name="zeta_c"> - обратное сужение консолей, -</param>
	/// <param name="D"> - диаметр фюзеляжа, м</param> 
	/// <param name="l"> - размах несущей поверхности, м</param> 
	/// <param name="y_v"> - нормальная координата вихря, м</param> 
	/// <param name="z_v"> - поперечная координата вихря, м</param> 
	/// <param name="x_4"> - входной комплекс, обозначающий группу графиков</param>
	/// <param name="x_3"> - входной комплекс, обозначающий график</param>
	/// <param name="x_2"> - входной комплекс, обозначающий ординату на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_interference_v(float& Result, float zeta_c, float D, float l, float y_v, float z_v, InputComplex& x_4, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента торможения потока, вызванного обтеканием конической носовой части
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 174, Рис.3.21.)</para>
	/// </summary>
	/// <param name="Result"> - Коэффициент торможения потока, вызванного обтеканием конической носовой части, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_nos"> - удлинение носовой части фюзеляжа, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_kM_Con(float& Result, float M, float lambda_nos, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента торможения потока, вызванного обтеканием передней несущей поверхности
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 175, Рис.3.22.)</para>
	/// </summary>
	/// <param name="Result"> - Коэффициент торможения потока, вызванного обтеканием передней несущей поверхности, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="x"> - расстояние между несущими поверхностями, м</param>
	/// <param name="b_Ac"> - средняя аэродинамическая хорда консолей передней несущей поверхности, м</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_kM_P(float& Result, float M, float x, float b_Ac, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента, характеризующего относительную эффективность концевых рулей
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 180, Рис.3.25.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент, характеризующий относительную эффективность концевых рулей, -</param>
	/// <param name="l_r"> - размах рулей, м</param>
	/// <param name="l_c"> - размах консолей несущей поверхности, м</param>
	/// <param name="eta_c"> - обратное сужение консолей, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_nn_Eff1(float& Result, float l_r, float l_c, float zeta_c, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента, характеризующего относительную эффективность рулей, расположенных вдоль задней кромки
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 181, Рис.3.28.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент, характеризующий относительную эффективность рулей, расположенных вдоль задней кромки, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_c"> - удлинение консолей несущей поверхности, -</param>
	/// <param name="bb_r"> - относительная хорда руля, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_nn_Eff2(float& Result, float M, float lambda_c, float bb_r, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициентов, определяющих давление на поверхности профиля по теории 2-ого приближения
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 183, Рис.3.29.)</para>
	/// </summary>
	/// <param name="Result"> - Коэффициенты, определяющие давление на поверхности профиля по теории 2-ого приближения</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="key"> - ключ, определяющий коэффициент, который возвращает функция (0: Cp2/Cp1, 1: Cp1, 2: Cp2)</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cp1_Cp2(float& Result, float M, float key, InputComplex& x_1);
	/// <summary>
	/// Функция для определения среднего по длине цилиндра коэффициента сопротивления при обтекании цилиндра по нормали к его оси
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 187, Рис.3.32.)</para>
	/// </summary>
	/// <param name="Result"> - Средний по длине цилиндра коэффициент сопротивления при обтекании цилиндра по нормали к его оси, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="alpha"> - угол атаки, рад</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cx_Cil_N(float& Result, float M, float alpha, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента дополнительной нормальной силы несущей поверхности при больших углах атаки
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 188, Рис.3.35.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент дополнительной нормальной силы несущей поверхности при больших углах атаки, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="zeta_c"> - обратное сужение консолей, -</param>
	/// <param name="Cyalf_IsP"> - производная по углу атаки коэффициента подъёмной силы изолированной несущей поверхности, 1/рад</param>
	/// <param name="x_3"> - входной комплекс, обозначающий график</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_A_IsP(float& Result, float M, float zeta_c, float Cyalf_IsP, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента трения плоской пластинки при М=0
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 205, Рис.4.2.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент трения плоской пластинки при М=0, -</param>
	/// <param name="Re"> - число Рейнольдса, -</param>
	/// <param name="xx_t"> - относительная координата точки перехода ламинарного пограничного слоя в турбулентный, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cf_M0(float& Result, float Re, float xx_t, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения поправочного множителя, учитывающего влияние числа Маха на коэффициент трения плоской пластинки
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 205, Рис.4.3.)</para>
	/// </summary>
	/// <param name="Result"> - поправочный множитель, учитывающий влияние числа Маха на коэффициент трения плоской пластинки, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="xx_t"> - относительная координата точки перехода ламинарного пограничного слоя в турбулентный, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Sigma_M(float& Result, float M, float xx_t, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения критического числа Рейнольдса при шероховатой поверхности тела, отсутствии теплопередачи и нулевом градиенте давления  
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 208, Рис.4.5.)</para>
	/// </summary>
	/// <param name="Result"> - критическое число Рейнольдса при шероховатой поверхности тела, отсутствии теплопередачи и нулевом градиенте давления, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="Re"> - число Рейнольдса, -</param>
	/// <param name="hh"> - относительная высота бугорков шероховатости поверхности, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Re_t0_1(float& Result, float M, float Re, float hh, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения относительной температуры восстановления и относительной температуры поверхности гладкой стенки, при которой ламинарный пограничный слой является устойчивым
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 210, Рис.4.8.)</para>
	/// </summary>
	/// <param name="Result"> - Относительные температуры</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="key"> - ключ, определяющий относительную температуру, которую возвращает функция (0: Tsl/Tr, 1: Tr/T, 2: Tsl/T)</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_TTr_TTsl(float& Result, float M, float key, InputComplex& x_1);
	/// <summary>
	/// Функция для определения поправочного множителя, учитывающего влияние температуры поверхности тела на критическое число Рейнольдса
	/// <para>Краснов Н.В. Аэродинамика ракет (с. 334, Рис.VI-1-16)</para>
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 210, Рис.4.9.)</para>
	/// </summary>
	/// <param name="Result"> - поправочный множитель, учитывающий влияние температуры поверхности тела на критическое число Рейнольдса</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="TT_s"> - относительная температура поверхности тела (Ts/Tr)</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Sigma_T(float& Result, float M, float TT_s, InputComplex& x_1);
	/// <summary>
	/// Функция для определения поправочного множителя, учитывающего отличие коэффициента трения конуса от коэффициента трения плоской пластинки
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 211, Рис.4.10.)</para>
	/// </summary>
	/// <param name="Result"> - поправочный множитель, учитывающий отличие коэффициента трения конуса от коэффициента трения плоской пластинки, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_nos"> - удлинение носовой части фюзеляжа, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Sigma_Con(float& Result, float M, float lambda_nos, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента сопротивления давления конической носовой части
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 213, Рис.4.11.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент сопротивления давления конической носовой части, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_nos"> - удлинение носовой части фюзеляжа, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cxnos_Con(float& Result, float M, float lambda_nos, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента сопротивления давления параболической носовой части
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 213, Рис.4.12.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент сопротивления давления параболической носовой части, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_nos"> - удлинение носовой части фюзеляжа, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cxnos_Par(float& Result, float M, float lambda_nos, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента сопротивления давления эллиптической носовой части
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 214, Рис.4.13.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент сопротивления давления эллиптической носовой части, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_nos"> - удлинение носовой части фюзеляжа, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cxnos_Ell(float& Result, float M, float lambda_nos, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения числа Маха на поверхности конуса
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 217, Рис.4.15.)</para>
	/// </summary>
	/// <param name="Result"> - число Маха на поверхности конуса, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="teta_Con"> - полуугол при вершине конуса, рад</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Ms_Con(float& Result, float M, float teta_Con, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента сопротивления давления конической кормовой части
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 226, Рис.4.24а.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент сопротивления давления конической кормовой части, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_cor"> - удлинение кормовой части фюзеляжа, -</param>
	/// <param name="eta_cor"> - сужение кормовой части фюзеляжа, -</param>
	/// <param name="x_3"> - входной комплекс, обозначающий график</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cxcor_Con(float& Result, float M, float lambda_cor, float eta_cor, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента сопротивления давления параболической кормовой части
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 226, Рис.4.24б.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент сопротивления давления параболической кормовой части, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_cor"> - удлинение кормовой части фюзеляжа, -</param>
	/// <param name="eta_cor"> - сужение кормовой части фюзеляжа, -</param>
	/// <param name="x_3"> - входной комплекс, обозначающий график</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cxcor_Par(float& Result, float M, float lambda_cor, float eta_cor, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента донного сопротивления фюзеляжа с цилиндрической кормовой частью
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 228, Рис.4.26.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент донного сопротивления фюзеляжа с цилиндрической кормовой частью, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="cc"> - относительная толщина профиля задней несущей поверхности, -</param>
	/// <param name="Re_f06"> - число Рейнольдса для фюзеляжа при скорости, соответствующей М=0.6, -</param>
	/// <param name="Re_f"> - число Рейнольдса для фюзеляжа при скорости, соответствующей М, -</param>
	/// <param name="xx_tf"> - относительная координата точки перехода ламинарного пограничного слоя в турбулентный на фюзеляже, -</param>
	/// <param name="lambda_f"> - удлинение фюзеляжа, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cxdon_Cil(float& Result, float M, float cc, float Re_f06, float Re_f, float xx_tf, float lambda_f, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения поправочного множителя, учитывающего влияние сужающейся кормовой части на коэффициент донного сопротивления фюзеляжа
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 230, Рис.4.27.)</para>
	/// </summary>
	/// <param name="Result"> - поправочный множитель, учитывающий влияние сужающейся кормовой части на коэффициент донного сопротивления фюзеляжа, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_cor"> - удлинение кормовой части фюзеляжа, -</param>
	/// <param name="eta_cor"> - сужение кормовой части фюзеляжа, -</param>	
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Sigma_eta(float& Result, float M, float lambda_cor, float eta_cor, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения поправочного множителя, учитывающего влияние толщины профиля на коэффициент профильного сопротивления несущей поверхности
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 232, Рис.4.28.)</para>
	/// </summary>
	/// <param name="Result"> - поправочный множитель, учитывающий влияние толщины профиля на коэффициент профильного сопротивления несущей поверхности, -</param>
	/// <param name="cc"> - относительная толщина профиля, -</param>
	/// <param name="xx_t"> - относительная координата точки перехода ламинарного пограничного слоя в турбулентный, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Sigma_c(float& Result, float cc, float xx_t, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения поправочного множителя, учитывающего влияние угла стреловидности по передней кромке на критическое число Рейнольдса	
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 232, Рис.4.29.)</para>
	/// </summary>
	/// <param name="Result"> - поправочный множитель, учитывающий влияние угла стреловидности по передней кромке на критическое число Рейнольдса</param>
	/// <param name="chi_0"> - угол стреловидности по передней кромке несущей поверхности, рад</param>	
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Sigma_chi(float& Result, float chi_0, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента волнового сопротивления несущей поверхности с ромбовидным профилем при М >= 1
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 234, Рис.4.30.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент волнового сопротивления несущей поверхности с ромбовидным профилем при М >= 1, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="cc"> - относительная толщина профиля, -</param>
	/// <param name="zeta_c"> - обратное сужение консолей, -</param>
	/// <param name="chi_c"> - угол стреловидности по линии максимальных толщин, рад</param>
	/// <param name="lambda_c"> - удлинение консолей несущей поверхности, -</param>
	/// <param name="x_4"> - входной комплекс, обозначающий график</param>
	/// <param name="x_3"> - входной комплекс, обозначающий семейство кривых на графике</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cxw_Rhomb_M1(float& Result, float M, float cc, float zeta_c, float chi_c, float lambda_c, InputComplex& x_4, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения поправочного множителя, учитывающего степень влияния формы профиля на коэффициент волнового сопротивления несущей поверхности	
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 240, Рис.4.32.)</para>
	/// </summary>
	/// <param name="Result"> - поправочный множитель, учитывающий степень влияния формы профиля на коэффициент волнового сопротивления несущей поверхности</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="chi_c"> - угол стреловидности по линии максимальных толщин, рад</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Sigma_pw(float& Result, float M, float chi_c, InputComplex& x_1);
	/// <summary>
	/// Функция для определения критического числа Маха для симметричных дозвуковых профилей
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 241, Рис.4.34.)</para>
	/// </summary>
	/// <param name="Result"> - критическое число Маха для симметричного дозвукового профиля, -</param>
	/// <param name="cc"> - относительная толщина профиля, -</param>
	/// <param name="Cn"> - коэффициент нормальной силы консолей, -</param>
	/// <param name="xx_c"> - относительная координата линии максимальных толщин, -</param>
	/// <param name="x_3"> - входной комплекс, обозначающий график</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Mcr_pr(float& Result, float cc, float Cn, float xx_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения поправки к критическому числу Маха, учитывающей конечность размаха несущей поверхности
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 242, Рис.4.35.)</para>
	/// </summary>
	/// <param name="Result"> - поправка к критическому числу Маха, учитывающая конечность размаха несущей поверхности, -</param>
	/// <param name="Mcr_pr0"> - критическое число Маха профиля при нулевом коэффициенте нормальной силы консолей, -</param>
	/// <param name="lambda_c"> - удлинение консолей несущей поверхности, -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_DELTA_Mcr0_lambda(float& Result, float Mcr_pr0, float lambda_c, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения поправки к критическому числу Маха, учитывающей стреловидность несущей поверхности
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 242, Рис.4.36.)</para>
	/// </summary>
	/// <param name="Result"> - поправка к критическому числу Маха, учитывающая стреловидность несущей поверхности, -</param>
	/// <param name="Mcr_pr0"> - критическое число Маха профиля при нулевом коэффициенте нормальной силы консолей, -</param>
	/// <param name="chi_c"> - угол стреловидности по линии максимальных толщин, рад</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_DELTA_Mcr0_chi(float& Result, float Mcr_pr0, float chi_c, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента донного сопротивления, создаваемого затупленной задней кромкой профиля несущей поверхности
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 243, Рис.4.38.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент донного сопротивления, создаваемого затупленной задней кромкой профиля несущей поверхности, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Cxdon_pr(float& Result, float M, InputComplex& x_1);
	/// <summary>
	/// Функция для определения множителя, учитывающего форму носовой части и число Маха при расчёте коэффициента тангенциальной силы, индуцированной перераспределением давления на носовой части при ненулевых углах атаки
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 245, Рис.4.40.)</para>
	/// </summary>
	/// <param name="Result"> - множитель, учитывающий форму носовой части и число Маха, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_nos"> - удлинение носовой части фюзеляжа, -</param>
	/// <param name="nos_typ"> - тип носовой части (0: коническая, 1: оживальная), -</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Sigma_Cxinos(float& Result, float M, float lambda_nos, float nos_typ, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения коэффициента пропорциональности подсасывающей силы консолей несущей поверхности
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 246, Рис.4.42.)</para>
	/// </summary>
	/// <param name="Result"> - коэффициент пропорциональности подсасывающей силы консолей несущей поверхности, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_c"> - удлинение консолей несущей поверхности, -</param>
	/// <param name="chi_0"> - угол стреловидности по передней кромке несущей поверхности, рад</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_CC_F_IsP(float& Result, float M, float lambda_c, float chi_0, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения множителя, учитывающего неполноту реализации подсасывающей силы консолей несущей поверхности
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 246, Рис.4.43.)</para>
	/// </summary>
	/// <param name="Result"> - множитель, учитывающий неполноту реализации подсасывающей силы консолей несущей поверхности, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="chi_0"> - угол стреловидности по передней кромке несущей поверхности, рад</param>
	/// <param name="alpha"> - угол атаки несущей поверхности, рад</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Sigma_CF(float& Result, float M, float chi_0, float alpha, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения множителя, учитывающего влияние числа Маха на смещение фокуса комбинации носовой части и цилиндра
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 264, Рис.5.7.)</para>
	/// </summary>
	/// <param name="Result"> - множитель, учитывающий влияние числа Маха на смещение фокуса комбинации носовой части и цилиндра, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_nos"> - удлинение носовой части фюзеляжа, -</param>
	/// <param name="lambda_cil"> - удлинение цилиндрической части фюзеляжа, -</param>	
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_xi_M(float& Result, float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения относительной координаты фокуса изолированной несущей поверхности
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 265, Рис.5.8.)</para>
	/// </summary>
	/// <param name="Result"> - относительная координата фокуса изолированной несущей поверхности, -</param>
	/// <param name="M"> - число Маха, -</param>
	/// <param name="lambda_c"> - удлинение консолей, -</param>	
	/// <param name="chi_05"> - угол стреловидности по линии середин хорд, рад</param>
	/// <param name="zeta_c"> - обратное сужение консолей, -</param>
	/// <param name="x_3"> - входной комплекс, обозначающий график</param>
	/// <param name="x_2"> - входной комплекс, обозначающий кривую на графике</param>
	/// <param name="x_1"> - входной комплекс, обозначающий абсциссу на графике</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_Coordinate_xxF_IsP(float& Result, float M, float lambda_c, float chi_05, float zeta_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1);
	/// <summary>
	/// Функция для определения множителя, учитывающего влияние относительного диаметра фюзеляжа на координату приложения дополнительной нормальной силы консолей
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 268, Рис.5.11.)</para>
	/// </summary>
	/// <param name="Result"> - множитель, учитывающий влияние относительного диаметра фюзеляжа на координату приложения дополнительной нормальной силы консолей, -</param>
	/// <param name="DD"> - относительный диаметр фюзеляжа в районе несущей поверхности, -</param>
	/// <returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode* get_xi_D(float& Result, float DD, InputComplex& x_1);
	/// <summary>
	///	Функция для расчёта незатенённой площади боковой проекции фюзеляжа
	/// <para>Лебедев, Чернобровкин. Динамика полёта БПЛА (с. 185 - 186)</para>
	/// </summary>
	/// <param name="Result"> - площадь незатенённой области фюзеляжа, м2</param>
	///	<param name="D"> - диаметр фюзеляжа, м</param>
	/// <param name="S_nos"> - площадь боковой проекции носовой части, м2</param>
	///	<param name="lambda_cil"> - удлинение цилиндрической части, -</param>
	///	<param name="lambda_cor"> - удлинение кормовой части, -</param>
	///	<param name="eta_cor"> - сужение кормовой части, -</param>
	///	<param name="M"> - массив чисел Маха набегающего потока на каждую несущую поверхность, -</param>
	///	<param name="b_b"> - массив длин бортовой хорды несущих поверхностей, м</param>
	///	<param name="L_hv"> - массив расстояний от конца бортовой хорды несущей поверхности до донного среза фюзеляжа, м</param>
	///	<returns>Код ошибки</returns>
	extern "C" DECLSPEC ErrorCode * get_S_bok(float& Result, float D, float S_nos, float lambda_cil, float lambda_cor, float eta_cor, std::vector<float>&M, std::vector<float>&b_b, std::vector<float>&L_hv);

	// функции для вектора
	extern "C" DECLSPEC std::vector<float>*new_vector();
	extern "C" DECLSPEC void delete_vector(std::vector<float>*v);
	extern "C" DECLSPEC int vector_size(std::vector<float>*v);
	extern "C" DECLSPEC float vector_get(std::vector<float>*v, int i);
	extern "C" DECLSPEC void vector_push_back(std::vector<float>*v, float val);
}