#include "pch.h"
#include "MCADINCL.H"
#include "..\AASM6_Library\AASM6\AASM6.h"
#include "ErrorMessages.h"
#include "Extensions.h"

// ����������� ������� (������������ �������� ����������� ��� ������ ��������, ����� - ������� ���������)
LRESULT MCDi_Cxw_Rhomb_M1(COMPLEXARRAY* const retVal,	// ������������ ������
	LPCCOMPLEXSCALAR    M,								// 1-� ��������
	LPCCOMPLEXSCALAR    cc,								// 2-� ��������
	LPCCOMPLEXSCALAR    zeta_c,							// 3-� ��������
	LPCCOMPLEXSCALAR    chi_c,							// 4-� ��������
	LPCCOMPLEXSCALAR    lambda_c)						// 5-� ��������
{

	// ��������: ��� ��������� ������ ���� ��������������� ������� (������ ����� = 0),
	// ����� ���������� ������ �1 ��� i-��� ���������
	if (M->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 1);
	if (cc->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 2);
	if (zeta_c->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 3);
	if (chi_c->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 4);
	if (lambda_c->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 5);

	float result;
	AASM6::ErrorCode* ErrC; //��������� �� ��������� ��� ��������� ���� ������, ������������� �� �������
	AASM6::InputComplex x_1, x_2, x_3, x_4; //���������� ��� ��������� �������� � ������ ������� ����������, ������������ � �������
	//�������� ������� ������������ �������
	ErrC = AASM6::get_Cxw_Rhomb_M1(result, M->real, cc->real, zeta_c->real, chi_c->real, lambda_c->real, x_4, x_3, x_2, x_1);

	//�������� �� ������� �� ������� ������
	if (ErrC->Code != 0) //���� ������
	{
		return MAKELRESULT(ErrC->Code, ErrC->ArgNumber);
	}

	//��������� ������� ���������� ��� ������ � ����������� ����� ��� �������
	COMPLEXSCALAR x_1_mcd = InputComplexToComplexScalar(x_1);
	COMPLEXSCALAR x_2_mcd = InputComplexToComplexScalar(x_2);
	COMPLEXSCALAR x_3_mcd = InputComplexToComplexScalar(x_3);
	COMPLEXSCALAR x_4_mcd = InputComplexToComplexScalar(x_4);

	// ��������� ������ ��� ������������ ������ (����� ������� = 1 (���������) + ���������� ������� ����������)
	if (!MathcadArrayAllocate(retVal, (unsigned int)5, (unsigned int)1, TRUE, TRUE))
	{
		// ��� ��������� ��������� ���������� ������
		return MAKELRESULT(ErrMsg::ErrC_MemAlloc, 0);
	}

	// ��� �������� ��������� ��������� �������� �������
	// 0 �������, �������������� ����� - ���������
	retVal->hReal[0][0] = result;	retVal->hImag[0][0] = 0;

	// ��������� �������� - ������� ���������. �������������� ����� - ������� ��������,
	// ������ ����� - ��������� �������� (������� ��� ������ ������� �� ������� �������� ���������)
	retVal->hReal[0][1] = x_4_mcd.real;		retVal->hImag[0][1] = x_4_mcd.imag;
	retVal->hReal[0][2] = x_3_mcd.real;		retVal->hImag[0][2] = x_3_mcd.imag;
	retVal->hReal[0][3] = x_2_mcd.real;		retVal->hImag[0][3] = x_2_mcd.imag;
	retVal->hReal[0][4] = x_1_mcd.real;		retVal->hImag[0][4] = x_1_mcd.imag;

	return 0;
}

FUNCTIONINFO AASM6_Cxw_Rhomb_M1 = {
	"AASM6_Cxw_Rhomb_M1",					// ��� �� �������� ������� ����� ���������� � Mathcad
	"\n1: M - ����� ����, -; \n2: cc - ������������� ������� �������, -; \n3: zeta_c - �������� ������� ��������, -; \n4: chi_c - ���� �������������� �� ����� ������������ ������, ���; \n5: lambda_c - ��������� �������� ������� �����������, -",			// ������ ������� ���������� �������
	"\n\n������� ��� ����������� ������������ ��������� ������������� ������� ����������� � ����������� �������� ��� � >= 1, -", // �������� �������
	(LPCFUNCTION)MCDi_Cxw_Rhomb_M1,		// ������ �� ����������� ���

	// 1) ��� ������������ � Mathcad ������ - ������ ����������� �����
	// 2) ���������� ������� ���������� �������
	COMPLEX_ARRAY, 5,

	// ��� ��� ������� �������� ���������, ��� ���� - ����������� ����� (������)
	{COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR, COMPLEX_SCALAR}
};