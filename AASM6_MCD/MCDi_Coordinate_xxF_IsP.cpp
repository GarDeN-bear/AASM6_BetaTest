#include "pch.h"
#include "MCADINCL.H"
#include "..\AASM6_Library\AASM6\AASM6.h"
#include "ErrorMessages.h"
#include "Extensions.h"

// ����������� ������� (������������ �������� ����������� ��� ������ ��������, ����� - ������� ���������)
LRESULT MCDi_Coordinate_xxF_IsP(COMPLEXARRAY* const retVal,	// ������������ ������
	LPCCOMPLEXSCALAR    M,						// 1-� ��������
	LPCCOMPLEXSCALAR    lambda_c,				// 2-� ��������
	LPCCOMPLEXSCALAR    chi_05,						// 3-� ��������
	LPCCOMPLEXSCALAR    zeta_c)					// 4-� ��������
{

	// ��������: ��� ��������� ������ ���� ��������������� ������� (������ ����� = 0),
	// ����� ���������� ������ �1 ��� i-��� ���������
	if (M->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 1);
	if (lambda_c->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 2);
	if (chi_05->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 3);
	if (zeta_c->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 4);

	float result;
	AASM6::ErrorCode* ErrC; //��������� �� ��������� ��� ��������� ���� ������, ������������� �� �������
	AASM6::InputComplex x_1, x_2, x_3; //���������� ��� ��������� �������� � ������ ������� ����������, ������������ � �������
	//�������� ������� ������������ �������
	ErrC = AASM6::get_Coordinate_xxF_IsP(result, M->real, lambda_c->real, chi_05->real, zeta_c->real, x_3, x_2, x_1);

	//�������� �� ������� �� ������� ������
	if (ErrC->Code != 0) //���� ������
	{
		return MAKELRESULT(ErrC->Code, ErrC->ArgNumber);
	}

	//��������� ������� ���������� ��� ������ � ����������� ����� ��� �������
	COMPLEXSCALAR x_1_mcd = InputComplexToComplexScalar(x_1);
	COMPLEXSCALAR x_2_mcd = InputComplexToComplexScalar(x_2);
	COMPLEXSCALAR x_3_mcd = InputComplexToComplexScalar(x_3);

	// ��������� ������ ��� ������������ ������ (����� ������� = 1 (���������) + ���������� ������� ����������)
	if (!MathcadArrayAllocate(retVal, (unsigned int)4, (unsigned int)1, TRUE, TRUE))
	{
		// ��� ��������� ��������� ���������� ������
		return MAKELRESULT(ErrMsg::ErrC_MemAlloc, 0);
	}

	// ��� �������� ��������� ��������� �������� �������
	// 0 �������, �������������� ����� - ���������
	retVal->hReal[0][0] = result;	retVal->hImag[0][0] = 0;

	// ��������� �������� - ������� ���������. �������������� ����� - ������� ��������,
	// ������ ����� - ��������� �������� (������� ��� ������ ������� �� ������� �������� ���������)
	retVal->hReal[0][1] = x_3_mcd.real;		retVal->hImag[0][1] = x_3_mcd.imag;
	retVal->hReal[0][2] = x_2_mcd.real;		retVal->hImag[0][2] = x_2_mcd.imag;
	retVal->hReal[0][3] = x_1_mcd.real;		retVal->hImag[0][3] = x_1_mcd.imag;

	return 0;
}

FUNCTIONINFO AASM6_Coordinate_xxF_IsP = {
	"AASM6_Coordinate_xxF_IsP",					// ��� �� �������� ������� ����� ���������� � Mathcad
	"\n1: M - ����� ����, -; \n2: lambda_c - ��������� ��������, -; \n3: chi_05 - ���� �������������� �� ����� ������� ����, ���; \n4: zeta_c - �������� ������� ��������, -",			// ������ ������� ���������� �������
	"\n\n������� ��� ����������� ������������� ���������� ������ ������������� ������� �����������, -", // �������� �������
	(LPCFUNCTION)MCDi_Coordinate_xxF_IsP,		// ������ �� ����������� ���

	// 1) ��� ������������ � Mathcad ������ - ������ ����������� �����
	// 2) ���������� ������� ���������� �������
	COMPLEX_ARRAY, 4,

	// ��� ��� ������� �������� ���������, ��� ���� - ����������� ����� (������)
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};