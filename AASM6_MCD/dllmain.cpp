// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include "mcadincl.h"
#include <ctime>

#include "..\AASM6_Library\AASM6\AASM6.h"
#include "ErrorMessages.h"

extern FUNCTIONINFO AASM6_Cyalf_ConCil;
extern FUNCTIONINFO AASM6_Cyalf_OgiCil;
extern FUNCTIONINFO AASM6_Cyalf_SphCil;
extern FUNCTIONINFO AASM6_Cyalf_IsP;
extern FUNCTIONINFO AASM6_kappa_M;
extern FUNCTIONINFO AASM6_Coordinate_zz_v;
extern FUNCTIONINFO AASM6_interference_v;
extern FUNCTIONINFO AASM6_kM_Con;
extern FUNCTIONINFO AASM6_kM_P;
extern FUNCTIONINFO AASM6_nn_Eff1;
extern FUNCTIONINFO AASM6_nn_Eff2;
extern FUNCTIONINFO AASM6_Cp1_Cp2;
extern FUNCTIONINFO AASM6_Cx_Cil_N;
extern FUNCTIONINFO AASM6_A_IsP;
extern FUNCTIONINFO AASM6_Cf_M0;
extern FUNCTIONINFO AASM6_Sigma_M;
extern FUNCTIONINFO AASM6_Re_t0_1;
extern FUNCTIONINFO AASM6_TTr_TTsl;
extern FUNCTIONINFO AASM6_Sigma_T;
extern FUNCTIONINFO AASM6_Sigma_Con;
extern FUNCTIONINFO AASM6_Cxnos_Con;
extern FUNCTIONINFO AASM6_Cxnos_Par;
extern FUNCTIONINFO AASM6_Cxnos_Ell;
extern FUNCTIONINFO AASM6_Ms_Con;
extern FUNCTIONINFO AASM6_Cxcor_Con;
extern FUNCTIONINFO AASM6_Cxcor_Par;
extern FUNCTIONINFO AASM6_Cxdon_Cil;
extern FUNCTIONINFO AASM6_Sigma_eta;
extern FUNCTIONINFO AASM6_Sigma_c;
extern FUNCTIONINFO AASM6_Sigma_chi;
extern FUNCTIONINFO AASM6_Cxw_Rhomb_M1;
extern FUNCTIONINFO AASM6_Sigma_pw;
extern FUNCTIONINFO AASM6_Mcr_pr;
extern FUNCTIONINFO AASM6_DELTA_Mcr0_lambda;
extern FUNCTIONINFO AASM6_DELTA_Mcr0_chi;
extern FUNCTIONINFO AASM6_Cxdon_pr;
extern FUNCTIONINFO AASM6_Sigma_Cxinos;
extern FUNCTIONINFO AASM6_CC_F_IsP;
extern FUNCTIONINFO AASM6_Sigma_CF;
extern FUNCTIONINFO AASM6_xi_M;
extern FUNCTIONINFO AASM6_Coordinate_xxF_IsP;
extern FUNCTIONINFO AASM6_xi_D;
extern FUNCTIONINFO AASM6_S_bok;

/*
extern FUNCTIONINFO Graffic_5_9;
*/

// Windows точка входа в библиотеку dll
extern "C" BOOL WINAPI DllMain(HINSTANCE hDLL, DWORD dwReason, LPVOID lpReserved)
{
    time_t now = time(0);
    struct tm ltm;
    localtime_s(&ltm, &now);
    int year = ltm.tm_year + 1900;

    switch (dwReason)
    {

        // DLL подключается к адресному пространству вызывающего процесса
    case DLL_PROCESS_ATTACH:

        if (/*year > 2021 &&*/ year < 2023)
        {

            if (!CreateUserErrorMessageTable(hDLL, ErrorMessageTable_Len, ErrMsg::ErrorMessageTable))
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cyalf_ConCil) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cyalf_OgiCil) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cyalf_SphCil) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cyalf_IsP) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_kappa_M) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Coordinate_zz_v) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_interference_v) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_kM_Con) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_kM_P) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_nn_Eff1) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_nn_Eff2) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cp1_Cp2) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cx_Cil_N) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_A_IsP) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cf_M0) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Sigma_M) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Re_t0_1) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_TTr_TTsl) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Sigma_T) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Sigma_Con) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cxnos_Con) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cxnos_Par) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cxnos_Ell) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Ms_Con) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cxcor_Con) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cxcor_Par) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cxdon_Cil) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Sigma_eta) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Sigma_c) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Sigma_chi) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cxw_Rhomb_M1) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Sigma_pw) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Mcr_pr) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_DELTA_Mcr0_lambda) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_DELTA_Mcr0_chi) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Cxdon_pr) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Sigma_Cxinos) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_CC_F_IsP) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Sigma_CF) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_xi_M) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_Coordinate_xxF_IsP) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_xi_D) == NULL)
                break;
            if (CreateUserFunction(hDLL, &AASM6_S_bok) == NULL)
                break;
            /*if (CreateUserFunction(hDLL, &Graffic_5_9) == NULL)
                break;*/
        }
        //Создали пользовательские функции
        break;

        // A new thread is being created in the current process.
    case DLL_THREAD_ATTACH:

        // A thread is exiting cleanly.
    case DLL_THREAD_DETACH:

        // The calling process is detaching the DLL from its address space.
    case DLL_PROCESS_DETACH:

        break;

    }
    return TRUE;
}

