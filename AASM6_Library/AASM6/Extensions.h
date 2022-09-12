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
/// ������� �������� �����������
/// </summary>
/// <param name="XY"> - ���������� ������, � ������� � XY[...][0] �������� ���������� x, � XY[...][1] �������� ��������������� �������� ������� y</param>
/// <param name="x"> - ���������� ��� ������� ����� ���������� ����������������� ��������</param>
/// <returns>y - �������� ������� � ����� � ����������� x</returns>
float Linterp(vector<vector<float> >& XY, float x);


/// <summary>
/// ������� �������� �����������
/// </summary>
/// <param name="XY"> - ���������� ������, � ������� � XY[...][0] �������� ���������� x, � XY[...][1] �������� ��������������� �������� ������� y</param>
/// <param name="size"> - ����� ��������</param>
/// <param name="x"> - ���������� ��� ������� ����� ���������� ����������������� ��������</param>
/// <returns>y - �������� ������� � ����� � ����������� x</returns>
float Linterp(const float XY[][2], unsigned int size, float x);

/// <summary>
/// ������� ���������� ����� � �������
/// </summary>
/// <param name="x"> - ����� ������� ����� �������� � �������</param>
/// <returns>x^2 - �������� � ��������</returns>
float sqr(float x);

/// <summary>
/// ������� �������� ������������ ����� ����� �������
/// </summary>
/// <param name="x1"> - ���������� ������ �����</param>
/// <param name="y1"> - �������� ������� � ������ �����</param>
/// <param name="x2"> - ���������� ������ �����</param>
/// <param name="y2"> - �������� ������� �� ������ �����</param>
/// <param name="x"> - ���������� ��� ������� ����� ���������� ����������������� ��������</param>
/// <returns>y - �������� ������� � ����� � ����������� x</returns>
float LinterpOnce(float x1, float y1, float x2, float y2, float x);

//������� ���������� ������������ �� �������
template <size_t N, size_t M>
/// <summary>
/// ������� ���������� ������������
/// </summary>
/// <param name="X">������, �������� X</param>
/// <param name="Y">������, �������� Y</param>
/// <param name="Z">�������, ��� �������� �������� Z ��������������� � (�� ��������) � Y (�� �������)</param>
/// <param name="x">�������� X ��� �������� ���� ����� ����������������� ��������</param>
/// <param name="y">�������� Y ��� �������� ���� ����� ����������������� ��������</param>
/// <returns>����������������� �������� Z ��� �������� x � y</returns>
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

	//���� ������� �� X ����� �������� ������������� (���� ��� ������� ������� ����� �������� �������������)	
	size_t j = std::upper_bound(std::begin(X), std::end(X), x) - std::begin(X) - 1; //������ ������� (�������� �� x) ������� ������� Z, � ������� (������� �� x) ������� ������ ����� j+1
	if (j == M - 1)
		j--;

	//���� ������� �� Y ����� �������� ������������� (���� ��� ������ ������� ����� �������� �������������)
	size_t i = std::upper_bound(std::begin(Y), std::end(Y), y) - std::begin(Y) - 1; //������ ������ (������� �� y) ������, � ������ (������� �� y) ������ ������ ����� i+1
	if (i == N - 1)
		i--;

	//������������ ��� ����������������� �������� �� X ��� y1 � y2
	float Z_y1 = Z[i][j] * ((X[j + 1] - x) / (X[j + 1] - X[j])) + Z[i][j + 1] * (1 - (X[j + 1] - x) / (X[j + 1] - X[j]));
	float Z_y2 = Z[i + 1][j] * ((X[j + 1] - x) / (X[j + 1] - X[j])) + Z[i + 1][j + 1] * (1 - (X[j + 1] - x) / (X[j + 1] - X[j]));

	//������������� ����� ���� �� Y
	return Z_y1 * ((Y[i + 1] - y) / (Y[i + 1] - Y[i])) + Z_y2 * (1 - (Y[i + 1] - y) / (Y[i + 1] - Y[i]));
}
