#include "pch.h"
#include "AASM6_DYN.h"
#include "AASM6.h"

namespace AASM6_DYN
{
    ErrorCode* get_Cyalf_ConCil(float& Result, float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Cyalf_ConCil(Result, M, lambda_nos, lambda_cil, x_2, x_1);
    }
    ErrorCode* get_Cyalf_OgiCil(float& Result, float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Cyalf_OgiCil(Result, M, lambda_nos, lambda_cil, x_2, x_1);
    }
    ErrorCode* get_Cyalf_SphCil(float& Result, float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Cyalf_SphCil(Result, M, lambda_nos, lambda_cil, x_2, x_1);
    }
    ErrorCode* get_Cyalf_IsP(float& Result, float M, float lambda_c, float cc, float chi_05, float eta_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Cyalf_IsP(Result, M, lambda_c, cc, chi_05, eta_c, x_3, x_2, x_1);
    }
    ErrorCode* get_kappa_M(float& Result, float M, InputComplex& x_1)
    {
        return AASM6::get_kappa_M(Result, M, x_1);
    }
    ErrorCode* get_Coordinate_zz_v(float& Result, float M, float lambda_c, float chi_05, float zeta_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Coordinate_zz_v(Result, M, lambda_c, chi_05, zeta_c, x_3, x_2, x_1);
    }
    ErrorCode* get_interference_v(float& Result, float zeta_c, float D, float l, float y_v, float z_v, InputComplex& x_4, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_interference_v(Result, zeta_c, D, l, y_v, z_v, x_4, x_3, x_2, x_1);
    }
    ErrorCode* get_kM_Con(float& Result, float M, float lambda_nos, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_kM_Con(Result, M, lambda_nos, x_2, x_1);
    }
    ErrorCode* get_kM_P(float& Result, float M, float x, float b_Ac, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_kM_P(Result, M, x, b_Ac, x_2, x_1);
    }
    ErrorCode* get_nn_Eff1(float& Result, float l_r, float l_c, float zeta_c, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_nn_Eff1(Result, l_r, l_c, zeta_c, x_2, x_1);
    }
    ErrorCode* get_nn_Eff2(float& Result, float M, float lambda_c, float bb_r, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_nn_Eff2(Result, M, lambda_c, bb_r, x_2, x_1);
    }
    ErrorCode* get_Cp1_Cp2(float& Result, float M, float key, InputComplex& x_1)
    {
        return AASM6::get_Cp1_Cp2(Result, M, key, x_1);
    }
    ErrorCode* get_Cx_Cil_N(float& Result, float M, float alpha, InputComplex& x_1)
    {
        return AASM6::get_Cx_Cil_N(Result, M, alpha, x_1);
    }
    ErrorCode* get_A_IsP(float& Result, float M, float zeta_c, float Cyalf_IsP, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_A_IsP(Result, M, zeta_c, Cyalf_IsP, x_3, x_2, x_1);
    }
    ErrorCode* get_Cf_M0(float& Result, float Re, float xx_t, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Cf_M0(Result, Re, xx_t, x_2, x_1);
    }
    ErrorCode* get_Sigma_M(float& Result, float M, float xx_t, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Sigma_M(Result, M, xx_t, x_2, x_1);
    }
    ErrorCode* get_Re_t0_1(float& Result, float M, float Re, float hh, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Re_t0_1(Result, M, Re, hh, x_2, x_1);
    }
    ErrorCode* get_TTr_TTsl(float& Result, float M, float key, InputComplex& x_1)
    {
        return AASM6::get_TTr_TTsl(Result, M, key, x_1);
    }
    ErrorCode* get_Sigma_T(float& Result, float M, float TT_s, InputComplex& x_1)
    {
        return AASM6::get_Sigma_T(Result, M, TT_s, x_1);
    }
    ErrorCode* get_Sigma_Con(float& Result, float M, float lambda_nos, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Sigma_Con(Result, M, lambda_nos, x_2, x_1);
    }
    ErrorCode* get_Cxnos_Con(float& Result, float M, float lambda_nos, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Cxnos_Con(Result, M, lambda_nos, x_2, x_1);
    }
    ErrorCode* get_Cxnos_Par(float& Result, float M, float lambda_nos, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Cxnos_Par(Result, M, lambda_nos, x_2, x_1);
    }
    ErrorCode* get_Cxnos_Ell(float& Result, float M, float lambda_nos, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Cxnos_Ell(Result, M, lambda_nos, x_2, x_1);
    }
    ErrorCode* get_Ms_Con(float& Result, float M, float teta_Con, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Ms_Con(Result, M, teta_Con, x_2, x_1);
    }
    ErrorCode* get_Cxcor_Con(float& Result, float M, float lambda_cor, float eta_cor, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Cxcor_Con(Result, M, lambda_cor, eta_cor, x_3, x_2, x_1);
    }
    ErrorCode* get_Cxcor_Par(float& Result, float M, float lambda_cor, float eta_cor, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Cxcor_Par(Result, M, lambda_cor, eta_cor, x_3, x_2, x_1);
    }
    ErrorCode* get_Cxdon_Cil(float& Result, float M, float cc, float Re_f06, float Re_f, float xx_tf, float lambda_f, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Cxdon_Cil(Result, M, cc, Re_f06, Re_f, xx_tf, lambda_f, x_2, x_1);
    }
    ErrorCode* get_Sigma_eta(float& Result, float M, float lambda_cor, float eta_cor, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Sigma_eta(Result, M, lambda_cor, eta_cor, x_2, x_1);
    }
    ErrorCode* get_Sigma_c(float& Result, float cc, float xx_t, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Sigma_c(Result, cc, xx_t, x_2, x_1);
    }
    ErrorCode* get_Sigma_chi(float& Result, float chi_0, InputComplex& x_1)
    {
        return AASM6::get_Sigma_chi(Result, chi_0, x_1);
    }
    ErrorCode* get_Cxw_Rhomb_M1(float& Result, float M, float cc, float zeta_c, float chi_c, float lambda_c, InputComplex& x_4, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Cxw_Rhomb_M1(Result, M, cc, zeta_c, chi_c, lambda_c, x_4, x_3, x_2, x_1);
    }
    ErrorCode* get_Sigma_pw(float& Result, float M, float chi_c, InputComplex& x_1)
    {
        return AASM6::get_Sigma_pw(Result, M, chi_c, x_1);
    }
    ErrorCode* get_Mcr_pr(float& Result, float cc, float Cn, float xx_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Mcr_pr(Result, cc, Cn, xx_c, x_3, x_2, x_1);
    }
    ErrorCode* get_DELTA_Mcr0_lambda(float& Result, float Mcr_pr0, float lambda_c, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_DELTA_Mcr0_lambda(Result, Mcr_pr0, lambda_c, x_2, x_1);
    }
    ErrorCode* get_DELTA_Mcr0_chi(float& Result, float Mcr_pr0, float chi_c, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_DELTA_Mcr0_chi(Result, Mcr_pr0, chi_c, x_2, x_1);
    }
    ErrorCode* get_Cxdon_pr(float& Result, float M, InputComplex& x_1)
    {
        return AASM6::get_Cxdon_pr(Result, M, x_1);
    }
    ErrorCode* get_Sigma_Cxinos(float& Result, float M, float lambda_nos, float nos_typ, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Sigma_Cxinos(Result, M, lambda_nos, nos_typ, x_2, x_1);
    }
    ErrorCode* get_CC_F_IsP(float& Result, float M, float lambda_c, float chi_0, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_CC_F_IsP(Result, M, lambda_c, chi_0, x_2, x_1);
    }
    ErrorCode* get_Sigma_CF(float& Result, float M, float chi_0, float alpha, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Sigma_CF(Result, M, chi_0, alpha, x_2, x_1);
    }
    ErrorCode* get_xi_M(float& Result, float M, float lambda_nos, float lambda_cil, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_xi_M(Result, M, lambda_nos, lambda_cil, x_2, x_1);
    }
    ErrorCode* get_Coordinate_xxF_IsP(float& Result, float M, float lambda_c, float chi_05, float zeta_c, InputComplex& x_3, InputComplex& x_2, InputComplex& x_1)
    {
        return AASM6::get_Coordinate_xxF_IsP(Result, M, lambda_c, chi_05, zeta_c, x_3, x_2, x_1);
    }
    ErrorCode* get_xi_D(float& Result, float DD, InputComplex& x_1)
    {
        return AASM6::get_xi_D(Result, DD, x_1);
    }
    ErrorCode* get_S_bok(float& Result, float D, float S_nos, float lambda_cil, float lambda_cor, float eta_cor, std::vector<float>& M, std::vector<float>& b_b, std::vector<float>& L_hv)
    {
        return AASM6::get_S_bok(Result, D, S_nos, lambda_cil, lambda_cor, eta_cor, M, b_b, L_hv);
    }

    // функции для вектора
    // создание вектора
    std::vector<float>* new_vector() {
        return new std::vector<float>;
    }

    // деструктор
    void delete_vector(std::vector<float>* v) {
        delete v;
    }

    // количетсво элементов в векторе
    int vector_size(std::vector<float>* v) {
        return v->size();
    }

    // позволяет получить i-ый элемент вектора
    float vector_get(std::vector<float>* v, int i) {
        return v->at(i);
    }

    // добавляет элемент val в конец вектора
    void vector_push_back(std::vector<float>* v, float val) {
        v->push_back(val);
    }
}