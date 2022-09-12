#include "AASM6.h"
#include "Extensions.h"

namespace AASM6
{
    /// <summary>График при eta_c=inf zeta_c=0, lambda_c*tan(chi_c)=0: интерполирует по lambda_с*pow(cс, 1.0f/3.0f)</summary> 
    float Cxw_Rhomb_M1_1_1(float x1, float x2)
    {
        static unsigned int Length_1_1 = 32; static float Matrix_1_1[][2] = { {-0.00000, 2.84957}, {0.05250, 2.90779}, {0.05927, 2.97033}, {0.07627, 3.01155}, {0.10443, 3.03635}, {0.16242, 3.03635}, {0.22473, 3.00561}, {0.27666, 2.97172}, {0.33204, 2.92351}, {0.37878, 2.88124}, {0.42378, 2.82989}, {0.47649, 2.77539}, {0.56191, 2.66967}, {0.64476, 2.56940}, {0.73629, 2.47037}, {0.83679, 2.38189}, {0.93549, 2.29361}, {1.06013, 2.20553}, {1.21223, 2.08897}, {1.37508, 1.96767}, {1.54308, 1.84269}, {1.95652, 1.61686}, {2.46357, 1.39493}, {2.95040, 1.21133}, {3.46133, 1.05051}, {3.96791, 0.91867}, {4.44857, 0.82014}, {4.95144, 0.74118}, {5.43509, 0.67816}, {5.94708, 0.61731}, {6.44943, 0.56877}, {7.00000, 0.52458} };
        static unsigned int Length_1_2 = 21; static float Matrix_1_2[][2] = { {-0.00000, 2.60000}, {0.15645, 2.56940}, {0.35984, 2.50602}, {0.47649, 2.45289}, {0.71370, 2.31089}, {0.88425, 2.20553}, {0.97757, 2.14711}, {1.14269, 2.05279}, {1.28177, 1.96767}, {1.46839, 1.86384}, {1.95652, 1.61686}, {2.46357, 1.39493}, {2.95040, 1.21133}, {3.46133, 1.05051}, {3.96791, 0.91867}, {4.44857, 0.82014}, {4.95144, 0.74118}, {5.43509, 0.67816}, {5.94708, 0.61731}, {6.44943, 0.56877}, {7.00000, 0.52458} };
        static unsigned int Length_1_3 = 20; static float Matrix_1_3[][2] = { {-0.00000, 2.09175}, {0.23825, 2.05279}, {0.47649, 2.00422}, {0.72703, 1.93302}, {0.97757, 1.85792}, {1.28177, 1.76878}, {1.46839, 1.70141}, {1.74980, 1.60796}, {1.95652, 1.52465}, {2.21005, 1.42627}, {2.46357, 1.34977}, {2.84834, 1.22685}, {3.46133, 1.05051}, {3.96791, 0.91867}, {4.44857, 0.82014}, {4.95144, 0.74118}, {5.43509, 0.67816}, {5.94708, 0.61731}, {6.44943, 0.56877}, {7.00000, 0.52458} };

        // Значения комплекса x2
        const float x2_min = 0.5f;
        const float x2_2 = 1.0f;
        const float x2_max = 1.5f;

        if (x2 < x2_min) {
            float y = Linterp(Matrix_1_1, Length_1_1, x1);

            return y;
        }
        else if (x2_min <= x2 && x2 < x2_2) {
            float y1 = Linterp(Matrix_1_1, Length_1_1, x1);
            float y2 = Linterp(Matrix_1_2, Length_1_2, x1);

            return LinterpOnce(x2_min, y1, x2_2, y2, x2);

        }
        else if (x2_2 <= x2 && x2 < x2_max) {
            float y1 = Linterp(Matrix_1_2, Length_1_2, x1);
            float y2 = Linterp(Matrix_1_3, Length_1_3, x1);

            return LinterpOnce(x2_2, y1, x2_max, y2, x2);

        }
        else if (x2 >= x2_max) {
            float y = Linterp(Matrix_1_3, Length_1_3, x1);

            return y;
        }
        else
            return NAN;
    }

    /// <summary>График при eta_c=inf zeta_c=0</summary> 
    float Cxw_Rhomb_M1_1(float M, float cc, float chi_c, float lambda_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        static unsigned int Length_1_4 = 15; static float Matrix_1_4[][2] = { {-0.00000, 1.93302}, {0.47649, 1.92051}, {0.97757, 1.85792}, {1.46839, 1.74421}, {1.95652, 1.58617}, {2.46357, 1.39493}, {2.95040, 1.23914}, {3.46133, 1.09602}, {3.96791, 0.97536}, {4.44857, 0.87539}, {4.95144, 0.79107}, {5.43509, 0.71196}, {5.94708, 0.64329}, {6.44943, 0.58939}, {7.00000, 0.54245} };
        static unsigned int Length_1_5 = 15; static float Matrix_1_5[][2] = { {-0.00000, 1.30132}, {0.47649, 1.36362}, {0.97757, 1.39477}, {1.46839, 1.37594}, {1.95652, 1.32986}, {2.46357, 1.26554}, {2.95040, 1.18817}, {3.46133, 1.09602}, {3.96791, 1.00561}, {4.44857, 0.90912}, {4.95144, 0.81871}, {5.43509, 0.73975}, {5.94708, 0.66658}, {6.44943, 0.60573}, {7.00000, 0.56444} };
        static unsigned int Length_1_6 = 15; static float Matrix_1_6[][2] = { {-0.00000, 0.79181}, {0.47649, 0.83913}, {0.97757, 0.88544}, {1.46839, 0.93051}, {1.95652, 0.96055}, {2.46357, 0.99185}, {2.95040, 0.99936}, {3.46133, 0.98559}, {3.96791, 0.95179}, {4.44857, 0.89796}, {4.95144, 0.84671}, {5.43509, 0.78672}, {5.94708, 0.71805}, {6.44943, 0.65459}, {7.00000, 0.60069} };
        static unsigned int Length_1_7 = 15; static float Matrix_1_7[][2] = { {-0.00000, 0.44436}, {0.47649, 0.47391}, {0.97757, 0.50270}, {1.46839, 0.52773}, {1.95652, 0.55778}, {2.46357, 0.60159}, {2.95040, 0.64791}, {3.46133, 0.68922}, {3.96791, 0.72677}, {4.44857, 0.75306}, {4.95144, 0.76900}, {5.43509, 0.77044}, {5.94708, 0.74871}, {6.44943, 0.71177}, {7.00000, 0.63570} };

        //Значения по комплексу x3
        const float x3_min = 0.0f;
        const float x3_2 = 1.0f;
        const float x3_3 = 2.0f;
        const float x3_4 = 3.0f;
        const float x3_max = 4.0f;

        //Входной комплекс x3
        float x3 = lambda_c * tan(chi_c);

        x_3.Min = x3_min;
        x_3.Value = x3;
        x_3.Max = x3_max;

        //Ограничение по диапазону x3
        if (x3 < x3_min)
            x3 = x3_min;
        else if (x3 > x3_max)
            x3 = x3_max;

        //Входной комплекс x2
        float x2 = lambda_c * pow(cc, 1.0f / 3.0f);

        const float x2_min = 0.5f;
        const float x2_max = 1.5f;

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
        const float x1_max = 7.0f;

        //Координата по оси х графика
        float x1 = lambda_c * sqrt(sqr(M) - 1.0f);

        x_1.Min = x1_min;
        x_1.Value = x1;
        x_1.Max = x1_max;

        //Ограничение по диапазону оси x
        if (x1 < x1_min)
            x1 = x1_min;
        else if (x1 > x1_max)
            x1 = x1_max;

        //Вычисление
        if (x3 == x3_min) {
            return Cxw_Rhomb_M1_1_1(x1, x2);
        }
        else if (x3_min <= x3 && x3 < x3_2) {
            float y1 = Cxw_Rhomb_M1_1_1(x1, x2);
            float y2 = Linterp(Matrix_1_4, Length_1_4, x1);

            return LinterpOnce(x3_min, y1, x3_2, y2, x3);
        }
        else if (x3_2 <= x3 && x3 < x3_3) {
            float y1 = Linterp(Matrix_1_4, Length_1_4, x1);
            float y2 = Linterp(Matrix_1_5, Length_1_5, x1);

            return LinterpOnce(x3_2, y1, x3_3, y2, x3);
        }
        else if (x3_3 <= x3 && x3 < x3_4) {
            float y1 = Linterp(Matrix_1_5, Length_1_5, x1);
            float y2 = Linterp(Matrix_1_6, Length_1_6, x1);

            return LinterpOnce(x3_3, y1, x3_4, y2, x3);
        }
        else if (x3_4 <= x3 && x3 < x3_max) {
            float y1 = Linterp(Matrix_1_6, Length_1_6, x1);
            float y2 = Linterp(Matrix_1_7, Length_1_7, x1);

            return LinterpOnce(x3_4, y1, x3_max, y2, x3);
        }
        else if (x3 == x3_max) {
            float y = Linterp(Matrix_1_7, Length_1_7, x1);

            return y;
        }
        else
            return NAN;
    }
    

    /// <summary>График при eta_c=5 zeta_c=0.2, lambda_c*tan(chi_c)=0: интерполирует по lambda_с*pow(cс, 1.0f/3.0f)</summary> 
    float Cxw_Rhomb_M1_2_1(float x1, float x2)        
    {
        static unsigned int Length_1_1 = 32; static float Matrix_1_1[][2] = { {0.00000, 2.84395}, {0.09202, 2.95629}, {0.13315, 3.01395}, {0.18674, 3.06913}, {0.22413, 3.10690}, {0.29890, 3.13474}, {0.37741, 3.12032}, {0.42602, 3.07062}, {0.47649, 3.00749}, {0.55363, 2.89892}, {0.63140, 2.79855}, {0.70169, 2.71461}, {0.76899, 2.62752}, {0.83653, 2.54735}, {0.97757, 2.40777}, {1.05194, 2.31394}, {1.20298, 2.16245}, {1.33691, 2.03610}, {1.46839, 1.91195}, {1.63218, 1.79693}, {1.82128, 1.67589}, {1.97801, 1.59345}, {2.35193, 1.39523}, {2.85011, 1.20088}, {3.46133, 1.01173}, {3.96791, 0.88203}, {4.44857, 0.77723}, {4.95144, 0.69907}, {5.43509, 0.63379}, {5.94708, 0.58311}, {6.44943, 0.53759}, {7.00000, 0.49464} };
        static unsigned int Length_1_2 = 24; static float Matrix_1_2[][2] = { {0.00000, 2.68148}, {0.19296, 2.65582}, {0.35746, 2.61655}, {0.47649, 2.57629}, {0.65985, 2.49226}, {0.78648, 2.41908}, {0.86917, 2.35723}, {0.97757, 2.27065}, {1.12631, 2.15005}, {1.33691, 2.00230}, {1.46839, 1.91195}, {1.63218, 1.79693}, {1.82128, 1.67589}, {1.95652, 1.60484}, {2.35193, 1.39523}, {2.85011, 1.20088}, {3.46133, 1.01173}, {3.96791, 0.88203}, {4.44857, 0.77723}, {4.95144, 0.69907}, {5.43509, 0.63379}, {5.94708, 0.58311}, {6.44943, 0.53759}, {7.00000, 0.49464} };
        static unsigned int Length_1_3 = 22; static float Matrix_1_3[][2] = { {0.00000, 2.11439}, {0.23890, 2.09927}, {0.47649, 2.06148}, {0.75137, 2.00230}, {0.97757, 1.95063}, {1.20742, 1.87886}, {1.40682, 1.79693}, {1.62900, 1.69273}, {1.82878, 1.59345}, {1.95652, 1.51911}, {2.22236, 1.39523}, {2.46357, 1.29924}, {2.75604, 1.20088}, {3.13882, 1.09402}, {3.44753, 1.01600}, {3.96791, 0.88203}, {4.44857, 0.77723}, {4.95144, 0.69907}, {5.43509, 0.63379}, {5.94708, 0.58311}, {6.44943, 0.53759}, {7.00000, 0.49464} };

        // Значения комплекса x2
        const float x2_min = 0.5f;
        const float x2_2 = 1.0f;
        const float x2_max = 1.5f;

        if (x2 < x2_min) {
            float y = Linterp(Matrix_1_1, Length_1_1, x1);

            return y;
        }
        else if (x2_min <= x2 && x2 < x2_2) {
            float y1 = Linterp(Matrix_1_1, Length_1_1, x1);
            float y2 = Linterp(Matrix_1_2, Length_1_2, x1);

            return LinterpOnce(x2_min, y1, x2_2, y2, x2);

        }
        else if (x2_2 <= x2 && x2 < x2_max) {
            float y1 = Linterp(Matrix_1_2, Length_1_2, x1);
            float y2 = Linterp(Matrix_1_3, Length_1_3, x1);

            return LinterpOnce(x2_2, y1, x2_max, y2, x2);

        }
        else if (x2 >= x2_max) {
            float y = Linterp(Matrix_1_3, Length_1_3, x1);

            return y;
        }
        else
            return NAN;
    }

    /// <summary>График при eta_c=5 zeta_c=0.2</summary> 
    float Cxw_Rhomb_M1_2(float M, float cc, float chi_c, float lambda_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        static unsigned int Length_1_4 = 22; static float Matrix_1_4[][2] = { {0.00000, 1.84684}, {0.23890, 1.93703}, {0.47649, 1.98114}, {0.71046, 2.00000}, {0.97757, 1.98824}, {1.27506, 1.93011}, {1.46839, 1.86712}, {1.63218, 1.79693}, {1.80626, 1.69605}, {2.15546, 1.52896}, {2.46357, 1.39523}, {2.74049, 1.29418}, {2.95040, 1.22045}, {3.20888, 1.13671}, {3.58754, 1.03292}, {3.96791, 0.92763}, {4.44857, 0.82621}, {4.95144, 0.73591}, {5.43509, 0.66833}, {5.94708, 0.60606}, {6.44943, 0.55933}, {7.00000, 0.51046} };
        static unsigned int Length_1_5 = 21; static float Matrix_1_5[][2] = { {0.00000, 1.06635}, {0.47649, 1.21581}, {0.97757, 1.36146}, {1.21901, 1.41664}, {1.46839, 1.45292}, {1.62778, 1.46684}, {1.83445, 1.46684}, {1.95652, 1.45766}, {2.20774, 1.43149}, {2.46357, 1.39523}, {2.74049, 1.33344}, {2.95040, 1.28622}, {3.29050, 1.20088}, {3.46133, 1.15913}, {3.96791, 1.01895}, {4.44857, 0.91039}, {4.95144, 0.80779}, {5.43509, 0.72786}, {5.94708, 0.65447}, {6.44943, 0.60022}, {7.00000, 0.54151} };
        static unsigned int Length_1_6 = 18; static float Matrix_1_6[][2] = { {0.00000, 0.60022}, {0.47649, 0.68549}, {0.97757, 0.78070}, {1.46839, 0.88377}, {1.95652, 0.98971}, {2.23150, 1.03735}, {2.46357, 1.06369}, {2.72750, 1.08308}, {2.95040, 1.09402}, {3.23597, 1.09402}, {3.46133, 1.08656}, {3.96791, 1.04232}, {4.44857, 0.96529}, {4.95144, 0.88449}, {5.43509, 0.80035}, {5.94708, 0.71169}, {6.44943, 0.64608}, {7.00000, 0.58703} };
        static unsigned int Length_1_7 = 17; static float Matrix_1_7[][2] = { {0.00000, 0.31749}, {0.47649, 0.37158}, {0.97757, 0.42501}, {1.46839, 0.47874}, {1.95652, 0.54746}, {2.46357, 0.63192}, {2.95040, 0.71138}, {3.46133, 0.78152}, {3.96791, 0.83950}, {4.24058, 0.86527}, {4.44857, 0.87386}, {4.73808, 0.88251}, {4.95144, 0.87953}, {5.43509, 0.85368}, {5.94708, 0.80035}, {6.44943, 0.73134}, {7.00000, 0.63041} };

        //Значения по комплексу x3
        const float x3_min = 0.0f;
        const float x3_2 = 1.0f;
        const float x3_3 = 2.0f;
        const float x3_4 = 3.0f;
        const float x3_max = 4.0f;

        //Входной комплекс x3
        float x3 = lambda_c * tan(chi_c);        

        x_3.Min = x3_min;
        x_3.Value = x3;
        x_3.Max = x3_max;

        //Ограничение по диапазону x3
        if (x3 < x3_min)
            x3 = x3_min;
        else if (x3 > x3_max)
            x3 = x3_max;

        //Входной комплекс x2
        float x2 = lambda_c * pow(cc, 1.0f / 3.0f);        

        const float x2_min = 0.5f;
        const float x2_max = 1.5f;

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
        const float x1_max = 7.0f;

        //Координата по оси х графика
        float x1 = lambda_c * sqrt(sqr(M) - 1.0f);       

        x_1.Min = x1_min;
        x_1.Value = x1;
        x_1.Max = x1_max;

        //Ограничение по диапазону оси x
        if (x1 < x1_min)
            x1 = x1_min;
        else if (x1 > x1_max)
            x1 = x1_max;

        //Вычисление
        if (x3 == x3_min) {
            return Cxw_Rhomb_M1_2_1(x1, x2);
        }
        else if (x3_min <= x3 && x3 < x3_2) {
            float y1 = Cxw_Rhomb_M1_2_1(x1, x2);
            float y2 = Linterp(Matrix_1_4, Length_1_4, x1);

            return LinterpOnce(x3_min, y1, x3_2, y2, x3);

        }
        else if (x3_2 <= x3 && x3 < x3_3) {
            float y1 = Linterp(Matrix_1_4, Length_1_4, x1);
            float y2 = Linterp(Matrix_1_5, Length_1_5, x1);

            return LinterpOnce(x3_2, y1, x3_3, y2, x3);

        }
        else if (x3_3 <= x3 && x3 < x3_4) {
            float y1 = Linterp(Matrix_1_5, Length_1_5, x1);
            float y2 = Linterp(Matrix_1_6, Length_1_6, x1);

            return LinterpOnce(x3_3, y1, x3_4, y2, x3);

        }
        else if (x3_4 <= x3 && x3 < x3_max) {
            float y1 = Linterp(Matrix_1_6, Length_1_6, x1);
            float y2 = Linterp(Matrix_1_7, Length_1_7, x1);

            return LinterpOnce(x3_4, y1, x3_max, y2, x3);

        }
        else if (x3 == x3_max) {
            float y = Linterp(Matrix_1_7, Length_1_7, x1);

            return y;
        }
        else
            return NAN;
    }
    

    /// <summary>График при eta_c=1 zeta_c=1, lambda_c*tan(chi_c)=0: интерполирует по lambda_с*pow(cс, 1.0f/3.0f)</summary>    
    float Cxw_Rhomb_M1_3_1(float x1, float x2)
    {
        static unsigned int Length_1_1 = 33; static float Matrix_1_1[][2] = { {0.00000f, 2.84095f}, {0.06251f, 2.91218f}, {0.09993f, 2.97719f}, {0.14681f, 3.06578f}, {0.19831f, 3.15707f}, {0.23033f, 3.20567f}, {0.27910f, 3.22577f}, {0.31334f, 3.23251f}, {0.36203f, 3.22267f}, {0.41525f, 3.19976f}, {0.47649f, 3.15770f}, {0.53688f, 3.08827f}, {0.58673f, 3.03338f}, {0.64904f, 2.96490f}, {0.70683f, 2.88389f}, {0.78005f, 2.80037f}, {0.93726f, 2.59250f}, {1.09128f, 2.39805f}, {1.28044f, 2.19699f}, {1.38088f, 2.05413f}, {1.52270f, 1.89196f}, {1.64051f, 1.79465f}, {1.95652f, 1.60632f}, {2.46357f, 1.33231f}, {2.81340f, 1.18675f}, {3.37977f, 0.99016f}, {3.96791f, 0.82416f}, {4.44857f, 0.73106f}, {4.95144f, 0.66215f}, {5.43509f, 0.61255f}, {5.94708f, 0.57238f}, {6.44943f, 0.53975f}, {7.00000f, 0.51220f} };
        static unsigned int Length_1_2 = 24; static float Matrix_1_2[][2] = { {0.00000f, 2.75104f}, {0.18736f, 2.74305f}, {0.34522f, 2.71788f}, {0.47649f, 2.67802f}, {0.67842f, 2.59250f}, {0.81307f, 2.51039f}, {0.97757f, 2.39805f}, {1.17845f, 2.19699f}, {1.38088f, 1.99655f}, {1.46839f, 1.90825f}, {1.64051f, 1.79465f}, {1.95652f, 1.60632f}, {2.36977f, 1.38282f}, {2.46357f, 1.33231f}, {2.81340f, 1.18675f}, {2.95040f, 1.13920f}, {3.37977f, 0.99016f}, {3.96791f, 0.82416f}, {4.44857f, 0.73106f}, {4.95144f, 0.66215f}, {5.43509f, 0.61255f}, {5.94708f, 0.57238f}, {6.44943f, 0.53975f}, {7.00000f, 0.51220f} };
        static unsigned int Length_1_3 = 23; static float Matrix_1_3[][2] = { {0.00000f, 2.10860f}, {0.17669f, 2.10860f}, {0.35532f, 2.09643f}, {0.47649f, 2.08049f}, {0.65470f, 2.05112f}, {0.88290f, 1.99655f}, {1.06525f, 1.93793f}, {1.25911f, 1.86660f}, {1.42182f, 1.79465f}, {1.59318f, 1.71833f}, {1.79851f, 1.62315f}, {2.09572f, 1.48405f}, {2.45582f, 1.33648f}, {2.81340f, 1.18675f}, {2.95040f, 1.13920f}, {3.37977f, 0.99016f}, {3.96791f, 0.82416f}, {4.44857f, 0.73106f}, {4.95144f, 0.66215f}, {5.43509f, 0.61255f}, {5.94708f, 0.57238f}, {6.44943f, 0.53975f}, {7.00000f, 0.51220f} };

        // Значения комплекса x2
        const float x2_min = 0.5f;
        const float x2_2 = 1.0f;
        const float x2_max = 1.5f;

        if (x2 < x2_min) {
            float y = Linterp(Matrix_1_1, Length_1_1, x1);

            return y;
        }
        else if (x2_min <= x2 && x2 < x2_2) {
            float y1 = Linterp(Matrix_1_1, Length_1_1, x1);
            float y2 = Linterp(Matrix_1_2, Length_1_2, x1);

            return LinterpOnce(x2_min, y1, x2_2, y2, x2);
        }
        else if (x2_2 <= x2 && x2 < x2_max) {
            float y1 = Linterp(Matrix_1_2, Length_1_2, x1);
            float y2 = Linterp(Matrix_1_3, Length_1_3, x1);

            return LinterpOnce(x2_2, y1, x2_max, y2, x2);
        }
        else if (x2 >= x2_max) {
            float y = Linterp(Matrix_1_3, Length_1_3, x1);

            return y;
        }
        else
            return NAN;
    }

    /// <summary>График при eta_c=1 zeta_c=1</summary> 
    float Cxw_Rhomb_M1_3(float M, float cc, float chi_c, float lambda_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        static unsigned int Length_1_4 = 24; static float Matrix_1_4[][2] = { {0.00000f, 1.52104f}, {0.25609f, 1.68237f}, {0.47649f, 1.86787f}, {0.58356f, 1.96371f}, {0.72584f, 2.03169f}, {0.97757f, 2.08708f}, {1.14971f, 2.08226f}, {1.32200f, 2.05413f}, {1.46839f, 2.01771f}, {1.57701f, 1.96923f}, {1.66249f, 1.91725f}, {1.84071f, 1.79465f}, {1.95652f, 1.72188f}, {2.18901f, 1.58912f}, {2.46357f, 1.44012f}, {2.95040f, 1.23130f}, {3.46133f, 1.05393f}, {3.96791f, 0.93710f}, {4.44857f, 0.83522f}, {4.95144f, 0.74786f}, {5.43509f, 0.67297f}, {5.94708f, 0.61106f}, {6.44943f, 0.56622f}, {7.00000f, 0.52861f} };
        static unsigned int Length_1_5 = 20; static float Matrix_1_5[][2] = { {0.00000f, 0.86671f}, {0.47649f, 0.97185f}, {0.97757f, 1.14297f}, {1.46839f, 1.36267f}, {1.68152f, 1.45677f}, {1.80926f, 1.48405f}, {1.95652f, 1.50419f}, {2.17275f, 1.51720f}, {2.32126f, 1.51720f}, {2.46357f, 1.49915f}, {2.68891f, 1.46433f}, {2.95040f, 1.39341f}, {3.46133f, 1.17686f}, {3.96791f, 1.01658f}, {4.44857f, 0.89875f}, {4.95144f, 0.80251f}, {5.43509f, 0.72094f}, {5.94708f, 0.64894f}, {6.44943f, 0.59506f}, {7.00000f, 0.54547f} };
        static unsigned int Length_1_6 = 20; static float Matrix_1_6[][2] = { {0.00000f, 0.44831f}, {0.47649f, 0.50225f}, {0.97757f, 0.60419f}, {1.46839f, 0.72051f}, {1.95652f, 0.86150f}, {2.46357f, 1.03220f}, {2.71556f, 1.12585f}, {2.95040f, 1.17369f}, {3.23064f, 1.19485f}, {3.46133f, 1.19171f}, {3.73962f, 1.16647f}, {3.96791f, 1.12940f}, {4.22976f, 1.06793f}, {4.44857f, 0.99905f}, {4.70001f, 0.92803f}, {4.95144f, 0.87397f}, {5.43509f, 0.78152f}, {5.94708f, 0.69813f}, {6.44943f, 0.63135f}, {7.00000f, 0.57407f} };
        static unsigned int Length_1_7 = 17; static float Matrix_1_7[][2] = { {0.00000f, 0.22535f}, {0.47649f, 0.25805f}, {0.97757f, 0.30953f}, {1.46839f, 0.37551f}, {1.95652f, 0.45599f}, {2.46357f, 0.56403f}, {2.95040f, 0.69672f}, {3.46133f, 0.82506f}, {3.96791f, 0.92803f}, {4.20265f, 0.96551f}, {4.44857f, 0.98466f}, {4.70001f, 0.98057f}, {4.95144f, 0.95993f}, {5.43509f, 0.87786f}, {5.94708f, 0.77513f}, {6.44943f, 0.69256f}, {7.00000f, 0.62156f} };

        //Значения по комплексу x3
        const float x3_min = 0.0f;
        const float x3_2 = 1.0f;
        const float x3_3 = 2.0f;
        const float x3_4 = 3.0f;
        const float x3_max = 4.0f;

        //Входной комплекс x3
        float x3 = lambda_c * tan(chi_c);

        x_3.Min = x3_min;
        x_3.Value = x3;
        x_3.Max = x3_max;

        //Ограничение по диапазону x3
        if (x3 < x3_min)
            x3 = x3_min;
        else if (x3 > x3_max)
            x3 = x3_max;

        //Входной комплекс x2
        float x2 = lambda_c * pow(cc, 1.0f / 3.0f);

        const float x2_min = 0.5f;
        const float x2_max = 1.5f;

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
        const float x1_max = 7.0f;

        //Координата по оси х графика
        float x1 = lambda_c * sqrt(sqr(M) - 1.0f);

        x_1.Min = x1_min;
        x_1.Value = x1;
        x_1.Max = x1_max;

        //Ограничение по диапазону оси x
        if (x1 < x1_min)
            x1 = x1_min;
        else if (x1 > x1_max)
            x1 = x1_max;

        //Вычисление
        if (x3 == x3_min) {
            return Cxw_Rhomb_M1_3_1(x1, x2);

        }
        else if (x3_min <= x3 && x3 < x3_2) {
            float y1 = Cxw_Rhomb_M1_3_1(x1, x2);
            float y2 = Linterp(Matrix_1_4, Length_1_4, x1);

            return LinterpOnce(x3_min, y1, x3_2, y2, x3);

        }
        else if (x3_2 <= x3 && x3 < x3_3) {
            float y1 = Linterp(Matrix_1_4, Length_1_4, x1);
            float y2 = Linterp(Matrix_1_5, Length_1_5, x1);

            return LinterpOnce(x3_2, y1, x3_3, y2, x3);

        }
        else if (x3_3 <= x3 && x3 < x3_4) {
            float y1 = Linterp(Matrix_1_5, Length_1_5, x1);
            float y2 = Linterp(Matrix_1_6, Length_1_6, x1);

            return LinterpOnce(x3_3, y1, x3_4, y2, x3);

        }
        else if (x3_4 <= x3 && x3 < x2_max) {
            float y1 = Linterp(Matrix_1_6, Length_1_6, x1);
            float y2 = Linterp(Matrix_1_7, Length_1_7, x1);

            return LinterpOnce(x3_4, y1, x3_max, y2, x3);

        }
        else if (x3 == x3_max) {
            float y = Linterp(Matrix_1_7, Length_1_7, x1);

            return y;
        }
        else
            return NAN;
    }
    

    float Cxw_Rhomb_M1(float M, float cc, float zeta_c, float chi_c, float lambda_c, InputComplex& x_4, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {        
        // Значения по комплексу x4
        const float x4_min = 0.0f;
        const float x4_2 = 0.2f;
        const float x4_max = 1.0f;

        //Входной комплекс x4
        float x4 = zeta_c;

        x_4.Min = x4_min;
        x_4.Value = x4;
        x_4.Max = x4_max;

        // Ограничение по диапазону x4   
        if (x4 < x4_min)
            x4 = x4_min;
        else if (x4 > x4_max)
            x4 = x4_max;

        // Вычисление
        if (x4 == x4_min) {            
            float y = Cxw_Rhomb_M1_1(M, cc, chi_c, lambda_c, x_3, x_2, x_1);

            return y * lambda_c * sqr(cc);
        }
        else if (x4_min <= x4 && x4 < x4_2) {
            float y1 = Cxw_Rhomb_M1_1(M, cc, chi_c, lambda_c, x_3, x_2, x_1);
            float y2 = Cxw_Rhomb_M1_2(M, cc, chi_c, lambda_c, x_3, x_2, x_1);

            return LinterpOnce(x4_min, y1, x4_2, y2, x4) * lambda_c * sqr(cc);
        }
        else if (x4_2 <= x4 && x4 < x4_max) {
            float y1 = Cxw_Rhomb_M1_2(M, cc, chi_c, lambda_c, x_3, x_2, x_1);
            float y2 = Cxw_Rhomb_M1_3(M, cc, chi_c, lambda_c, x_3, x_2, x_1);

            return LinterpOnce(x4_2, y1, x4_max, y2, x4) * lambda_c * sqr(cc);
        }
        else if (x4 == x4_max) {
            float y = Cxw_Rhomb_M1_3(M, cc, chi_c, lambda_c, x_3, x_2, x_1);

            return y * lambda_c * sqr(cc);
        }
        else
            return NAN;
    }

    ErrorCode* get_Cxw_Rhomb_M1(float& Result, float M, float cc, float zeta_c, float chi_c, float lambda_c, InputComplex& x_4, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        static ErrorCode ErrC;
        // Проверка: некоторые аргументы не должны быть меньше 0		
        if (M < 0.0f)
        {
            ErrC.ArgNumber = 1;
            ErrC.Code = ErrC_NumberMustNotBeNeg;
            return &ErrC;
        }
        if (cc < 0.0f)
        {
            ErrC.ArgNumber = 2;
            ErrC.Code = ErrC_NumberMustNotBeNeg;
            return &ErrC;
        }
        if (zeta_c < 0.0f)
        {
            ErrC.ArgNumber = 3;
            ErrC.Code = ErrC_NumberMustNotBeNeg;
            return &ErrC;
        }
        if (chi_c < 0.0f)
        {
            ErrC.ArgNumber = 4;
            ErrC.Code = ErrC_NumberMustNotBeNeg;
            return &ErrC;
        }
        if (lambda_c < 0.0f)
        {
            ErrC.ArgNumber = 5;
            ErrC.Code = ErrC_NumberMustNotBeNeg;
            return &ErrC;
        }

        // Проверка: некоторые аргументы не должны быть больше 1	
        if (zeta_c > 1.0f)
        {
            ErrC.ArgNumber = 3;
            ErrC.Code = ErrC_ArgMustNotBeGT1;
            return &ErrC;
        }

        // Проверка: некоторые аргументы не должны быть меньше 1	
        if (M < 1.0f)
        {
            ErrC.ArgNumber = 1;
            ErrC.Code = ErrC_ArgMustNotBeLT1;
            return &ErrC;
        }

        // Проверка: некоторые аргументы не должны быть больше 90 градусов	
        if (chi_c > 90.0f / deg)
        {
            ErrC.ArgNumber = 4;
            ErrC.Code = ErrC_AngleMustBeLT90deg;
            return &ErrC;
        }

        // Вызываем функцию интерполяции графика
        Result = Cxw_Rhomb_M1(M, cc, zeta_c, chi_c, lambda_c, x_4, x_3, x_2, x_1);
        ErrC.ArgNumber = ErrC_OK;
        ErrC.Code = ErrC_OK;

        return &ErrC;
    }
}