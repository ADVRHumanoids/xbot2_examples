//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, educational organizations only. Not for
// government, commercial, or other organizational use.
//
// File: CartesianImpedance_Task.h
//
// Code generated for Simulink model 'CartesianImpedance_Task'.
//
// Model version                  : 1.1032
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Thu Feb  4 14:46:32 2021
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-32 (Windows32)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_CartesianImpedance_Task_h_
#define RTW_HEADER_CartesianImpedance_Task_h_
#include <cmath>
#include <cstring>
#include <math.h>
#ifndef CartesianImpedance_Task_COMMON_INCLUDES_
# define CartesianImpedance_Task_COMMON_INCLUDES_
#include <cstdio>
#include <BlockFactory/Core/Block.h>
#include <BlockFactory/Core/Log.h>
#include <BlockFactory/Core/Parameter.h>
#include <BlockFactory/Core/Parameters.h>
#include <BlockFactory/Core/FactorySingleton.h>
#include <BlockFactory/SimulinkCoder/CoderBlockInformation.h>
#include "rtwtypes.h"
#endif                              // CartesianImpedance_Task_COMMON_INCLUDES_

#include "CartesianImpedance_Task_types.h"
#include "rtGetNaN.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Block signals for system '<S4>/Coordinate Transformation Conversion2'
typedef struct {
  creal_T eigVec[16];
  creal_T b_At[16];
  creal_T A[16];
  creal_T b_V[16];
  creal_T e_A[16];
  creal_T c_V[16];
  real_T rtu_0[16];
  real_T c_V_m[16];
  real_T T[16];
  real_T b_A[16];
  real_T c_V_c[16];
  real_T b_h[16];
  real_T c_a[16];
  creal_T eigVal[4];
  creal_T b_beta1[4];
  creal_T work1[4];
  real_T CoordinateTransformationConve_i[4];
                                // '<S4>/Coordinate Transformation Conversion2'
  real_T varargin_1[4];
  real_T work[4];
  real_T rworka[4];
  real_T work_k[4];
  real_T tau[3];
  real_T v[3];
  real_T b_v[3];
  int32_T rscale[4];
  int8_T b_I[16];
  creal_T s;
  creal_T ctemp;
  creal_T shift;
  creal_T ascale;
  creal_T work1_c;
  creal_T work1_b;
  creal_T work1_p;
  real_T K12;
  real_T K13;
  real_T K14;
  real_T K23;
  real_T K24;
  real_T K34;
  real_T colnorm;
  real_T scale;
  real_T absxk;
  real_T t;
  real_T anrm;
  real_T absxk_c;
  real_T cfromc;
  real_T ctoc;
  real_T cfrom1;
  real_T cto1;
  real_T mul;
  real_T anorm;
  real_T b_atol;
  real_T absxr;
  real_T absxi;
  real_T ar;
  real_T ai;
  real_T t1_re;
  real_T t1_im;
  real_T ad11_re;
  real_T ad11_im;
  real_T ad11_im_f;
  real_T eshift_re;
  real_T eshift_im;
  real_T scale_g;
  real_T g2;
  real_T f2s;
  real_T di;
  real_T b_x;
  real_T fs_re;
  real_T fs_im;
  real_T gs_re;
  real_T gs_im;
  real_T a;
  real_T tst;
  real_T ab;
  real_T ba;
  real_T aa;
  real_T bb;
  real_T h12;
  real_T h21s;
  real_T d;
  real_T e;
  real_T p;
  real_T bcmax;
  real_T bcmis;
  real_T scale_g1;
  real_T z;
  real_T anorm_m;
  real_T ascale_n;
  real_T temp;
  real_T acoeff;
  real_T scale_p;
  real_T salpha_re;
  real_T salpha_im;
  real_T d_re;
  real_T d_im;
  real_T work2_idx_2_re;
  real_T b_alpha1;
  real_T xnorm;
  real_T temp_l;
  real_T scale_j;
  real_T g2_d;
  real_T f2s_g;
  real_T di_l;
  real_T b_x_d;
  real_T fs_re_d;
  real_T fs_im_l;
  real_T gs_re_o;
  real_T scale_b;
  real_T sumsq;
  real_T temp1;
  real_T temp2;
  real_T xnorm_n;
  real_T scale_bs;
  real_T absxk_l;
  real_T temp_h;
  real_T scale_bn;
  int32_T b_idx;
  int32_T b_idx_d;
  int32_T k;
  int32_T ia;
  int32_T i;
  int32_T itau;
  int32_T iaii;
  int32_T lastv;
  int32_T lastc;
  int32_T coltop;
  int32_T ix;
  int32_T iy;
  int32_T iac;
  int32_T d_e;
  int32_T ihi;
  int32_T i_b;
  int32_T j;
  int32_T k_j;
  int32_T ii;
  int32_T nzcount;
  int32_T b_jj;
  int32_T in;
  int32_T ia0;
  int32_T b_i;
  int32_T knt;
  int32_T atmp_re_tmp;
  int32_T j_f;
} B_CoordinateTransformationCon_T;

// Block states (default storage) for system '<S4>/Coordinate Transformation Conversion2' 
typedef struct {
  robotics_slcore_internal_bloc_T obj;
                                // '<S4>/Coordinate Transformation Conversion2'
  boolean_T objisempty;         // '<S4>/Coordinate Transformation Conversion2'
} DW_CoordinateTransformationCo_T;

// Block signals (default storage)
typedef struct {
  real_T Sinv_sat[36];
  real_T b_V[36];
  real_T R[36];
  real_T K[36];                        // '<Root>/K'
  real_T ProductofElements1[36];       // '<Root>/Product of Elements1'
  real_T U[36];                        // '<Root>/M_PINV1'
  real_T D_e[36];                      // '<Root>/D'
  real_T b_A[36];
  real_T Vf[36];
  real_T b_A_m[36];
  real_T Vf_c[36];
  real_T b_A_k[36];
  real_T b_A_c[36];
  real_T b_A_b[36];
  real_T getJacobian_o1[30];           // '<Root>/getJacobian'
  real_T rtb_MultiportSwitch_tmp_tmp[30];
  real_T dv[30];
  real_T A[25];
  real_T MathFunction_b[16];           // '<S5>/Math Function'
  real_T MathFunction[16];             // '<S10>/Math Function'
  real_T s[6];                         // '<Root>/M_PINV1'
  real_T dv1[6];
  real_T rtb_D_e_p[6];
  real_T rtb_K_c[6];
  real_T b_s[6];
  real_T e[6];
  real_T work[6];
  real_T b_s_f[6];
  real_T e_g[6];
  real_T work_g[6];
  real_T s_m[6];
  real_T b_s_n[6];
  real_T e_p[6];
  real_T work_l[6];
  real_T b_s_j[6];
  real_T e_d[6];
  real_T work_gu[6];
  real_T b_s_l[6];
  real_T e_dh[6];
  real_T work_d[6];
  real_T getJointPosition[5];          // '<Root>/getJointPosition'
  real_T getJacobian_o2[3];            // '<Root>/getJacobian'
  real_T getInertiaInverse[25];        // '<Root>/getInertiaInverse'
  real_T MatrixConcatenate[16];        // '<S10>/Matrix Concatenate'
  real_T MatrixConcatenate_k[16];      // '<S5>/Matrix Concatenate'
  real_T getJointVelocity[5];          // '<Root>/getJointVelocity'
  real_T computeGravityCompensation[5];// '<Root>/computeGravityCompensation'
  real_T Sum1[5];                      // '<Root>/Sum1'
  real_T getStiffness[5];              // '<Root>/getStiffness'
  real_T Gain[5];                      // '<Root>/Gain'
  real_T getDamping[5];                // '<Root>/getDamping'
  real_T Gain1[5];                     // '<Root>/Gain1'
  real_T getInertiaMatrix[25];         // '<Root>/getInertiaMatrix'
  real_T absx;
  real_T quat_ref_idx_3;
  real_T quat_ref_idx_2;
  real_T quat_ref_idx_1;
  real_T nrm;
  real_T rt;
  real_T r;
  real_T smm1;
  real_T emm1;
  real_T sqds;
  real_T shift;
  real_T roe;
  real_T absa;
  real_T absb;
  real_T scale;
  real_T ads;
  real_T bds;
  real_T nrm_l;
  real_T rt_o;
  real_T r_b;
  real_T smm1_n;
  real_T emm1_b;
  real_T sqds_l;
  real_T nrm_h;
  real_T rt_b;
  real_T r_d;
  real_T smm1_e;
  real_T emm1_bj;
  real_T sqds_j;
  real_T shift_f;
  real_T scale_a;
  real_T absxk;
  real_T t;
  real_T nrm_j;
  real_T rt_j;
  real_T r_o;
  real_T smm1_ny;
  real_T emm1_i;
  real_T sqds_o;
  real_T nrm_n;
  real_T rt_m;
  real_T r_c;
  real_T smm1_m;
  real_T emm1_m;
  real_T sqds_ja;
  real_T scale_h;
  real_T absxk_c;
  real_T t_c;
  real_T temp;
  real_T temp_p;
  int32_T vcol;
  int32_T b_j;
  int32_T ar;
  int32_T ia;
  int32_T ib;
  int32_T b_ic;
  int32_T i;
  int32_T rtb_ProductofElements1_tmp;
  int32_T qq;
  int32_T qjj;
  int32_T qp1jj;
  int32_T qp1q;
  int32_T i_p;
  int32_T i_a;
  int32_T qq_e;
  int32_T qjj_a;
  int32_T qp1jj_a;
  int32_T qp1q_i;
  int32_T i_l;
  int32_T kend;
  int32_T k;
  int32_T kend_o;
  int32_T k_o;
  int32_T ix;
  int32_T iy;
  int32_T k_i;
  int32_T ix_f;
  int32_T iy_i;
  int32_T k_f;
  int32_T ix_g;
  int32_T iy_c;
  int32_T k_o3;
  int32_T ix_l;
  int32_T iy_m;
  int32_T k_m;
  int32_T ix_c;
  int32_T iy_f;
  int32_T k_p;
  int32_T ix_e;
  int32_T iy_o;
  int32_T k_h;
  int32_T k_l;
  int32_T k_h2;
  boolean_T apply_transform;
  boolean_T p;
  boolean_T apply_transform_m;
  boolean_T b_p;
  B_CoordinateTransformationCon_T CoordinateTransformationConv_pn;
                                // '<S4>/Coordinate Transformation Conversion2'
  B_CoordinateTransformationCon_T CoordinateTransformationConve_p;
                                // '<S4>/Coordinate Transformation Conversion2'
} B_CartesianImpedance_Task_T;

// Block states (default storage) for system '<Root>'
typedef struct {
  struct {
    void *blockPWork[2];
  } getJointPosition_PWORK;            // '<Root>/getJointPosition'

  struct {
    void *blockPWork[2];
  } setPositionReference1_PWORK;       // '<Root>/setPositionReference1'

  struct {
    void *blockPWork[2];
  } getPoseFun_PWORK;                  // '<S10>/getPoseFun'

  struct {
    void *blockPWork[2];
  } getPoseFun_PWORK_h;                // '<S5>/getPoseFun'

  struct {
    void *blockPWork[2];
  } getJacobian_PWORK;                 // '<Root>/getJacobian'

  struct {
    void *blockPWork[2];
  } getInertiaInverse_PWORK;           // '<Root>/getInertiaInverse'

  struct {
    void *blockPWork[2];
  } getJointVelocity_PWORK;            // '<Root>/getJointVelocity'

  struct {
    void *blockPWork[2];
  } computeGravityCompensation_PWOR;   // '<Root>/computeGravityCompensation'

  struct {
    void *blockPWork[2];
  } setEffortReference_PWORK;          // '<Root>/setEffortReference'

  struct {
    void *blockPWork[2];
  } getStiffness_PWORK;                // '<Root>/getStiffness'

  struct {
    void *blockPWork[2];
  } setStiffness1_PWORK;               // '<Root>/setStiffness1'

  struct {
    void *blockPWork[2];
  } getDamping_PWORK;                  // '<Root>/getDamping'

  struct {
    void *blockPWork[2];
  } setDamping_PWORK;                  // '<Root>/setDamping'

  struct {
    void *blockPWork[2];
  } getInertiaMatrix_PWORK;            // '<Root>/getInertiaMatrix'

  DW_CoordinateTransformationCo_T CoordinateTransformationConv_pn;
                                // '<S4>/Coordinate Transformation Conversion2'
  DW_CoordinateTransformationCo_T CoordinateTransformationConve_p;
                                // '<S4>/Coordinate Transformation Conversion2'
} DW_CartesianImpedance_Task_T;

// Invariant block signals (default storage)
typedef const struct tag_ConstB_CartesianImpedance_T {
  real_T MatrixConcatenate2[6];        // '<Root>/Matrix Concatenate2'
} ConstB_CartesianImpedance_Tas_T;

// Real-time Model Data Structure
struct tag_RTM_CartesianImpedance_Ta_T {
  const char_T *errorStatus;
};

extern const ConstB_CartesianImpedance_Tas_T CartesianImpedance_Task_ConstB;// constant block i/o 

// Class declaration for model CartesianImpedance_Task
class modelModelClass {
  // public data and function members
 public:
  // model initialize function
  void initialize();

  // model step function
  void step();

  // model terminate function
  void terminate();

  // Constructor
  modelModelClass();

  // Destructor
  ~modelModelClass();

  // Real-Time Model get method
  RT_MODEL_CartesianImpedance_T_T * getRTM();

  // private data and function members
 private:
  // Block signals
  B_CartesianImpedance_Task_T CartesianImpedance_Task_B;

  // Block states
  DW_CartesianImpedance_Task_T CartesianImpedance_Task_DW;

  // Real-Time Model
  RT_MODEL_CartesianImpedance_T_T CartesianImpedance_Task_M;

  // private member function(s) for subsystem '<S4>/Coordinate Transformation Conversion2'
  void CoordinateTransformationC_Start(DW_CoordinateTransformationCo_T *localDW);
  void CoordinateTransformationConvers(const real_T rtu_0[16],
    B_CoordinateTransformationCon_T *localB);
  real_T CartesianImpedance_Task_xnrm2(int32_T n, const real_T x[16], int32_T
    ix0, B_CoordinateTransformationCon_T *localB);
  real_T CartesianImpedanc_rt_hypotd_snf(real_T u0, real_T u1,
    B_CoordinateTransformationCon_T *localB);
  void CartesianImpedance_Task_xgerc(int32_T m, int32_T n, real_T alpha1,
    int32_T ix0, const real_T y[4], const real_T A[16], int32_T ia0, real_T b_A
    [16], B_CoordinateTransformationCon_T *localB);
  void CartesianImpedance_Task_xgehrd(const real_T a[16], real_T b_a[16], real_T
    tau[3], B_CoordinateTransformationCon_T *localB);
  real_T CartesianImpedance_Task_xzlanhs(const creal_T A[16], int32_T ilo,
    int32_T ihi, B_CoordinateTransformationCon_T *localB);
  void CartesianImpedance_Ta_xzlartg_m(const creal_T f, const creal_T g, real_T *
    cs, creal_T *sn, B_CoordinateTransformationCon_T *localB);
  void CartesianImpedance_Task_xzlartg(const creal_T f, const creal_T g, real_T *
    cs, creal_T *sn, creal_T *r, B_CoordinateTransformationCon_T *localB);
  void CartesianImpedance_Task_xzhgeqz(const creal_T A[16], int32_T ilo, int32_T
    ihi, const creal_T Z[16], int32_T *info, creal_T alpha1[4], creal_T beta1[4],
    creal_T b_A[16], creal_T b_Z[16], B_CoordinateTransformationCon_T *localB);
  void CartesianImpedance_Task_xztgevc(const creal_T A[16], const creal_T V[16],
    creal_T b_V[16], B_CoordinateTransformationCon_T *localB);
  void CartesianImpedance_Task_xzggev(const creal_T A[16], creal_T b_A[16],
    int32_T *info, creal_T alpha1[4], creal_T beta1[4], creal_T V[16],
    B_CoordinateTransformationCon_T *localB);
  void CartesianImpedance_Task_xdlanv2(real_T a, real_T b, real_T c, real_T d,
    real_T *rt1r, real_T *rt1i, real_T *rt2r, real_T *rt2i, real_T *b_a, real_T *
    b_b, real_T *b_c, real_T *b_d, real_T *cs, real_T *sn,
    B_CoordinateTransformationCon_T *localB);
  void CartesianImpedance_Task_xrot(int32_T n, const real_T x[16], int32_T ix0,
    int32_T iy0, real_T c, real_T s, real_T b_x[16],
    B_CoordinateTransformationCon_T *localB);
  real_T CartesianImpedance_Task_xnrm2_p(int32_T n, const real_T x[3],
    B_CoordinateTransformationCon_T *localB);
  void CartesianImpedance_Ta_xzlarfg_d(int32_T n, real_T alpha1, real_T x[3],
    real_T *b_alpha1, real_T *tau, B_CoordinateTransformationCon_T *localB);
  void CartesianImpedance_Task_xhseqr(const real_T h[16], const real_T z[16],
    real_T b_h[16], int32_T *info, real_T b_z[16],
    B_CoordinateTransformationCon_T *localB);
  void CartesianImpedance_Task_eig(const real_T A[16], creal_T V[16], creal_T D
    [4], B_CoordinateTransformationCon_T *localB);

  // private member function(s) for subsystem '<Root>'
  boolean_T CartesianImpedance_anyNonFinite(const real_T x[36]);
  real_T CartesianImpedance_Task_xnrm2_g(int32_T n, const real_T x[36], int32_T
    ix0);
  real_T CartesianImpedance_Tas_xnrm2_gh(int32_T n, const real_T x[6], int32_T
    ix0);
  void CartesianImpedance_Tas_xaxpy_ag(int32_T n, real_T a, const real_T x[6],
    int32_T ix0, real_T y[36], int32_T iy0);
  void CartesianImpedance_Task_xaxpy_a(int32_T n, real_T a, const real_T x[36],
    int32_T ix0, real_T y[6], int32_T iy0);
  real_T CartesianImpedance_Task_xdotc(int32_T n, const real_T x[36], int32_T
    ix0, const real_T y[36], int32_T iy0);
  void CartesianImpedance_Task_xaxpy(int32_T n, real_T a, int32_T ix0, real_T y
    [36], int32_T iy0);
  void CartesianImpedance_Task_xscal(real_T a, real_T x[36], int32_T ix0);
  void CartesianImpedance_Task_xswap(real_T x[36], int32_T ix0, int32_T iy0);
  void CartesianImpedance_Task_xrotg(real_T *a, real_T *b, real_T *c, real_T *s);
  void CartesianImpedance_Task_xrot_i(real_T x[36], int32_T ix0, int32_T iy0,
    real_T c, real_T s);
  void CartesianImpedance_Task_svd_b(const real_T A[36], real_T U[36], real_T s
    [6], real_T V[36]);
  void CartesianImpedance_Task_svd_ij(const real_T A[36], real_T U[36], real_T
    s[6], real_T V[36]);
  void CartesianImpedance_Task_svd(const real_T A[36], real_T U[36], real_T S[36],
    real_T V[36]);
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Add' : Unused code path elimination
//  Block '<Root>/Constant4' : Unused code path elimination
//  Block '<Root>/Discrete-Time Integrator' : Unused code path elimination
//  Block '<Root>/Display1' : Unused code path elimination
//  Block '<Root>/Display10' : Unused code path elimination
//  Block '<Root>/Display11' : Unused code path elimination
//  Block '<Root>/Display12' : Unused code path elimination
//  Block '<Root>/Display13' : Unused code path elimination
//  Block '<Root>/Display15' : Unused code path elimination
//  Block '<Root>/Display16' : Unused code path elimination
//  Block '<Root>/Display2' : Unused code path elimination
//  Block '<Root>/Display5' : Unused code path elimination
//  Block '<Root>/Display6' : Unused code path elimination
//  Block '<Root>/Display7' : Unused code path elimination
//  Block '<Root>/Display8' : Unused code path elimination
//  Block '<Root>/Display9' : Unused code path elimination
//  Block '<S4>/Display1' : Unused code path elimination
//  Block '<S4>/Display25' : Unused code path elimination
//  Block '<S4>/Display4' : Unused code path elimination
//  Block '<S4>/Display5' : Unused code path elimination
//  Block '<S4>/Scope3' : Unused code path elimination
//  Block '<Root>/Gain4' : Unused code path elimination
//  Block '<Root>/Scope1' : Unused code path elimination
//  Block '<Root>/Scope4' : Unused code path elimination
//  Block '<Root>/Selector' : Unused code path elimination
//  Block '<Root>/Selector1' : Unused code path elimination
//  Block '<Root>/Selector2' : Unused code path elimination
//  Block '<S4>/Reshape' : Reshape block reduction
//  Block '<S4>/Reshape1' : Reshape block reduction
//  Block '<Root>/Gain3' : Eliminated nontunable gain of 1
//  Block '<Root>/Gain6' : Eliminated nontunable gain of 1
//  Block '<Root>/Manual Switch' : Eliminated due to constant selection input


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'CartesianImpedance_Task'
//  '<S1>'   : 'CartesianImpedance_Task/D'
//  '<S2>'   : 'CartesianImpedance_Task/D1'
//  '<S3>'   : 'CartesianImpedance_Task/D3'
//  '<S4>'   : 'CartesianImpedance_Task/ErrorComp'
//  '<S5>'   : 'CartesianImpedance_Task/GetPose'
//  '<S6>'   : 'CartesianImpedance_Task/INV'
//  '<S7>'   : 'CartesianImpedance_Task/K'
//  '<S8>'   : 'CartesianImpedance_Task/M_PINV'
//  '<S9>'   : 'CartesianImpedance_Task/M_PINV1'
//  '<S10>'  : 'CartesianImpedance_Task/TargetPose'
//  '<S11>'  : 'CartesianImpedance_Task/ErrorComp/QuaternionOrientationError '

#endif                                 // RTW_HEADER_CartesianImpedance_Task_h_

//
// File trailer for generated code.
//
// [EOF]
//
