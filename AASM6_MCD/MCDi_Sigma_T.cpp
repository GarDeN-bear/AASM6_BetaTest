#include "pch.h"
#include "MCADINCL.H"
#include "..\AASM6_Library\AASM6\AASM6.h"
#include "ErrorMessages.h"
#include "Extensions.h"

// ����������� ������� (������������ �������� ����������� ��� ������ ��������, ����� - ������� ���������)
LRESULT MCDi_Sigma_T(COMPLEXARRAY* const retVal,	// ������������ ������
	LPCCOMPLEXSCALAR    M,							// 1-� ��������
	LPCCOMPLEXSCALAR    TT_s)						// 2-� ��������	
{
	// ��������: ��� ��������� ������ ���� ��������������� ������� (������ ����� = 0),
	// ����� ���������� ������ �1 ��� i-��� ���������
	if (M->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 1);
	if (TT_s->imag != 0.0)
		return MAKELRESULT(ErrMsg::ErrC_NumberMustBeReal, 2);

	float result;
	AASM6::ErrorCode* ErrC; //��������� �� ��������� ��� ��������� ���� ������, ������������� �� �������
	AASM6::InputComplex x_1; //���������� ��� ��������� �������� � ������ ������� ����������, ������������ � �������
	//�������� ������� ������������ �������
	ErrC = AASM6::get_Sigma_T(result, M->real, TT_s->real, x_1);

	//�������� �� ������� �� ������� ������
	if (ErrC->Code != 0) //���� ������
	{
		return MAKELRESULT(ErrC->Code, ErrC->ArgNumber);
	}

	//��������� ������� ���������� ��� ������ � ����������� ����� ��� �������
	COMPLEXSCALAR x_1_mcd = InputComplexToComplexScalar(x_1);

	// ��������� ������ ��� ������������ ������ (����� ������� = 1 (���������) + ���������� ������� ����������)
	if (!MathcadArrayAllocate(retVal, (unsigned int)2, (unsigned int)1, TRUE, TRUE))
	{
		// ��� ��������� ��������� ���������� ������
		return MAKELRESULT(ErrMsg::ErrC_MemAlloc, 0);
	}

	// ��� �������� ��������� ��������� �������� �������
	// 0 �������, �������������� ����� - ���������
	retVal->hReal[0][0] = result;	retVal->hImag[0][0] = 0;

	// ��������� �������� - ������� ���������. �������������� ����� - ������� ��������,
	// ������ ����� - ��������� �������� (������� ��� ������ ������� �� ������� �������� ���������)		
	retVal->hReal[0][1] = x_1_mcd.real;		retVal->hImag[0][1] = x_1_mcd.imag;

	return 0;
}

FUNCTIONINFO AASM6_Sigma_T = {
	"AASM6_Sigma_T",					// ��� �� �������� ������� ����� ���������� � Mathcad
	"\n1: M  - ����� ����, -; \n2: TT_s - ������������� ����������� ����������� ���� (Ts/Tr), -",				// ������ ������� ���������� �������
	"\n\n������� ��� ����������� ������������ ���������, ������������ ������� ����������� ����������� ���� �� ����������� ����� ����������, -", // �������� �������
	(LPCFUNCTION)MCDi_Sigma_T,			// ������ �� ����������� ���

	// 1) ��� ������������ � Mathcad ������ - ������ ����������� �����
	// 2) ���������� ������� ���������� �������
	COMPLEX_ARRAY, 2,

	// ��� ��� ������� �������� ���������, ��� ���� - ����������� ����� (������)
	{COMPLEX_SCALAR, COMPLEX_SCALAR}
};