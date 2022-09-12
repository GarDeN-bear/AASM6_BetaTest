#pragma once

#define _USE_MATH_DEFINES
#include <vector>
#include <array>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

const float deg = 57.295779513082320876798154814105f;
# define M_PI           3.14159265358979323846

/// <summary>
/// Функция линейной интеполяции
/// </summary>
/// <param name="XY"> - Двухмерный массив, в котором в XY[...][0] записаны координаты x, в XY[...][1] записаны соответствующие значения функции y</param>
/// <param name="x"> - Координата для которой нужно рассчитать интерполированное значение</param>
/// <returns>y - значение функции в точке с координатой x</returns>
float Linterp(vector<vector<float> >& XY, float x);


/// <summary>
/// Функция линейной интеполяции
/// </summary>
/// <param name="XY"> - Двухмерный массив, в котором в XY[...][0] записаны координаты x, в XY[...][1] записаны соответствующие значения функции y</param>
/// <param name="size"> - Длина массивов</param>
/// <param name="x"> - Координата для которой нужно рассчитать интерполированное значение</param>
/// <returns>y - значение функции в точке с координатой x</returns>
float Linterp(const float XY[][2], unsigned int size, float x);

/// <summary>
/// Функция возведения числа в квадрат
/// </summary>
/// <param name="x"> - Число которое нужно возвести в квадрат</param>
/// <returns>x^2 - Параметр в квадрате</returns>
float sqr(float x);

/// <summary>
/// Функция линейной интерполяции между двумя точками
/// </summary>
/// <param name="x1"> - Координата первой точки</param>
/// <param name="y1"> - Значение функции в первой точке</param>
/// <param name="x2"> - Координата второй точки</param>
/// <param name="y2"> - Значение функции во второй точке</param>
/// <param name="x"> - Координата для которой нужно рассчитать интерполированное значение</param>
/// <returns>y - значение функции в точке с координатой x</returns>
float LinterpOnce(float x1, float y1, float x2, float y2, float x);

//Функция билинейной интерполяции по матрице
template <size_t N, size_t M>
/// <summary>
/// Функция билинейной интерполяции
/// </summary>
/// <param name="X">Массив, значений X</param>
/// <param name="Y">Массив, значений Y</param>
/// <param name="Z">Матрица, где записаны значения Z соответствующие Х (по столбцам) и Y (по строкам)</param>
/// <param name="x">Аргумент X для которого надо найти интерполированное значение</param>
/// <param name="y">Аргумент Y для которого надо найти интерполированное значение</param>
/// <returns>Интерполированное значение Z при заданных x и y</returns>
/// <remarks>
///		X1	X2	X3	...	X_M
/// Y1	Z11	Z12	Z13	...	Z1M
/// Y2	Z21	Z22	Z23	...	Z2M
/// Y3	Z31	Z32	Z33	...	Z3M
/// ...	...	...	...	...	...
/// Y_N	ZN1	ZN2	ZN3	...	ZNM
/// </remarks>
float Bilinterp(float(&X)[M], float(&Y)[N], float(&Z)[N][M], float x, float y)
{
	if (x <= X[0])
		x = X[0];
	else if (x >= X[M - 1])
		x = X[M - 1];

	if (y <= Y[0])
		y = Y[0];
	else if (y >= Y[N - 1])
		y = Y[N - 1];

	//Ищем индексы по X между которыми интерполируем (ищем два столбца матрицы между которыми интерполируем)	
	size_t j = std::upper_bound(std::begin(X), std::end(X), x) - std::begin(X) - 1; //Индекс первого (меньшего по x) столбца матрицы Z, у второго (большой по x) столбца индекс будет j+1
	if (j == M - 1)
		j--;

	//Ищем индексы по Y между которыми интерполируем (ищем две строки матрицы между которыми интерполируем)
	size_t i = std::upper_bound(std::begin(Y), std::end(Y), y) - std::begin(Y) - 1; //Индекс первой (меньшей по y) строки, у второй (большой по y) строки индекс будет i+1
	if (i == N - 1)
		i--;

	//Рассчитываем два интерполированных значения по X при y1 и y2
	float Z_y1 = Z[i][j] * ((X[j + 1] - x) / (X[j + 1] - X[j])) + Z[i][j + 1] * (1 - (X[j + 1] - x) / (X[j + 1] - X[j]));
	float Z_y2 = Z[i + 1][j] * ((X[j + 1] - x) / (X[j + 1] - X[j])) + Z[i + 1][j + 1] * (1 - (X[j + 1] - x) / (X[j + 1] - X[j]));

	//Интерполируем между ними по Y
	return Z_y1 * ((Y[i + 1] - y) / (Y[i + 1] - Y[i])) + Z_y2 * (1 - (Y[i + 1] - y) / (Y[i + 1] - Y[i]));
}
