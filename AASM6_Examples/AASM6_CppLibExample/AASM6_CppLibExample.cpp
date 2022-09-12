// AASM6_CppLibExample.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale>
#include <vector>

#include "..\..\AASM6_Library\AASM6\AASM6.h"

// Для подключения статической библиотеки в свойствах проекта указать путь к библиотеке:
// Свойства Конфигурации -> Компоновщик -> Ввод -> Дополнительные Зависимости 
// указать путь к файлу .lib для всех конфигураций (release, debug, x32, x64) 

// Добавить в #include файл AASM6.h

// Объявляем таблицу с сообщениями об ошибках
const char* ErrorMessageTable[] = {
    /*0*/ "Нет ошибок",
    /*1*/ "Число должно быть действительным",
    /*2*/ "Число не должно быть отрицательным",
    /*3*/ "Число строк/столбцов должно быть больше либо равно 1",
    /*4*/ "Ошибка выделения памяти",
    /*5*/ "Вычисление прервано пользователем",
    /*6*/ "Этот аргумент может быть равен только 0 или 1",
    /*7*/ "Угол должен быть меньше 90 градусов",
    /*8*/ "Число не должно быть больше 1",
    /*9*/ "Этот аргумент не должен быть больше следующего аргумента",
    /*10*/ "Число не должно быть меньше 1",
    /*11*/ "Этот аргумент может быть равен только 0, 1 или 2",
    /*12*/ "Количество элементов в массиве не совпадает с количеством элементов в массиве M",
    /*13*/ "Несущие поверхности не должны пересекаться",
    /*14*/ "Несущая поверхность не должна выходить за цилиндрическую часть ЛА",
    /*15*/ "Несущая поверхность не должна заходить на носовую часть ЛА"
};

/// <summary>
/// Процедура для проверки выхода входных комплексов графиков за границы и сообщения об этом
/// </summary>
/// <param name="x">Входной комплекс, полученный из библиотечной функции</param>
/// <param name="Number">Номер входного комплекса (для отображения в сообщении)</param>
void CheckInputComplex(const AASM6::InputComplex& x, int Number){
    
    std::cout << "x_" << Number << ": " << x.Min << " < " << x.Value << " < " << x.Max;
    if (x.Min <= x.Value || x.Value <= x.Max)
        std::cout << std::endl;
    else
        std::cout << "  ВЫХОД ЗА ГРАНИЦУ!!!" << std::endl;
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    std::cout << "Пример использования статической библиотеки аналитической аэродинамики\n";

    AASM6::ErrorCode* ErrC; //Указатель на структуру для получения кода ошибки, возвращаемого из функции
    AASM6::InputComplex x_1{ 0.0f, 0.0f, 0.0f }, x_2{ 0.0f, 0.0f, 0.0f }, x_3{ 0.0f, 0.0f, 0.0f }, x_4{ 0.0f, 0.0f, 0.0f }; //Структуры для получения значений и границ входных комплексов, рассчитанных в функции

    float M = 4.0f;
    float lambda_nos = 2.0f;
    float lambda_cil = 6.0f;
    float lambda_c = 2.0f;
    float cc = 0.03f;
    float chi_0 = 35.0f / 57.3f;
    float chi_05 = 30.0f / 57.3f;
    float chi_c = 30.0f / 57.3f;
    float eta_c = 2.0f;
    float zeta_c = 1.0f / eta_c;
    float D = 0.13f;
    float zeta_c_II = zeta_c;
    float D_II = D;
    float l_II = 0.3f;
    float y_v = 0.2f;
    float z_v = 0.2f;
    float x_I_II = 1.5f;
    float b_Ac_I = 0.5f;
    float l_r = 0.1f;
    float l_c = 0.3f;
    float bb_r = 0.25f;
    float alpha = 15.0f / 57.3f;
    float Re = 2e7f;
    float Re_f06 = 1.5e7f;
    float xx_t = 0.45f;
    float hh = 3.2e-6f / 3.0f;
    float TT_s = 0.8f;
    float teta_Con = 17.0f / 57.3f;
    float Cn = 0.4f;
    float xx_c = 0.45f;
    float Mcr_pr0 = 0.75f;
    float nos_typ = 0.5f;
    float DD = 0.3f;
    std::vector<float> Ms = { 3.938f, 3.842f };
    std::vector<float> b_bs = { 0.240f,0.115f };
    std::vector<float> L_hvs = { 0.225f, 0.1f };
    float lambda_cor = 0.1f / D;
    float eta_cor = 0.811f;
    
#pragma region get_Cyalf_ConCil (Рис.3.2)
    std::cout << "\nget_Cyalf_ConCil\n";
    float Cyalf_ConCil;
    //Вызов функции
    ErrC = AASM6::get_Cyalf_ConCil(Cyalf_ConCil, M, lambda_nos, lambda_cil, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cyalf_ConCil = " << Cyalf_ConCil << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion
   
#pragma region get_Cyalf_OgiCil (Рис.3.3)
    std::cout << "\nget_Cyalf_OgiCil\n";
    float Cyalf_OgiCil;
    //Вызов функции
    ErrC = AASM6::get_Cyalf_OgiCil(Cyalf_OgiCil, M, lambda_nos, lambda_cil, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cyalf_OgiCil = " << Cyalf_OgiCil << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cyalf_SphCil (Рис.3.4)
    std::cout << "\nget_Cyalf_SphCil\n";
    float Cyalf_SphCil;
    //Вызов функции
    ErrC = AASM6::get_Cyalf_SphCil(Cyalf_SphCil, M, lambda_nos, lambda_cil, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cyalf_SphCil = " << Cyalf_SphCil << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);     
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cyalf_IsP (Рис.3.5)
    std::cout << "\nget_Cyalf_IsP\n";
    float Cyalf_IsP;
    //Вызов функции
    ErrC = AASM6::get_Cyalf_IsP(Cyalf_IsP, M, lambda_c, cc, chi_05, eta_c, x_3, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cyalf_IsP = " << Cyalf_IsP << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
        CheckInputComplex(x_3, 3);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_kappa_M (Рис.3.13)
    std::cout << "\nget_kappa_M\n";
    float kappa_M;
    //Вызов функции
    ErrC = AASM6::get_kappa_M(kappa_M, M, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "kappa_M = " << kappa_M << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);        
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Coordinate_zz_v (Рис.3.16)
    std::cout << "\nget_Coordinate_zz_v\n";
    float zz_v;
    //Вызов функции
    ErrC = AASM6::get_Coordinate_zz_v(zz_v, M, lambda_c, chi_05, zeta_c, x_3, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "zz_v = " << zz_v << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
        CheckInputComplex(x_3, 3);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_interference_v (Рис.3.17)
    std::cout << "\nget_interference_v\n";
    float i_v;
    //Вызов функции
    ErrC = AASM6::get_interference_v(i_v, zeta_c_II, D_II, l_II, y_v, z_v, x_4, x_3, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "i_v = " << i_v << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
        CheckInputComplex(x_3, 3);
        CheckInputComplex(x_4, 4);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_kM_Con (Рис.3.21)
    std::cout << "\nget_kM_Con\n";
    float kM_Con;
    //Вызов функции
    ErrC = AASM6::get_kM_Con(kM_Con, M, lambda_nos, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "kM_Con = " << kM_Con << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_kM_P (Рис.3.22)
    std::cout << "\nget_kM_P\n";
    float kM_P;
    //Вызов функции
    ErrC = AASM6::get_kM_P(kM_P, M, x_I_II, b_Ac_I, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "kM_P = " << kM_P << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_nn_Eff1 (Рис.3.25)
    std::cout << "\nget_nn_Eff1\n";
    float nn_Eff1;
    //Вызов функции
    ErrC = AASM6::get_nn_Eff1(nn_Eff1, l_r, l_c, zeta_c, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "nn_Eff1 = " << nn_Eff1 << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_nn_Eff2 (Рис.3.28)
    std::cout << "\nget_nn_Eff2\n";
    float nn_Eff2;
    //Вызов функции
    ErrC = AASM6::get_nn_Eff2(nn_Eff2, M, lambda_c, bb_r, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "nn_Eff2 = " << nn_Eff2 << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cp1_Cp2 (Рис.3.29)
    std::cout << "\nget_Cp1_Cp2\n";
    float Cp2_Cp1;
    //Вызов функции
    ErrC = AASM6::get_Cp1_Cp2(Cp2_Cp1, M, 0.0f, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cp2_Cp1 = " << Cp2_Cp1 << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);        
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cx_Cil_N (Рис.3.32)
    std::cout << "\nget_Cx_Cil_N\n";
    float Cx_Cil_N;
    //Вызов функции
    ErrC = AASM6::get_Cx_Cil_N(Cx_Cil_N, M, alpha, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cx_Cil_N = " << Cx_Cil_N << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_A_IsP (Рис.3.35)
    std::cout << "\nget_A_IsP\n";
    float A_IsP;
    //Вызов функции
    ErrC = AASM6::get_A_IsP(A_IsP, M, zeta_c, Cyalf_IsP, x_3, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "A_IsP = " << A_IsP << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
        CheckInputComplex(x_3, 3);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cf_M0 (Рис.4.2)
    std::cout << "\nget_Cf_M0\n";
    float Cf_M0;
    //Вызов функции
    ErrC = AASM6::get_Cf_M0(Cf_M0, Re, xx_t, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cf_M0 = " << Cf_M0 << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);        
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Sigma_M (Рис.4.3)
    std::cout << "\nget_Sigma_M\n";
    float Sigma_M;
    //Вызов функции
    ErrC = AASM6::get_Sigma_M(Sigma_M, M, xx_t, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Sigma_M = " << Sigma_M << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Re_t0_1 (Рис.4.5)
    std::cout << "\nget_Re_t0_1\n";
    float Re_t0_1;
    //Вызов функции
    ErrC = AASM6::get_Re_t0_1(Re_t0_1, M, Re, hh, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Re_t0_1 = " << Re_t0_1 << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_TTr_TTsl (Рис.4.8)
    std::cout << "\nget_TTr_TTsl\n";
    float TTsl_TTr;
    //Вызов функции
    ErrC = AASM6::get_TTr_TTsl(TTsl_TTr, M, 0.0f, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "TTsl_TTr = " << TTsl_TTr << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Sigma_T (Рис.4.9)
    std::cout << "\nget_Sigma_T\n";
    float Sigma_T;
    //Вызов функции
    ErrC = AASM6::get_Sigma_T(Sigma_T, M, TT_s, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Sigma_T = " << Sigma_T << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Sigma_Con (Рис.4.10)
    std::cout << "\nget_Sigma_Con\n";
    float Sigma_Con;
    //Вызов функции
    ErrC = AASM6::get_Sigma_Con(Sigma_Con, M, lambda_nos, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Sigma_Con = " << Sigma_Con << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cxnos_Con (Рис.4.11)
    std::cout << "\nget_Cxnos_Con\n";
    float Cxnos_Con;
    //Вызов функции
    ErrC = AASM6::get_Cxnos_Con(Cxnos_Con, M, lambda_nos, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cxnos_Con = " << Cxnos_Con << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cxnos_Par (Рис.4.12)
    std::cout << "\nget_Cxnos_Par\n";
    float Cxnos_Par;
    //Вызов функции
    ErrC = AASM6::get_Cxnos_Par(Cxnos_Par, M, lambda_nos, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cxnos_Par = " << Cxnos_Par << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cxnos_Ell (Рис.4.13)
    std::cout << "\nget_Cxnos_Ell\n";
    float Cxnos_Ell;
    //Вызов функции
    ErrC = AASM6::get_Cxnos_Ell(Cxnos_Ell, M, lambda_nos, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cxnos_Ell = " << Cxnos_Ell << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Ms_Con (Рис.4.15)
    std::cout << "\nget_Ms_Con\n";
    float Ms_Con;
    //Вызов функции
    ErrC = AASM6::get_Ms_Con(Ms_Con, M, teta_Con, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Ms_Con = " << Ms_Con << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cxcor_Con (Рис.4.24a)
    std::cout << "\nget_Cxcor_Con\n";
    float Cxcor_Con;
    //Вызов функции
    ErrC = AASM6::get_Cxcor_Con(Cxcor_Con, M, lambda_cor, eta_cor, x_3, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cxcor_Con = " << Cxcor_Con << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
        CheckInputComplex(x_3, 3);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cxcor_Par (Рис.4.24б)
    std::cout << "\nget_Cxcor_Par\n";
    float Cxcor_Par;
    //Вызов функции
    ErrC = AASM6::get_Cxcor_Par(Cxcor_Par, M, lambda_cor, eta_cor, x_3, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cxcor_Par = " << Cxcor_Par << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
        CheckInputComplex(x_3, 3);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cxdon_Cil (Рис.4.26)
    std::cout << "\nget_Cxdon_Cil\n";
    float Cxdon_Cil;
    //Вызов функции
    ErrC = AASM6::get_Cxdon_Cil(Cxdon_Cil, M, cc, Re_f06, Re, xx_t, lambda_cil, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cxdon_Cil = " << Cxdon_Cil << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Sigma_eta (Рис.4.27)
    std::cout << "\nget_Sigma_eta\n";
    float Sigma_eta;
    //Вызов функции
    ErrC = AASM6::get_Sigma_eta(Sigma_eta, M, lambda_cor, eta_cor, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Sigma_eta = " << Sigma_eta << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Sigma_c (Рис.4.28)
    std::cout << "\nget_Sigma_c\n";
    float Sigma_c;
    //Вызов функции
    ErrC = AASM6::get_Sigma_c(Sigma_c, cc, xx_t, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Sigma_c = " << Sigma_c << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Sigma_chi (Рис.4.29)
    std::cout << "\nget_Sigma_chi\n";
    float Sigma_chi;
    //Вызов функции
    ErrC = AASM6::get_Sigma_chi(Sigma_chi, chi_0, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Sigma_chi = " << Sigma_chi << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cxw_Rhomb_M1 (Рис.4.30)
    std::cout << "\nget_Cxw_Rhomb_M1\n";
    float Cxw_Rhomb_M1;
    //Вызов функции
    ErrC = AASM6::get_Cxw_Rhomb_M1(Cxw_Rhomb_M1, M, cc, zeta_c, chi_c, lambda_c, x_4, x_3, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cxw_Rhomb_M1 = " << Cxw_Rhomb_M1 << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
        CheckInputComplex(x_3, 3);
        CheckInputComplex(x_4, 4);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Sigma_pw (Рис.4.32)
    std::cout << "\nget_Sigma_pw\n";
    float Sigma_pw;
    //Вызов функции
    ErrC = AASM6::get_Sigma_pw(Sigma_pw, M, chi_c, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Sigma_pw = " << Sigma_pw << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Mcr_pr (Рис.4.34)
    std::cout << "\nget_Mcr_pr\n";
    float Mcr_pr;
    //Вызов функции
    ErrC = AASM6::get_Mcr_pr(Mcr_pr, cc, Cn, xx_c, x_3, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Mcr_pr = " << Mcr_pr << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
        CheckInputComplex(x_3, 3);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_DELTA_Mcr0_lambda (Рис.4.35)
    std::cout << "\nget_DELTA_Mcr0_lambda\n";
    float DELTA_Mcr0_lambda;
    //Вызов функции
    ErrC = AASM6::get_DELTA_Mcr0_lambda(DELTA_Mcr0_lambda, Mcr_pr0, lambda_c, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "DELTA_Mcr0_lambda = " << DELTA_Mcr0_lambda << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_DELTA_Mcr0_chi (Рис.4.36)
    std::cout << "\nget_DELTA_Mcr0_chi\n";
    float DELTA_Mcr0_chi;
    //Вызов функции
    ErrC = AASM6::get_DELTA_Mcr0_chi(DELTA_Mcr0_chi, Mcr_pr0, chi_c, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "DELTA_Mcr0_chi = " << DELTA_Mcr0_chi << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Cxdon_pr (Рис.4.38)
    std::cout << "\nget_Cxdon_pr\n";
    float Cxdon_pr;
    //Вызов функции
    ErrC = AASM6::get_Cxdon_pr(Cxdon_pr, M, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Cxdon_pr = " << Cxdon_pr << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Sigma_Cxinos (Рис.4.40)
    std::cout << "\nget_Sigma_Cxinos\n";
    float Sigma_Cxinos;
    //Вызов функции
    ErrC = AASM6::get_Sigma_Cxinos(Sigma_Cxinos, M, lambda_nos, nos_typ, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Sigma_Cxinos = " << Sigma_Cxinos << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_CC_F_IsP (Рис.4.42)
    std::cout << "\nget_CC_F_IsP\n";
    float CC_F_IsP;
    //Вызов функции
    ErrC = AASM6::get_CC_F_IsP(CC_F_IsP, M, lambda_c, chi_0, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "CC_F_IsP = " << CC_F_IsP << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Sigma_CF (Рис.4.43)
    std::cout << "\nget_Sigma_CF\n";
    float Sigma_CF;
    //Вызов функции
    ErrC = AASM6::get_Sigma_CF(Sigma_CF, M, chi_0, alpha, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "Sigma_CF = " << Sigma_CF << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_ksi_M (Рис.5.7)
    std::cout << "\nget_ksi_M\n";
    float ksi_M;
    //Вызов функции
    ErrC = AASM6::get_xi_M(ksi_M, M, lambda_nos, lambda_cil, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "ksi_M = " << ksi_M << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_Coordinate_xxF_IsP (Рис.5.8)
    std::cout << "\nget_Coordinate_xxF_IsP\n";
    float xxF_IsP;
    //Вызов функции
    ErrC = AASM6::get_Coordinate_xxF_IsP(xxF_IsP, M, lambda_c, chi_05, zeta_c, x_3, x_2, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "xxF_IsP = " << xxF_IsP << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
        CheckInputComplex(x_2, 2);
        CheckInputComplex(x_3, 3);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_ksi_D (Рис.5.11)
    std::cout << "\nget_ksi_D\n";
    float ksi_D;
    //Вызов функции
    ErrC = AASM6::get_xi_D(ksi_D, DD, x_1);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "ksi_D = " << ksi_D << std::endl;
        //Вывод значений входных комплексов и проверка выхода их за границы
        CheckInputComplex(x_1, 1);
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

#pragma region get_S_bok
    std::cout << "\nget_S_bok\n";
    float S_bok;
    //Расчет площади носовой части
    float S_nos = 2.0f / 3.0f * lambda_nos * D * D;
    //Вызов функции
    ErrC = AASM6::get_S_bok(S_bok, D, S_nos, lambda_cil, lambda_cor, eta_cor, Ms, b_bs, L_hvs);
    //Проверка не вернула ли функция ошибку
    if (ErrC->Code == 0) //Нет ошибки
    {
        std::cout << "S_bok = " << S_bok << std::endl;
    }
    else //Есть ошибка
    {
        std::cout << "Ошибка! Аргумент №" << ErrC->ArgNumber << " : " << ErrorMessageTable[ErrC->Code] << std::endl;
    }
#pragma endregion

    system("Pause");
}
