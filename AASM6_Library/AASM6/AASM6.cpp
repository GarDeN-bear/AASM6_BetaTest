// AASM6.cpp : Определяет функции для статической библиотеки.
//

#include "framework.h"

namespace AASM6
{
	//При изменении или добавлении кодов ошибок нужно внести соответсвующие изменения в таблицу сообщений об ошибках
	//в вызывающих программах, в том числе в интерфейсе для маткада AASM6_MCD в файл ErrorMessages.h и .cpp
	extern const int ErrC_OK = 0;
	extern const int ErrC_NumberMustBeReal = 1;
	extern const int ErrC_NumberMustNotBeNeg = 2;
	extern const int ErrC_NumberOfRowsOrColumnsMustBeGE1 = 3;
	extern const int ErrC_MemAlloc = 4;
	extern const int ErrC_InterruptByUser = 5;
	extern const int ErrC_ArgMustBe0or1 = 6;
	extern const int ErrC_AngleMustBeLT90deg = 7;
	extern const int ErrC_ArgMustNotBeGT1 = 8;
	extern const int ErrC_ArgMustNotBeGTNextArg = 9;
	extern const int ErrC_ArgMustNotBeLT1 = 10;
	extern const int ErrC_ArgMustBe01or2 = 11;
	extern const int ErrC_RowCountMustBeTheSame = 12;
	extern const int ErrC_PlaneMustNotIntersect = 13;
	extern const int ErrC_PlaneMustNotBeOverTheCilPart = 14;
	extern const int ErrC_PlaneMustNotBeOverTheNosPart = 15;
}
