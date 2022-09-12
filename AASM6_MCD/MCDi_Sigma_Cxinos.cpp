#include "pch.h"
#include "MCADINCL.H"
#include "..\AASM6_Library\AASM6\AASM6.h"
#include "ErrorMessages.h"
#include "Extensions.h"

// ����������� ������� (������������ �������� ����������� ��� ������ ��������, ����� - ������� ���������)
LRESULT MCDi_Sigma_Cxinos(COMPLEXARRAY* const retVal,	// ������������ ������
	LPCCOMPLEXSCALAR    M,						// 1-� ��������
	LPCCOMPLEXSCALAR    lambda_nos,				// 2-� ��������
	LPCCOMPLEXSCALAR    nos_typ)				// 3-� ��������
{

	// ��������: ��� ��������� ������ ���� ��������������� ������� (������ ����� = 0),
	// ����� ���������� ������ �1 ��� i-��� ���������
	if (M->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 1);
	if (lambda_nos->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 2);
	if (nos_typ->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 3);

	float result;
	AASM6::ErrorCode* ErrC; //��������� �� ��������� ��� ��������� ���� ������, ������������� �� �������
	AASM6::InputComplex x_1, x_2; //���������� ��� ��������� �������� � ������ ������� ����������, ������������ � �������
	//�������� ������� ������������ �������
	ErrC = AASM6::get_Sigma_Cxinos(result, M->real, lambda_nos->real, nos_typ->real, x_2, x_1);

	//�������� �� ������� �� ������� ������
	if (ErrC->Code != 0) //���� ������
	{
		return MAKELRESULT(ErrC->Code, ErrC->ArgNumber);
	}

	//��������� ������� ���������� ��� ������ � ����������� ����� ��� �������
	COMPLEXSCALAR x_1_mcd = InputComplexToComplexScalar(x_1);
	COMPLEXSCALAR x_2_mcd = InputComplexToComplexScalar(x_2);

	// ��������� ������ ��� ������������ ������ (����� ������� = 1 (���������) + ���������� ������� ����������)
	if (!MathcadArrayAllocate(retVal, (unsigned int)3, (unsigned int)1, TRUE, TRUE))
	{
		// ��� ��������� ��������� ���������� ������
		return MAKELRESULT(ErrMsg::ErrC_MemAlloc, 0);
	}

	// ��� �������� ��������� ��������� �������� �������
	// 0 �������, �������������� ����� - ���������
	retVal->hReal[0][0] = result;	retVal->hImag[0][0] = 0;

	// ��������� �������� - ������� ���������. �������������� ����� - ������� ��������,
	// ������ ����� - ��������� �������� (������� ��� ������ ������� �� ������� �������� ���������)
	retVal->hReal[0][1] = x_2_mcd.real;		retVal->hImag[0][1] = x_2_mcd.imag;
	retVal->hReal[0][2] = x_1_mcd.real;		retVal->hImag[0][2] = x_1_mcd.imag;

	return 0;
}

FUNCTIONINFO AASM6_Sigma_Cxinos = {
	"AASM6_Sigma_Cxinos",					// ��� �� �������� ������� ����� ���������� � Mathcad
	"\n1: M  - ����� ����, -; \n2: lambda_nos - ��������� ������� ����� ��������, -; \n3: nos_typ - ��� ������� ����� (0: ����������, 1: ����������), -",			// ������ ������� ���������� �������
	"\n\n������� ��� ����������� ���������, ������������ ����� ������� ����� � ����� ���� ��� ������� ������������ �������������� ����, �������������� ������������������ �������� �� ������� ����� ��� ��������� ����� �����, -", // �������� �������
	(LPCFUNCTION)MCDi_Sigma_Cxinos,		// ������ �� ����������� ���

	// 1) ��� ������������ � Mathcad ������ - ������ ����������� �����
	// 2) ���������� ������� ���������� �������
	COMPLEX_ARRAY, 3,

	// ��� ��� ������� �������� ���������, ��� ���� - ����������� ����� (������)
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};