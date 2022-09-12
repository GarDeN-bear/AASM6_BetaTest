#include "pch.h"
#include "Extensions.h"
#include <cmath>

COMPLEXSCALAR InputComplexToComplexScalar(const AASM6::InputComplex& x)
{
	COMPLEXSCALAR x_mcd;
	if (fabs(x.Value - x.Min) < fabs(x.Value - x.Max))
	{
		//�������� ��������� ����� � ����� ������� ��� ������� �� ��
		x_mcd.real = x.Min;
		x_mcd.imag = x.Value;
		// ���� x_mcd.real > x_mcd.imag �� ��� ����� �� ����� �������		
	}
	else
	{
		//�������� ��������� ����� � ������ ������� ��� ������� �� ��
		x_mcd.real = x.Value;
		x_mcd.imag = x.Max;
		// ���� x_mcd.real > x_mcd.imag �� ��� ����� �� ������ �������	
	}
    return x_mcd;
}
