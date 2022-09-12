#include "pch.h"
#include "MCADINCL.H"
#include "..\AASM6_Library\AASM6\AASM6.h"
#include "ErrorMessages.h"
#include "Extensions.h"

// ����������� ������� (������������ �������� ����������� ��� ������ ��������, ����� - ������� ���������)
LRESULT MCDi_Mcr_pr(COMPLEXARRAY* const retVal,	// ������������ ������
	LPCCOMPLEXSCALAR    cc,						// 1-� ��������
	LPCCOMPLEXSCALAR    Cn,						// 2-� ��������
	LPCCOMPLEXSCALAR    xx_c)					// 3-� ��������	
{

	// ��������: ��� ��������� ������ ���� ��������������� ������� (������ ����� = 0),
	// ����� ���������� ������ �1 ��� i-��� ���������
	if (cc->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 1);
	if (Cn->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 2);
	if (xx_c->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 3);

	float result;
	AASM6::ErrorCode* ErrC; //��������� �� ��������� ��� ��������� ���� ������, ������������� �� �������
	AASM6::InputComplex x_1, x_2, x_3; //���������� ��� ��������� �������� � ������ ������� ����������, ������������ � �������
	//�������� ������� ������������ �������
	ErrC = AASM6::get_Mcr_pr(result, cc->real, Cn->real, xx_c->real, x_3, x_2, x_1);

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

FUNCTIONINFO AASM6_Mcr_pr = {
	"AASM6_Mcr_pr",					// ��� �� �������� ������� ����� ���������� � Mathcad
	"\n1: cc - ������������� ������� �������, -; \n2: Cn - ����������� ���������� ���� ��������, -; \n3: xx_c - ������������� ���������� ����� ������������ ������, -",			// ������ ������� ���������� �������
	"\n\n������� ��� ����������� ������������ ����� ���� ��� ������������ ���������� ��������, -", // �������� �������
	(LPCFUNCTION)MCDi_Mcr_pr,		// ������ �� ����������� ���

	// 1) ��� ������������ � Mathcad ������ - ������ ����������� �����
	// 2) ���������� ������� ���������� �������
	COMPLEX_ARRAY, 3,

	// ��� ��� ������� �������� ���������, ��� ���� - ����������� ����� (������)
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};