#pragma once
namespace ErrMsg
{
	//Эти коды ошибок должны совпадать с аналогичными в AASM6.Lib
	extern const int ErrC_OK;
	extern const int ErrC_NumberMustBeReal;
	extern const int ErrC_NumberMustNotBeNeg;
	extern const int ErrC_NumberOfRowsOrColumnsMustBeGE1;
	extern const int ErrC_MemAlloc;
	extern const int ErrC_InterruptByUser;
	extern const int ErrC_ArgMustBe0or1;
	extern const int ErrC_AngleMustBeLT90deg;
	extern const int ErrC_ArgMustNotBeGT1;
	extern const int ErrC_ArgMustNotBeGTNextArg;
	extern const int ErrC_ArgMustNotBeLT1;
	extern const int ErrC_ArgMustBe01or2;
	extern const int ErrC_RowCountMustBeTheSame;
	extern const int ErrC_SurfMustNotIntersect;
	extern const int ErrC_SurfMustNotBeOverTheZcilPart;
	extern const int ErrC_SurfMustNotBeOverTheNosPart;
	
#define ErrorMessageTable_Len 15
	extern const char* ErrorMessageTable[];
}
