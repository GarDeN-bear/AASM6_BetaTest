#include "pch.h"
#include "MCADINCL.H"
#include "..\AASM6_Library\AASM6\AASM6.h"
#include "ErrorMessages.h"
#include "Extensions.h"

// ����������� ������� (������������ �������� ����������� ��� ������ ��������, ����� - ������� ���������)
LRESULT MCDi_DELTA_Mcr0_lambda(COMPLEXARRAY* const retVal,	// ������������ ������
	LPCCOMPLEXSCALAR    Mcr_pr0,						// 1-� ��������
	LPCCOMPLEXSCALAR    lambda_c)				// 2-� ��������	
{
	// ��������: ��� ��������� ������ ���� ��������������� ������� (������ ����� = 0),
	// ����� ���������� ������ �1 ��� i-��� ���������
	if (Mcr_pr0->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 1);
	if (lambda_c->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 2);

	float result;
	AASM6::ErrorCode* ErrC; //��������� �� ��������� ��� ��������� ���� ������, ������������� �� �������
	AASM6::InputComplex x_1, x_2; //���������� ��� ��������� �������� � ������ ������� ����������, ������������ � �������
	//�������� ������� ������������ �������
	ErrC = AASM6::get_DELTA_Mcr0_lambda(result, Mcr_pr0->real, lambda_c->real, x_2, x_1);

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

FUNCTIONINFO AASM6_DELTA_Mcr0_lambda = {
	"AASM6_DELTA_Mcr0_lambda",					// ��� �� �������� ������� ����� ���������� � Mathcad
	"\n1: Mcr_pr0  - ����������� ����� ���� ������� ��� ������� ������������ ���������� ���� ��������, -; \n2: lambda_c - ��������� �������� ������� �����������, -",				// ������ ������� ���������� �������
	"\n\n������� ��� ����������� �������� � ������������ ����� ����, ����������� ���������� ������� ������� �����������, -", // �������� �������
	(LPCFUNCTION)MCDi_DELTA_Mcr0_lambda,			// ������ �� ����������� ���

	// 1) ��� ������������ � Mathcad ������ - ������ ����������� �����
	// 2) ���������� ������� ���������� �������
	COMPLEX_ARRAY, 2,

	// ��� ��� ������� �������� ���������, ��� ���� - ����������� ����� (������)
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};