from AASM6 import *
import numpy as np

print('Cyalf_ConCil:')
M = 1
lambda_nos = 2
lambda_cil = 1
Cyalf_ConCil = get_Cyalf_ConCil(
    M=M,
    lambda_nos=lambda_nos,
    lambda_cil=lambda_cil
)
print(f'M = {M}')
print(f'lambda_nos = {lambda_nos}')
print(f'lambda_cil = {lambda_cil}')
print('Result =', np.deg2rad(Cyalf_ConCil['Result']))
print('x1_Min =', Cyalf_ConCil['x1']['Min'])
print('x1_Value =', Cyalf_ConCil['x1']['Value'])
print('x1_Max =', Cyalf_ConCil['x1']['Max'])
print('x2_Min =', Cyalf_ConCil['x2']['Min'])
print('x2_Value =', Cyalf_ConCil['x2']['Value'])
print('x2_Max =', Cyalf_ConCil['x2']['Max'])
print()


print('Cyalf_OgiCil:')
M = 1
lambda_nos = 2
lambda_cil = 1
Cyalf_OgiCil = get_Cyalf_OgiCil(
    M=M,
    lambda_nos=lambda_nos,
    lambda_cil=lambda_cil
)
print(f'M = {M}')
print(f'lambda_nos = {lambda_nos}')
print(f'lambda_cil = {lambda_cil}')
print('Result =', np.deg2rad(Cyalf_OgiCil['Result']))
print('x1_Min =', Cyalf_OgiCil['x1']['Min'])
print('x1_Value =', Cyalf_OgiCil['x1']['Value'])
print('x1_Max =', Cyalf_OgiCil['x1']['Max'])
print('x2_Min =', Cyalf_OgiCil['x2']['Min'])
print('x2_Value =', Cyalf_OgiCil['x2']['Value'])
print('x2_Max =', Cyalf_OgiCil['x2']['Max'])
print()


print('Cyalf_SphCil:')
M = 1
lambda_nos = 2
lambda_cil = 1
Cyalf_SphCil = get_Cyalf_SphCil(
    M=M,
    lambda_nos=lambda_nos,
    lambda_cil=lambda_cil
)
print(f'M = {M}')
print(f'lambda_nos = {lambda_nos}')
print(f'lambda_cil = {lambda_cil}')
print('Result =', np.deg2rad(Cyalf_SphCil['Result']))
print('x1_Min =', Cyalf_SphCil['x1']['Min'])
print('x1_Value =', Cyalf_SphCil['x1']['Value'])
print('x1_Max =', Cyalf_SphCil['x1']['Max'])
print('x2_Min =', Cyalf_SphCil['x2']['Min'])
print('x2_Value =', Cyalf_SphCil['x2']['Value'])
print('x2_Max =', Cyalf_SphCil['x2']['Max'])
print()

print('Cyalf_IsP:')
M = 1
lambda_c = 0.25
cc = 1
chi_05 = 0
eta_c = 1
Cyalf_IsP = get_Cyalf_IsP(
    M=M,
    lambda_c=lambda_c,
    cc=cc,
    chi_05=chi_05,
    eta_c=eta_c
)
print(f'M = {M}')
print(f'lambda_c = {lambda_c}')
print(f'cc = {cc}')
print(f'chi_05 = {chi_05}')
print(f'eta_c = {eta_c}')
print('Result =', np.deg2rad(Cyalf_IsP['Result']/lambda_c))
print('x1_Min =', Cyalf_IsP['x1']['Min'])
print('x1_Value =', Cyalf_IsP['x1']['Value'])
print('x1_Max =', Cyalf_IsP['x1']['Max'])
print('x2_Min =', Cyalf_IsP['x2']['Min'])
print('x2_Value =', Cyalf_IsP['x2']['Value'])
print('x2_Max =', Cyalf_IsP['x2']['Max'])
print('x3_Min =', Cyalf_IsP['x3']['Min'])
print('x3_Value =', Cyalf_IsP['x3']['Value'])
print('x3_Max =', Cyalf_IsP['x3']['Max'])
print()


print('kappa_M:')
M = 1
kappa_M = get_kappa_M(
    M=M
)
print(f'M = {M}')
print('Result =', kappa_M['Result'])
print('x1_Min =', kappa_M['x1']['Min'])
print('x1_Value =', kappa_M['x1']['Value'])
print('x1_Max =', kappa_M['x1']['Max'])
print()


print('Coordinate_zz_v:')
M = 1
lambda_c = 0.25
chi_05 = 0
zeta_c = 1
Coordinate_zz_v = get_Coordinate_zz_v(
    M=M,
    lambda_c=lambda_c,
    chi_05=chi_05,
    zeta_c=zeta_c
)
print(f'M = {M}')
print(f'lambda_c = {lambda_c}')
print(f'chi_05 = {chi_05}')
print(f'zeta_c = {zeta_c}')
print('Result =', Coordinate_zz_v['Result'])
print('x1_Min =', Coordinate_zz_v['x1']['Min'])
print('x1_Value =', Coordinate_zz_v['x1']['Value'])
print('x1_Max =', Coordinate_zz_v['x1']['Max'])
print('x2_Min =', Coordinate_zz_v['x2']['Min'])
print('x2_Value =', Coordinate_zz_v['x2']['Value'])
print('x2_Max =', Coordinate_zz_v['x2']['Max'])
print('x3_Min =', Coordinate_zz_v['x3']['Min'])
print('x3_Value =', Coordinate_zz_v['x3']['Value'])
print('x3_Max =', Coordinate_zz_v['x3']['Max'])
print()


print('interference_v:')
zeta_c = 1
D = 1.2
l = 2
y_v = 0.4
z_v = 1.7
interference_v = get_interference_v(
    zeta_c=zeta_c,
    D=D,
    l=l,
    y_v=y_v,
    z_v=z_v
)
print(f'zeta_c = {zeta_c}')
print(f'D = {D}')
print(f'l = {l}')
print(f'y_v = {y_v}')
print(f'z_v = {z_v}')
print('Result =', interference_v['Result'])
print('x1_Min =', interference_v['x1']['Min'])
print('x1_Value =', interference_v['x1']['Value'])
print('x1_Max =', interference_v['x1']['Max'])
print('x2_Min =', interference_v['x2']['Min'])
print('x2_Value =', interference_v['x2']['Value'])
print('x2_Max =', interference_v['x2']['Max'])
print('x3_Min =', interference_v['x3']['Min'])
print('x3_Value =', interference_v['x3']['Value'])
print('x3_Max =', interference_v['x3']['Max'])
print('x4_Min =', interference_v['x4']['Min'])
print('x4_Value =', interference_v['x4']['Value'])
print('x4_Max =', interference_v['x4']['Max'])
print()


print('kM_Con:')
M = 2
lambda_nos = 1
kM_Con = get_kM_Con(
    M=M,
    lambda_nos=lambda_nos
)
print(f'M = {M}')
print(f'lambda_nos = {lambda_nos}')
print('Result =', kM_Con['Result'])
print('x1_Min =', kM_Con['x1']['Min'])
print('x1_Value =', kM_Con['x1']['Value'])
print('x1_Max =', kM_Con['x1']['Max'])
print('x2_Min =', kM_Con['x2']['Min'])
print('x2_Value =', kM_Con['x2']['Value'])
print('x2_Max =', kM_Con['x2']['Max'])
print()


print('kM_P:')
M = 1
x = 1
b_Ac = 1
kM_P = get_kM_P(
    M=M,
    x=x,
    b_Ac=b_Ac
)
print(f'M = {M}')
print(f'x = {x}')
print(f'b_Ac = {b_Ac}')
print('Result =', kM_P['Result'])
print('x1_Min =', kM_P['x1']['Min'])
print('x1_Value =', kM_P['x1']['Value'])
print('x1_Max =', kM_P['x1']['Max'])
print('x2_Min =', kM_P['x2']['Min'])
print('x2_Value =', kM_P['x2']['Value'])
print('x2_Max =', kM_P['x2']['Max'])
print()


print('nn_Eff1:')
l_r = 1
l_c = 1
zeta_c = 1
nn_Eff1 = get_nn_Eff1(
    l_r=l_r,
    l_c=l_c,
    zeta_c=zeta_c
)
print(f'l_r = {l_r}')
print(f'l_c = {l_c}')
print(f'zeta_c = {zeta_c}')
print('Result =', nn_Eff1['Result'])
print('x1_Min =', nn_Eff1['x1']['Min'])
print('x1_Value =', nn_Eff1['x1']['Value'])
print('x1_Max =', nn_Eff1['x1']['Max'])
print('x2_Min =', nn_Eff1['x2']['Min'])
print('x2_Value =', nn_Eff1['x2']['Value'])
print('x2_Max =', nn_Eff1['x2']['Max'])
print()


print('nn_Eff2:')
M = 1
lambda_c = 4
bb_r = 0.05
nn_Eff2 = get_nn_Eff2(
    M=M,
    lambda_c=lambda_c,
    bb_r=bb_r
)
print(f'M = {M}')
print(f'lambda_c = {lambda_c}')
print(f'bb_r = {bb_r}')
print('Result =', nn_Eff2['Result'])
print('x1_Min =', nn_Eff2['x1']['Min'])
print('x1_Value =', nn_Eff2['x1']['Value'])
print('x1_Max =', nn_Eff2['x1']['Max'])
print('x2_Min =', nn_Eff2['x2']['Min'])
print('x2_Value =', nn_Eff2['x2']['Value'])
print('x2_Max =', nn_Eff2['x2']['Max'])
print()


print('Cp1_Cp2:')
M = 1.8
key = 0
Cp1_Cp2 = get_Cp1_Cp2(
    M=M,
    key=key
)
print(f'M = {M}')
print(f'key = {key}')
print('Result =', Cp1_Cp2['Result'])
print('x1_Min =', Cp1_Cp2['x1']['Min'])
print('x1_Value =', Cp1_Cp2['x1']['Value'])
print('x1_Max =', Cp1_Cp2['x1']['Max'])
print()


print('Cx_Cil_N:')
M = 0.8
alpha = 1.57
Cx_Cil_N = get_Cx_Cil_N(
    M=M,
    alpha=alpha
)
print(f'M = {M}')
print(f'alpha = {alpha}')
print('Result =', Cx_Cil_N['Result'])
print('x1_Min =', Cx_Cil_N['x1']['Min'])
print('x1_Value =', Cx_Cil_N['x1']['Value'])
print('x1_Max =', Cx_Cil_N['x1']['Max'])
print()


print('A_IsP:')
M = 2
zeta_c = 1
Cyalf_IsP = np.rad2deg(0.03)
A_IsP = get_A_IsP(
    M=M,
    zeta_c=zeta_c,
    Cyalf_IsP=Cyalf_IsP
)
print(f'M = {M}')
print(f'zeta_c = {zeta_c}')
print(f'Cyalf_IsP = {Cyalf_IsP}')
print('Result =', A_IsP['Result'])
print('x1_Min =', A_IsP['x1']['Min'])
print('x1_Value =', A_IsP['x1']['Value'])
print('x1_Max =', A_IsP['x1']['Max'])
print('x2_Min =', A_IsP['x2']['Min'])
print('x2_Value =', A_IsP['x2']['Value'])
print('x2_Max =', A_IsP['x2']['Max'])
print('x3_Min =', A_IsP['x3']['Min'])
print('x3_Value =', A_IsP['x3']['Value'])
print('x3_Max =', A_IsP['x3']['Max'])
print()


print('Cf_M0:')
Re = 1e6
xx_t = 1
Cf_M0 = get_Cf_M0(
    Re=Re,
    xx_t=xx_t
)
print(f'Re = {Re}')
print(f'xx_t = {xx_t}')
print('Result =', 2*Cf_M0['Result'])
print('x1_Min =', Cf_M0['x1']['Min'])
print('x1_Value =', Cf_M0['x1']['Value'])
print('x1_Max =', Cf_M0['x1']['Max'])
print('x2_Min =', Cf_M0['x2']['Min'])
print('x2_Value =', Cf_M0['x2']['Value'])
print('x2_Max =', Cf_M0['x2']['Max'])
print()


print('Sigma_M:')
M = 4
xx_t = 1
Sigma_M = get_Sigma_M(
    M=M,
    xx_t=xx_t
)
print(f'M = {M}')
print(f'xx_t = {xx_t}')
print('Result =', Sigma_M['Result'])
print('x1_Min =', Sigma_M['x1']['Min'])
print('x1_Value =', Sigma_M['x1']['Value'])
print('x1_Max =', Sigma_M['x1']['Max'])
print('x2_Min =', Sigma_M['x2']['Min'])
print('x2_Value =', Sigma_M['x2']['Value'])
print('x2_Max =', Sigma_M['x2']['Max'])
print()


print('Re_t0_1:')
M = 1
Re = 10
hh = 0
Re_t0_1 = get_Re_t0_1(
    M=M,
    Re=Re,
    hh=hh
)
print(f'M = {M}')
print(f'Re = {Re}')
print(f'hh = {hh}')
print('Result =', Re_t0_1['Result'])
print('x1_Min =', Re_t0_1['x1']['Min'])
print('x1_Value =', Re_t0_1['x1']['Value'])
print('x1_Max =', Re_t0_1['x1']['Max'])
print('x2_Min =', Re_t0_1['x2']['Min'])
print('x2_Value =', Re_t0_1['x2']['Value'])
print('x2_Max =', Re_t0_1['x2']['Max'])
print()


print('TTr_TTsl:')
M = 1
key = 2
TTr_TTsl = get_TTr_TTsl(
    M=M,
    key=key
)
print(f'M = {M}')
print(f'key = {key}')
print('Result =', TTr_TTsl['Result'])
print('x1_Min =', TTr_TTsl['x1']['Min'])
print('x1_Value =', TTr_TTsl['x1']['Value'])
print('x1_Max =', TTr_TTsl['x1']['Max'])
print()


print('Sigma_T:')
M = 3.12
TT_s = 0.6
Sigma_T = get_Sigma_T(
    M=M,
    TT_s=TT_s
)
print(f'M = {M}')
print(f'TT_s = {TT_s}')
print('Result =', Sigma_T['Result'])
print('x1_Min =', Sigma_T['x1']['Min'])
print('x1_Value =', Sigma_T['x1']['Value'])
print('x1_Max =', Sigma_T['x1']['Max'])
print()


print('Sigma_Con:')
M = 10
lambda_nos = 5
Sigma_Con = get_Sigma_Con(
    M=M,
    lambda_nos=lambda_nos
)
print(f'M = {M}')
print(f'lambda_nos = {lambda_nos}')
print('Result =', Sigma_Con['Result'])
print('x1_Min =', Sigma_Con['x1']['Min'])
print('x1_Value =', Sigma_Con['x1']['Value'])
print('x1_Max =', Sigma_Con['x1']['Max'])
print('x2_Min =', Sigma_Con['x2']['Min'])
print('x2_Value =', Sigma_Con['x2']['Value'])
print('x2_Max =', Sigma_Con['x2']['Max'])
print()


print('Cxnos_Con:')
M = 1.4
lambda_nos = 1.5
Cxnos_Con = get_Cxnos_Con(
    M=M,
    lambda_nos=lambda_nos
)
print(f'M = {M}')
print(f'lambda_nos = {lambda_nos}')
print('Result =', Cxnos_Con['Result'])
print('x1_Min =', Cxnos_Con['x1']['Min'])
print('x1_Value =', Cxnos_Con['x1']['Value'])
print('x1_Max =', Cxnos_Con['x1']['Max'])
print('x2_Min =', Cxnos_Con['x2']['Min'])
print('x2_Value =', Cxnos_Con['x2']['Value'])
print('x2_Max =', Cxnos_Con['x2']['Max'])
print()


print('Cxnos_Par:')
M = 1.4
lambda_nos = 2
Cxnos_Par = get_Cxnos_Par(
    M=M,
    lambda_nos=lambda_nos
)
print(f'M = {M}')
print(f'lambda_nos = {lambda_nos}')
print('Result =', Cxnos_Par['Result'])
print('x1_Min =', Cxnos_Par['x1']['Min'])
print('x1_Value =', Cxnos_Par['x1']['Value'])
print('x1_Max =', Cxnos_Par['x1']['Max'])
print('x2_Min =', Cxnos_Par['x2']['Min'])
print('x2_Value =', Cxnos_Par['x2']['Value'])
print('x2_Max =', Cxnos_Par['x2']['Max'])
print()


print('Cxnos_Ell:')
M = 1.4
lambda_nos = 0
Cxnos_Ell = get_Cxnos_Ell(
    M=M,
    lambda_nos=lambda_nos
)
print(f'M = {M}')
print(f'lambda_nos = {lambda_nos}')
print('Result =', Cxnos_Ell['Result'])
print('x1_Min =', Cxnos_Ell['x1']['Min'])
print('x1_Value =', Cxnos_Ell['x1']['Value'])
print('x1_Max =', Cxnos_Ell['x1']['Max'])
print('x2_Min =', Cxnos_Ell['x2']['Min'])
print('x2_Value =', Cxnos_Ell['x2']['Value'])
print('x2_Max =', Cxnos_Ell['x2']['Max'])
print()


print('Ms_Con:')
M = 7
teta_Con = 0.35
Ms_Con = get_Ms_Con(
    M=M,
    teta_Con=teta_Con
)
print(f'M = {M}')
print(f'teta_Con = {teta_Con}')
print('Result =', Ms_Con['Result'])
print('x1_Min =', Ms_Con['x1']['Min'])
print('x1_Value =', Ms_Con['x1']['Value'])
print('x1_Max =', Ms_Con['x1']['Max'])
print('x2_Min =', Ms_Con['x2']['Min'])
print('x2_Value =', Ms_Con['x2']['Value'])
print('x2_Max =', Ms_Con['x2']['Max'])
print()


print('Cxcor_Con:')
M = 4.5
lambda_cor = 1.5
eta_cor = 0.5
Cxcor_Con = get_Cxcor_Con(
    M=M,
    lambda_cor=lambda_cor,
    eta_cor=eta_cor
)
print(f'M = {M}')
print(f'lambda_cor = {lambda_cor}')
print(f'eta_cor = {eta_cor}')
print('Result =', Cxcor_Con['Result'])
print('x1_Min =', Cxcor_Con['x1']['Min'])
print('x1_Value =', Cxcor_Con['x1']['Value'])
print('x1_Max =', Cxcor_Con['x1']['Max'])
print('x2_Min =', Cxcor_Con['x2']['Min'])
print('x2_Value =', Cxcor_Con['x2']['Value'])
print('x2_Max =', Cxcor_Con['x2']['Max'])
print('x3_Min =', Cxcor_Con['x3']['Min'])
print('x3_Value =', Cxcor_Con['x3']['Value'])
print('x3_Max =', Cxcor_Con['x3']['Max'])
print()


print('Cxcor_Par:')
M = 1.4
lambda_cor = 3
eta_cor = 0
Cxcor_Par = get_Cxcor_Par(
    M=M,
    lambda_cor=lambda_cor,
    eta_cor=eta_cor
)
print(f'M = {M}')
print(f'lambda_cor = {lambda_cor}')
print(f'eta_cor = {eta_cor}')
print('Result =', Cxcor_Par['Result'])
print('x1_Min =', Cxcor_Par['x1']['Min'])
print('x1_Value =', Cxcor_Par['x1']['Value'])
print('x1_Max =', Cxcor_Par['x1']['Max'])
print('x2_Min =', Cxcor_Par['x2']['Min'])
print('x2_Value =', Cxcor_Par['x2']['Value'])
print('x2_Max =', Cxcor_Par['x2']['Max'])
print('x3_Min =', Cxcor_Par['x3']['Min'])
print('x3_Value =', Cxcor_Par['x3']['Value'])
print('x3_Max =', Cxcor_Par['x3']['Max'])
print()


print('Cxdon_Cil:')
a, L_f, nu = 320.545, 1, 22.11e-6
def Re(M): return M * a * L_f / nu


M = 0.8
cc = 0
Re_f06 = Re(0.6)
Re_f = Re(0.8)
xx_tf = 0.2
lambda_f = 4
Cxdon_Cil = get_Cxdon_Cil(
    M=M,
    cc=cc,
    Re_f06=Re_f06,
    Re_f=Re_f,
    xx_tf=xx_tf,
    lambda_f=lambda_f
)
print(f'M = {M}')
print(f'cc = {cc}')
print(f'Re_f06 = {Re_f06}')
print(f'Re_f = {Re_f}')
print(f'xx_tf = {xx_tf}')
print(f'lambda_f = {lambda_f}')
print('Result =', Cxdon_Cil['Result'])
print('x1_Min =', Cxdon_Cil['x1']['Min'])
print('x1_Value =', Cxdon_Cil['x1']['Value'])
print('x1_Max =', Cxdon_Cil['x1']['Max'])
print('x2_Min =', Cxdon_Cil['x2']['Min'])
print('x2_Value =', Cxdon_Cil['x2']['Value'])
print('x2_Max =', Cxdon_Cil['x2']['Max'])
print()


print('Sigma_eta:')
M = 1.5
lambda_cor = 1
eta_cor = 1
Sigma_eta = get_Sigma_eta(
    M=M,
    lambda_cor=lambda_cor,
    eta_cor=eta_cor
)
print(f'M = {M}')
print(f'lambda_cor = {lambda_cor}')
print(f'eta_cor = {eta_cor}')
print('Result =', Sigma_eta['Result'])
print('x1_Min =', Sigma_eta['x1']['Min'])
print('x1_Value =', Sigma_eta['x1']['Value'])
print('x1_Max =', Sigma_eta['x1']['Max'])
print('x2_Min =', Sigma_eta['x2']['Min'])
print('x2_Value =', Sigma_eta['x2']['Value'])
print('x2_Max =', Sigma_eta['x2']['Max'])
print()


print('Sigma_c:')
cc = 0.1
xx_t = 0.4
Sigma_c = get_Sigma_c(
    cc=cc,
    xx_t=xx_t
)
print(f'cc = {cc}')
print(f'xx_t = {xx_t}')
print('Result =', Sigma_c['Result'])
print('x1_Min =', Sigma_c['x1']['Min'])
print('x1_Value =', Sigma_c['x1']['Value'])
print('x1_Max =', Sigma_c['x1']['Max'])
print('x2_Min =', Sigma_c['x2']['Min'])
print('x2_Value =', Sigma_c['x2']['Value'])
print('x2_Max =', Sigma_c['x2']['Max'])
print()


print('Sigma_chi:')
chi_0 = 1.05
Sigma_chi = get_Sigma_chi(
    chi_0=chi_0
)
print(f'chi_0 = {chi_0}')
print('Result =', Sigma_chi['Result'])
print('x1_Min =', Sigma_chi['x1']['Min'])
print('x1_Value =', Sigma_chi['x1']['Value'])
print('x1_Max =', Sigma_chi['x1']['Max'])
print()


print('Cxw_Rhomb_M1:')
M = 1
cc = 1
zeta_c = 1
chi_c = 0
lambda_c = 1
Cxw_Rhomb_M1 = get_Cxw_Rhomb_M1(
    M=M,
    cc=cc,
    zeta_c=zeta_c,
    chi_c=chi_c,
    lambda_c=lambda_c
)
print(f'M = {M}')
print(f'cc = {cc}')
print(f'zeta_c = {zeta_c}')
print(f'chi_c = {chi_c}')
print(f'lambda_c = {lambda_c}')
print('Result =', Cxw_Rhomb_M1['Result'] / lambda_c / cc**2)
print('x1_Min =', Cxw_Rhomb_M1['x1']['Min'])
print('x1_Value =', Cxw_Rhomb_M1['x1']['Value'])
print('x1_Max =', Cxw_Rhomb_M1['x1']['Max'])
print('x2_Min =', Cxw_Rhomb_M1['x2']['Min'])
print('x2_Value =', Cxw_Rhomb_M1['x2']['Value'])
print('x2_Max =', Cxw_Rhomb_M1['x2']['Max'])
print('x3_Min =', Cxw_Rhomb_M1['x3']['Min'])
print('x3_Value =', Cxw_Rhomb_M1['x3']['Value'])
print('x3_Max =', Cxw_Rhomb_M1['x3']['Max'])
print('x4_Min =', Cxw_Rhomb_M1['x4']['Min'])
print('x4_Value =', Cxw_Rhomb_M1['x4']['Value'])
print('x4_Max =', Cxw_Rhomb_M1['x4']['Max'])
print()


print('Sigma_pw:')
M = 1
chi_c = 0
Sigma_pw = get_Sigma_pw(
    M=M,
    chi_c=chi_c
)
print(f'M = {M}')
print(f'chi_c = {chi_c}')
print('Result =', Sigma_pw['Result'])
print('x1_Min =', Sigma_pw['x1']['Min'])
print('x1_Value =', Sigma_pw['x1']['Value'])
print('x1_Max =', Sigma_pw['x1']['Max'])
print()


print('Mcr_pr:')
cc = 0.1
Cn = 0.04
xx_c = 0.35
Mcr_pr = get_Mcr_pr(
    cc=cc,
    Cn=Cn,
    xx_c=xx_c
)
print(f'cc = {cc}')
print(f'Cn = {Cn}')
print(f'xx_c = {xx_c}')
print('Result =', Mcr_pr['Result'])
print('x1_Min =', Mcr_pr['x1']['Min'])
print('x1_Value =', Mcr_pr['x1']['Value'])
print('x1_Max =', Mcr_pr['x1']['Max'])
print('x2_Min =', Mcr_pr['x2']['Min'])
print('x2_Value =', Mcr_pr['x2']['Value'])
print('x2_Max =', Mcr_pr['x2']['Max'])
print('x3_Min =', Mcr_pr['x3']['Min'])
print('x3_Value =', Mcr_pr['x3']['Value'])
print('x3_Max =', Mcr_pr['x3']['Max'])
print()


print('DELTA_Mcr0_lambda:')
Mcr_pr0 = 0.9
lambda_c = 1
DELTA_Mcr0_lambda = get_DELTA_Mcr0_lambda(
    Mcr_pr0=Mcr_pr0,
    lambda_c=lambda_c
)
print(f'Mcr_pr0 = {Mcr_pr0}')
print(f'lambda_c = {lambda_c}')
print('Result =', DELTA_Mcr0_lambda['Result'])
print('x1_Min =', DELTA_Mcr0_lambda['x1']['Min'])
print('x1_Value =', DELTA_Mcr0_lambda['x1']['Value'])
print('x1_Max =', DELTA_Mcr0_lambda['x1']['Max'])
print('x2_Min =', DELTA_Mcr0_lambda['x2']['Min'])
print('x2_Value =', DELTA_Mcr0_lambda['x2']['Value'])
print('x2_Max =', DELTA_Mcr0_lambda['x2']['Max'])
print()


print('DELTA_Mcr0_chi:')
Mcr_pr0 = 0.9
chi_c = 1.05
DELTA_Mcr0_chi = get_DELTA_Mcr0_chi(
    Mcr_pr0=Mcr_pr0,
    chi_c=chi_c
)
print(f'Mcr_pr0 = {Mcr_pr0}')
print(f'chi_c = {chi_c}')
print('Result =', DELTA_Mcr0_chi['Result'])
print('x1_Min =', DELTA_Mcr0_chi['x1']['Min'])
print('x1_Value =', DELTA_Mcr0_chi['x1']['Value'])
print('x1_Max =', DELTA_Mcr0_chi['x1']['Max'])
print('x2_Min =', DELTA_Mcr0_chi['x2']['Min'])
print('x2_Value =', DELTA_Mcr0_chi['x2']['Value'])
print('x2_Max =', DELTA_Mcr0_chi['x2']['Max'])
print()


print('Cxdon_pr:')
M = 2
Cxdon_pr = get_Cxdon_pr(
    M=M
)
print(f'M = {M}')
print('Result =', Cxdon_pr['Result'])
print('x1_Min =', Cxdon_pr['x1']['Min'])
print('x1_Value =', Cxdon_pr['x1']['Value'])
print('x1_Max =', Cxdon_pr['x1']['Max'])
print()


print('Sigma_Cxinos:')
M = 1
lambda_nos = 1
key = 1
Sigma_Cxinos = get_Sigma_Cxinos(
    M=M,
    lambda_nos=lambda_nos,
    key=key
)
print(f'M = {M}')
print(f'lambda_nos = {lambda_nos}')
print(f'key = {key}')
print('Result =', Sigma_Cxinos['Result'])
print('x1_Min =', Sigma_Cxinos['x1']['Min'])
print('x1_Value =', Sigma_Cxinos['x1']['Value'])
print('x1_Max =', Sigma_Cxinos['x1']['Max'])
print('x2_Min =', Sigma_Cxinos['x2']['Min'])
print('x2_Value =', Sigma_Cxinos['x2']['Value'])
print('x2_Max =', Sigma_Cxinos['x2']['Max'])
print()


print('CC_F_IsP:')
M = 1
lambda_c = 1
chi_0 = 0
CC_F_IsP = get_CC_F_IsP(
    M=M,
    lambda_c=lambda_c,
    chi_0=chi_0
)
print(f'M = {M}')
print(f'lambda_c = {lambda_c}')
print(f'chi_0 = {chi_0}')
print('Result =', lambda_c*CC_F_IsP['Result'])
print('x1_Min =', CC_F_IsP['x1']['Min'])
print('x1_Value =', CC_F_IsP['x1']['Value'])
print('x1_Max =', CC_F_IsP['x1']['Max'])
print('x2_Min =', CC_F_IsP['x2']['Min'])
print('x2_Value =', CC_F_IsP['x2']['Value'])
print('x2_Max =', CC_F_IsP['x2']['Max'])
print()


print('Sigma_CF:')
M = 1
chi_0 = 0.79
alpha = 0.1
Sigma_CF = get_Sigma_CF(
    M=M,
    chi_0=chi_0,
    alpha=alpha
)
print(f'M = {M}')
print(f'chi_0 = {chi_0}')
print(f'alpha = {alpha}')
print('Result =', Sigma_CF['Result'])
print('x1_Min =', Sigma_CF['x1']['Min'])
print('x1_Value =', Sigma_CF['x1']['Value'])
print('x1_Max =', Sigma_CF['x1']['Max'])
print('x2_Min =', Sigma_CF['x2']['Min'])
print('x2_Value =', Sigma_CF['x2']['Value'])
print('x2_Max =', Sigma_CF['x2']['Max'])
print()


print('xi_M:')
M = 1
lambda_nos = 0.5
lambda_cil = 2
xi_M = get_xi_M(
    M=M,
    lambda_nos=lambda_nos,
    lambda_cil=lambda_cil
)
print(f'M = {M}')
print(f'lambda_nos = {lambda_nos}')
print(f'lambda_cil = {lambda_cil}')
print('Result =', xi_M['Result'])
print('x1_Min =', xi_M['x1']['Min'])
print('x1_Value =', xi_M['x1']['Value'])
print('x1_Max =', xi_M['x1']['Max'])
print('x2_Min =', xi_M['x2']['Min'])
print('x2_Value =', xi_M['x2']['Value'])
print('x2_Max =', xi_M['x2']['Max'])
print()


print('Coordinate_xxF_IsP:')
M = 1
lambda_c = 1
chi_05 = 0
zeta_c = 1
Coordinate_xxF_IsP = get_Coordinate_xxF_IsP(
    M=M,
    lambda_c=lambda_c,
    chi_05=chi_05,
    zeta_c=zeta_c
)
print(f'M = {M}')
print(f'lambda_c = {lambda_c}')
print(f'chi_05 = {chi_05}')
print(f'zeta_c = {zeta_c}')
print('Result =', Coordinate_xxF_IsP['Result'])
print('x1_Min =', Coordinate_xxF_IsP['x1']['Min'])
print('x1_Value =', Coordinate_xxF_IsP['x1']['Value'])
print('x1_Max =', Coordinate_xxF_IsP['x1']['Max'])
print('x2_Min =', Coordinate_xxF_IsP['x2']['Min'])
print('x2_Value =', Coordinate_xxF_IsP['x2']['Value'])
print('x2_Max =', Coordinate_xxF_IsP['x2']['Max'])
print('x3_Min =', Coordinate_xxF_IsP['x3']['Min'])
print('x3_Value =', Coordinate_xxF_IsP['x3']['Value'])
print('x3_Max =', Coordinate_xxF_IsP['x3']['Max'])
print()


print('xi_D:')
DD = 0.6
xi_D = get_xi_D(
    DD=0.6
)
print(f'DD = {DD}')
print('Result =', xi_D['Result'])
print('x1_Min =', xi_D['x1']['Min'])
print('x1_Value =', xi_D['x1']['Value'])
print('x1_Max =', xi_D['x1']['Max'])
print()


print('S_bok:')
D = 0.13
S_nos = 1
lambda_cil = 7.5
lambda_cor = 0.769
eta_cor = 0.811
M = [1, 1.2]
b_b = [0.24, 0.115]
L_hv = [0.225, 0.1]
S_bok = get_S_bok(
    D=D,
    S_nos=S_nos,
    lambda_cil=lambda_cil,
    lambda_cor=lambda_cor,
    eta_cor=eta_cor,
    M=M,
    b_b=b_b,
    L_hv=L_hv
)
print(f'D = {D}')
print(f'S_nos = {S_nos}')
print(f'lambda_cil = {lambda_cil}')
print(f'lambda_cor = {lambda_cor}')
print(f'eta_cor = {eta_cor}')
print(f'M = {M}')
print(f'b_b = {b_b}')
print(f'L_hv = {L_hv}')
print('Result =', S_bok['Result'])
print()
