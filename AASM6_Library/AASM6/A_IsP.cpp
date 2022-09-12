#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
    float A_IsP_1(float zeta_c, float Cyalf_IsP, InputComplex& x_2, InputComplex& x_1)
    {      
        static unsigned int Length_1_1 = 24; static float Matrix_1_1[][2] = { {0.00000f, 2.50779f}, {0.00098f, 2.65123f}, {0.00250f, 2.81772f}, {0.00500f, 2.98851f}, {0.00750f, 3.07873f}, {0.01000f, 3.13185f}, {0.01250f, 3.16184f}, {0.01500f, 3.16650f}, {0.01750f, 3.14681f}, {0.02000f, 3.10856f}, {0.02250f, 3.05367f}, {0.02500f, 2.98329f}, {0.02750f, 2.89791f}, {0.03000f, 2.79736f}, {0.03250f, 2.68066f}, {0.03500f, 2.54552f}, {0.03750f, 2.38721f}, {0.04000f, 2.19481f}, {0.04250f, 1.96878f}, {0.04500f, 1.70665f}, {0.04750f, 1.38473f}, {0.05000f, 0.95771f}, {0.05250f, 0.33594f}, {0.05350f, 0.00000f} };

        //Значения по комплексу x2
        const float x2_min = 0.0f;
        const float x2_max = 1.0f;

        //Входной комплекс x2
        float x2 = zeta_c;        

        x_2.Min = x2_min;
        x_2.Value = x2;
        x_2.Max = x2_max;

        //Ограничение по диапазону x2
        if (x2 < x2_min)
            x2 = x2_min;
        else if (x2 > x2_max)
            x2 = x2_max;

        //Входной комплекс x1
        const float x1_min = 0.0f;
        const float x1_max = 3.065f;

        //Координата по оси х графика
        float x1 = Cyalf_IsP;        

        x_1.Min = x1_min;
        x_1.Value = x1;
        x_1.Max = x1_max;

        //Ограничение по диапазону оси x
        if (x1 < x1_min)
            x1 = x1_min;
        else if (x1 > x1_max)
            x1 = x1_max;

        //Вычисление
        float y = Linterp(Matrix_1_1, Length_1_1, x1 / deg);

        return y;
    }

    float A_IsP_2(float zeta_c, float Cyalf_IsP, InputComplex& x_2, InputComplex& x_1)
    {        
        static unsigned int Length_2_1 = 24; static float Matrix_2_1[][2] = { {0.00000f, 2.50779f}, {0.00109f, 2.29614f}, {0.00250f, 2.11046f}, {0.00500f, 1.86159f}, {0.00750f, 1.66205f}, {0.01000f, 1.49216f}, {0.01250f, 1.34447f}, {0.01500f, 1.21613f}, {0.01750f, 1.10677f}, {0.02000f, 1.00488f}, {0.02250f, 0.90517f}, {0.02500f, 0.80831f}, {0.02750f, 0.71499f}, {0.03000f, 0.62584f}, {0.03250f, 0.54132f}, {0.03500f, 0.46167f}, {0.03750f, 0.38689f}, {0.04000f, 0.31676f}, {0.04250f, 0.25089f}, {0.04500f, 0.18884f}, {0.04750f, 0.13011f}, {0.05000f, 0.07424f}, {0.05250f, 0.02079f}, {0.05350f, 0.00000f} };
        static unsigned int Length_2_2 = 24; static float Matrix_2_2[][2] = { {0.00000f, 2.50779f}, {0.00126f, 2.45919f}, {0.00250f, 2.41169f}, {0.00500f, 2.31560f}, {0.00750f, 2.21951f}, {0.01000f, 2.12342f}, {0.01250f, 2.02733f}, {0.01500f, 1.93124f}, {0.01750f, 1.83466f}, {0.02000f, 1.73238f}, {0.02250f, 1.62234f}, {0.02500f, 1.50354f}, {0.02750f, 1.37487f}, {0.03000f, 1.24267f}, {0.03250f, 1.11047f}, {0.03500f, 0.97827f}, {0.03750f, 0.84607f}, {0.04000f, 0.71387f}, {0.04250f, 0.58168f}, {0.04500f, 0.44948f}, {0.04750f, 0.31728f}, {0.05000f, 0.18508f}, {0.05250f, 0.05288f}, {0.05350f, 0.00000f} };

        //Значения по комплексу x2
        const float x2_min = 0.0f;
        const float x2_max = 1.0f;

        //Входной комплекс x2
        float x2 = zeta_c;
                
        x_2.Min = x2_min;
        x_2.Value = x2;
        x_2.Max = x2_max;

        //Ограничение по диапазону x2
        if (x2 < x2_min)
            x2 = x2_min;
        else if (x2 > x2_max)
            x2 = x2_max;

        //Входной комплекс x1
        const float x1_min = 0.0f;
        const float x1_max = 3.065f;

        //Координата по оси х графика
        float x1 = Cyalf_IsP;
        
        x_1.Min = x1_min;
        x_1.Value = x1;
        x_1.Max = x1_max;

        //Ограничение по диапазону оси x
        if (x1 < x1_min)
            x1 = x1_min;
        else if (x1 > x1_max)
            x1 = x1_max;

        //Вычисление
        if (x2 == x2_min) {
            float y = Linterp(Matrix_2_1, Length_2_1, x1 / deg);

            return y;
        }
        else if (x2_min <= x2 && x2 < x2_max) {
            float y1 = Linterp(Matrix_2_1, Length_2_1, x1 / deg);
            float y2 = Linterp(Matrix_2_2, Length_2_2, x1 / deg);

            return LinterpOnce(x2_min, y1, x2_max, y2, x2);
        }
        else if (x2 == x2_max) {
            float y = Linterp(Matrix_2_2, Length_2_2, x1 / deg);

            return y;
        }
        else
            return NAN;
    }

    float A_IsP(float M, float zeta_c, float Cyalf_IsP, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {       
        // Значения по комплексу x3
        const float x3_min = 0.0f;
        const float x3_2 = 1.1f;
        const float x3_3 = 2.0f;
        const float x3_max = 6.0f;

        //Входной комплекс x3
        float x3 = M;        

        x_3.Min = x3_min;
        x_3.Value = x3;
        x_3.Max = x3_max;

        // Ограничение по диапазону x3   
        if (x3 < x3_min)
            x3 = x3_min;
        else if (x3 > x3_max)
            x3 = x3_max;

        // Вычисление
        if (x3 < x3_2)
        {
            float y = A_IsP_1(zeta_c, Cyalf_IsP, x_2, x_1);

            return y;
        }
        else if (x3_2 <= x3 && x3 < x3_3)
        {
            float y1 = A_IsP_1(zeta_c, Cyalf_IsP, x_2, x_1);
            float y2 = A_IsP_2(zeta_c, Cyalf_IsP, x_2, x_1);

            return LinterpOnce(x3_2, y1, x3_3, y2, x3);
        }
        else 
        {
            float y = A_IsP_2(zeta_c, Cyalf_IsP, x_2, x_1);

            return y;
        }
    }

    ErrorCode* get_A_IsP(float& Result, float M, float zeta_c, float Cyalf_IsP, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        static ErrorCode ErrC;
        // Проверка: некоторые аргументы не должны быть меньше 0		
        if (M < 0.0f)
        {
            ErrC.ArgNumber = 1;
            ErrC.Code = ErrC_NumberMustNotBeNeg;
            return &ErrC;
        }
        if (zeta_c < 0.0f)
        {
            ErrC.ArgNumber = 2;
            ErrC.Code = ErrC_NumberMustNotBeNeg;
            return &ErrC;
        }
        if (Cyalf_IsP < 0.0f)
        {
            ErrC.ArgNumber = 3;
            ErrC.Code = ErrC_NumberMustNotBeNeg;
            return &ErrC;
        }

        // Проверка: некоторые аргументы не должны быть больше 1	
        if (zeta_c > 1.0f)
        {
            ErrC.ArgNumber = 2;
            ErrC.Code = ErrC_ArgMustNotBeGT1;
            return &ErrC;
        }

        // Вызываем функцию интерполяции графика
        Result = A_IsP(M, zeta_c, Cyalf_IsP, x_3, x_2, x_1);
        ErrC.ArgNumber = ErrC_OK;
        ErrC.Code = ErrC_OK;

        return &ErrC;
    }
}