//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, educational organizations only. Not for
// government, commercial, or other organizational use.
//
// File: CartesianImpedance_Task.cpp
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
#include "CartesianImpedance_Task.h"
#include "CartesianImpedance_Task_private.h"

real_T modelModelClass::CartesianImpedance_Task_xnrm2(int32_T n, const real_T x
  [16], int32_T ix0, B_CoordinateTransformationCon_T *localB)
{
  real_T y;
  real_T absxk;
  real_T t;
  int32_T k;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = std::abs(x[ix0 - 1]);
    } else {
      localB->scale_bn = 3.3121686421112381E-170;
      for (k = ix0; k <= ix0 + 1; k++) {
        absxk = std::abs(x[k - 1]);
        if (absxk > localB->scale_bn) {
          t = localB->scale_bn / absxk;
          y = y * t * t + 1.0;
          localB->scale_bn = absxk;
        } else {
          t = absxk / localB->scale_bn;
          y += t * t;
        }
      }

      y = localB->scale_bn * std::sqrt(y);
    }
  }

  return y;
}

real_T modelModelClass::CartesianImpedanc_rt_hypotd_snf(real_T u0, real_T u1,
  B_CoordinateTransformationCon_T *localB)
{
  real_T y;
  localB->a = std::abs(u0);
  y = std::abs(u1);
  if (localB->a < y) {
    localB->a /= y;
    y *= std::sqrt(localB->a * localB->a + 1.0);
  } else if (localB->a > y) {
    y /= localB->a;
    y = std::sqrt(y * y + 1.0) * localB->a;
  } else {
    if (!rtIsNaN(y)) {
      y = localB->a * 1.4142135623730951;
    }
  }

  return y;
}

void modelModelClass::CartesianImpedance_Task_xgerc(int32_T m, int32_T n, real_T
  alpha1, int32_T ix0, const real_T y[4], const real_T A[16], int32_T ia0,
  real_T b_A[16], B_CoordinateTransformationCon_T *localB)
{
  int32_T jA;
  int32_T jy;
  int32_T ix;
  int32_T j;
  int32_T c;
  int32_T ijA;
  std::memcpy(&b_A[0], &A[0], sizeof(real_T) << 4U);
  if (!(alpha1 == 0.0)) {
    jA = ia0;
    jy = 0;
    for (j = 0; j < n; j++) {
      if (y[jy] != 0.0) {
        localB->temp_l = y[jy] * alpha1;
        ix = ix0 - 1;
        c = (m + jA) - 1;
        for (ijA = jA; ijA <= c; ijA++) {
          b_A[ijA - 1] += b_A[ix] * localB->temp_l;
          ix++;
        }
      }

      jy++;
      jA += 4;
    }
  }
}

void modelModelClass::CartesianImpedance_Task_xgehrd(const real_T a[16], real_T
  b_a[16], real_T tau[3], B_CoordinateTransformationCon_T *localB)
{
  int32_T lastc;
  int32_T iy;
  int32_T ix;
  int32_T iac;
  int32_T d;
  int32_T jA;
  int32_T jy;
  int32_T b_i;
  int32_T im1n_tmp;
  int32_T exitg1;
  boolean_T exitg2;
  std::memcpy(&b_a[0], &a[0], sizeof(real_T) << 4U);
  localB->work_k[0] = 0.0;
  localB->work_k[1] = 0.0;
  localB->work_k[2] = 0.0;
  localB->work_k[3] = 0.0;
  for (localB->b_i = 0; localB->b_i < 3; localB->b_i++) {
    im1n_tmp = localB->b_i << 2;
    localB->in = (localB->b_i + 1) << 2;
    if (localB->b_i + 3 < 4) {
      b_i = 3;
    } else {
      b_i = 4;
    }

    localB->ia0 = im1n_tmp + b_i;
    std::memcpy(&localB->c_a[0], &b_a[0], sizeof(real_T) << 4U);
    b_i = (im1n_tmp + localB->b_i) + 1;
    localB->b_alpha1 = b_a[b_i];
    tau[localB->b_i] = 0.0;
    localB->xnorm = CartesianImpedance_Task_xnrm2(2 - localB->b_i, b_a,
      localB->ia0, localB);
    if (localB->xnorm != 0.0) {
      localB->xnorm = CartesianImpedanc_rt_hypotd_snf(b_a[b_i], localB->xnorm,
        localB);
      if (b_a[b_i] >= 0.0) {
        localB->xnorm = -localB->xnorm;
      }

      if (std::abs(localB->xnorm) < 1.0020841800044864E-292) {
        localB->knt = -1;
        ix = localB->ia0 - localB->b_i;
        do {
          localB->knt++;
          for (lastc = localB->ia0; lastc <= ix + 1; lastc++) {
            localB->c_a[lastc - 1] *= 9.9792015476736E+291;
          }

          localB->xnorm *= 9.9792015476736E+291;
          localB->b_alpha1 *= 9.9792015476736E+291;
        } while (!(std::abs(localB->xnorm) >= 1.0020841800044864E-292));

        localB->xnorm = CartesianImpedanc_rt_hypotd_snf(localB->b_alpha1,
          CartesianImpedance_Task_xnrm2(2 - localB->b_i, localB->c_a,
          localB->ia0, localB), localB);
        if (localB->b_alpha1 >= 0.0) {
          localB->xnorm = -localB->xnorm;
        }

        tau[localB->b_i] = (localB->xnorm - localB->b_alpha1) / localB->xnorm;
        localB->b_alpha1 = 1.0 / (localB->b_alpha1 - localB->xnorm);
        for (lastc = localB->ia0; lastc <= ix + 1; lastc++) {
          localB->c_a[lastc - 1] *= localB->b_alpha1;
        }

        for (lastc = 0; lastc <= localB->knt; lastc++) {
          localB->xnorm *= 1.0020841800044864E-292;
        }

        localB->b_alpha1 = localB->xnorm;
      } else {
        tau[localB->b_i] = (localB->xnorm - b_a[b_i]) / localB->xnorm;
        localB->b_alpha1 = 1.0 / (b_a[b_i] - localB->xnorm);
        std::memcpy(&localB->c_a[0], &b_a[0], sizeof(real_T) << 4U);
        jA = localB->ia0 - localB->b_i;
        for (lastc = localB->ia0; lastc <= jA + 1; lastc++) {
          localB->c_a[lastc - 1] *= localB->b_alpha1;
        }

        localB->b_alpha1 = localB->xnorm;
      }
    }

    std::memcpy(&b_a[0], &localB->c_a[0], sizeof(real_T) << 4U);
    b_a[b_i] = 1.0;
    im1n_tmp = (localB->b_i + im1n_tmp) + 2;
    std::memcpy(&localB->c_a[0], &b_a[0], sizeof(real_T) << 4U);
    if (tau[localB->b_i] != 0.0) {
      localB->ia0 = 2 - localB->b_i;
      lastc = im1n_tmp - localB->b_i;
      while ((localB->ia0 + 1 > 0) && (b_a[lastc + 1] == 0.0)) {
        localB->ia0--;
        lastc--;
      }

      lastc = 4;
      exitg2 = false;
      while ((!exitg2) && (lastc > 0)) {
        localB->knt = localB->in + lastc;
        jy = localB->knt;
        do {
          exitg1 = 0;
          if (jy <= (localB->ia0 << 2) + localB->knt) {
            if (b_a[jy - 1] != 0.0) {
              exitg1 = 1;
            } else {
              jy += 4;
            }
          } else {
            lastc--;
            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = true;
        }
      }

      std::memcpy(&localB->c_a[0], &b_a[0], sizeof(real_T) << 4U);
    } else {
      localB->ia0 = -1;
      lastc = 0;
    }

    if (localB->ia0 + 1 > 0) {
      if (lastc != 0) {
        if (0 <= lastc - 1) {
          std::memset(&localB->work_k[0], 0, lastc * sizeof(real_T));
        }

        ix = im1n_tmp - 1;
        jA = (localB->ia0 << 2) + localB->in;
        for (iac = localB->in + 1; iac <= jA + 1; iac += 4) {
          iy = 0;
          d = iac + lastc;
          for (jy = iac; jy < d; jy++) {
            localB->work_k[iy] += localB->c_a[jy - 1] * localB->c_a[ix];
            iy++;
          }

          ix++;
        }
      }

      if (!(-tau[localB->b_i] == 0.0)) {
        jA = localB->in;
        jy = im1n_tmp - 1;
        for (iac = 0; iac <= localB->ia0; iac++) {
          if (localB->c_a[jy] != 0.0) {
            localB->xnorm = localB->c_a[jy] * -tau[localB->b_i];
            ix = 0;
            localB->knt = lastc + jA;
            for (iy = jA + 1; iy <= localB->knt; iy++) {
              localB->c_a[iy - 1] += localB->work_k[ix] * localB->xnorm;
              ix++;
            }
          }

          jy++;
          jA += 4;
        }
      }
    }

    localB->knt = (localB->b_i + localB->in) + 2;
    std::memcpy(&b_a[0], &localB->c_a[0], sizeof(real_T) << 4U);
    if (tau[localB->b_i] != 0.0) {
      localB->ia0 = 3 - localB->b_i;
      lastc = im1n_tmp - localB->b_i;
      while ((localB->ia0 > 0) && (localB->c_a[lastc + 1] == 0.0)) {
        localB->ia0--;
        lastc--;
      }

      lastc = 3 - localB->b_i;
      exitg2 = false;
      while ((!exitg2) && (lastc > 0)) {
        localB->in = ((lastc - 1) << 2) + localB->knt;
        jy = localB->in;
        do {
          exitg1 = 0;
          if (jy <= (localB->in + localB->ia0) - 1) {
            if (localB->c_a[jy - 1] != 0.0) {
              exitg1 = 1;
            } else {
              jy++;
            }
          } else {
            lastc--;
            exitg1 = 2;
          }
        } while (exitg1 == 0);

        if (exitg1 == 1) {
          exitg2 = true;
        }
      }

      std::memcpy(&b_a[0], &localB->c_a[0], sizeof(real_T) << 4U);
    } else {
      localB->ia0 = 0;
      lastc = 0;
    }

    if (localB->ia0 > 0) {
      if (lastc != 0) {
        if (0 <= lastc - 1) {
          std::memset(&localB->work_k[0], 0, lastc * sizeof(real_T));
        }

        iy = 0;
        jA = ((lastc - 1) << 2) + localB->knt;
        for (iac = localB->knt; iac <= jA; iac += 4) {
          ix = im1n_tmp - 1;
          localB->xnorm = 0.0;
          d = iac + localB->ia0;
          for (jy = iac; jy < d; jy++) {
            localB->xnorm += b_a[jy - 1] * b_a[ix];
            ix++;
          }

          localB->work_k[iy] += localB->xnorm;
          iy++;
        }
      }

      std::memcpy(&localB->c_a[0], &b_a[0], sizeof(real_T) << 4U);
      CartesianImpedance_Task_xgerc(localB->ia0, lastc, -tau[localB->b_i],
        im1n_tmp, localB->work_k, localB->c_a, localB->knt, b_a, localB);
    }

    b_a[b_i] = localB->b_alpha1;
  }
}

real_T modelModelClass::CartesianImpedance_Task_xzlanhs(const creal_T A[16],
  int32_T ilo, int32_T ihi, B_CoordinateTransformationCon_T *localB)
{
  real_T f;
  boolean_T firstNonZero;
  int32_T j;
  int32_T b;
  int32_T i;
  int32_T reAij_tmp;
  f = 0.0;
  if (ilo <= ihi) {
    localB->scale_b = 0.0;
    localB->sumsq = 0.0;
    firstNonZero = true;
    for (j = ilo; j <= ihi; j++) {
      b = j + 1;
      if (ihi < j + 1) {
        b = ihi;
      }

      for (i = ilo; i <= b; i++) {
        reAij_tmp = (((j - 1) << 2) + i) - 1;
        if (A[reAij_tmp].re != 0.0) {
          localB->temp1 = std::abs(A[reAij_tmp].re);
          if (firstNonZero) {
            localB->sumsq = 1.0;
            localB->scale_b = localB->temp1;
            firstNonZero = false;
          } else if (localB->scale_b < localB->temp1) {
            localB->temp2 = localB->scale_b / localB->temp1;
            localB->sumsq = localB->sumsq * localB->temp2 * localB->temp2 + 1.0;
            localB->scale_b = localB->temp1;
          } else {
            localB->temp2 = localB->temp1 / localB->scale_b;
            localB->sumsq += localB->temp2 * localB->temp2;
          }
        }

        if (A[reAij_tmp].im != 0.0) {
          localB->temp1 = std::abs(A[reAij_tmp].im);
          if (firstNonZero) {
            localB->sumsq = 1.0;
            localB->scale_b = localB->temp1;
            firstNonZero = false;
          } else if (localB->scale_b < localB->temp1) {
            localB->temp2 = localB->scale_b / localB->temp1;
            localB->sumsq = localB->sumsq * localB->temp2 * localB->temp2 + 1.0;
            localB->scale_b = localB->temp1;
          } else {
            localB->temp2 = localB->temp1 / localB->scale_b;
            localB->sumsq += localB->temp2 * localB->temp2;
          }
        }
      }
    }

    f = localB->scale_b * std::sqrt(localB->sumsq);
  }

  return f;
}

void modelModelClass::CartesianImpedance_Ta_xzlartg_m(const creal_T f, const
  creal_T g, real_T *cs, creal_T *sn, B_CoordinateTransformationCon_T *localB)
{
  real_T gs_im;
  boolean_T guard1 = false;
  localB->f2s_g = std::abs(f.re);
  localB->di_l = std::abs(f.im);
  localB->scale_j = localB->f2s_g;
  if (localB->di_l > localB->f2s_g) {
    localB->scale_j = localB->di_l;
  }

  localB->gs_re_o = std::abs(g.re);
  gs_im = std::abs(g.im);
  if (gs_im > localB->gs_re_o) {
    localB->gs_re_o = gs_im;
  }

  if (localB->gs_re_o > localB->scale_j) {
    localB->scale_j = localB->gs_re_o;
  }

  localB->fs_re_d = f.re;
  localB->fs_im_l = f.im;
  localB->gs_re_o = g.re;
  gs_im = g.im;
  guard1 = false;
  if (localB->scale_j >= 7.4428285367870146E+137) {
    do {
      localB->fs_re_d *= 1.3435752215134178E-138;
      localB->fs_im_l *= 1.3435752215134178E-138;
      localB->gs_re_o *= 1.3435752215134178E-138;
      gs_im *= 1.3435752215134178E-138;
      localB->scale_j *= 1.3435752215134178E-138;
    } while (!(localB->scale_j < 7.4428285367870146E+137));

    guard1 = true;
  } else if (localB->scale_j <= 1.3435752215134178E-138) {
    if ((g.re == 0.0) && (g.im == 0.0)) {
      *cs = 1.0;
      sn->re = 0.0;
      sn->im = 0.0;
    } else {
      do {
        localB->fs_re_d *= 7.4428285367870146E+137;
        localB->fs_im_l *= 7.4428285367870146E+137;
        localB->gs_re_o *= 7.4428285367870146E+137;
        gs_im *= 7.4428285367870146E+137;
        localB->scale_j *= 7.4428285367870146E+137;
      } while (!(localB->scale_j > 1.3435752215134178E-138));

      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    localB->scale_j = localB->fs_re_d * localB->fs_re_d + localB->fs_im_l *
      localB->fs_im_l;
    localB->g2_d = localB->gs_re_o * localB->gs_re_o + gs_im * gs_im;
    localB->b_x_d = localB->g2_d;
    if (1.0 > localB->g2_d) {
      localB->b_x_d = 1.0;
    }

    if (localB->scale_j <= localB->b_x_d * 2.0041683600089728E-292) {
      if ((f.re == 0.0) && (f.im == 0.0)) {
        *cs = 0.0;
        localB->f2s_g = CartesianImpedanc_rt_hypotd_snf(localB->gs_re_o, gs_im,
          localB);
        sn->re = localB->gs_re_o / localB->f2s_g;
        sn->im = -gs_im / localB->f2s_g;
      } else {
        localB->scale_j = std::sqrt(localB->g2_d);
        *cs = CartesianImpedanc_rt_hypotd_snf(localB->fs_re_d, localB->fs_im_l,
          localB) / localB->scale_j;
        if (localB->di_l > localB->f2s_g) {
          localB->f2s_g = localB->di_l;
        }

        if (localB->f2s_g > 1.0) {
          localB->f2s_g = CartesianImpedanc_rt_hypotd_snf(f.re, f.im, localB);
          localB->fs_re_d = f.re / localB->f2s_g;
          localB->fs_im_l = f.im / localB->f2s_g;
        } else {
          localB->fs_re_d = 7.4428285367870146E+137 * f.re;
          localB->di_l = 7.4428285367870146E+137 * f.im;
          localB->f2s_g = CartesianImpedanc_rt_hypotd_snf(localB->fs_re_d,
            localB->di_l, localB);
          localB->fs_re_d /= localB->f2s_g;
          localB->fs_im_l = localB->di_l / localB->f2s_g;
        }

        localB->gs_re_o /= localB->scale_j;
        gs_im = -gs_im / localB->scale_j;
        sn->re = localB->fs_re_d * localB->gs_re_o - localB->fs_im_l * gs_im;
        sn->im = localB->fs_re_d * gs_im + localB->fs_im_l * localB->gs_re_o;
      }
    } else {
      localB->f2s_g = std::sqrt(localB->g2_d / localB->scale_j + 1.0);
      localB->fs_re_d *= localB->f2s_g;
      localB->fs_im_l *= localB->f2s_g;
      *cs = 1.0 / localB->f2s_g;
      localB->f2s_g = localB->scale_j + localB->g2_d;
      localB->fs_re_d /= localB->f2s_g;
      localB->fs_im_l /= localB->f2s_g;
      sn->re = localB->fs_re_d * localB->gs_re_o - localB->fs_im_l * -gs_im;
      sn->im = localB->fs_re_d * -gs_im + localB->fs_im_l * localB->gs_re_o;
    }
  }
}

void modelModelClass::CartesianImpedance_Task_xzlartg(const creal_T f, const
  creal_T g, real_T *cs, creal_T *sn, creal_T *r,
  B_CoordinateTransformationCon_T *localB)
{
  int32_T count;
  int32_T rescaledir;
  boolean_T guard1 = false;
  localB->f2s = std::abs(f.re);
  localB->di = std::abs(f.im);
  localB->scale_g = localB->f2s;
  if (localB->di > localB->f2s) {
    localB->scale_g = localB->di;
  }

  localB->gs_re = std::abs(g.re);
  localB->gs_im = std::abs(g.im);
  if (localB->gs_im > localB->gs_re) {
    localB->gs_re = localB->gs_im;
  }

  if (localB->gs_re > localB->scale_g) {
    localB->scale_g = localB->gs_re;
  }

  localB->fs_re = f.re;
  localB->fs_im = f.im;
  localB->gs_re = g.re;
  localB->gs_im = g.im;
  count = -1;
  rescaledir = 0;
  guard1 = false;
  if (localB->scale_g >= 7.4428285367870146E+137) {
    do {
      count++;
      localB->fs_re *= 1.3435752215134178E-138;
      localB->fs_im *= 1.3435752215134178E-138;
      localB->gs_re *= 1.3435752215134178E-138;
      localB->gs_im *= 1.3435752215134178E-138;
      localB->scale_g *= 1.3435752215134178E-138;
    } while (!(localB->scale_g < 7.4428285367870146E+137));

    rescaledir = 1;
    guard1 = true;
  } else if (localB->scale_g <= 1.3435752215134178E-138) {
    if ((g.re == 0.0) && (g.im == 0.0)) {
      *cs = 1.0;
      sn->re = 0.0;
      sn->im = 0.0;
      *r = f;
    } else {
      do {
        count++;
        localB->fs_re *= 7.4428285367870146E+137;
        localB->fs_im *= 7.4428285367870146E+137;
        localB->gs_re *= 7.4428285367870146E+137;
        localB->gs_im *= 7.4428285367870146E+137;
        localB->scale_g *= 7.4428285367870146E+137;
      } while (!(localB->scale_g > 1.3435752215134178E-138));

      rescaledir = -1;
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    localB->scale_g = localB->fs_re * localB->fs_re + localB->fs_im *
      localB->fs_im;
    localB->g2 = localB->gs_re * localB->gs_re + localB->gs_im * localB->gs_im;
    localB->b_x = localB->g2;
    if (1.0 > localB->g2) {
      localB->b_x = 1.0;
    }

    if (localB->scale_g <= localB->b_x * 2.0041683600089728E-292) {
      if ((f.re == 0.0) && (f.im == 0.0)) {
        *cs = 0.0;
        r->re = CartesianImpedanc_rt_hypotd_snf(g.re, g.im, localB);
        r->im = 0.0;
        localB->f2s = CartesianImpedanc_rt_hypotd_snf(localB->gs_re,
          localB->gs_im, localB);
        sn->re = localB->gs_re / localB->f2s;
        sn->im = -localB->gs_im / localB->f2s;
      } else {
        localB->scale_g = std::sqrt(localB->g2);
        *cs = CartesianImpedanc_rt_hypotd_snf(localB->fs_re, localB->fs_im,
          localB) / localB->scale_g;
        if (localB->di > localB->f2s) {
          localB->f2s = localB->di;
        }

        if (localB->f2s > 1.0) {
          localB->f2s = CartesianImpedanc_rt_hypotd_snf(f.re, f.im, localB);
          localB->fs_re = f.re / localB->f2s;
          localB->fs_im = f.im / localB->f2s;
        } else {
          localB->fs_re = 7.4428285367870146E+137 * f.re;
          localB->di = 7.4428285367870146E+137 * f.im;
          localB->f2s = CartesianImpedanc_rt_hypotd_snf(localB->fs_re,
            localB->di, localB);
          localB->fs_re /= localB->f2s;
          localB->fs_im = localB->di / localB->f2s;
        }

        localB->gs_re /= localB->scale_g;
        localB->gs_im = -localB->gs_im / localB->scale_g;
        sn->re = localB->fs_re * localB->gs_re - localB->fs_im * localB->gs_im;
        sn->im = localB->fs_re * localB->gs_im + localB->fs_im * localB->gs_re;
        r->re = (sn->re * g.re - sn->im * g.im) + *cs * f.re;
        r->im = (sn->re * g.im + sn->im * g.re) + *cs * f.im;
      }
    } else {
      localB->f2s = std::sqrt(localB->g2 / localB->scale_g + 1.0);
      r->re = localB->f2s * localB->fs_re;
      r->im = localB->f2s * localB->fs_im;
      *cs = 1.0 / localB->f2s;
      localB->f2s = localB->scale_g + localB->g2;
      localB->fs_re = r->re / localB->f2s;
      localB->f2s = r->im / localB->f2s;
      sn->re = localB->fs_re * localB->gs_re - localB->f2s * -localB->gs_im;
      sn->im = localB->fs_re * -localB->gs_im + localB->f2s * localB->gs_re;
      if (rescaledir > 0) {
        for (rescaledir = 0; rescaledir <= count; rescaledir++) {
          r->re *= 7.4428285367870146E+137;
          r->im *= 7.4428285367870146E+137;
        }
      } else {
        if (rescaledir < 0) {
          for (rescaledir = 0; rescaledir <= count; rescaledir++) {
            r->re *= 1.3435752215134178E-138;
            r->im *= 1.3435752215134178E-138;
          }
        }
      }
    }
  }
}

void modelModelClass::CartesianImpedance_Task_xzhgeqz(const creal_T A[16],
  int32_T ilo, int32_T ihi, const creal_T Z[16], int32_T *info, creal_T alpha1[4],
  creal_T beta1[4], creal_T b_A[16], creal_T b_Z[16],
  B_CoordinateTransformationCon_T *localB)
{
  boolean_T failed;
  int32_T ifirst;
  int32_T istart;
  int32_T ilast;
  int32_T ilastm1;
  int32_T iiter;
  boolean_T goto60;
  boolean_T goto70;
  boolean_T goto90;
  int32_T jp1;
  int32_T jiter;
  int32_T i;
  int32_T ctemp_tmp;
  int32_T ctemp_tmp_tmp;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  boolean_T guard3 = false;
  int32_T exitg1;
  boolean_T exitg2;
  boolean_T guard11 = false;
  std::memcpy(&b_Z[0], &Z[0], sizeof(creal_T) << 4U);
  std::memcpy(&b_A[0], &A[0], sizeof(creal_T) << 4U);
  *info = 0;
  alpha1[0].re = 0.0;
  alpha1[0].im = 0.0;
  beta1[0].re = 1.0;
  beta1[0].im = 0.0;
  alpha1[1].re = 0.0;
  alpha1[1].im = 0.0;
  beta1[1].re = 1.0;
  beta1[1].im = 0.0;
  alpha1[2].re = 0.0;
  alpha1[2].im = 0.0;
  beta1[2].re = 1.0;
  beta1[2].im = 0.0;
  alpha1[3].re = 0.0;
  alpha1[3].im = 0.0;
  beta1[3].re = 1.0;
  beta1[3].im = 0.0;
  localB->eshift_re = 0.0;
  localB->eshift_im = 0.0;
  localB->ctemp.re = 0.0;
  localB->ctemp.im = 0.0;
  localB->anorm = CartesianImpedance_Task_xzlanhs(A, ilo, ihi, localB);
  localB->t1_re = 2.2204460492503131E-16 * localB->anorm;
  localB->b_atol = 2.2250738585072014E-308;
  if (localB->t1_re > 2.2250738585072014E-308) {
    localB->b_atol = localB->t1_re;
  }

  localB->t1_re = 2.2250738585072014E-308;
  if (localB->anorm > 2.2250738585072014E-308) {
    localB->t1_re = localB->anorm;
  }

  localB->anorm = 1.0 / localB->t1_re;
  failed = true;
  for (ilast = ihi + 1; ilast < 5; ilast++) {
    alpha1[ilast - 1] = A[(((ilast - 1) << 2) + ilast) - 1];
  }

  guard1 = false;
  guard2 = false;
  if (ihi >= ilo) {
    ifirst = ilo;
    istart = ilo;
    ilast = ihi - 1;
    ilastm1 = ihi - 2;
    iiter = 0;
    goto60 = false;
    goto70 = false;
    goto90 = false;
    jiter = 0;
    do {
      exitg1 = 0;
      if (jiter <= ((ihi - ilo) + 1) * 30 - 1) {
        guard11 = false;
        if (ilast + 1 == ilo) {
          goto60 = true;
          guard11 = true;
        } else {
          jp1 = (ilastm1 << 2) + ilast;
          if (std::abs(b_A[jp1].re) + std::abs(b_A[jp1].im) <= localB->b_atol) {
            b_A[jp1].re = 0.0;
            b_A[jp1].im = 0.0;
            goto60 = true;
            guard11 = true;
          } else {
            localB->j_f = ilastm1 + 1;
            guard3 = false;
            exitg2 = false;
            while ((!exitg2) && (localB->j_f >= ilo)) {
              if (localB->j_f == ilo) {
                guard3 = true;
                exitg2 = true;
              } else {
                jp1 = (((localB->j_f - 2) << 2) + localB->j_f) - 1;
                if (std::abs(b_A[jp1].re) + std::abs(b_A[jp1].im) <=
                    localB->b_atol) {
                  b_A[jp1].re = 0.0;
                  b_A[jp1].im = 0.0;
                  guard3 = true;
                  exitg2 = true;
                } else {
                  localB->j_f--;
                  guard3 = false;
                }
              }
            }

            if (guard3) {
              ifirst = localB->j_f;
              goto70 = true;
            }

            if (goto70) {
              guard11 = true;
            } else {
              alpha1[0].re = (rtNaN);
              alpha1[0].im = 0.0;
              beta1[0].re = (rtNaN);
              beta1[0].im = 0.0;
              alpha1[1].re = (rtNaN);
              alpha1[1].im = 0.0;
              beta1[1].re = (rtNaN);
              beta1[1].im = 0.0;
              alpha1[2].re = (rtNaN);
              alpha1[2].im = 0.0;
              beta1[2].re = (rtNaN);
              beta1[2].im = 0.0;
              alpha1[3].re = (rtNaN);
              alpha1[3].im = 0.0;
              beta1[3].re = (rtNaN);
              beta1[3].im = 0.0;
              for (jp1 = 0; jp1 < 16; jp1++) {
                b_Z[jp1].re = (rtNaN);
                b_Z[jp1].im = 0.0;
              }

              *info = 1;
              exitg1 = 1;
            }
          }
        }

        if (guard11) {
          if (goto60) {
            goto60 = false;
            alpha1[ilast] = b_A[(ilast << 2) + ilast];
            ilast = ilastm1;
            ilastm1--;
            if (ilast + 1 < ilo) {
              failed = false;
              guard2 = true;
              exitg1 = 1;
            } else {
              iiter = 0;
              localB->eshift_re = 0.0;
              localB->eshift_im = 0.0;
              jiter++;
            }
          } else {
            if (goto70) {
              goto70 = false;
              iiter++;
              if (iiter - iiter / 10 * 10 != 0) {
                localB->j_f = (ilastm1 << 2) + ilastm1;
                localB->ar = b_A[localB->j_f].re * localB->anorm;
                localB->ai = b_A[localB->j_f].im * localB->anorm;
                if (localB->ai == 0.0) {
                  localB->ad11_re = localB->ar / 0.5;
                  localB->ad11_im = 0.0;
                } else if (localB->ar == 0.0) {
                  localB->ad11_re = 0.0;
                  localB->ad11_im = localB->ai / 0.5;
                } else {
                  localB->ad11_re = localB->ar / 0.5;
                  localB->ad11_im = localB->ai / 0.5;
                }

                localB->j_f = (ilast << 2) + ilast;
                localB->ar = b_A[localB->j_f].re * localB->anorm;
                localB->ai = b_A[localB->j_f].im * localB->anorm;
                if (localB->ai == 0.0) {
                  localB->shift.re = localB->ar / 0.5;
                  localB->shift.im = 0.0;
                } else if (localB->ar == 0.0) {
                  localB->shift.re = 0.0;
                  localB->shift.im = localB->ai / 0.5;
                } else {
                  localB->shift.re = localB->ar / 0.5;
                  localB->shift.im = localB->ai / 0.5;
                }

                localB->t1_re = (localB->ad11_re + localB->shift.re) * 0.5;
                localB->t1_im = (localB->ad11_im + localB->shift.im) * 0.5;
                localB->j_f = (ilast << 2) + ilastm1;
                localB->ar = b_A[localB->j_f].re * localB->anorm;
                localB->ai = b_A[localB->j_f].im * localB->anorm;
                if (localB->ai == 0.0) {
                  localB->absxr = localB->ar / 0.5;
                  localB->absxi = 0.0;
                } else if (localB->ar == 0.0) {
                  localB->absxr = 0.0;
                  localB->absxi = localB->ai / 0.5;
                } else {
                  localB->absxr = localB->ar / 0.5;
                  localB->absxi = localB->ai / 0.5;
                }

                localB->j_f = (ilastm1 << 2) + ilast;
                localB->ar = b_A[localB->j_f].re * localB->anorm;
                localB->ai = b_A[localB->j_f].im * localB->anorm;
                if (localB->ai == 0.0) {
                  localB->ar /= 0.5;
                  localB->ai = 0.0;
                } else if (localB->ar == 0.0) {
                  localB->ar = 0.0;
                  localB->ai /= 0.5;
                } else {
                  localB->ar /= 0.5;
                  localB->ai /= 0.5;
                }

                localB->ad11_im_f = localB->ad11_re * localB->shift.im +
                  localB->ad11_im * localB->shift.re;
                localB->ad11_re = ((localB->t1_re * localB->t1_re -
                                    localB->t1_im * localB->t1_im) +
                                   (localB->absxr * localB->ar - localB->absxi *
                                    localB->ai)) - (localB->ad11_re *
                  localB->shift.re - localB->ad11_im * localB->shift.im);
                localB->ad11_im = localB->t1_re * localB->t1_im;
                localB->ad11_im = ((localB->ad11_im + localB->ad11_im) +
                                   (localB->absxr * localB->ai + localB->absxi *
                                    localB->ar)) - localB->ad11_im_f;
                if (localB->ad11_im == 0.0) {
                  if (localB->ad11_re < 0.0) {
                    localB->absxr = 0.0;
                    localB->ad11_re = std::sqrt(-localB->ad11_re);
                  } else {
                    localB->absxr = std::sqrt(localB->ad11_re);
                    localB->ad11_re = 0.0;
                  }
                } else if (localB->ad11_re == 0.0) {
                  if (localB->ad11_im < 0.0) {
                    localB->absxr = std::sqrt(-localB->ad11_im / 2.0);
                    localB->ad11_re = -localB->absxr;
                  } else {
                    localB->absxr = std::sqrt(localB->ad11_im / 2.0);
                    localB->ad11_re = localB->absxr;
                  }
                } else if (rtIsNaN(localB->ad11_re)) {
                  localB->absxr = localB->ad11_re;
                } else if (rtIsNaN(localB->ad11_im)) {
                  localB->absxr = localB->ad11_im;
                  localB->ad11_re = localB->ad11_im;
                } else if (rtIsInf(localB->ad11_im)) {
                  localB->absxr = std::abs(localB->ad11_im);
                  localB->ad11_re = localB->ad11_im;
                } else if (rtIsInf(localB->ad11_re)) {
                  if (localB->ad11_re < 0.0) {
                    localB->absxr = 0.0;
                    localB->ad11_re = localB->ad11_im * -localB->ad11_re;
                  } else {
                    localB->absxr = localB->ad11_re;
                    localB->ad11_re = 0.0;
                  }
                } else {
                  localB->absxr = std::abs(localB->ad11_re);
                  localB->absxi = std::abs(localB->ad11_im);
                  if ((localB->absxr > 4.4942328371557893E+307) ||
                      (localB->absxi > 4.4942328371557893E+307)) {
                    localB->absxr *= 0.5;
                    localB->absxi *= 0.5;
                    localB->absxi = CartesianImpedanc_rt_hypotd_snf
                      (localB->absxr, localB->absxi, localB);
                    if (localB->absxi > localB->absxr) {
                      localB->absxr = std::sqrt(localB->absxr / localB->absxi +
                        1.0) * std::sqrt(localB->absxi);
                    } else {
                      localB->absxr = std::sqrt(localB->absxi) *
                        1.4142135623730951;
                    }
                  } else {
                    localB->absxr = std::sqrt((CartesianImpedanc_rt_hypotd_snf
                      (localB->absxr, localB->absxi, localB) + localB->absxr) *
                      0.5);
                  }

                  if (localB->ad11_re > 0.0) {
                    localB->ad11_re = localB->ad11_im / localB->absxr * 0.5;
                  } else {
                    if (localB->ad11_im < 0.0) {
                      localB->ad11_re = -localB->absxr;
                    } else {
                      localB->ad11_re = localB->absxr;
                    }

                    localB->absxr = localB->ad11_im / localB->ad11_re * 0.5;
                  }
                }

                if ((localB->t1_re - localB->shift.re) * localB->absxr +
                    (localB->t1_im - localB->shift.im) * localB->ad11_re <= 0.0)
                {
                  localB->shift.re = localB->t1_re + localB->absxr;
                  localB->shift.im = localB->t1_im + localB->ad11_re;
                } else {
                  localB->shift.re = localB->t1_re - localB->absxr;
                  localB->shift.im = localB->t1_im - localB->ad11_re;
                }
              } else {
                localB->j_f = (ilastm1 << 2) + ilast;
                localB->ar = b_A[localB->j_f].re * localB->anorm;
                localB->ai = b_A[localB->j_f].im * localB->anorm;
                if (localB->ai == 0.0) {
                  localB->absxr = localB->ar / 0.5;
                  localB->absxi = 0.0;
                } else if (localB->ar == 0.0) {
                  localB->absxr = 0.0;
                  localB->absxi = localB->ai / 0.5;
                } else {
                  localB->absxr = localB->ar / 0.5;
                  localB->absxi = localB->ai / 0.5;
                }

                localB->eshift_re += localB->absxr;
                localB->eshift_im += localB->absxi;
                localB->shift.re = localB->eshift_re;
                localB->shift.im = localB->eshift_im;
              }

              localB->j_f = ilastm1;
              jp1 = ilastm1 + 1;
              exitg2 = false;
              while ((!exitg2) && (localB->j_f + 1 > ifirst)) {
                istart = localB->j_f + 1;
                ctemp_tmp_tmp = localB->j_f << 2;
                ctemp_tmp = ctemp_tmp_tmp + localB->j_f;
                localB->ctemp.re = b_A[ctemp_tmp].re * localB->anorm -
                  localB->shift.re * 0.5;
                localB->ctemp.im = b_A[ctemp_tmp].im * localB->anorm -
                  localB->shift.im * 0.5;
                localB->t1_re = std::abs(localB->ctemp.re) + std::abs
                  (localB->ctemp.im);
                jp1 += ctemp_tmp_tmp;
                localB->t1_im = (std::abs(b_A[jp1].re) + std::abs(b_A[jp1].im)) *
                  localB->anorm;
                localB->ad11_re = localB->t1_re;
                if (localB->t1_im > localB->t1_re) {
                  localB->ad11_re = localB->t1_im;
                }

                if ((localB->ad11_re < 1.0) && (localB->ad11_re != 0.0)) {
                  localB->t1_re /= localB->ad11_re;
                  localB->t1_im /= localB->ad11_re;
                }

                jp1 = ((localB->j_f - 1) << 2) + localB->j_f;
                if ((std::abs(b_A[jp1].re) + std::abs(b_A[jp1].im)) *
                    localB->t1_im <= localB->t1_re * localB->b_atol) {
                  goto90 = true;
                  exitg2 = true;
                } else {
                  jp1 = localB->j_f;
                  localB->j_f--;
                }
              }

              if (!goto90) {
                istart = ifirst;
                ctemp_tmp = (((ifirst - 1) << 2) + ifirst) - 1;
                localB->ctemp.re = b_A[ctemp_tmp].re * localB->anorm -
                  localB->shift.re * 0.5;
                localB->ctemp.im = b_A[ctemp_tmp].im * localB->anorm -
                  localB->shift.im * 0.5;
              }

              goto90 = false;
              localB->j_f = ((istart - 1) << 2) + istart;
              localB->ascale.re = b_A[localB->j_f].re * localB->anorm;
              localB->ascale.im = b_A[localB->j_f].im * localB->anorm;
              CartesianImpedance_Ta_xzlartg_m(localB->ctemp, localB->ascale,
                &localB->ad11_re, &localB->shift, localB);
              localB->j_f = istart;
              jp1 = istart - 2;
              while (localB->j_f < ilast + 1) {
                if (localB->j_f > istart) {
                  CartesianImpedance_Task_xzlartg(b_A[(localB->j_f + (jp1 << 2))
                    - 1], b_A[localB->j_f + (jp1 << 2)], &localB->ad11_re,
                    &localB->shift, &b_A[(localB->j_f + (jp1 << 2)) - 1], localB);
                  jp1 = localB->j_f + (jp1 << 2);
                  b_A[jp1].re = 0.0;
                  b_A[jp1].im = 0.0;
                }

                for (ctemp_tmp = localB->j_f; ctemp_tmp < 5; ctemp_tmp++) {
                  jp1 = ((ctemp_tmp - 1) << 2) + localB->j_f;
                  ctemp_tmp_tmp = jp1 - 1;
                  localB->t1_re = b_A[ctemp_tmp_tmp].re * localB->ad11_re +
                    (b_A[jp1].re * localB->shift.re - b_A[jp1].im *
                     localB->shift.im);
                  localB->t1_im = b_A[ctemp_tmp_tmp].im * localB->ad11_re +
                    (b_A[jp1].im * localB->shift.re + b_A[jp1].re *
                     localB->shift.im);
                  localB->ad11_im = b_A[ctemp_tmp_tmp].re;
                  b_A[jp1].re = b_A[jp1].re * localB->ad11_re -
                    (b_A[ctemp_tmp_tmp].re * localB->shift.re +
                     b_A[ctemp_tmp_tmp].im * localB->shift.im);
                  b_A[jp1].im = b_A[jp1].im * localB->ad11_re -
                    (b_A[ctemp_tmp_tmp].im * localB->shift.re - localB->shift.im
                     * localB->ad11_im);
                  b_A[ctemp_tmp_tmp].re = localB->t1_re;
                  b_A[ctemp_tmp_tmp].im = localB->t1_im;
                }

                localB->shift.re = -localB->shift.re;
                localB->shift.im = -localB->shift.im;
                ctemp_tmp = localB->j_f + 2;
                if (ilast + 1 < localB->j_f + 2) {
                  ctemp_tmp = ilast + 1;
                }

                for (i = 1; i <= ctemp_tmp; i++) {
                  jp1 = (((localB->j_f - 1) << 2) + i) - 1;
                  ctemp_tmp_tmp = ((localB->j_f << 2) + i) - 1;
                  localB->t1_re = (b_A[jp1].re * localB->shift.re - b_A[jp1].im *
                                   localB->shift.im) + b_A[ctemp_tmp_tmp].re *
                    localB->ad11_re;
                  localB->t1_im = (b_A[jp1].im * localB->shift.re + b_A[jp1].re *
                                   localB->shift.im) + b_A[ctemp_tmp_tmp].im *
                    localB->ad11_re;
                  localB->ad11_im = b_A[ctemp_tmp_tmp].re;
                  b_A[jp1].re = b_A[jp1].re * localB->ad11_re -
                    (b_A[ctemp_tmp_tmp].re * localB->shift.re +
                     b_A[ctemp_tmp_tmp].im * localB->shift.im);
                  b_A[jp1].im = b_A[jp1].im * localB->ad11_re -
                    (b_A[ctemp_tmp_tmp].im * localB->shift.re - localB->shift.im
                     * localB->ad11_im);
                  b_A[ctemp_tmp_tmp].re = localB->t1_re;
                  b_A[ctemp_tmp_tmp].im = localB->t1_im;
                }

                for (i = 1; i < 5; i++) {
                  jp1 = (((localB->j_f - 1) << 2) + i) - 1;
                  ctemp_tmp_tmp = ((localB->j_f << 2) + i) - 1;
                  localB->t1_re = (b_Z[jp1].re * localB->shift.re - b_Z[jp1].im *
                                   localB->shift.im) + b_Z[ctemp_tmp_tmp].re *
                    localB->ad11_re;
                  localB->t1_im = (b_Z[jp1].im * localB->shift.re + b_Z[jp1].re *
                                   localB->shift.im) + b_Z[ctemp_tmp_tmp].im *
                    localB->ad11_re;
                  localB->ad11_im = b_Z[ctemp_tmp_tmp].re;
                  b_Z[jp1].re = b_Z[jp1].re * localB->ad11_re -
                    (b_Z[ctemp_tmp_tmp].re * localB->shift.re +
                     b_Z[ctemp_tmp_tmp].im * localB->shift.im);
                  b_Z[jp1].im = b_Z[jp1].im * localB->ad11_re -
                    (b_Z[ctemp_tmp_tmp].im * localB->shift.re - localB->shift.im
                     * localB->ad11_im);
                  b_Z[ctemp_tmp_tmp].re = localB->t1_re;
                  b_Z[ctemp_tmp_tmp].im = localB->t1_im;
                }

                jp1 = localB->j_f - 1;
                localB->j_f++;
              }
            }

            jiter++;
          }
        }
      } else {
        guard2 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    guard1 = true;
  }

  if (guard2) {
    if (failed) {
      *info = ilast + 1;
      for (ifirst = 0; ifirst <= ilast; ifirst++) {
        alpha1[ifirst].re = (rtNaN);
        alpha1[ifirst].im = 0.0;
        beta1[ifirst].re = (rtNaN);
        beta1[ifirst].im = 0.0;
      }

      for (jp1 = 0; jp1 < 16; jp1++) {
        b_Z[jp1].re = (rtNaN);
        b_Z[jp1].im = 0.0;
      }
    } else {
      guard1 = true;
    }
  }

  if (guard1) {
    ilast = ilo - 2;
    for (ifirst = 0; ifirst <= ilast; ifirst++) {
      alpha1[ifirst] = b_A[(ifirst << 2) + ifirst];
    }
  }
}

void modelModelClass::CartesianImpedance_Task_xztgevc(const creal_T A[16], const
  creal_T V[16], creal_T b_V[16], B_CoordinateTransformationCon_T *localB)
{
  int32_T j;
  boolean_T lscalea;
  boolean_T lscaleb;
  int32_T b_j;
  int32_T b_i;
  int32_T c_jr;
  int32_T d_jr;
  real_T work2_idx_3_re;
  real_T work2_idx_3_im;
  int32_T rworka_tmp;
  int32_T d_re_tmp;
  int32_T d_re_tmp_tmp;
  std::memcpy(&b_V[0], &V[0], sizeof(creal_T) << 4U);
  localB->rworka[0] = 0.0;
  localB->rworka[1] = 0.0;
  localB->rworka[2] = 0.0;
  localB->rworka[3] = 0.0;
  localB->anorm_m = std::abs(A[0].re) + std::abs(A[0].im);
  for (b_j = 0; b_j < 3; b_j++) {
    for (b_i = 0; b_i <= b_j; b_i++) {
      rworka_tmp = ((b_j + 1) << 2) + b_i;
      localB->rworka[b_j + 1] += std::abs(A[rworka_tmp].re) + std::abs
        (A[rworka_tmp].im);
    }

    b_i = (((b_j + 1) << 2) + b_j) + 1;
    localB->d_im = (std::abs(A[b_i].re) + std::abs(A[b_i].im)) + localB->
      rworka[b_j + 1];
    if (localB->d_im > localB->anorm_m) {
      localB->anorm_m = localB->d_im;
    }
  }

  localB->work2_idx_2_re = localB->anorm_m;
  if (2.2250738585072014E-308 > localB->anorm_m) {
    localB->work2_idx_2_re = 2.2250738585072014E-308;
  }

  localB->ascale_n = 1.0 / localB->work2_idx_2_re;
  for (b_j = 0; b_j < 4; b_j++) {
    b_i = (3 - b_j) << 2;
    rworka_tmp = (b_i - b_j) + 3;
    localB->temp = (std::abs(A[rworka_tmp].re) + std::abs(A[rworka_tmp].im)) *
      localB->ascale_n;
    if (1.0 > localB->temp) {
      localB->temp = 1.0;
    }

    localB->temp = 1.0 / localB->temp;
    localB->salpha_re = A[rworka_tmp].re * localB->temp * localB->ascale_n;
    localB->salpha_im = A[rworka_tmp].im * localB->temp * localB->ascale_n;
    localB->acoeff = localB->temp * localB->ascale_n;
    if ((localB->temp >= 2.2250738585072014E-308) && (localB->acoeff <
         4.0083367200179456E-292)) {
      lscalea = true;
    } else {
      lscalea = false;
    }

    localB->d_im = std::abs(localB->salpha_re) + std::abs(localB->salpha_im);
    if ((localB->d_im >= 2.2250738585072014E-308) && (localB->d_im <
         4.0083367200179456E-292)) {
      lscaleb = true;
    } else {
      lscaleb = false;
    }

    localB->scale_p = 1.0;
    if (lscalea) {
      localB->work2_idx_2_re = localB->anorm_m;
      if (2.4948003869184E+291 < localB->anorm_m) {
        localB->work2_idx_2_re = 2.4948003869184E+291;
      }

      localB->scale_p = 4.0083367200179456E-292 / localB->temp *
        localB->work2_idx_2_re;
    }

    if (lscaleb) {
      localB->work2_idx_2_re = 4.0083367200179456E-292 / localB->d_im;
      if (localB->work2_idx_2_re > localB->scale_p) {
        localB->scale_p = localB->work2_idx_2_re;
      }
    }

    if (lscalea || lscaleb) {
      localB->work2_idx_2_re = localB->acoeff;
      if (1.0 > localB->acoeff) {
        localB->work2_idx_2_re = 1.0;
      }

      if (localB->d_im > localB->work2_idx_2_re) {
        localB->work2_idx_2_re = localB->d_im;
      }

      localB->d_im = 1.0 / (2.2250738585072014E-308 * localB->work2_idx_2_re);
      if (localB->d_im < localB->scale_p) {
        localB->scale_p = localB->d_im;
      }

      if (lscalea) {
        localB->acoeff = localB->scale_p * localB->temp * localB->ascale_n;
      } else {
        localB->acoeff *= localB->scale_p;
      }

      localB->salpha_re *= localB->scale_p;
      localB->salpha_im *= localB->scale_p;
    }

    std::memset(&localB->work1[0], 0, sizeof(creal_T) << 2U);
    localB->work1[3 - b_j].re = 1.0;
    localB->work1[3 - b_j].im = 0.0;
    localB->scale_p = 2.2204460492503131E-16 * localB->acoeff * localB->anorm_m;
    localB->d_im = (std::abs(localB->salpha_re) + std::abs(localB->salpha_im)) *
      2.2204460492503131E-16;
    if (localB->d_im > localB->scale_p) {
      localB->scale_p = localB->d_im;
    }

    if (2.2250738585072014E-308 > localB->scale_p) {
      localB->scale_p = 2.2250738585072014E-308;
    }

    rworka_tmp = 2 - b_j;
    for (c_jr = 0; c_jr <= rworka_tmp; c_jr++) {
      d_re_tmp_tmp = b_i + c_jr;
      localB->work1[c_jr].re = A[d_re_tmp_tmp].re * localB->acoeff;
      localB->work1[c_jr].im = A[d_re_tmp_tmp].im * localB->acoeff;
    }

    localB->work1[3 - b_j].re = 1.0;
    localB->work1[3 - b_j].im = 0.0;
    rworka_tmp = static_cast<int32_T>(((-1.0 - ((-static_cast<real_T>(b_j) + 4.0)
      - 1.0)) + 1.0) / -1.0) - 1;
    for (c_jr = 0; c_jr <= rworka_tmp; c_jr++) {
      j = 3 - (b_j + c_jr);
      d_re_tmp_tmp = (j - 1) << 2;
      d_re_tmp = (d_re_tmp_tmp + j) - 1;
      localB->d_re = A[d_re_tmp].re * localB->acoeff - localB->salpha_re;
      localB->d_im = A[d_re_tmp].im * localB->acoeff - localB->salpha_im;
      if (std::abs(localB->d_re) + std::abs(localB->d_im) <= localB->scale_p) {
        localB->d_re = localB->scale_p;
        localB->d_im = 0.0;
      }

      localB->work2_idx_2_re = std::abs(localB->d_re);
      work2_idx_3_im = std::abs(localB->d_im);
      localB->temp = localB->work2_idx_2_re + work2_idx_3_im;
      if (localB->temp < 1.0) {
        work2_idx_3_re = std::abs(localB->work1[j - 1].re) + std::abs
          (localB->work1[j - 1].im);
        if (work2_idx_3_re >= localB->temp * 1.1235582092889474E+307) {
          localB->temp = 1.0 / work2_idx_3_re;
          d_re_tmp = 3 - b_j;
          for (d_jr = 0; d_jr <= d_re_tmp; d_jr++) {
            localB->work1_c.re = localB->temp * localB->work1[d_jr].re;
            localB->work1_c.im = localB->temp * localB->work1[d_jr].im;
            localB->work1[d_jr] = localB->work1_c;
          }
        }
      }

      localB->temp = -localB->work1[j - 1].re;
      work2_idx_3_re = -localB->work1[j - 1].im;
      if (localB->d_im == 0.0) {
        if (work2_idx_3_re == 0.0) {
          localB->work1[j - 1].re = localB->temp / localB->d_re;
          localB->work1[j - 1].im = 0.0;
        } else if (localB->temp == 0.0) {
          localB->work1[j - 1].re = 0.0;
          localB->work1[j - 1].im = work2_idx_3_re / localB->d_re;
        } else {
          localB->work1[j - 1].re = localB->temp / localB->d_re;
          localB->work1[j - 1].im = work2_idx_3_re / localB->d_re;
        }
      } else if (localB->d_re == 0.0) {
        if (localB->temp == 0.0) {
          localB->work1[j - 1].re = work2_idx_3_re / localB->d_im;
          localB->work1[j - 1].im = 0.0;
        } else if (work2_idx_3_re == 0.0) {
          localB->work1[j - 1].re = 0.0;
          localB->work1[j - 1].im = -(localB->temp / localB->d_im);
        } else {
          localB->work1[j - 1].re = work2_idx_3_re / localB->d_im;
          localB->work1[j - 1].im = -(localB->temp / localB->d_im);
        }
      } else if (localB->work2_idx_2_re > work2_idx_3_im) {
        localB->work2_idx_2_re = localB->d_im / localB->d_re;
        localB->d_im = localB->work2_idx_2_re * localB->d_im + localB->d_re;
        localB->work1[j - 1].re = (localB->work2_idx_2_re * work2_idx_3_re +
          localB->temp) / localB->d_im;
        localB->work1[j - 1].im = (work2_idx_3_re - localB->work2_idx_2_re *
          localB->temp) / localB->d_im;
      } else if (work2_idx_3_im == localB->work2_idx_2_re) {
        localB->d_re = localB->d_re > 0.0 ? 0.5 : -0.5;
        localB->d_im = localB->d_im > 0.0 ? 0.5 : -0.5;
        localB->work1[j - 1].re = (localB->temp * localB->d_re + work2_idx_3_re *
          localB->d_im) / localB->work2_idx_2_re;
        localB->work1[j - 1].im = (work2_idx_3_re * localB->d_re - localB->temp *
          localB->d_im) / localB->work2_idx_2_re;
      } else {
        localB->work2_idx_2_re = localB->d_re / localB->d_im;
        localB->d_im += localB->work2_idx_2_re * localB->d_re;
        localB->work1[j - 1].re = (localB->work2_idx_2_re * localB->temp +
          work2_idx_3_re) / localB->d_im;
        localB->work1[j - 1].im = (localB->work2_idx_2_re * work2_idx_3_re -
          localB->temp) / localB->d_im;
      }

      if (j > 1) {
        if (std::abs(localB->work1[j - 1].re) + std::abs(localB->work1[j - 1].im)
            > 1.0) {
          localB->temp = 1.0 / (std::abs(localB->work1[j - 1].re) + std::abs
                                (localB->work1[j - 1].im));
          if (localB->rworka[j - 1] * localB->acoeff >= 1.1235582092889474E+307 *
              localB->temp) {
            d_re_tmp = 3 - b_j;
            for (d_jr = 0; d_jr <= d_re_tmp; d_jr++) {
              localB->work1_b.re = localB->temp * localB->work1[d_jr].re;
              localB->work1_b.im = localB->temp * localB->work1[d_jr].im;
              localB->work1[d_jr] = localB->work1_b;
            }
          }
        }

        localB->d_re = localB->work1[j - 1].re * localB->acoeff;
        localB->d_im = localB->work1[j - 1].im * localB->acoeff;
        j -= 2;
        for (d_re_tmp = 0; d_re_tmp <= j; d_re_tmp++) {
          d_jr = d_re_tmp_tmp + d_re_tmp;
          localB->work1_p.re = (A[d_jr].re * localB->d_re - A[d_jr].im *
                                localB->d_im) + localB->work1[d_re_tmp].re;
          localB->work1_p.im = (A[d_jr].im * localB->d_re + A[d_jr].re *
                                localB->d_im) + localB->work1[d_re_tmp].im;
          localB->work1[d_re_tmp] = localB->work1_p;
        }
      }
    }

    localB->salpha_re = 0.0;
    localB->salpha_im = 0.0;
    localB->acoeff = 0.0;
    localB->scale_p = 0.0;
    localB->work2_idx_2_re = 0.0;
    localB->d_re = 0.0;
    work2_idx_3_re = 0.0;
    work2_idx_3_im = 0.0;
    rworka_tmp = 3 - b_j;
    for (c_jr = 0; c_jr <= rworka_tmp; c_jr++) {
      d_re_tmp_tmp = c_jr << 2;
      localB->salpha_re += b_V[d_re_tmp_tmp].re * localB->work1[c_jr].re -
        b_V[d_re_tmp_tmp].im * localB->work1[c_jr].im;
      localB->salpha_im += b_V[d_re_tmp_tmp].re * localB->work1[c_jr].im +
        b_V[d_re_tmp_tmp].im * localB->work1[c_jr].re;
      j = d_re_tmp_tmp + 1;
      localB->acoeff += b_V[j].re * localB->work1[c_jr].re - b_V[j].im *
        localB->work1[c_jr].im;
      localB->scale_p += b_V[j].re * localB->work1[c_jr].im + b_V[j].im *
        localB->work1[c_jr].re;
      j = d_re_tmp_tmp + 2;
      localB->work2_idx_2_re += b_V[j].re * localB->work1[c_jr].re - b_V[j].im *
        localB->work1[c_jr].im;
      localB->d_re += b_V[j].re * localB->work1[c_jr].im + b_V[j].im *
        localB->work1[c_jr].re;
      d_re_tmp_tmp += 3;
      work2_idx_3_re += b_V[d_re_tmp_tmp].re * localB->work1[c_jr].re -
        b_V[d_re_tmp_tmp].im * localB->work1[c_jr].im;
      work2_idx_3_im += b_V[d_re_tmp_tmp].re * localB->work1[c_jr].im +
        b_V[d_re_tmp_tmp].im * localB->work1[c_jr].re;
    }

    localB->temp = std::abs(localB->salpha_re) + std::abs(localB->salpha_im);
    localB->d_im = std::abs(localB->acoeff) + std::abs(localB->scale_p);
    if (localB->d_im > localB->temp) {
      localB->temp = localB->d_im;
    }

    localB->d_im = std::abs(localB->work2_idx_2_re) + std::abs(localB->d_re);
    if (localB->d_im > localB->temp) {
      localB->temp = localB->d_im;
    }

    localB->d_im = std::abs(work2_idx_3_re) + std::abs(work2_idx_3_im);
    if (localB->d_im > localB->temp) {
      localB->temp = localB->d_im;
    }

    if (localB->temp > 2.2250738585072014E-308) {
      localB->temp = 1.0 / localB->temp;
      b_V[b_i].re = localB->temp * localB->salpha_re;
      b_V[b_i].im = localB->temp * localB->salpha_im;
      d_re_tmp_tmp = ((3 - b_j) << 2) + 1;
      b_V[d_re_tmp_tmp].re = localB->temp * localB->acoeff;
      b_V[d_re_tmp_tmp].im = localB->temp * localB->scale_p;
      d_re_tmp_tmp = ((3 - b_j) << 2) + 2;
      b_V[d_re_tmp_tmp].re = localB->temp * localB->work2_idx_2_re;
      b_V[d_re_tmp_tmp].im = localB->temp * localB->d_re;
      d_re_tmp_tmp = ((3 - b_j) << 2) + 3;
      b_V[d_re_tmp_tmp].re = localB->temp * work2_idx_3_re;
      b_V[d_re_tmp_tmp].im = localB->temp * work2_idx_3_im;
    } else {
      b_V[b_i].re = 0.0;
      b_V[b_i].im = 0.0;
      d_re_tmp_tmp = b_i + 1;
      b_V[d_re_tmp_tmp].re = 0.0;
      b_V[d_re_tmp_tmp].im = 0.0;
      d_re_tmp_tmp = b_i + 2;
      b_V[d_re_tmp_tmp].re = 0.0;
      b_V[d_re_tmp_tmp].im = 0.0;
      d_re_tmp_tmp = b_i + 3;
      b_V[d_re_tmp_tmp].re = 0.0;
      b_V[d_re_tmp_tmp].im = 0.0;
    }
  }
}

void modelModelClass::CartesianImpedance_Task_xzggev(const creal_T A[16],
  creal_T b_A[16], int32_T *info, creal_T alpha1[4], creal_T beta1[4], creal_T
  V[16], B_CoordinateTransformationCon_T *localB)
{
  boolean_T ilascl;
  boolean_T notdone;
  boolean_T guard1 = false;
  boolean_T exitg1;
  int32_T exitg2;
  int32_T exitg3;
  boolean_T exitg4;
  std::memcpy(&b_A[0], &A[0], sizeof(creal_T) << 4U);
  *info = 0;
  localB->anrm = 0.0;
  localB->ii = 0;
  exitg1 = false;
  while ((!exitg1) && (localB->ii < 16)) {
    localB->absxk_c = CartesianImpedanc_rt_hypotd_snf(A[localB->ii].re, A
      [localB->ii].im, localB);
    if (rtIsNaN(localB->absxk_c)) {
      localB->anrm = (rtNaN);
      exitg1 = true;
    } else {
      if (localB->absxk_c > localB->anrm) {
        localB->anrm = localB->absxk_c;
      }

      localB->ii++;
    }
  }

  if (rtIsInf(localB->anrm) || rtIsNaN(localB->anrm)) {
    alpha1[0].re = (rtNaN);
    alpha1[0].im = 0.0;
    beta1[0].re = (rtNaN);
    beta1[0].im = 0.0;
    alpha1[1].re = (rtNaN);
    alpha1[1].im = 0.0;
    beta1[1].re = (rtNaN);
    beta1[1].im = 0.0;
    alpha1[2].re = (rtNaN);
    alpha1[2].im = 0.0;
    beta1[2].re = (rtNaN);
    beta1[2].im = 0.0;
    alpha1[3].re = (rtNaN);
    alpha1[3].im = 0.0;
    beta1[3].re = (rtNaN);
    beta1[3].im = 0.0;
    for (localB->atmp_re_tmp = 0; localB->atmp_re_tmp < 16; localB->atmp_re_tmp
         ++) {
      V[localB->atmp_re_tmp].re = (rtNaN);
      V[localB->atmp_re_tmp].im = 0.0;
    }
  } else {
    ilascl = false;
    localB->absxk_c = localB->anrm;
    guard1 = false;
    if ((localB->anrm > 0.0) && (localB->anrm < 6.7178761075670888E-139)) {
      localB->absxk_c = 6.7178761075670888E-139;
      ilascl = true;
      guard1 = true;
    } else {
      if (localB->anrm > 1.4885657073574029E+138) {
        localB->absxk_c = 1.4885657073574029E+138;
        ilascl = true;
        guard1 = true;
      }
    }

    if (guard1) {
      std::memcpy(&b_A[0], &A[0], sizeof(creal_T) << 4U);
      localB->cfromc = localB->anrm;
      localB->ctoc = localB->absxk_c;
      notdone = true;
      while (notdone) {
        localB->cfrom1 = localB->cfromc * 2.0041683600089728E-292;
        localB->cto1 = localB->ctoc / 4.9896007738368E+291;
        if ((localB->cfrom1 > localB->ctoc) && (localB->ctoc != 0.0)) {
          localB->mul = 2.0041683600089728E-292;
          localB->cfromc = localB->cfrom1;
        } else if (localB->cto1 > localB->cfromc) {
          localB->mul = 4.9896007738368E+291;
          localB->ctoc = localB->cto1;
        } else {
          localB->mul = localB->ctoc / localB->cfromc;
          notdone = false;
        }

        for (localB->atmp_re_tmp = 0; localB->atmp_re_tmp < 16;
             localB->atmp_re_tmp++) {
          localB->s.re = localB->mul * b_A[localB->atmp_re_tmp].re;
          localB->s.im = localB->mul * b_A[localB->atmp_re_tmp].im;
          b_A[localB->atmp_re_tmp] = localB->s;
        }
      }
    }

    localB->rscale[0] = 1;
    localB->rscale[1] = 1;
    localB->rscale[2] = 1;
    localB->rscale[3] = 1;
    localB->k_j = 1;
    localB->ihi = 4;
    do {
      exitg3 = 0;
      localB->i_b = -1;
      localB->j = 0;
      notdone = false;
      localB->ii = localB->ihi;
      exitg1 = false;
      while ((!exitg1) && (localB->ii > 0)) {
        localB->nzcount = 0;
        localB->i_b = localB->ii - 1;
        localB->j = localB->ihi;
        localB->b_jj = 1;
        exitg4 = false;
        while ((!exitg4) && (localB->b_jj - 1 <= localB->ihi - 1)) {
          localB->atmp_re_tmp = (((localB->b_jj - 1) << 2) + localB->ii) - 1;
          if ((b_A[localB->atmp_re_tmp].re != 0.0) || (b_A[localB->atmp_re_tmp].
               im != 0.0) || (localB->ii == localB->b_jj)) {
            if (localB->nzcount == 0) {
              localB->j = localB->b_jj;
              localB->nzcount = 1;
              localB->b_jj++;
            } else {
              localB->nzcount = 2;
              exitg4 = true;
            }
          } else {
            localB->b_jj++;
          }
        }

        if (localB->nzcount < 2) {
          notdone = true;
          exitg1 = true;
        } else {
          localB->ii--;
        }
      }

      if (!notdone) {
        exitg3 = 2;
      } else {
        if (localB->i_b + 1 != localB->ihi) {
          for (localB->ii = 1; localB->ii < 5; localB->ii++) {
            localB->nzcount = (localB->ii - 1) << 2;
            localB->atmp_re_tmp = localB->nzcount + localB->i_b;
            localB->cfromc = b_A[localB->atmp_re_tmp].re;
            localB->ctoc = b_A[localB->atmp_re_tmp].im;
            localB->nzcount = (localB->nzcount + localB->ihi) - 1;
            b_A[localB->atmp_re_tmp] = b_A[localB->nzcount];
            b_A[localB->nzcount].re = localB->cfromc;
            b_A[localB->nzcount].im = localB->ctoc;
          }
        }

        if (localB->j != localB->ihi) {
          for (localB->i_b = 0; localB->i_b < localB->ihi; localB->i_b++) {
            localB->atmp_re_tmp = ((localB->j - 1) << 2) + localB->i_b;
            localB->cfromc = b_A[localB->atmp_re_tmp].re;
            localB->ctoc = b_A[localB->atmp_re_tmp].im;
            localB->nzcount = ((localB->ihi - 1) << 2) + localB->i_b;
            b_A[localB->atmp_re_tmp] = b_A[localB->nzcount];
            b_A[localB->nzcount].re = localB->cfromc;
            b_A[localB->nzcount].im = localB->ctoc;
          }
        }

        localB->rscale[localB->ihi - 1] = localB->j;
        localB->ihi--;
        if (localB->ihi == 1) {
          localB->rscale[0] = 1;
          exitg3 = 1;
        }
      }
    } while (exitg3 == 0);

    if (exitg3 == 1) {
    } else {
      do {
        exitg2 = 0;
        localB->i_b = 0;
        localB->j = 0;
        notdone = false;
        localB->b_jj = localB->k_j;
        exitg1 = false;
        while ((!exitg1) && (localB->b_jj <= localB->ihi)) {
          localB->nzcount = 0;
          localB->i_b = localB->ihi;
          localB->j = localB->b_jj;
          localB->ii = localB->k_j;
          exitg4 = false;
          while ((!exitg4) && (localB->ii <= localB->ihi)) {
            localB->atmp_re_tmp = (((localB->b_jj - 1) << 2) + localB->ii) - 1;
            if ((b_A[localB->atmp_re_tmp].re != 0.0) || (b_A[localB->atmp_re_tmp]
                 .im != 0.0) || (localB->ii == localB->b_jj)) {
              if (localB->nzcount == 0) {
                localB->i_b = localB->ii;
                localB->nzcount = 1;
                localB->ii++;
              } else {
                localB->nzcount = 2;
                exitg4 = true;
              }
            } else {
              localB->ii++;
            }
          }

          if (localB->nzcount < 2) {
            notdone = true;
            exitg1 = true;
          } else {
            localB->b_jj++;
          }
        }

        if (!notdone) {
          exitg2 = 1;
        } else {
          if (localB->i_b != localB->k_j) {
            for (localB->ii = localB->k_j; localB->ii < 5; localB->ii++) {
              localB->nzcount = (localB->ii - 1) << 2;
              localB->atmp_re_tmp = (localB->nzcount + localB->i_b) - 1;
              localB->cfromc = b_A[localB->atmp_re_tmp].re;
              localB->ctoc = b_A[localB->atmp_re_tmp].im;
              localB->nzcount = (localB->nzcount + localB->k_j) - 1;
              b_A[localB->atmp_re_tmp] = b_A[localB->nzcount];
              b_A[localB->nzcount].re = localB->cfromc;
              b_A[localB->nzcount].im = localB->ctoc;
            }
          }

          if (localB->j != localB->k_j) {
            for (localB->i_b = 0; localB->i_b < localB->ihi; localB->i_b++) {
              localB->atmp_re_tmp = ((localB->j - 1) << 2) + localB->i_b;
              localB->cfromc = b_A[localB->atmp_re_tmp].re;
              localB->ctoc = b_A[localB->atmp_re_tmp].im;
              localB->nzcount = ((localB->k_j - 1) << 2) + localB->i_b;
              b_A[localB->atmp_re_tmp] = b_A[localB->nzcount];
              b_A[localB->nzcount].re = localB->cfromc;
              b_A[localB->nzcount].im = localB->ctoc;
            }
          }

          localB->rscale[localB->k_j - 1] = localB->j;
          localB->k_j++;
          if (localB->k_j == localB->ihi) {
            localB->rscale[localB->k_j - 1] = localB->k_j;
            exitg2 = 1;
          }
        }
      } while (exitg2 == 0);
    }

    for (localB->atmp_re_tmp = 0; localB->atmp_re_tmp < 16; localB->atmp_re_tmp
         ++) {
      localB->b_I[localB->atmp_re_tmp] = 0;
    }

    localB->b_I[0] = 1;
    localB->b_I[5] = 1;
    localB->b_I[10] = 1;
    localB->b_I[15] = 1;
    for (localB->atmp_re_tmp = 0; localB->atmp_re_tmp < 16; localB->atmp_re_tmp
         ++) {
      localB->b_V[localB->atmp_re_tmp].re = localB->b_I[localB->atmp_re_tmp];
      localB->b_V[localB->atmp_re_tmp].im = 0.0;
    }

    if (localB->ihi >= localB->k_j + 2) {
      localB->ii = localB->k_j - 1;
      while (localB->ii + 1 < localB->ihi - 1) {
        localB->nzcount = localB->ihi - 1;
        while (localB->nzcount + 1 > localB->ii + 2) {
          CartesianImpedance_Task_xzlartg(b_A[(localB->nzcount + (localB->ii <<
            2)) - 1], b_A[localB->nzcount + (localB->ii << 2)], &localB->cfrom1,
            &localB->s, &b_A[(localB->nzcount + (localB->ii << 2)) - 1], localB);
          localB->atmp_re_tmp = localB->nzcount + (localB->ii << 2);
          b_A[localB->atmp_re_tmp].re = 0.0;
          b_A[localB->atmp_re_tmp].im = 0.0;
          for (localB->j = localB->ii + 2; localB->j < 5; localB->j++) {
            localB->atmp_re_tmp = ((localB->j - 1) << 2) + localB->nzcount;
            localB->b_jj = localB->atmp_re_tmp - 1;
            localB->cfromc = b_A[localB->b_jj].re * localB->cfrom1 + (b_A
              [localB->atmp_re_tmp].re * localB->s.re - b_A[localB->atmp_re_tmp]
              .im * localB->s.im);
            localB->ctoc = b_A[localB->b_jj].im * localB->cfrom1 + (b_A
              [localB->atmp_re_tmp].im * localB->s.re + b_A[localB->atmp_re_tmp]
              .re * localB->s.im);
            localB->cto1 = b_A[localB->b_jj].re;
            b_A[localB->atmp_re_tmp].re = b_A[localB->atmp_re_tmp].re *
              localB->cfrom1 - (b_A[localB->b_jj].re * localB->s.re + b_A
                                [localB->b_jj].im * localB->s.im);
            b_A[localB->atmp_re_tmp].im = b_A[localB->atmp_re_tmp].im *
              localB->cfrom1 - (b_A[localB->b_jj].im * localB->s.re -
                                localB->s.im * localB->cto1);
            b_A[localB->b_jj].re = localB->cfromc;
            b_A[localB->b_jj].im = localB->ctoc;
          }

          localB->s.re = -localB->s.re;
          localB->s.im = -localB->s.im;
          for (localB->i_b = 1; localB->i_b <= localB->ihi; localB->i_b++) {
            localB->atmp_re_tmp = (((localB->nzcount - 1) << 2) + localB->i_b) -
              1;
            localB->b_jj = ((localB->nzcount << 2) + localB->i_b) - 1;
            localB->cfromc = (b_A[localB->atmp_re_tmp].re * localB->s.re -
                              b_A[localB->atmp_re_tmp].im * localB->s.im) +
              b_A[localB->b_jj].re * localB->cfrom1;
            localB->ctoc = (b_A[localB->atmp_re_tmp].im * localB->s.re +
                            b_A[localB->atmp_re_tmp].re * localB->s.im) +
              b_A[localB->b_jj].im * localB->cfrom1;
            localB->cto1 = b_A[localB->b_jj].re;
            b_A[localB->atmp_re_tmp].re = b_A[localB->atmp_re_tmp].re *
              localB->cfrom1 - (b_A[localB->b_jj].re * localB->s.re + b_A
                                [localB->b_jj].im * localB->s.im);
            b_A[localB->atmp_re_tmp].im = b_A[localB->atmp_re_tmp].im *
              localB->cfrom1 - (b_A[localB->b_jj].im * localB->s.re -
                                localB->s.im * localB->cto1);
            b_A[localB->b_jj].re = localB->cfromc;
            b_A[localB->b_jj].im = localB->ctoc;
          }

          for (localB->i_b = 1; localB->i_b < 5; localB->i_b++) {
            localB->atmp_re_tmp = (((localB->nzcount - 1) << 2) + localB->i_b) -
              1;
            localB->b_jj = ((localB->nzcount << 2) + localB->i_b) - 1;
            localB->cfromc = (localB->b_V[localB->atmp_re_tmp].re * localB->s.re
                              - localB->b_V[localB->atmp_re_tmp].im *
                              localB->s.im) + localB->b_V[localB->b_jj].re *
              localB->cfrom1;
            localB->ctoc = (localB->b_V[localB->atmp_re_tmp].im * localB->s.re +
                            localB->b_V[localB->atmp_re_tmp].re * localB->s.im)
              + localB->b_V[localB->b_jj].im * localB->cfrom1;
            localB->cto1 = localB->b_V[localB->b_jj].re;
            localB->b_V[localB->atmp_re_tmp].re = localB->b_V
              [localB->atmp_re_tmp].re * localB->cfrom1 - (localB->b_V
              [localB->b_jj].re * localB->s.re + localB->b_V[localB->b_jj].im *
              localB->s.im);
            localB->b_V[localB->atmp_re_tmp].im = localB->b_V
              [localB->atmp_re_tmp].im * localB->cfrom1 - (localB->b_V
              [localB->b_jj].im * localB->s.re - localB->s.im * localB->cto1);
            localB->b_V[localB->b_jj].re = localB->cfromc;
            localB->b_V[localB->b_jj].im = localB->ctoc;
          }

          localB->nzcount--;
        }

        localB->ii++;
      }
    }

    CartesianImpedance_Task_xzhgeqz(b_A, localB->k_j, localB->ihi, localB->b_V,
      info, alpha1, beta1, localB->e_A, localB->c_V, localB);
    std::memcpy(&b_A[0], &localB->e_A[0], sizeof(creal_T) << 4U);
    std::memcpy(&V[0], &localB->c_V[0], sizeof(creal_T) << 4U);
    if (*info == 0) {
      CartesianImpedance_Task_xztgevc(localB->e_A, localB->c_V, V, localB);
      if (localB->k_j > 1) {
        localB->i_b = localB->k_j - 2;
        while (localB->i_b + 1 >= 1) {
          localB->k_j = localB->rscale[localB->i_b] - 1;
          if (localB->i_b + 1 != localB->rscale[localB->i_b]) {
            localB->cfromc = V[localB->i_b].re;
            localB->ctoc = V[localB->i_b].im;
            V[localB->i_b] = V[localB->k_j];
            V[localB->k_j].re = localB->cfromc;
            V[localB->k_j].im = localB->ctoc;
            localB->cfromc = V[localB->i_b + 4].re;
            localB->ctoc = V[localB->i_b + 4].im;
            V[localB->i_b + 4] = V[localB->k_j + 4];
            V[localB->k_j + 4].re = localB->cfromc;
            V[localB->k_j + 4].im = localB->ctoc;
            localB->cfromc = V[localB->i_b + 8].re;
            localB->ctoc = V[localB->i_b + 8].im;
            V[localB->i_b + 8] = V[localB->k_j + 8];
            V[localB->k_j + 8].re = localB->cfromc;
            V[localB->k_j + 8].im = localB->ctoc;
            localB->cfromc = V[localB->i_b + 12].re;
            localB->ctoc = V[localB->i_b + 12].im;
            V[localB->i_b + 12] = V[localB->k_j + 12];
            V[localB->k_j + 12].re = localB->cfromc;
            V[localB->k_j + 12].im = localB->ctoc;
          }

          localB->i_b--;
        }
      }

      if (localB->ihi < 4) {
        for (localB->i_b = localB->ihi + 1; localB->i_b < 5; localB->i_b++) {
          localB->j = localB->rscale[localB->i_b - 1];
          localB->k_j = localB->j - 1;
          if (localB->j != localB->i_b) {
            localB->cfromc = V[localB->i_b - 1].re;
            localB->ctoc = V[localB->i_b - 1].im;
            V[localB->i_b - 1] = V[localB->k_j];
            V[localB->k_j].re = localB->cfromc;
            V[localB->k_j].im = localB->ctoc;
            localB->cfromc = V[localB->i_b + 3].re;
            localB->ctoc = V[localB->i_b + 3].im;
            V[localB->i_b + 3] = V[localB->k_j + 4];
            V[localB->k_j + 4].re = localB->cfromc;
            V[localB->k_j + 4].im = localB->ctoc;
            localB->cfromc = V[localB->i_b + 7].re;
            localB->ctoc = V[localB->i_b + 7].im;
            V[localB->i_b + 7] = V[localB->k_j + 8];
            V[localB->k_j + 8].re = localB->cfromc;
            V[localB->k_j + 8].im = localB->ctoc;
            localB->cfromc = V[localB->i_b + 11].re;
            localB->ctoc = V[localB->i_b + 11].im;
            V[localB->i_b + 11] = V[localB->k_j + 12];
            V[localB->k_j + 12].re = localB->cfromc;
            V[localB->k_j + 12].im = localB->ctoc;
          }
        }
      }

      for (localB->ihi = 0; localB->ihi < 4; localB->ihi++) {
        localB->k_j = localB->ihi << 2;
        localB->cfromc = std::abs(V[localB->k_j].re) + std::abs(V[localB->k_j].
          im);
        localB->i_b = localB->k_j + 1;
        localB->ctoc = std::abs(V[localB->i_b].re) + std::abs(V[localB->i_b].im);
        if (localB->ctoc > localB->cfromc) {
          localB->cfromc = localB->ctoc;
        }

        localB->j = localB->k_j + 2;
        localB->ctoc = std::abs(V[localB->j].re) + std::abs(V[localB->j].im);
        if (localB->ctoc > localB->cfromc) {
          localB->cfromc = localB->ctoc;
        }

        localB->atmp_re_tmp = localB->k_j + 3;
        localB->ctoc = std::abs(V[localB->atmp_re_tmp].re) + std::abs(V
          [localB->atmp_re_tmp].im);
        if (localB->ctoc > localB->cfromc) {
          localB->cfromc = localB->ctoc;
        }

        if (localB->cfromc >= 6.7178761075670888E-139) {
          localB->cfromc = 1.0 / localB->cfromc;
          V[localB->k_j].re *= localB->cfromc;
          V[localB->k_j].im *= localB->cfromc;
          V[localB->i_b].re *= localB->cfromc;
          V[localB->i_b].im *= localB->cfromc;
          V[localB->j].re *= localB->cfromc;
          V[localB->j].im *= localB->cfromc;
          V[localB->atmp_re_tmp].re *= localB->cfromc;
          V[localB->atmp_re_tmp].im *= localB->cfromc;
        }
      }

      if (ilascl) {
        notdone = true;
        while (notdone) {
          localB->cfrom1 = localB->absxk_c * 2.0041683600089728E-292;
          localB->cto1 = localB->anrm / 4.9896007738368E+291;
          if ((localB->cfrom1 > localB->anrm) && (localB->anrm != 0.0)) {
            localB->mul = 2.0041683600089728E-292;
            localB->absxk_c = localB->cfrom1;
          } else if (localB->cto1 > localB->absxk_c) {
            localB->mul = 4.9896007738368E+291;
            localB->anrm = localB->cto1;
          } else {
            localB->mul = localB->anrm / localB->absxk_c;
            notdone = false;
          }

          alpha1[0].re *= localB->mul;
          alpha1[0].im *= localB->mul;
          alpha1[1].re *= localB->mul;
          alpha1[1].im *= localB->mul;
          alpha1[2].re *= localB->mul;
          alpha1[2].im *= localB->mul;
          alpha1[3].re *= localB->mul;
          alpha1[3].im *= localB->mul;
        }
      }
    }
  }
}

void modelModelClass::CartesianImpedance_Task_xdlanv2(real_T a, real_T b, real_T
  c, real_T d, real_T *rt1r, real_T *rt1i, real_T *rt2r, real_T *rt2i, real_T
  *b_a, real_T *b_b, real_T *b_c, real_T *b_d, real_T *cs, real_T *sn,
  B_CoordinateTransformationCon_T *localB)
{
  real_T tau;
  int32_T b_0;
  int32_T c_0;
  boolean_T tmp;
  *b_d = d;
  *b_c = c;
  *b_b = b;
  *b_a = a;
  if (c == 0.0) {
    *cs = 1.0;
    *sn = 0.0;
  } else if (b == 0.0) {
    *cs = 0.0;
    *sn = 1.0;
    *b_d = a;
    *b_a = d;
    *b_b = -c;
    *b_c = 0.0;
  } else {
    tau = a - d;
    if ((tau == 0.0) && ((b < 0.0) != (c < 0.0))) {
      *cs = 1.0;
      *sn = 0.0;
    } else {
      localB->p = 0.5 * tau;
      localB->z = std::abs(b);
      localB->bcmis = std::abs(c);
      tmp = rtIsNaN(localB->bcmis);
      if ((localB->z > localB->bcmis) || tmp) {
        localB->bcmax = localB->z;
      } else {
        localB->bcmax = localB->bcmis;
      }

      if ((localB->z < localB->bcmis) || tmp) {
        localB->bcmis = localB->z;
      }

      if (!(b < 0.0)) {
        b_0 = 1;
      } else {
        b_0 = -1;
      }

      if (!(c < 0.0)) {
        c_0 = 1;
      } else {
        c_0 = -1;
      }

      localB->bcmis = localB->bcmis * static_cast<real_T>(b_0) *
        static_cast<real_T>(c_0);
      localB->scale_g1 = std::abs(localB->p);
      if ((!(localB->scale_g1 > localB->bcmax)) && (!rtIsNaN(localB->bcmax))) {
        localB->scale_g1 = localB->bcmax;
      }

      localB->z = localB->p / localB->scale_g1 * localB->p + localB->bcmax /
        localB->scale_g1 * localB->bcmis;
      if (localB->z >= 8.8817841970012523E-16) {
        if (!(localB->p < 0.0)) {
          tau = std::sqrt(localB->scale_g1) * std::sqrt(localB->z);
        } else {
          tau = -(std::sqrt(localB->scale_g1) * std::sqrt(localB->z));
        }

        localB->z = localB->p + tau;
        *b_a = d + localB->z;
        *b_d = d - localB->bcmax / localB->z * localB->bcmis;
        tau = CartesianImpedanc_rt_hypotd_snf(c, localB->z, localB);
        *cs = localB->z / tau;
        *sn = c / tau;
        *b_b = b - c;
        *b_c = 0.0;
      } else {
        localB->bcmax = b + c;
        tau = CartesianImpedanc_rt_hypotd_snf(localB->bcmax, tau, localB);
        *cs = std::sqrt((std::abs(localB->bcmax) / tau + 1.0) * 0.5);
        if (!(localB->bcmax < 0.0)) {
          b_0 = 1;
        } else {
          b_0 = -1;
        }

        *sn = -(localB->p / (tau * *cs)) * static_cast<real_T>(b_0);
        localB->p = a * *cs + b * *sn;
        tau = -a * *sn + b * *cs;
        localB->bcmax = c * *cs + d * *sn;
        localB->z = -c * *sn + d * *cs;
        *b_b = tau * *cs + localB->z * *sn;
        *b_c = -localB->p * *sn + localB->bcmax * *cs;
        localB->bcmax = ((localB->p * *cs + localB->bcmax * *sn) + (-tau * *sn +
          localB->z * *cs)) * 0.5;
        *b_a = localB->bcmax;
        *b_d = localB->bcmax;
        if (*b_c != 0.0) {
          if (*b_b != 0.0) {
            if ((*b_b < 0.0) == (*b_c < 0.0)) {
              localB->bcmis = std::sqrt(std::abs(*b_b));
              localB->z = std::sqrt(std::abs(*b_c));
              if (!(*b_c < 0.0)) {
                localB->p = localB->bcmis * localB->z;
              } else {
                localB->p = -(localB->bcmis * localB->z);
              }

              tau = 1.0 / std::sqrt(std::abs(*b_b + *b_c));
              *b_a = localB->bcmax + localB->p;
              *b_d = localB->bcmax - localB->p;
              *b_b -= *b_c;
              *b_c = 0.0;
              localB->p = localB->bcmis * tau;
              tau *= localB->z;
              localB->bcmax = *cs * localB->p - *sn * tau;
              *sn = *cs * tau + *sn * localB->p;
              *cs = localB->bcmax;
            }
          } else {
            *b_b = -*b_c;
            *b_c = 0.0;
            localB->bcmax = *cs;
            *cs = -*sn;
            *sn = localB->bcmax;
          }
        }
      }
    }
  }

  *rt1r = *b_a;
  *rt2r = *b_d;
  if (*b_c == 0.0) {
    *rt1i = 0.0;
    *rt2i = 0.0;
  } else {
    *rt1i = std::sqrt(std::abs(*b_b)) * std::sqrt(std::abs(*b_c));
    *rt2i = -*rt1i;
  }
}

void modelModelClass::CartesianImpedance_Task_xrot(int32_T n, const real_T x[16],
  int32_T ix0, int32_T iy0, real_T c, real_T s, real_T b_x[16],
  B_CoordinateTransformationCon_T *localB)
{
  int32_T ix;
  int32_T iy;
  int32_T k;
  std::memcpy(&b_x[0], &x[0], sizeof(real_T) << 4U);
  ix = ix0 - 1;
  iy = iy0 - 1;
  for (k = 0; k < n; k++) {
    localB->temp_h = c * b_x[ix] + s * b_x[iy];
    b_x[iy] = c * b_x[iy] - s * b_x[ix];
    b_x[ix] = localB->temp_h;
    iy += 4;
    ix += 4;
  }
}

real_T modelModelClass::CartesianImpedance_Task_xnrm2_p(int32_T n, const real_T
  x[3], B_CoordinateTransformationCon_T *localB)
{
  real_T y;
  real_T t;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = std::abs(x[1]);
    } else {
      localB->scale_bs = 3.3121686421112381E-170;
      localB->absxk_l = std::abs(x[1]);
      if (localB->absxk_l > 3.3121686421112381E-170) {
        y = 1.0;
        localB->scale_bs = localB->absxk_l;
      } else {
        t = localB->absxk_l / 3.3121686421112381E-170;
        y = t * t;
      }

      localB->absxk_l = std::abs(x[2]);
      if (localB->absxk_l > localB->scale_bs) {
        t = localB->scale_bs / localB->absxk_l;
        y = y * t * t + 1.0;
        localB->scale_bs = localB->absxk_l;
      } else {
        t = localB->absxk_l / localB->scale_bs;
        y += t * t;
      }

      y = localB->scale_bs * std::sqrt(y);
    }
  }

  return y;
}

void modelModelClass::CartesianImpedance_Ta_xzlarfg_d(int32_T n, real_T alpha1,
  real_T x[3], real_T *b_alpha1, real_T *tau, B_CoordinateTransformationCon_T
  *localB)
{
  int32_T knt;
  int32_T k;
  *b_alpha1 = alpha1;
  *tau = 0.0;
  if (n > 0) {
    localB->xnorm_n = CartesianImpedance_Task_xnrm2_p(n - 1, x, localB);
    if (localB->xnorm_n != 0.0) {
      localB->xnorm_n = CartesianImpedanc_rt_hypotd_snf(alpha1, localB->xnorm_n,
        localB);
      if (alpha1 >= 0.0) {
        localB->xnorm_n = -localB->xnorm_n;
      }

      if (std::abs(localB->xnorm_n) < 1.0020841800044864E-292) {
        knt = -1;
        do {
          knt++;
          for (k = 2; k <= n; k++) {
            x[k - 1] *= 9.9792015476736E+291;
          }

          localB->xnorm_n *= 9.9792015476736E+291;
          *b_alpha1 *= 9.9792015476736E+291;
        } while (!(std::abs(localB->xnorm_n) >= 1.0020841800044864E-292));

        localB->xnorm_n = CartesianImpedanc_rt_hypotd_snf(*b_alpha1,
          CartesianImpedance_Task_xnrm2_p(n - 1, x, localB), localB);
        if (*b_alpha1 >= 0.0) {
          localB->xnorm_n = -localB->xnorm_n;
        }

        *tau = (localB->xnorm_n - *b_alpha1) / localB->xnorm_n;
        *b_alpha1 = 1.0 / (*b_alpha1 - localB->xnorm_n);
        for (k = 2; k <= n; k++) {
          x[k - 1] *= *b_alpha1;
        }

        for (k = 0; k <= knt; k++) {
          localB->xnorm_n *= 1.0020841800044864E-292;
        }

        *b_alpha1 = localB->xnorm_n;
      } else {
        *tau = (localB->xnorm_n - alpha1) / localB->xnorm_n;
        *b_alpha1 = 1.0 / (alpha1 - localB->xnorm_n);
        for (k = 2; k <= n; k++) {
          x[k - 1] *= *b_alpha1;
        }

        *b_alpha1 = localB->xnorm_n;
      }
    }
  }
}

void modelModelClass::CartesianImpedance_Task_xhseqr(const real_T h[16], const
  real_T z[16], real_T b_h[16], int32_T *info, real_T b_z[16],
  B_CoordinateTransformationCon_T *localB)
{
  int32_T i;
  int32_T L;
  boolean_T goto150;
  int32_T k;
  int32_T m;
  int32_T nr;
  int32_T hoffset;
  int32_T its;
  int32_T b_j;
  int32_T c_j;
  int32_T d_j;
  int32_T tst_tmp;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
  std::memcpy(&b_z[0], &z[0], sizeof(real_T) << 4U);
  std::memcpy(&b_h[0], &h[0], sizeof(real_T) << 4U);
  *info = 0;
  localB->v[0] = 0.0;
  localB->v[1] = 0.0;
  localB->v[2] = 0.0;
  b_h[2] = 0.0;
  b_h[3] = 0.0;
  b_h[7] = 0.0;
  i = 3;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    L = 1;
    goto150 = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 301)) {
      k = i;
      exitg3 = false;
      while ((!exitg3) && (k + 1 > L)) {
        nr = ((k - 1) << 2) + k;
        localB->ba = std::abs(b_h[nr]);
        if (localB->ba <= 4.0083367200179456E-292) {
          exitg3 = true;
        } else {
          m = (k << 2) + k;
          localB->bb = std::abs(b_h[m]);
          tst_tmp = nr - 1;
          localB->tst = std::abs(b_h[tst_tmp]) + localB->bb;
          if (localB->tst == 0.0) {
            if (k - 1 >= 1) {
              localB->tst = std::abs(b_h[(((k - 2) << 2) + k) - 1]);
            }

            if (k + 2 <= 4) {
              localB->tst += std::abs(b_h[((k << 2) + k) + 1]);
            }
          }

          if (localB->ba <= 2.2204460492503131E-16 * localB->tst) {
            localB->tst = std::abs(b_h[m - 1]);
            if (localB->ba > localB->tst) {
              localB->ab = localB->ba;
              localB->ba = localB->tst;
            } else {
              localB->ab = localB->tst;
            }

            localB->tst = std::abs(b_h[tst_tmp] - b_h[m]);
            if (localB->bb > localB->tst) {
              localB->aa = localB->bb;
              localB->bb = localB->tst;
            } else {
              localB->aa = localB->tst;
            }

            localB->tst = localB->aa + localB->ab;
            localB->bb = localB->aa / localB->tst * localB->bb *
              2.2204460492503131E-16;
            if ((4.0083367200179456E-292 > localB->bb) || rtIsNaN(localB->bb)) {
              localB->bb = 4.0083367200179456E-292;
            }

            if (localB->ab / localB->tst * localB->ba <= localB->bb) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }
      }

      L = k + 1;
      if (k + 1 > 1) {
        b_h[k + ((k - 1) << 2)] = 0.0;
      }

      if (k + 1 >= i) {
        goto150 = true;
        exitg2 = true;
      } else {
        if (its == 10) {
          tst_tmp = (k << 2) + k;
          localB->tst = std::abs(b_h[(((k + 1) << 2) + k) + 2]) + std::abs
            (b_h[tst_tmp + 1]);
          localB->ab = b_h[tst_tmp] + 0.75 * localB->tst;
          localB->h12 = -0.4375 * localB->tst;
          localB->aa = localB->tst;
          localB->ba = localB->ab;
        } else if (its == 20) {
          localB->tst = std::abs(b_h[(((i - 2) << 2) + i) - 1]) + std::abs(b_h
            [((i - 1) << 2) + i]);
          localB->ab = b_h[(i << 2) + i] + 0.75 * localB->tst;
          localB->h12 = -0.4375 * localB->tst;
          localB->aa = localB->tst;
          localB->ba = localB->ab;
        } else {
          m = ((i - 1) << 2) + i;
          localB->ab = b_h[m - 1];
          localB->aa = b_h[m];
          localB->h12 = b_h[((i << 2) + i) - 1];
          localB->ba = b_h[(i << 2) + i];
        }

        localB->tst = ((std::abs(localB->ab) + std::abs(localB->h12)) + std::abs
                       (localB->aa)) + std::abs(localB->ba);
        if (localB->tst == 0.0) {
          localB->ab = 0.0;
          localB->ba = 0.0;
          localB->bb = 0.0;
          localB->aa = 0.0;
        } else {
          localB->ab /= localB->tst;
          localB->aa /= localB->tst;
          localB->h12 /= localB->tst;
          localB->ba /= localB->tst;
          localB->bb = (localB->ab + localB->ba) / 2.0;
          localB->ab = (localB->ab - localB->bb) * (localB->ba - localB->bb) -
            localB->h12 * localB->aa;
          localB->aa = std::sqrt(std::abs(localB->ab));
          if (localB->ab >= 0.0) {
            localB->ab = localB->bb * localB->tst;
            localB->bb = localB->ab;
            localB->ba = localB->aa * localB->tst;
            localB->aa = -localB->ba;
          } else {
            localB->ab = localB->bb + localB->aa;
            localB->bb -= localB->aa;
            if (std::abs(localB->ab - localB->ba) <= std::abs(localB->bb -
                 localB->ba)) {
              localB->ab *= localB->tst;
              localB->bb = localB->ab;
            } else {
              localB->bb *= localB->tst;
              localB->ab = localB->bb;
            }

            localB->ba = 0.0;
            localB->aa = 0.0;
          }
        }

        m = i - 2;
        exitg3 = false;
        while ((!exitg3) && (m + 1 >= k + 1)) {
          tst_tmp = (m << 2) + m;
          nr = tst_tmp + 1;
          localB->h12 = b_h[tst_tmp] - localB->bb;
          localB->tst = (std::abs(localB->h12) + std::abs(localB->aa)) + std::
            abs(b_h[nr]);
          localB->h21s = b_h[nr] / localB->tst;
          nr = ((m + 1) << 2) + m;
          localB->v[0] = (localB->h12 / localB->tst * (b_h[tst_tmp] - localB->ab)
                          + b_h[nr] * localB->h21s) - localB->aa / localB->tst *
            localB->ba;
          hoffset = nr + 1;
          localB->v[1] = (((b_h[hoffset] + b_h[tst_tmp]) - localB->ab) -
                          localB->bb) * localB->h21s;
          localB->v[2] = b_h[nr + 2] * localB->h21s;
          localB->tst = (std::abs(localB->v[0]) + std::abs(localB->v[1])) + std::
            abs(localB->v[2]);
          localB->v[0] /= localB->tst;
          localB->v[1] /= localB->tst;
          localB->v[2] /= localB->tst;
          if (m + 1 == k + 1) {
            exitg3 = true;
          } else {
            nr = ((m - 1) << 2) + m;
            if (std::abs(b_h[nr]) * (std::abs(localB->v[1]) + std::abs(localB->
                  v[2])) <= ((std::abs(b_h[nr - 1]) + std::abs(b_h[tst_tmp])) +
                             std::abs(b_h[hoffset])) * (2.2204460492503131E-16 *
                 std::abs(localB->v[0]))) {
              exitg3 = true;
            } else {
              m--;
            }
          }
        }

        for (tst_tmp = m + 1; tst_tmp <= i; tst_tmp++) {
          nr = (i - tst_tmp) + 2;
          if (3 < nr) {
            nr = 3;
          }

          if (tst_tmp > m + 1) {
            hoffset = (((tst_tmp - 2) << 2) + tst_tmp) - 2;
            for (b_j = 0; b_j < nr; b_j++) {
              localB->v[b_j] = b_h[(b_j + hoffset) + 1];
            }
          }

          localB->b_v[0] = localB->v[0];
          localB->b_v[1] = localB->v[1];
          localB->b_v[2] = localB->v[2];
          CartesianImpedance_Ta_xzlarfg_d(nr, localB->v[0], localB->b_v,
            &localB->ba, &localB->tst, localB);
          localB->v[1] = localB->b_v[1];
          localB->v[2] = localB->b_v[2];
          localB->v[0] = localB->ba;
          if (tst_tmp > m + 1) {
            hoffset = tst_tmp + ((tst_tmp - 2) << 2);
            b_h[hoffset - 1] = localB->ba;
            b_h[hoffset] = 0.0;
            if (tst_tmp < i) {
              b_h[tst_tmp + 1] = 0.0;
            }
          } else {
            if (m + 1 > k + 1) {
              b_h[tst_tmp - 1] *= 1.0 - localB->tst;
            }
          }

          localB->ba = localB->b_v[1];
          localB->ab = localB->tst * localB->b_v[1];
          if (nr == 3) {
            localB->aa = localB->b_v[2];
            localB->h12 = localB->tst * localB->b_v[2];
            for (c_j = tst_tmp; c_j < 5; c_j++) {
              nr = ((c_j - 1) << 2) + tst_tmp;
              hoffset = nr - 1;
              b_j = nr + 1;
              localB->bb = (b_h[hoffset] + b_h[nr] * localB->ba) + b_h[b_j] *
                localB->aa;
              b_h[hoffset] -= localB->bb * localB->tst;
              b_h[nr] -= localB->bb * localB->ab;
              b_h[b_j] -= localB->bb * localB->h12;
            }

            nr = tst_tmp + 3;
            hoffset = i + 1;
            if (nr < hoffset) {
              hoffset = nr;
            }

            c_j = hoffset - 1;
            for (d_j = 0; d_j <= c_j; d_j++) {
              nr = ((tst_tmp - 1) << 2) + d_j;
              hoffset = (tst_tmp << 2) + d_j;
              b_j = ((tst_tmp + 1) << 2) + d_j;
              localB->bb = (b_h[nr] + b_h[hoffset] * localB->ba) + b_h[b_j] *
                localB->aa;
              b_h[nr] -= localB->bb * localB->tst;
              b_h[hoffset] -= localB->bb * localB->ab;
              b_h[b_j] -= localB->bb * localB->h12;
            }

            for (c_j = 0; c_j < 4; c_j++) {
              nr = ((tst_tmp - 1) << 2) + c_j;
              hoffset = (tst_tmp << 2) + c_j;
              b_j = ((tst_tmp + 1) << 2) + c_j;
              localB->bb = (b_z[nr] + b_z[hoffset] * localB->ba) + b_z[b_j] *
                localB->aa;
              b_z[nr] -= localB->bb * localB->tst;
              b_z[hoffset] -= localB->bb * localB->ab;
              b_z[b_j] -= localB->bb * localB->h12;
            }
          } else {
            if (nr == 2) {
              for (b_j = tst_tmp; b_j < 5; b_j++) {
                nr = ((b_j - 1) << 2) + tst_tmp;
                hoffset = nr - 1;
                localB->bb = b_h[hoffset] + b_h[nr] * localB->ba;
                b_h[hoffset] -= localB->bb * localB->tst;
                b_h[nr] -= localB->bb * localB->ab;
              }

              for (b_j = 0; b_j <= i; b_j++) {
                nr = ((tst_tmp - 1) << 2) + b_j;
                hoffset = (tst_tmp << 2) + b_j;
                localB->bb = b_h[nr] + b_h[hoffset] * localB->ba;
                b_h[nr] -= localB->bb * localB->tst;
                b_h[hoffset] -= localB->bb * localB->ab;
              }

              for (b_j = 0; b_j < 4; b_j++) {
                nr = ((tst_tmp - 1) << 2) + b_j;
                hoffset = (tst_tmp << 2) + b_j;
                localB->bb = b_z[nr] + b_z[hoffset] * localB->ba;
                b_z[nr] -= localB->bb * localB->tst;
                b_z[hoffset] -= localB->bb * localB->ab;
              }
            }
          }
        }

        its++;
      }
    }

    if (!goto150) {
      *info = i + 1;
      exitg1 = true;
    } else {
      if ((i + 1 != L) && (L == i)) {
        CartesianImpedance_Task_xdlanv2(b_h[(i + ((i - 1) << 2)) - 1], b_h[(i +
          (i << 2)) - 1], b_h[i + ((i - 1) << 2)], b_h[i + (i << 2)],
          &localB->ab, &localB->bb, &localB->aa, &localB->h12, &b_h[(i + ((i - 1)
          << 2)) - 1], &localB->h21s, &localB->d, &localB->e, &localB->tst,
          &localB->ba, localB);
        its = i << 2;
        hoffset = i + its;
        b_h[hoffset - 1] = localB->h21s;
        m = (i - 1) << 2;
        b_h[i + m] = localB->d;
        b_h[hoffset] = localB->e;
        if (4 > i + 1) {
          std::memcpy(&localB->b_h[0], &b_h[0], sizeof(real_T) << 4U);
          hoffset = ((i + 1) << 2) + i;
          CartesianImpedance_Task_xrot(3 - i, localB->b_h, hoffset, hoffset + 1,
            localB->tst, localB->ba, b_h, localB);
        }

        tst_tmp = i - 2;
        if (i - 1 >= 1) {
          i = m;
          nr = its;
          for (k = 0; k <= tst_tmp; k++) {
            localB->ab = localB->tst * b_h[i] + localB->ba * b_h[nr];
            b_h[nr] = localB->tst * b_h[nr] - localB->ba * b_h[i];
            b_h[i] = localB->ab;
            nr++;
            i++;
          }
        }

        localB->ab = localB->tst * b_z[m] + localB->ba * b_z[its];
        b_z[its] = localB->tst * b_z[its] - localB->ba * b_z[m];
        b_z[m] = localB->ab;
        nr = its + 1;
        i = m + 1;
        localB->ab = localB->tst * b_z[i] + localB->ba * b_z[nr];
        b_z[nr] = localB->tst * b_z[nr] - localB->ba * b_z[i];
        b_z[i] = localB->ab;
        nr++;
        i++;
        localB->ab = localB->tst * b_z[i] + localB->ba * b_z[nr];
        b_z[nr] = localB->tst * b_z[nr] - localB->ba * b_z[i];
        b_z[i] = localB->ab;
        nr++;
        i++;
        localB->ab = localB->tst * b_z[i] + localB->ba * b_z[nr];
        b_z[nr] = localB->tst * b_z[nr] - localB->ba * b_z[i];
        b_z[i] = localB->ab;
      }

      i = L - 2;
    }
  }

  b_h[3] = 0.0;
}

void modelModelClass::CartesianImpedance_Task_eig(const real_T A[16], creal_T V
  [16], creal_T D[4], B_CoordinateTransformationCon_T *localB)
{
  boolean_T p;
  int32_T exitg1;
  boolean_T exitg2;
  p = true;
  for (localB->ia = 0; localB->ia < 16; localB->ia++) {
    if (p && ((!rtIsInf(A[localB->ia])) && (!rtIsNaN(A[localB->ia])))) {
    } else {
      p = false;
    }
  }

  if (!p) {
    for (localB->ia = 0; localB->ia < 16; localB->ia++) {
      V[localB->ia].re = (rtNaN);
      V[localB->ia].im = 0.0;
    }

    D[0].re = (rtNaN);
    D[0].im = 0.0;
    D[1].re = (rtNaN);
    D[1].im = 0.0;
    D[2].re = (rtNaN);
    D[2].im = 0.0;
    D[3].re = (rtNaN);
    D[3].im = 0.0;
  } else {
    p = true;
    localB->ia = 0;
    exitg2 = false;
    while ((!exitg2) && (localB->ia < 4)) {
      localB->itau = 0;
      do {
        exitg1 = 0;
        if (localB->itau <= localB->ia) {
          if (!(A[(localB->ia << 2) + localB->itau] == A[(localB->itau << 2) +
                localB->ia])) {
            p = false;
            exitg1 = 1;
          } else {
            localB->itau++;
          }
        } else {
          localB->ia++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }

    if (p) {
      p = true;
      for (localB->ia = 0; localB->ia < 16; localB->ia++) {
        if (p && ((!rtIsInf(A[localB->ia])) && (!rtIsNaN(A[localB->ia])))) {
        } else {
          p = false;
        }
      }

      if (!p) {
        for (localB->ia = 0; localB->ia < 16; localB->ia++) {
          localB->c_V_m[localB->ia] = (rtNaN);
        }

        localB->itau = 2;
        for (localB->ia = 0; localB->ia < 3; localB->ia++) {
          if (localB->itau <= 4) {
            std::memset(&localB->c_V_m[((localB->ia << 2) + localB->itau) + -1],
                        0, (5 - localB->itau) * sizeof(real_T));
          }

          localB->itau++;
        }

        for (localB->ia = 0; localB->ia < 16; localB->ia++) {
          localB->T[localB->ia] = (rtNaN);
        }
      } else {
        CartesianImpedance_Task_xgehrd(A, localB->b_A, localB->tau, localB);
        std::memcpy(&localB->c_V_m[0], &localB->b_A[0], sizeof(real_T) << 4U);
        for (localB->i = 2; localB->i >= 0; localB->i--) {
          localB->iaii = (localB->i + 1) << 2;
          localB->ia = localB->iaii - 5;
          for (localB->itau = 0; localB->itau <= localB->i; localB->itau++) {
            localB->c_V_m[localB->iaii + localB->itau] = 0.0;
          }

          for (localB->itau = localB->i + 3; localB->itau < 5; localB->itau++) {
            localB->c_V_m[(localB->iaii + localB->itau) - 1] = localB->
              c_V_m[localB->ia + localB->itau];
          }
        }

        localB->c_V_m[1] = 0.0;
        localB->c_V_m[2] = 0.0;
        localB->c_V_m[3] = 0.0;
        localB->c_V_m[0] = 1.0;
        localB->itau = 2;
        localB->work[0] = 0.0;
        localB->work[1] = 0.0;
        localB->work[2] = 0.0;
        localB->work[3] = 0.0;
        for (localB->i = 2; localB->i >= 0; localB->i--) {
          localB->iaii = ((localB->i << 2) + localB->i) + 10;
          if (localB->i + 1 < 3) {
            localB->c_V_m[localB->iaii - 5] = 1.0;
            std::memcpy(&localB->T[0], &localB->c_V_m[0], sizeof(real_T) << 4U);
            if (localB->tau[localB->itau] != 0.0) {
              localB->lastv = 3 - localB->i;
              localB->ia = (localB->iaii - localB->i) - 3;
              while ((localB->lastv > 0) && (localB->c_V_m[localB->ia] == 0.0))
              {
                localB->lastv--;
                localB->ia--;
              }

              localB->lastc = 2 - localB->i;
              exitg2 = false;
              while ((!exitg2) && (localB->lastc > 0)) {
                localB->coltop = ((localB->lastc - 1) << 2) + localB->iaii;
                localB->ia = localB->coltop;
                do {
                  exitg1 = 0;
                  if (localB->ia <= (localB->coltop + localB->lastv) - 1) {
                    if (localB->c_V_m[localB->ia - 1] != 0.0) {
                      exitg1 = 1;
                    } else {
                      localB->ia++;
                    }
                  } else {
                    localB->lastc--;
                    exitg1 = 2;
                  }
                } while (exitg1 == 0);

                if (exitg1 == 1) {
                  exitg2 = true;
                }
              }

              std::memcpy(&localB->T[0], &localB->c_V_m[0], sizeof(real_T) << 4U);
            } else {
              localB->lastv = 0;
              localB->lastc = 0;
            }

            if (localB->lastv > 0) {
              if (localB->lastc != 0) {
                if (0 <= localB->lastc - 1) {
                  std::memset(&localB->work[0], 0, localB->lastc * sizeof(real_T));
                }

                localB->iy = 0;
                localB->coltop = ((localB->lastc - 1) << 2) + localB->iaii;
                for (localB->iac = localB->iaii; localB->iac <= localB->coltop;
                     localB->iac += 4) {
                  localB->ix = localB->iaii - 5;
                  localB->colnorm = 0.0;
                  localB->d_e = localB->iac + localB->lastv;
                  for (localB->ia = localB->iac; localB->ia < localB->d_e;
                       localB->ia++) {
                    localB->colnorm += localB->T[localB->ia - 1] * localB->
                      T[localB->ix];
                    localB->ix++;
                  }

                  localB->work[localB->iy] += localB->colnorm;
                  localB->iy++;
                }
              }

              std::memcpy(&localB->c_V_m[0], &localB->T[0], sizeof(real_T) << 4U);
              CartesianImpedance_Task_xgerc(localB->lastv, localB->lastc,
                -localB->tau[localB->itau], localB->iaii - 4, localB->work,
                localB->c_V_m, localB->iaii, localB->T, localB);
            }

            std::memcpy(&localB->c_V_m[0], &localB->T[0], sizeof(real_T) << 4U);
            localB->coltop = localB->iaii - localB->i;
            for (localB->ia = localB->iaii - 3; localB->ia <= localB->coltop - 2;
                 localB->ia++) {
              localB->c_V_m[localB->ia - 1] *= -localB->tau[localB->itau];
            }
          }

          localB->c_V_m[localB->iaii - 5] = 1.0 - localB->tau[localB->itau];
          localB->coltop = localB->i - 1;
          for (localB->ia = 0; localB->ia <= localB->coltop; localB->ia++) {
            localB->c_V_m[(localB->iaii - localB->ia) - 6] = 0.0;
          }

          localB->itau--;
        }

        std::memcpy(&localB->c_V_c[0], &localB->c_V_m[0], sizeof(real_T) << 4U);
        CartesianImpedance_Task_xhseqr(localB->b_A, localB->c_V_c, localB->T,
          &localB->ia, localB->c_V_m, localB);
      }

      for (localB->ia = 0; localB->ia < 16; localB->ia++) {
        V[localB->ia].re = localB->c_V_m[localB->ia];
        V[localB->ia].im = 0.0;
      }

      D[0].re = localB->T[0];
      D[0].im = 0.0;
      D[1].re = localB->T[5];
      D[1].im = 0.0;
      D[2].re = localB->T[10];
      D[2].im = 0.0;
      D[3].re = localB->T[15];
      D[3].im = 0.0;
    } else {
      for (localB->ia = 0; localB->ia < 16; localB->ia++) {
        localB->A[localB->ia].re = A[localB->ia];
        localB->A[localB->ia].im = 0.0;
      }

      CartesianImpedance_Task_xzggev(localB->A, localB->b_At, &localB->ia, D,
        localB->b_beta1, V, localB);
      localB->colnorm = 0.0;
      localB->scale = 3.3121686421112381E-170;
      for (localB->ia = 1; localB->ia < 5; localB->ia++) {
        localB->absxk = std::abs(V[localB->ia - 1].re);
        if (localB->absxk > localB->scale) {
          localB->t = localB->scale / localB->absxk;
          localB->colnorm = localB->colnorm * localB->t * localB->t + 1.0;
          localB->scale = localB->absxk;
        } else {
          localB->t = localB->absxk / localB->scale;
          localB->colnorm += localB->t * localB->t;
        }

        localB->absxk = std::abs(V[localB->ia - 1].im);
        if (localB->absxk > localB->scale) {
          localB->t = localB->scale / localB->absxk;
          localB->colnorm = localB->colnorm * localB->t * localB->t + 1.0;
          localB->scale = localB->absxk;
        } else {
          localB->t = localB->absxk / localB->scale;
          localB->colnorm += localB->t * localB->t;
        }
      }

      localB->colnorm = localB->scale * std::sqrt(localB->colnorm);
      for (localB->i = 1; localB->i < 5; localB->i++) {
        localB->scale = V[localB->i - 1].re;
        localB->absxk = V[localB->i - 1].im;
        if (localB->absxk == 0.0) {
          V[localB->i - 1].re = localB->scale / localB->colnorm;
          V[localB->i - 1].im = 0.0;
        } else if (localB->scale == 0.0) {
          V[localB->i - 1].re = 0.0;
          V[localB->i - 1].im = localB->absxk / localB->colnorm;
        } else {
          V[localB->i - 1].re = localB->scale / localB->colnorm;
          V[localB->i - 1].im = localB->absxk / localB->colnorm;
        }
      }

      localB->colnorm = 0.0;
      localB->scale = 3.3121686421112381E-170;
      for (localB->ia = 5; localB->ia < 9; localB->ia++) {
        localB->absxk = std::abs(V[localB->ia - 1].re);
        if (localB->absxk > localB->scale) {
          localB->t = localB->scale / localB->absxk;
          localB->colnorm = localB->colnorm * localB->t * localB->t + 1.0;
          localB->scale = localB->absxk;
        } else {
          localB->t = localB->absxk / localB->scale;
          localB->colnorm += localB->t * localB->t;
        }

        localB->absxk = std::abs(V[localB->ia - 1].im);
        if (localB->absxk > localB->scale) {
          localB->t = localB->scale / localB->absxk;
          localB->colnorm = localB->colnorm * localB->t * localB->t + 1.0;
          localB->scale = localB->absxk;
        } else {
          localB->t = localB->absxk / localB->scale;
          localB->colnorm += localB->t * localB->t;
        }
      }

      localB->colnorm = localB->scale * std::sqrt(localB->colnorm);
      for (localB->i = 5; localB->i < 9; localB->i++) {
        localB->scale = V[localB->i - 1].re;
        localB->absxk = V[localB->i - 1].im;
        if (localB->absxk == 0.0) {
          V[localB->i - 1].re = localB->scale / localB->colnorm;
          V[localB->i - 1].im = 0.0;
        } else if (localB->scale == 0.0) {
          V[localB->i - 1].re = 0.0;
          V[localB->i - 1].im = localB->absxk / localB->colnorm;
        } else {
          V[localB->i - 1].re = localB->scale / localB->colnorm;
          V[localB->i - 1].im = localB->absxk / localB->colnorm;
        }
      }

      localB->colnorm = 0.0;
      localB->scale = 3.3121686421112381E-170;
      for (localB->ia = 9; localB->ia < 13; localB->ia++) {
        localB->absxk = std::abs(V[localB->ia - 1].re);
        if (localB->absxk > localB->scale) {
          localB->t = localB->scale / localB->absxk;
          localB->colnorm = localB->colnorm * localB->t * localB->t + 1.0;
          localB->scale = localB->absxk;
        } else {
          localB->t = localB->absxk / localB->scale;
          localB->colnorm += localB->t * localB->t;
        }

        localB->absxk = std::abs(V[localB->ia - 1].im);
        if (localB->absxk > localB->scale) {
          localB->t = localB->scale / localB->absxk;
          localB->colnorm = localB->colnorm * localB->t * localB->t + 1.0;
          localB->scale = localB->absxk;
        } else {
          localB->t = localB->absxk / localB->scale;
          localB->colnorm += localB->t * localB->t;
        }
      }

      localB->colnorm = localB->scale * std::sqrt(localB->colnorm);
      for (localB->i = 9; localB->i < 13; localB->i++) {
        localB->scale = V[localB->i - 1].re;
        localB->absxk = V[localB->i - 1].im;
        if (localB->absxk == 0.0) {
          V[localB->i - 1].re = localB->scale / localB->colnorm;
          V[localB->i - 1].im = 0.0;
        } else if (localB->scale == 0.0) {
          V[localB->i - 1].re = 0.0;
          V[localB->i - 1].im = localB->absxk / localB->colnorm;
        } else {
          V[localB->i - 1].re = localB->scale / localB->colnorm;
          V[localB->i - 1].im = localB->absxk / localB->colnorm;
        }
      }

      localB->colnorm = 0.0;
      localB->scale = 3.3121686421112381E-170;
      for (localB->ia = 13; localB->ia < 17; localB->ia++) {
        localB->absxk = std::abs(V[localB->ia - 1].re);
        if (localB->absxk > localB->scale) {
          localB->t = localB->scale / localB->absxk;
          localB->colnorm = localB->colnorm * localB->t * localB->t + 1.0;
          localB->scale = localB->absxk;
        } else {
          localB->t = localB->absxk / localB->scale;
          localB->colnorm += localB->t * localB->t;
        }

        localB->absxk = std::abs(V[localB->ia - 1].im);
        if (localB->absxk > localB->scale) {
          localB->t = localB->scale / localB->absxk;
          localB->colnorm = localB->colnorm * localB->t * localB->t + 1.0;
          localB->scale = localB->absxk;
        } else {
          localB->t = localB->absxk / localB->scale;
          localB->colnorm += localB->t * localB->t;
        }
      }

      localB->colnorm = localB->scale * std::sqrt(localB->colnorm);
      for (localB->i = 13; localB->i < 17; localB->i++) {
        localB->scale = V[localB->i - 1].re;
        localB->absxk = V[localB->i - 1].im;
        if (localB->absxk == 0.0) {
          V[localB->i - 1].re = localB->scale / localB->colnorm;
          V[localB->i - 1].im = 0.0;
        } else if (localB->scale == 0.0) {
          V[localB->i - 1].re = 0.0;
          V[localB->i - 1].im = localB->absxk / localB->colnorm;
        } else {
          V[localB->i - 1].re = localB->scale / localB->colnorm;
          V[localB->i - 1].im = localB->absxk / localB->colnorm;
        }
      }

      if (localB->b_beta1[0].im == 0.0) {
        if (D[0].im == 0.0) {
          localB->colnorm = D[0].re / localB->b_beta1[0].re;
          localB->scale = 0.0;
        } else if (D[0].re == 0.0) {
          localB->colnorm = 0.0;
          localB->scale = D[0].im / localB->b_beta1[0].re;
        } else {
          localB->colnorm = D[0].re / localB->b_beta1[0].re;
          localB->scale = D[0].im / localB->b_beta1[0].re;
        }
      } else if (localB->b_beta1[0].re == 0.0) {
        if (D[0].re == 0.0) {
          localB->colnorm = D[0].im / localB->b_beta1[0].im;
          localB->scale = 0.0;
        } else if (D[0].im == 0.0) {
          localB->colnorm = 0.0;
          localB->scale = -(D[0].re / localB->b_beta1[0].im);
        } else {
          localB->colnorm = D[0].im / localB->b_beta1[0].im;
          localB->scale = -(D[0].re / localB->b_beta1[0].im);
        }
      } else {
        localB->scale = std::abs(localB->b_beta1[0].re);
        localB->colnorm = std::abs(localB->b_beta1[0].im);
        if (localB->scale > localB->colnorm) {
          localB->scale = localB->b_beta1[0].im / localB->b_beta1[0].re;
          localB->absxk = localB->scale * localB->b_beta1[0].im +
            localB->b_beta1[0].re;
          localB->colnorm = (localB->scale * D[0].im + D[0].re) / localB->absxk;
          localB->scale = (D[0].im - localB->scale * D[0].re) / localB->absxk;
        } else if (localB->colnorm == localB->scale) {
          localB->absxk = localB->b_beta1[0].re > 0.0 ? 0.5 : -0.5;
          localB->t = localB->b_beta1[0].im > 0.0 ? 0.5 : -0.5;
          localB->colnorm = (D[0].re * localB->absxk + D[0].im * localB->t) /
            localB->scale;
          localB->scale = (D[0].im * localB->absxk - D[0].re * localB->t) /
            localB->scale;
        } else {
          localB->scale = localB->b_beta1[0].re / localB->b_beta1[0].im;
          localB->absxk = localB->scale * localB->b_beta1[0].re +
            localB->b_beta1[0].im;
          localB->colnorm = (localB->scale * D[0].re + D[0].im) / localB->absxk;
          localB->scale = (localB->scale * D[0].im - D[0].re) / localB->absxk;
        }
      }

      D[0].re = localB->colnorm;
      D[0].im = localB->scale;
      if (localB->b_beta1[1].im == 0.0) {
        if (D[1].im == 0.0) {
          localB->colnorm = D[1].re / localB->b_beta1[1].re;
          localB->scale = 0.0;
        } else if (D[1].re == 0.0) {
          localB->colnorm = 0.0;
          localB->scale = D[1].im / localB->b_beta1[1].re;
        } else {
          localB->colnorm = D[1].re / localB->b_beta1[1].re;
          localB->scale = D[1].im / localB->b_beta1[1].re;
        }
      } else if (localB->b_beta1[1].re == 0.0) {
        if (D[1].re == 0.0) {
          localB->colnorm = D[1].im / localB->b_beta1[1].im;
          localB->scale = 0.0;
        } else if (D[1].im == 0.0) {
          localB->colnorm = 0.0;
          localB->scale = -(D[1].re / localB->b_beta1[1].im);
        } else {
          localB->colnorm = D[1].im / localB->b_beta1[1].im;
          localB->scale = -(D[1].re / localB->b_beta1[1].im);
        }
      } else {
        localB->scale = std::abs(localB->b_beta1[1].re);
        localB->colnorm = std::abs(localB->b_beta1[1].im);
        if (localB->scale > localB->colnorm) {
          localB->scale = localB->b_beta1[1].im / localB->b_beta1[1].re;
          localB->absxk = localB->scale * localB->b_beta1[1].im +
            localB->b_beta1[1].re;
          localB->colnorm = (localB->scale * D[1].im + D[1].re) / localB->absxk;
          localB->scale = (D[1].im - localB->scale * D[1].re) / localB->absxk;
        } else if (localB->colnorm == localB->scale) {
          localB->absxk = localB->b_beta1[1].re > 0.0 ? 0.5 : -0.5;
          localB->t = localB->b_beta1[1].im > 0.0 ? 0.5 : -0.5;
          localB->colnorm = (D[1].re * localB->absxk + D[1].im * localB->t) /
            localB->scale;
          localB->scale = (D[1].im * localB->absxk - D[1].re * localB->t) /
            localB->scale;
        } else {
          localB->scale = localB->b_beta1[1].re / localB->b_beta1[1].im;
          localB->absxk = localB->scale * localB->b_beta1[1].re +
            localB->b_beta1[1].im;
          localB->colnorm = (localB->scale * D[1].re + D[1].im) / localB->absxk;
          localB->scale = (localB->scale * D[1].im - D[1].re) / localB->absxk;
        }
      }

      D[1].re = localB->colnorm;
      D[1].im = localB->scale;
      if (localB->b_beta1[2].im == 0.0) {
        if (D[2].im == 0.0) {
          localB->colnorm = D[2].re / localB->b_beta1[2].re;
          localB->scale = 0.0;
        } else if (D[2].re == 0.0) {
          localB->colnorm = 0.0;
          localB->scale = D[2].im / localB->b_beta1[2].re;
        } else {
          localB->colnorm = D[2].re / localB->b_beta1[2].re;
          localB->scale = D[2].im / localB->b_beta1[2].re;
        }
      } else if (localB->b_beta1[2].re == 0.0) {
        if (D[2].re == 0.0) {
          localB->colnorm = D[2].im / localB->b_beta1[2].im;
          localB->scale = 0.0;
        } else if (D[2].im == 0.0) {
          localB->colnorm = 0.0;
          localB->scale = -(D[2].re / localB->b_beta1[2].im);
        } else {
          localB->colnorm = D[2].im / localB->b_beta1[2].im;
          localB->scale = -(D[2].re / localB->b_beta1[2].im);
        }
      } else {
        localB->scale = std::abs(localB->b_beta1[2].re);
        localB->colnorm = std::abs(localB->b_beta1[2].im);
        if (localB->scale > localB->colnorm) {
          localB->scale = localB->b_beta1[2].im / localB->b_beta1[2].re;
          localB->absxk = localB->scale * localB->b_beta1[2].im +
            localB->b_beta1[2].re;
          localB->colnorm = (localB->scale * D[2].im + D[2].re) / localB->absxk;
          localB->scale = (D[2].im - localB->scale * D[2].re) / localB->absxk;
        } else if (localB->colnorm == localB->scale) {
          localB->absxk = localB->b_beta1[2].re > 0.0 ? 0.5 : -0.5;
          localB->t = localB->b_beta1[2].im > 0.0 ? 0.5 : -0.5;
          localB->colnorm = (D[2].re * localB->absxk + D[2].im * localB->t) /
            localB->scale;
          localB->scale = (D[2].im * localB->absxk - D[2].re * localB->t) /
            localB->scale;
        } else {
          localB->scale = localB->b_beta1[2].re / localB->b_beta1[2].im;
          localB->absxk = localB->scale * localB->b_beta1[2].re +
            localB->b_beta1[2].im;
          localB->colnorm = (localB->scale * D[2].re + D[2].im) / localB->absxk;
          localB->scale = (localB->scale * D[2].im - D[2].re) / localB->absxk;
        }
      }

      D[2].re = localB->colnorm;
      D[2].im = localB->scale;
      if (localB->b_beta1[3].im == 0.0) {
        if (D[3].im == 0.0) {
          localB->colnorm = D[3].re / localB->b_beta1[3].re;
          localB->scale = 0.0;
        } else if (D[3].re == 0.0) {
          localB->colnorm = 0.0;
          localB->scale = D[3].im / localB->b_beta1[3].re;
        } else {
          localB->colnorm = D[3].re / localB->b_beta1[3].re;
          localB->scale = D[3].im / localB->b_beta1[3].re;
        }
      } else if (localB->b_beta1[3].re == 0.0) {
        if (D[3].re == 0.0) {
          localB->colnorm = D[3].im / localB->b_beta1[3].im;
          localB->scale = 0.0;
        } else if (D[3].im == 0.0) {
          localB->colnorm = 0.0;
          localB->scale = -(D[3].re / localB->b_beta1[3].im);
        } else {
          localB->colnorm = D[3].im / localB->b_beta1[3].im;
          localB->scale = -(D[3].re / localB->b_beta1[3].im);
        }
      } else {
        localB->scale = std::abs(localB->b_beta1[3].re);
        localB->colnorm = std::abs(localB->b_beta1[3].im);
        if (localB->scale > localB->colnorm) {
          localB->scale = localB->b_beta1[3].im / localB->b_beta1[3].re;
          localB->absxk = localB->scale * localB->b_beta1[3].im +
            localB->b_beta1[3].re;
          localB->colnorm = (localB->scale * D[3].im + D[3].re) / localB->absxk;
          localB->scale = (D[3].im - localB->scale * D[3].re) / localB->absxk;
        } else if (localB->colnorm == localB->scale) {
          localB->absxk = localB->b_beta1[3].re > 0.0 ? 0.5 : -0.5;
          localB->t = localB->b_beta1[3].im > 0.0 ? 0.5 : -0.5;
          localB->colnorm = (D[3].re * localB->absxk + D[3].im * localB->t) /
            localB->scale;
          localB->scale = (D[3].im * localB->absxk - D[3].re * localB->t) /
            localB->scale;
        } else {
          localB->scale = localB->b_beta1[3].re / localB->b_beta1[3].im;
          localB->absxk = localB->scale * localB->b_beta1[3].re +
            localB->b_beta1[3].im;
          localB->colnorm = (localB->scale * D[3].re + D[3].im) / localB->absxk;
          localB->scale = (localB->scale * D[3].im - D[3].re) / localB->absxk;
        }
      }

      D[3].re = localB->colnorm;
      D[3].im = localB->scale;
    }
  }
}

//
// Start for atomic system:
//    synthesized block
//    synthesized block
//
void modelModelClass::CoordinateTransformationC_Start
  (DW_CoordinateTransformationCo_T *localDW)
{
  // Start for MATLABSystem: '<S4>/Coordinate Transformation Conversion2'
  localDW->objisempty = true;
  localDW->obj.isInitialized = 1;
}

//
// Output and update for atomic system:
//    synthesized block
//    synthesized block
//
void modelModelClass::CoordinateTransformationConvers(const real_T rtu_0[16],
  B_CoordinateTransformationCon_T *localB)
{
  boolean_T exitg1;

  // MATLABSystem: '<S4>/Coordinate Transformation Conversion2'
  localB->K12 = rtu_0[4] + rtu_0[1];
  localB->K13 = rtu_0[8] + rtu_0[2];
  localB->K14 = rtu_0[6] - rtu_0[9];
  localB->K23 = rtu_0[9] + rtu_0[6];
  localB->K24 = rtu_0[8] - rtu_0[2];
  localB->K34 = rtu_0[1] - rtu_0[4];
  localB->rtu_0[0] = ((rtu_0[0] - rtu_0[5]) - rtu_0[10]) / 3.0;
  localB->rtu_0[4] = localB->K12 / 3.0;
  localB->rtu_0[8] = localB->K13 / 3.0;
  localB->rtu_0[12] = localB->K14 / 3.0;
  localB->rtu_0[1] = localB->K12 / 3.0;
  localB->rtu_0[5] = ((rtu_0[5] - rtu_0[0]) - rtu_0[10]) / 3.0;
  localB->rtu_0[9] = localB->K23 / 3.0;
  localB->rtu_0[13] = localB->K24 / 3.0;
  localB->rtu_0[2] = localB->K13 / 3.0;
  localB->rtu_0[6] = localB->K23 / 3.0;
  localB->rtu_0[10] = ((rtu_0[10] - rtu_0[0]) - rtu_0[5]) / 3.0;
  localB->rtu_0[14] = localB->K34 / 3.0;
  localB->rtu_0[3] = localB->K14 / 3.0;
  localB->rtu_0[7] = localB->K24 / 3.0;
  localB->rtu_0[11] = localB->K34 / 3.0;
  localB->rtu_0[15] = ((rtu_0[0] + rtu_0[5]) + rtu_0[10]) / 3.0;
  CartesianImpedance_Task_eig(localB->rtu_0, localB->eigVec, localB->eigVal,
    localB);
  localB->varargin_1[0] = localB->eigVal[0].re;
  localB->varargin_1[1] = localB->eigVal[1].re;
  localB->varargin_1[2] = localB->eigVal[2].re;
  localB->varargin_1[3] = localB->eigVal[3].re;
  if (!rtIsNaN(localB->eigVal[0].re)) {
    localB->b_idx = 1;
  } else {
    localB->b_idx = 0;
    localB->k = 2;
    exitg1 = false;
    while ((!exitg1) && (localB->k < 5)) {
      if (!rtIsNaN(localB->varargin_1[localB->k - 1])) {
        localB->b_idx = localB->k;
        exitg1 = true;
      } else {
        localB->k++;
      }
    }
  }

  if (localB->b_idx != 0) {
    localB->K12 = localB->varargin_1[localB->b_idx - 1];
    localB->b_idx_d = localB->b_idx;
    for (localB->k = localB->b_idx + 1; localB->k < 5; localB->k++) {
      localB->K13 = localB->varargin_1[localB->k - 1];
      if (localB->K12 < localB->K13) {
        localB->K12 = localB->K13;
        localB->b_idx_d = localB->k;
      }
    }

    localB->b_idx = localB->b_idx_d - 1;
  }

  localB->b_idx <<= 2;
  localB->CoordinateTransformationConve_i[0] = localB->eigVec[localB->b_idx + 3]
    .re;
  localB->CoordinateTransformationConve_i[1] = localB->eigVec[localB->b_idx].re;
  localB->CoordinateTransformationConve_i[2] = localB->eigVec[localB->b_idx + 1]
    .re;
  localB->CoordinateTransformationConve_i[3] = localB->eigVec[localB->b_idx + 2]
    .re;
  if (localB->CoordinateTransformationConve_i[0] < 0.0) {
    localB->CoordinateTransformationConve_i[0] =
      -localB->CoordinateTransformationConve_i[0];
    localB->CoordinateTransformationConve_i[1] =
      -localB->CoordinateTransformationConve_i[1];
    localB->CoordinateTransformationConve_i[2] =
      -localB->CoordinateTransformationConve_i[2];
    localB->CoordinateTransformationConve_i[3] =
      -localB->CoordinateTransformationConve_i[3];
  }

  // End of MATLABSystem: '<S4>/Coordinate Transformation Conversion2'
}

// Function for MATLAB Function: '<Root>/M_PINV1'
boolean_T modelModelClass::CartesianImpedance_anyNonFinite(const real_T x[36])
{
  CartesianImpedance_Task_B.b_p = true;
  for (CartesianImpedance_Task_B.k_l = 0; CartesianImpedance_Task_B.k_l < 36;
       CartesianImpedance_Task_B.k_l++) {
    if (CartesianImpedance_Task_B.b_p && (rtIsInf
         (x[CartesianImpedance_Task_B.k_l]) || rtIsNaN
         (x[CartesianImpedance_Task_B.k_l]))) {
      CartesianImpedance_Task_B.b_p = false;
    }
  }

  return !CartesianImpedance_Task_B.b_p;
}

// Function for MATLAB Function: '<Root>/D1'
real_T modelModelClass::CartesianImpedance_Task_xnrm2_g(int32_T n, const real_T
  x[36], int32_T ix0)
{
  real_T y;
  y = 0.0;
  CartesianImpedance_Task_B.scale_h = 3.3121686421112381E-170;
  CartesianImpedance_Task_B.kend_o = (ix0 + n) - 1;
  CartesianImpedance_Task_B.k_o = ix0;
  while (CartesianImpedance_Task_B.k_o <= CartesianImpedance_Task_B.kend_o) {
    CartesianImpedance_Task_B.absxk_c = std::abs(x[CartesianImpedance_Task_B.k_o
      - 1]);
    if (CartesianImpedance_Task_B.absxk_c > CartesianImpedance_Task_B.scale_h) {
      CartesianImpedance_Task_B.t_c = CartesianImpedance_Task_B.scale_h /
        CartesianImpedance_Task_B.absxk_c;
      y = y * CartesianImpedance_Task_B.t_c * CartesianImpedance_Task_B.t_c +
        1.0;
      CartesianImpedance_Task_B.scale_h = CartesianImpedance_Task_B.absxk_c;
    } else {
      CartesianImpedance_Task_B.t_c = CartesianImpedance_Task_B.absxk_c /
        CartesianImpedance_Task_B.scale_h;
      y += CartesianImpedance_Task_B.t_c * CartesianImpedance_Task_B.t_c;
    }

    CartesianImpedance_Task_B.k_o++;
  }

  return CartesianImpedance_Task_B.scale_h * std::sqrt(y);
}

// Function for MATLAB Function: '<Root>/D1'
real_T modelModelClass::CartesianImpedance_Tas_xnrm2_gh(int32_T n, const real_T
  x[6], int32_T ix0)
{
  real_T y;
  y = 0.0;
  CartesianImpedance_Task_B.scale_a = 3.3121686421112381E-170;
  CartesianImpedance_Task_B.kend = (ix0 + n) - 1;
  CartesianImpedance_Task_B.k = ix0;
  while (CartesianImpedance_Task_B.k <= CartesianImpedance_Task_B.kend) {
    CartesianImpedance_Task_B.absxk = std::abs(x[CartesianImpedance_Task_B.k - 1]);
    if (CartesianImpedance_Task_B.absxk > CartesianImpedance_Task_B.scale_a) {
      CartesianImpedance_Task_B.t = CartesianImpedance_Task_B.scale_a /
        CartesianImpedance_Task_B.absxk;
      y = y * CartesianImpedance_Task_B.t * CartesianImpedance_Task_B.t + 1.0;
      CartesianImpedance_Task_B.scale_a = CartesianImpedance_Task_B.absxk;
    } else {
      CartesianImpedance_Task_B.t = CartesianImpedance_Task_B.absxk /
        CartesianImpedance_Task_B.scale_a;
      y += CartesianImpedance_Task_B.t * CartesianImpedance_Task_B.t;
    }

    CartesianImpedance_Task_B.k++;
  }

  return CartesianImpedance_Task_B.scale_a * std::sqrt(y);
}

// Function for MATLAB Function: '<Root>/D1'
void modelModelClass::CartesianImpedance_Tas_xaxpy_ag(int32_T n, real_T a, const
  real_T x[6], int32_T ix0, real_T y[36], int32_T iy0)
{
  if (!(a == 0.0)) {
    CartesianImpedance_Task_B.ix_e = ix0 - 1;
    CartesianImpedance_Task_B.iy_o = iy0 - 1;
    CartesianImpedance_Task_B.k_h = 0;
    while (CartesianImpedance_Task_B.k_h <= n - 1) {
      y[CartesianImpedance_Task_B.iy_o] += a * x[CartesianImpedance_Task_B.ix_e];
      CartesianImpedance_Task_B.ix_e++;
      CartesianImpedance_Task_B.iy_o++;
      CartesianImpedance_Task_B.k_h++;
    }
  }
}

// Function for MATLAB Function: '<Root>/D1'
void modelModelClass::CartesianImpedance_Task_xaxpy_a(int32_T n, real_T a, const
  real_T x[36], int32_T ix0, real_T y[6], int32_T iy0)
{
  if (!(a == 0.0)) {
    CartesianImpedance_Task_B.ix_c = ix0 - 1;
    CartesianImpedance_Task_B.iy_f = iy0 - 1;
    CartesianImpedance_Task_B.k_p = 0;
    while (CartesianImpedance_Task_B.k_p <= n - 1) {
      y[CartesianImpedance_Task_B.iy_f] += a * x[CartesianImpedance_Task_B.ix_c];
      CartesianImpedance_Task_B.ix_c++;
      CartesianImpedance_Task_B.iy_f++;
      CartesianImpedance_Task_B.k_p++;
    }
  }
}

// Function for MATLAB Function: '<Root>/D1'
real_T modelModelClass::CartesianImpedance_Task_xdotc(int32_T n, const real_T x
  [36], int32_T ix0, const real_T y[36], int32_T iy0)
{
  real_T d;
  d = 0.0;
  CartesianImpedance_Task_B.ix_l = ix0;
  CartesianImpedance_Task_B.iy_m = iy0;
  CartesianImpedance_Task_B.k_m = 0;
  while (CartesianImpedance_Task_B.k_m <= n - 1) {
    d += x[CartesianImpedance_Task_B.ix_l - 1] *
      y[CartesianImpedance_Task_B.iy_m - 1];
    CartesianImpedance_Task_B.ix_l++;
    CartesianImpedance_Task_B.iy_m++;
    CartesianImpedance_Task_B.k_m++;
  }

  return d;
}

// Function for MATLAB Function: '<Root>/D1'
void modelModelClass::CartesianImpedance_Task_xaxpy(int32_T n, real_T a, int32_T
  ix0, real_T y[36], int32_T iy0)
{
  if (!(a == 0.0)) {
    CartesianImpedance_Task_B.ix_g = ix0 - 1;
    CartesianImpedance_Task_B.iy_c = iy0 - 1;
    CartesianImpedance_Task_B.k_o3 = 0;
    while (CartesianImpedance_Task_B.k_o3 <= n - 1) {
      y[CartesianImpedance_Task_B.iy_c] += a * y[CartesianImpedance_Task_B.ix_g];
      CartesianImpedance_Task_B.ix_g++;
      CartesianImpedance_Task_B.iy_c++;
      CartesianImpedance_Task_B.k_o3++;
    }
  }
}

// Function for MATLAB Function: '<Root>/D1'
void modelModelClass::CartesianImpedance_Task_xscal(real_T a, real_T x[36],
  int32_T ix0)
{
  CartesianImpedance_Task_B.k_h2 = ix0;
  while (CartesianImpedance_Task_B.k_h2 <= ix0 + 5) {
    x[CartesianImpedance_Task_B.k_h2 - 1] *= a;
    CartesianImpedance_Task_B.k_h2++;
  }
}

// Function for MATLAB Function: '<Root>/D1'
void modelModelClass::CartesianImpedance_Task_xswap(real_T x[36], int32_T ix0,
  int32_T iy0)
{
  CartesianImpedance_Task_B.ix_f = ix0 - 1;
  CartesianImpedance_Task_B.iy_i = iy0 - 1;
  for (CartesianImpedance_Task_B.k_f = 0; CartesianImpedance_Task_B.k_f < 6;
       CartesianImpedance_Task_B.k_f++) {
    CartesianImpedance_Task_B.temp_p = x[CartesianImpedance_Task_B.ix_f];
    x[CartesianImpedance_Task_B.ix_f] = x[CartesianImpedance_Task_B.iy_i];
    x[CartesianImpedance_Task_B.iy_i] = CartesianImpedance_Task_B.temp_p;
    CartesianImpedance_Task_B.ix_f++;
    CartesianImpedance_Task_B.iy_i++;
  }
}

// Function for MATLAB Function: '<Root>/D1'
void modelModelClass::CartesianImpedance_Task_xrotg(real_T *a, real_T *b, real_T
  *c, real_T *s)
{
  CartesianImpedance_Task_B.roe = *b;
  CartesianImpedance_Task_B.absa = std::abs(*a);
  CartesianImpedance_Task_B.absb = std::abs(*b);
  if (CartesianImpedance_Task_B.absa > CartesianImpedance_Task_B.absb) {
    CartesianImpedance_Task_B.roe = *a;
  }

  CartesianImpedance_Task_B.scale = CartesianImpedance_Task_B.absa +
    CartesianImpedance_Task_B.absb;
  if (CartesianImpedance_Task_B.scale == 0.0) {
    *s = 0.0;
    *c = 1.0;
    CartesianImpedance_Task_B.scale = 0.0;
    *b = 0.0;
  } else {
    CartesianImpedance_Task_B.ads = CartesianImpedance_Task_B.absa /
      CartesianImpedance_Task_B.scale;
    CartesianImpedance_Task_B.bds = CartesianImpedance_Task_B.absb /
      CartesianImpedance_Task_B.scale;
    CartesianImpedance_Task_B.scale *= std::sqrt(CartesianImpedance_Task_B.ads *
      CartesianImpedance_Task_B.ads + CartesianImpedance_Task_B.bds *
      CartesianImpedance_Task_B.bds);
    if (CartesianImpedance_Task_B.roe < 0.0) {
      CartesianImpedance_Task_B.scale = -CartesianImpedance_Task_B.scale;
    }

    *c = *a / CartesianImpedance_Task_B.scale;
    *s = *b / CartesianImpedance_Task_B.scale;
    if (CartesianImpedance_Task_B.absa > CartesianImpedance_Task_B.absb) {
      *b = *s;
    } else if (*c != 0.0) {
      *b = 1.0 / *c;
    } else {
      *b = 1.0;
    }
  }

  *a = CartesianImpedance_Task_B.scale;
}

// Function for MATLAB Function: '<Root>/D1'
void modelModelClass::CartesianImpedance_Task_xrot_i(real_T x[36], int32_T ix0,
  int32_T iy0, real_T c, real_T s)
{
  CartesianImpedance_Task_B.ix = ix0 - 1;
  CartesianImpedance_Task_B.iy = iy0 - 1;
  for (CartesianImpedance_Task_B.k_i = 0; CartesianImpedance_Task_B.k_i < 6;
       CartesianImpedance_Task_B.k_i++) {
    CartesianImpedance_Task_B.temp = c * x[CartesianImpedance_Task_B.ix] + s *
      x[CartesianImpedance_Task_B.iy];
    x[CartesianImpedance_Task_B.iy] = c * x[CartesianImpedance_Task_B.iy] - s *
      x[CartesianImpedance_Task_B.ix];
    x[CartesianImpedance_Task_B.ix] = CartesianImpedance_Task_B.temp;
    CartesianImpedance_Task_B.iy++;
    CartesianImpedance_Task_B.ix++;
  }
}

// Function for MATLAB Function: '<Root>/D1'
void modelModelClass::CartesianImpedance_Task_svd_b(const real_T A[36], real_T
  U[36], real_T s[6], real_T V[36])
{
  boolean_T exitg1;
  std::memcpy(&CartesianImpedance_Task_B.b_A_k[0], &A[0], 36U * sizeof(real_T));
  for (CartesianImpedance_Task_B.i_l = 0; CartesianImpedance_Task_B.i_l < 6;
       CartesianImpedance_Task_B.i_l++) {
    CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l] = 0.0;
    CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l] = 0.0;
    CartesianImpedance_Task_B.work_l[CartesianImpedance_Task_B.i_l] = 0.0;
  }

  std::memset(&U[0], 0, 36U * sizeof(real_T));
  std::memset(&V[0], 0, 36U * sizeof(real_T));
  for (CartesianImpedance_Task_B.i_l = 0; CartesianImpedance_Task_B.i_l < 5;
       CartesianImpedance_Task_B.i_l++) {
    CartesianImpedance_Task_B.qq_e = 6 * CartesianImpedance_Task_B.i_l +
      CartesianImpedance_Task_B.i_l;
    CartesianImpedance_Task_B.apply_transform_m = false;
    CartesianImpedance_Task_B.nrm_h = CartesianImpedance_Task_xnrm2_g(6 -
      CartesianImpedance_Task_B.i_l, CartesianImpedance_Task_B.b_A_k,
      CartesianImpedance_Task_B.qq_e + 1);
    if (CartesianImpedance_Task_B.nrm_h > 0.0) {
      CartesianImpedance_Task_B.apply_transform_m = true;
      if (CartesianImpedance_Task_B.b_A_k[CartesianImpedance_Task_B.qq_e] < 0.0)
      {
        CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l] =
          -CartesianImpedance_Task_B.nrm_h;
      } else {
        CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l] =
          CartesianImpedance_Task_B.nrm_h;
      }

      if (std::abs(CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l])
          >= 1.0020841800044864E-292) {
        CartesianImpedance_Task_B.nrm_h = 1.0 /
          CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l];
        CartesianImpedance_Task_B.qp1q_i = (CartesianImpedance_Task_B.qq_e -
          CartesianImpedance_Task_B.i_l) + 6;
        CartesianImpedance_Task_B.qjj_a = CartesianImpedance_Task_B.qq_e;
        while (CartesianImpedance_Task_B.qjj_a + 1 <=
               CartesianImpedance_Task_B.qp1q_i) {
          CartesianImpedance_Task_B.b_A_k[CartesianImpedance_Task_B.qjj_a] *=
            CartesianImpedance_Task_B.nrm_h;
          CartesianImpedance_Task_B.qjj_a++;
        }
      } else {
        CartesianImpedance_Task_B.qp1q_i = (CartesianImpedance_Task_B.qq_e -
          CartesianImpedance_Task_B.i_l) + 6;
        CartesianImpedance_Task_B.qjj_a = CartesianImpedance_Task_B.qq_e;
        while (CartesianImpedance_Task_B.qjj_a + 1 <=
               CartesianImpedance_Task_B.qp1q_i) {
          CartesianImpedance_Task_B.b_A_k[CartesianImpedance_Task_B.qjj_a] /=
            CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l];
          CartesianImpedance_Task_B.qjj_a++;
        }
      }

      CartesianImpedance_Task_B.b_A_k[CartesianImpedance_Task_B.qq_e]++;
      CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l] =
        -CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l];
    } else {
      CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l] = 0.0;
    }

    CartesianImpedance_Task_B.qp1q_i = CartesianImpedance_Task_B.i_l + 1;
    while (CartesianImpedance_Task_B.qp1q_i + 1 < 7) {
      CartesianImpedance_Task_B.qjj_a = 6 * CartesianImpedance_Task_B.qp1q_i +
        CartesianImpedance_Task_B.i_l;
      if (CartesianImpedance_Task_B.apply_transform_m) {
        CartesianImpedance_Task_xaxpy(6 - CartesianImpedance_Task_B.i_l,
          -(CartesianImpedance_Task_xdotc(6 - CartesianImpedance_Task_B.i_l,
          CartesianImpedance_Task_B.b_A_k, CartesianImpedance_Task_B.qq_e + 1,
          CartesianImpedance_Task_B.b_A_k, CartesianImpedance_Task_B.qjj_a + 1) /
            CartesianImpedance_Task_B.b_A_k[CartesianImpedance_Task_B.i_l + 6 *
            CartesianImpedance_Task_B.i_l]), CartesianImpedance_Task_B.qq_e + 1,
          CartesianImpedance_Task_B.b_A_k, CartesianImpedance_Task_B.qjj_a + 1);
      }

      CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qp1q_i] =
        CartesianImpedance_Task_B.b_A_k[CartesianImpedance_Task_B.qjj_a];
      CartesianImpedance_Task_B.qp1q_i++;
    }

    CartesianImpedance_Task_B.qq_e = CartesianImpedance_Task_B.i_l;
    while (CartesianImpedance_Task_B.qq_e + 1 < 7) {
      U[CartesianImpedance_Task_B.qq_e + 6 * CartesianImpedance_Task_B.i_l] =
        CartesianImpedance_Task_B.b_A_k[6 * CartesianImpedance_Task_B.i_l +
        CartesianImpedance_Task_B.qq_e];
      CartesianImpedance_Task_B.qq_e++;
    }

    if (CartesianImpedance_Task_B.i_l + 1 <= 4) {
      CartesianImpedance_Task_B.nrm_h = CartesianImpedance_Tas_xnrm2_gh(5 -
        CartesianImpedance_Task_B.i_l, CartesianImpedance_Task_B.e_p,
        CartesianImpedance_Task_B.i_l + 2);
      if (CartesianImpedance_Task_B.nrm_h == 0.0) {
        CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l] = 0.0;
      } else {
        if (CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l + 1] <
            0.0) {
          CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l] =
            -CartesianImpedance_Task_B.nrm_h;
        } else {
          CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l] =
            CartesianImpedance_Task_B.nrm_h;
        }

        CartesianImpedance_Task_B.nrm_h =
          CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l];
        if (std::abs(CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l])
            >= 1.0020841800044864E-292) {
          CartesianImpedance_Task_B.nrm_h = 1.0 /
            CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l];
          CartesianImpedance_Task_B.qq_e = CartesianImpedance_Task_B.i_l + 1;
          while (CartesianImpedance_Task_B.qq_e + 1 <= 6) {
            CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qq_e] *=
              CartesianImpedance_Task_B.nrm_h;
            CartesianImpedance_Task_B.qq_e++;
          }
        } else {
          CartesianImpedance_Task_B.qq_e = CartesianImpedance_Task_B.i_l + 1;
          while (CartesianImpedance_Task_B.qq_e + 1 <= 6) {
            CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qq_e] /=
              CartesianImpedance_Task_B.nrm_h;
            CartesianImpedance_Task_B.qq_e++;
          }
        }

        CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l + 1]++;
        CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l] =
          -CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l];
        CartesianImpedance_Task_B.qq_e = CartesianImpedance_Task_B.i_l + 1;
        while (CartesianImpedance_Task_B.qq_e + 1 < 7) {
          CartesianImpedance_Task_B.work_l[CartesianImpedance_Task_B.qq_e] = 0.0;
          CartesianImpedance_Task_B.qq_e++;
        }

        CartesianImpedance_Task_B.qq_e = CartesianImpedance_Task_B.i_l + 1;
        while (CartesianImpedance_Task_B.qq_e + 1 < 7) {
          CartesianImpedance_Task_xaxpy_a(5 - CartesianImpedance_Task_B.i_l,
            CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qq_e],
            CartesianImpedance_Task_B.b_A_k, (CartesianImpedance_Task_B.i_l + 6 *
            CartesianImpedance_Task_B.qq_e) + 2,
            CartesianImpedance_Task_B.work_l, CartesianImpedance_Task_B.i_l + 2);
          CartesianImpedance_Task_B.qq_e++;
        }

        CartesianImpedance_Task_B.qq_e = CartesianImpedance_Task_B.i_l + 1;
        while (CartesianImpedance_Task_B.qq_e + 1 < 7) {
          CartesianImpedance_Tas_xaxpy_ag(5 - CartesianImpedance_Task_B.i_l,
            -CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qq_e] /
            CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l + 1],
            CartesianImpedance_Task_B.work_l, CartesianImpedance_Task_B.i_l + 2,
            CartesianImpedance_Task_B.b_A_k, (CartesianImpedance_Task_B.i_l + 6 *
            CartesianImpedance_Task_B.qq_e) + 2);
          CartesianImpedance_Task_B.qq_e++;
        }
      }

      CartesianImpedance_Task_B.qq_e = CartesianImpedance_Task_B.i_l + 1;
      while (CartesianImpedance_Task_B.qq_e + 1 < 7) {
        V[CartesianImpedance_Task_B.qq_e + 6 * CartesianImpedance_Task_B.i_l] =
          CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qq_e];
        CartesianImpedance_Task_B.qq_e++;
      }
    }
  }

  CartesianImpedance_Task_B.i_l = 4;
  CartesianImpedance_Task_B.b_s_n[5] = CartesianImpedance_Task_B.b_A_k[35];
  CartesianImpedance_Task_B.e_p[4] = CartesianImpedance_Task_B.b_A_k[34];
  CartesianImpedance_Task_B.e_p[5] = 0.0;
  for (CartesianImpedance_Task_B.qq_e = 0; CartesianImpedance_Task_B.qq_e < 6;
       CartesianImpedance_Task_B.qq_e++) {
    U[CartesianImpedance_Task_B.qq_e + 30] = 0.0;
  }

  U[35] = 1.0;
  for (CartesianImpedance_Task_B.qp1q_i = 4; CartesianImpedance_Task_B.qp1q_i >=
       0; CartesianImpedance_Task_B.qp1q_i--) {
    CartesianImpedance_Task_B.qq_e = 6 * CartesianImpedance_Task_B.qp1q_i +
      CartesianImpedance_Task_B.qp1q_i;
    if (CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1q_i] != 0.0)
    {
      CartesianImpedance_Task_B.qp1jj_a = CartesianImpedance_Task_B.qp1q_i + 1;
      while (CartesianImpedance_Task_B.qp1jj_a + 1 < 7) {
        CartesianImpedance_Task_B.qjj_a = (6 * CartesianImpedance_Task_B.qp1jj_a
          + CartesianImpedance_Task_B.qp1q_i) + 1;
        CartesianImpedance_Task_xaxpy(6 - CartesianImpedance_Task_B.qp1q_i,
          -(CartesianImpedance_Task_xdotc(6 - CartesianImpedance_Task_B.qp1q_i,
          U, CartesianImpedance_Task_B.qq_e + 1, U,
          CartesianImpedance_Task_B.qjj_a) / U[CartesianImpedance_Task_B.qq_e]),
          CartesianImpedance_Task_B.qq_e + 1, U, CartesianImpedance_Task_B.qjj_a);
        CartesianImpedance_Task_B.qp1jj_a++;
      }

      CartesianImpedance_Task_B.qjj_a = CartesianImpedance_Task_B.qp1q_i;
      while (CartesianImpedance_Task_B.qjj_a + 1 < 7) {
        CartesianImpedance_Task_B.qp1jj_a = 6 * CartesianImpedance_Task_B.qp1q_i
          + CartesianImpedance_Task_B.qjj_a;
        U[CartesianImpedance_Task_B.qp1jj_a] =
          -U[CartesianImpedance_Task_B.qp1jj_a];
        CartesianImpedance_Task_B.qjj_a++;
      }

      U[CartesianImpedance_Task_B.qq_e]++;
      CartesianImpedance_Task_B.qq_e = 0;
      while (CartesianImpedance_Task_B.qq_e <= CartesianImpedance_Task_B.qp1q_i
             - 1) {
        U[CartesianImpedance_Task_B.qq_e + 6 * CartesianImpedance_Task_B.qp1q_i]
          = 0.0;
        CartesianImpedance_Task_B.qq_e++;
      }
    } else {
      for (CartesianImpedance_Task_B.qjj_a = 0; CartesianImpedance_Task_B.qjj_a <
           6; CartesianImpedance_Task_B.qjj_a++) {
        U[CartesianImpedance_Task_B.qjj_a + 6 * CartesianImpedance_Task_B.qp1q_i]
          = 0.0;
      }

      U[CartesianImpedance_Task_B.qq_e] = 1.0;
    }
  }

  for (CartesianImpedance_Task_B.qq_e = 5; CartesianImpedance_Task_B.qq_e >= 0;
       CartesianImpedance_Task_B.qq_e--) {
    if ((CartesianImpedance_Task_B.qq_e + 1 <= 4) &&
        (CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qq_e] != 0.0))
    {
      CartesianImpedance_Task_B.qp1q_i = (6 * CartesianImpedance_Task_B.qq_e +
        CartesianImpedance_Task_B.qq_e) + 2;
      CartesianImpedance_Task_B.qjj_a = CartesianImpedance_Task_B.qq_e + 1;
      while (CartesianImpedance_Task_B.qjj_a + 1 < 7) {
        CartesianImpedance_Task_B.qp1jj_a = (6 * CartesianImpedance_Task_B.qjj_a
          + CartesianImpedance_Task_B.qq_e) + 2;
        CartesianImpedance_Task_xaxpy(5 - CartesianImpedance_Task_B.qq_e,
          -(CartesianImpedance_Task_xdotc(5 - CartesianImpedance_Task_B.qq_e, V,
          CartesianImpedance_Task_B.qp1q_i, V, CartesianImpedance_Task_B.qp1jj_a)
            / V[CartesianImpedance_Task_B.qp1q_i - 1]),
          CartesianImpedance_Task_B.qp1q_i, V, CartesianImpedance_Task_B.qp1jj_a);
        CartesianImpedance_Task_B.qjj_a++;
      }
    }

    for (CartesianImpedance_Task_B.qp1q_i = 0; CartesianImpedance_Task_B.qp1q_i <
         6; CartesianImpedance_Task_B.qp1q_i++) {
      V[CartesianImpedance_Task_B.qp1q_i + 6 * CartesianImpedance_Task_B.qq_e] =
        0.0;
    }

    V[CartesianImpedance_Task_B.qq_e + 6 * CartesianImpedance_Task_B.qq_e] = 1.0;
  }

  for (CartesianImpedance_Task_B.qq_e = 0; CartesianImpedance_Task_B.qq_e < 6;
       CartesianImpedance_Task_B.qq_e++) {
    CartesianImpedance_Task_B.nrm_h =
      CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qq_e];
    if (CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qq_e] != 0.0)
    {
      CartesianImpedance_Task_B.rt_b = std::abs
        (CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qq_e]);
      CartesianImpedance_Task_B.r_d =
        CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qq_e] /
        CartesianImpedance_Task_B.rt_b;
      CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qq_e] =
        CartesianImpedance_Task_B.rt_b;
      if (CartesianImpedance_Task_B.qq_e + 1 < 6) {
        CartesianImpedance_Task_B.nrm_h =
          CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qq_e] /
          CartesianImpedance_Task_B.r_d;
      }

      CartesianImpedance_Task_xscal(CartesianImpedance_Task_B.r_d, U, 6 *
        CartesianImpedance_Task_B.qq_e + 1);
    }

    if ((CartesianImpedance_Task_B.qq_e + 1 < 6) &&
        (CartesianImpedance_Task_B.nrm_h != 0.0)) {
      CartesianImpedance_Task_B.rt_b = std::abs(CartesianImpedance_Task_B.nrm_h);
      CartesianImpedance_Task_B.r_d = CartesianImpedance_Task_B.rt_b /
        CartesianImpedance_Task_B.nrm_h;
      CartesianImpedance_Task_B.nrm_h = CartesianImpedance_Task_B.rt_b;
      CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qq_e + 1] *=
        CartesianImpedance_Task_B.r_d;
      CartesianImpedance_Task_xscal(CartesianImpedance_Task_B.r_d, V, 6 *
        (CartesianImpedance_Task_B.qq_e + 1) + 1);
    }

    CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qq_e] =
      CartesianImpedance_Task_B.nrm_h;
  }

  CartesianImpedance_Task_B.qq_e = 0;
  CartesianImpedance_Task_B.nrm_h = 0.0;
  for (CartesianImpedance_Task_B.qp1q_i = 0; CartesianImpedance_Task_B.qp1q_i <
       6; CartesianImpedance_Task_B.qp1q_i++) {
    CartesianImpedance_Task_B.r_d = std::abs
      (CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1q_i]);
    CartesianImpedance_Task_B.rt_b = std::abs
      (CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qp1q_i]);
    if ((CartesianImpedance_Task_B.r_d > CartesianImpedance_Task_B.rt_b) ||
        rtIsNaN(CartesianImpedance_Task_B.rt_b)) {
      CartesianImpedance_Task_B.rt_b = CartesianImpedance_Task_B.r_d;
    }

    if ((!(CartesianImpedance_Task_B.nrm_h > CartesianImpedance_Task_B.rt_b)) &&
        (!rtIsNaN(CartesianImpedance_Task_B.rt_b))) {
      CartesianImpedance_Task_B.nrm_h = CartesianImpedance_Task_B.rt_b;
    }
  }

  while ((CartesianImpedance_Task_B.i_l + 2 > 0) &&
         (CartesianImpedance_Task_B.qq_e < 75)) {
    CartesianImpedance_Task_B.qp1q_i = CartesianImpedance_Task_B.i_l + 1;
    exitg1 = false;
    while (!(exitg1 || (CartesianImpedance_Task_B.qp1q_i == 0))) {
      CartesianImpedance_Task_B.rt_b = std::abs
        (CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qp1q_i - 1]);
      if (CartesianImpedance_Task_B.rt_b <= (std::abs
           (CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1q_i - 1])
           + std::abs
           (CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1q_i])) *
          2.2204460492503131E-16) {
        CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qp1q_i - 1] =
          0.0;
        exitg1 = true;
      } else if ((CartesianImpedance_Task_B.rt_b <= 1.0020841800044864E-292) ||
                 ((CartesianImpedance_Task_B.qq_e > 20) &&
                  (CartesianImpedance_Task_B.rt_b <= 2.2204460492503131E-16 *
                   CartesianImpedance_Task_B.nrm_h))) {
        CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qp1q_i - 1] =
          0.0;
        exitg1 = true;
      } else {
        CartesianImpedance_Task_B.qp1q_i--;
      }
    }

    if (CartesianImpedance_Task_B.i_l + 1 == CartesianImpedance_Task_B.qp1q_i) {
      CartesianImpedance_Task_B.qp1jj_a = 4;
    } else {
      CartesianImpedance_Task_B.qjj_a = CartesianImpedance_Task_B.i_l + 2;
      CartesianImpedance_Task_B.qp1jj_a = CartesianImpedance_Task_B.i_l + 2;
      exitg1 = false;
      while ((!exitg1) && (CartesianImpedance_Task_B.qp1jj_a >=
                           CartesianImpedance_Task_B.qp1q_i)) {
        CartesianImpedance_Task_B.qjj_a = CartesianImpedance_Task_B.qp1jj_a;
        if (CartesianImpedance_Task_B.qp1jj_a ==
            CartesianImpedance_Task_B.qp1q_i) {
          exitg1 = true;
        } else {
          CartesianImpedance_Task_B.rt_b = 0.0;
          if (CartesianImpedance_Task_B.qp1jj_a < CartesianImpedance_Task_B.i_l
              + 2) {
            CartesianImpedance_Task_B.rt_b = std::abs
              (CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qp1jj_a -
               1]);
          }

          if (CartesianImpedance_Task_B.qp1jj_a >
              CartesianImpedance_Task_B.qp1q_i + 1) {
            CartesianImpedance_Task_B.rt_b += std::abs
              (CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qp1jj_a -
               2]);
          }

          CartesianImpedance_Task_B.r_d = std::abs
            (CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1jj_a -
             1]);
          if ((CartesianImpedance_Task_B.r_d <= 2.2204460492503131E-16 *
               CartesianImpedance_Task_B.rt_b) || (CartesianImpedance_Task_B.r_d
               <= 1.0020841800044864E-292)) {
            CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1jj_a -
              1] = 0.0;
            exitg1 = true;
          } else {
            CartesianImpedance_Task_B.qp1jj_a--;
          }
        }
      }

      if (CartesianImpedance_Task_B.qjj_a == CartesianImpedance_Task_B.qp1q_i) {
        CartesianImpedance_Task_B.qp1jj_a = 3;
      } else if (CartesianImpedance_Task_B.i_l + 2 ==
                 CartesianImpedance_Task_B.qjj_a) {
        CartesianImpedance_Task_B.qp1jj_a = 1;
      } else {
        CartesianImpedance_Task_B.qp1jj_a = 2;
        CartesianImpedance_Task_B.qp1q_i = CartesianImpedance_Task_B.qjj_a;
      }
    }

    switch (CartesianImpedance_Task_B.qp1jj_a) {
     case 1:
      CartesianImpedance_Task_B.rt_b =
        CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l];
      CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l] = 0.0;
      CartesianImpedance_Task_B.qjj_a = CartesianImpedance_Task_B.i_l;
      while (CartesianImpedance_Task_B.qjj_a + 1 >=
             CartesianImpedance_Task_B.qp1q_i + 1) {
        CartesianImpedance_Task_xrotg
          (&CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qjj_a],
           &CartesianImpedance_Task_B.rt_b, &CartesianImpedance_Task_B.r_d,
           &CartesianImpedance_Task_B.sqds_j);
        if (CartesianImpedance_Task_B.qjj_a + 1 >
            CartesianImpedance_Task_B.qp1q_i + 1) {
          CartesianImpedance_Task_B.smm1_e =
            CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qjj_a - 1];
          CartesianImpedance_Task_B.rt_b = CartesianImpedance_Task_B.smm1_e *
            -CartesianImpedance_Task_B.sqds_j;
          CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qjj_a - 1] =
            CartesianImpedance_Task_B.smm1_e * CartesianImpedance_Task_B.r_d;
        }

        CartesianImpedance_Task_xrot_i(V, 6 * CartesianImpedance_Task_B.qjj_a +
          1, 6 * (CartesianImpedance_Task_B.i_l + 1) + 1,
          CartesianImpedance_Task_B.r_d, CartesianImpedance_Task_B.sqds_j);
        CartesianImpedance_Task_B.qjj_a--;
      }
      break;

     case 2:
      CartesianImpedance_Task_B.rt_b =
        CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qp1q_i - 1];
      CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qp1q_i - 1] = 0.0;
      CartesianImpedance_Task_B.qjj_a = CartesianImpedance_Task_B.qp1q_i;
      while (CartesianImpedance_Task_B.qjj_a + 1 <=
             CartesianImpedance_Task_B.i_l + 2) {
        CartesianImpedance_Task_xrotg
          (&CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qjj_a],
           &CartesianImpedance_Task_B.rt_b, &CartesianImpedance_Task_B.r_d,
           &CartesianImpedance_Task_B.sqds_j);
        CartesianImpedance_Task_B.rt_b = -CartesianImpedance_Task_B.sqds_j *
          CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qjj_a];
        CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qjj_a] *=
          CartesianImpedance_Task_B.r_d;
        CartesianImpedance_Task_xrot_i(U, 6 * CartesianImpedance_Task_B.qjj_a +
          1, 6 * (CartesianImpedance_Task_B.qp1q_i - 1) + 1,
          CartesianImpedance_Task_B.r_d, CartesianImpedance_Task_B.sqds_j);
        CartesianImpedance_Task_B.qjj_a++;
      }
      break;

     case 3:
      CartesianImpedance_Task_B.sqds_j =
        CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l + 1];
      CartesianImpedance_Task_B.r_d = std::abs(CartesianImpedance_Task_B.sqds_j);
      CartesianImpedance_Task_B.rt_b = std::abs
        (CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l]);
      if ((CartesianImpedance_Task_B.r_d > CartesianImpedance_Task_B.rt_b) ||
          rtIsNaN(CartesianImpedance_Task_B.rt_b)) {
        CartesianImpedance_Task_B.rt_b = CartesianImpedance_Task_B.r_d;
      }

      CartesianImpedance_Task_B.r_d = std::abs
        (CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l]);
      if ((CartesianImpedance_Task_B.rt_b > CartesianImpedance_Task_B.r_d) ||
          rtIsNaN(CartesianImpedance_Task_B.r_d)) {
        CartesianImpedance_Task_B.r_d = CartesianImpedance_Task_B.rt_b;
      }

      CartesianImpedance_Task_B.rt_b = std::abs
        (CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1q_i]);
      if ((CartesianImpedance_Task_B.r_d > CartesianImpedance_Task_B.rt_b) ||
          rtIsNaN(CartesianImpedance_Task_B.rt_b)) {
        CartesianImpedance_Task_B.rt_b = CartesianImpedance_Task_B.r_d;
      }

      CartesianImpedance_Task_B.r_d = std::abs
        (CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qp1q_i]);
      if ((CartesianImpedance_Task_B.rt_b > CartesianImpedance_Task_B.r_d) ||
          rtIsNaN(CartesianImpedance_Task_B.r_d)) {
        CartesianImpedance_Task_B.r_d = CartesianImpedance_Task_B.rt_b;
      }

      CartesianImpedance_Task_B.rt_b = CartesianImpedance_Task_B.sqds_j /
        CartesianImpedance_Task_B.r_d;
      CartesianImpedance_Task_B.smm1_e =
        CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l] /
        CartesianImpedance_Task_B.r_d;
      CartesianImpedance_Task_B.emm1_bj =
        CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l] /
        CartesianImpedance_Task_B.r_d;
      CartesianImpedance_Task_B.sqds_j =
        CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1q_i] /
        CartesianImpedance_Task_B.r_d;
      CartesianImpedance_Task_B.smm1_e = ((CartesianImpedance_Task_B.smm1_e +
        CartesianImpedance_Task_B.rt_b) * (CartesianImpedance_Task_B.smm1_e -
        CartesianImpedance_Task_B.rt_b) + CartesianImpedance_Task_B.emm1_bj *
        CartesianImpedance_Task_B.emm1_bj) / 2.0;
      CartesianImpedance_Task_B.emm1_bj *= CartesianImpedance_Task_B.rt_b;
      CartesianImpedance_Task_B.emm1_bj *= CartesianImpedance_Task_B.emm1_bj;
      if ((CartesianImpedance_Task_B.smm1_e != 0.0) ||
          (CartesianImpedance_Task_B.emm1_bj != 0.0)) {
        CartesianImpedance_Task_B.shift_f = std::sqrt
          (CartesianImpedance_Task_B.smm1_e * CartesianImpedance_Task_B.smm1_e +
           CartesianImpedance_Task_B.emm1_bj);
        if (CartesianImpedance_Task_B.smm1_e < 0.0) {
          CartesianImpedance_Task_B.shift_f = -CartesianImpedance_Task_B.shift_f;
        }

        CartesianImpedance_Task_B.shift_f = CartesianImpedance_Task_B.emm1_bj /
          (CartesianImpedance_Task_B.smm1_e + CartesianImpedance_Task_B.shift_f);
      } else {
        CartesianImpedance_Task_B.shift_f = 0.0;
      }

      CartesianImpedance_Task_B.rt_b = (CartesianImpedance_Task_B.sqds_j +
        CartesianImpedance_Task_B.rt_b) * (CartesianImpedance_Task_B.sqds_j -
        CartesianImpedance_Task_B.rt_b) + CartesianImpedance_Task_B.shift_f;
      CartesianImpedance_Task_B.smm1_e =
        CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qp1q_i] /
        CartesianImpedance_Task_B.r_d * CartesianImpedance_Task_B.sqds_j;
      CartesianImpedance_Task_B.qjj_a = CartesianImpedance_Task_B.qp1q_i + 1;
      while (CartesianImpedance_Task_B.qjj_a <= CartesianImpedance_Task_B.i_l +
             1) {
        CartesianImpedance_Task_xrotg(&CartesianImpedance_Task_B.rt_b,
          &CartesianImpedance_Task_B.smm1_e, &CartesianImpedance_Task_B.r_d,
          &CartesianImpedance_Task_B.sqds_j);
        if (CartesianImpedance_Task_B.qjj_a > CartesianImpedance_Task_B.qp1q_i +
            1) {
          CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qjj_a - 2] =
            CartesianImpedance_Task_B.rt_b;
        }

        CartesianImpedance_Task_B.smm1_e =
          CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qjj_a - 1];
        CartesianImpedance_Task_B.emm1_bj =
          CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qjj_a - 1];
        CartesianImpedance_Task_B.rt_b = CartesianImpedance_Task_B.emm1_bj *
          CartesianImpedance_Task_B.r_d + CartesianImpedance_Task_B.smm1_e *
          CartesianImpedance_Task_B.sqds_j;
        CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qjj_a - 1] =
          CartesianImpedance_Task_B.smm1_e * CartesianImpedance_Task_B.r_d -
          CartesianImpedance_Task_B.emm1_bj * CartesianImpedance_Task_B.sqds_j;
        CartesianImpedance_Task_B.smm1_e = CartesianImpedance_Task_B.sqds_j *
          CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qjj_a];
        CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qjj_a] *=
          CartesianImpedance_Task_B.r_d;
        CartesianImpedance_Task_xrot_i(V, 6 * (CartesianImpedance_Task_B.qjj_a -
          1) + 1, 6 * CartesianImpedance_Task_B.qjj_a + 1,
          CartesianImpedance_Task_B.r_d, CartesianImpedance_Task_B.sqds_j);
        CartesianImpedance_Task_xrotg(&CartesianImpedance_Task_B.rt_b,
          &CartesianImpedance_Task_B.smm1_e, &CartesianImpedance_Task_B.r_d,
          &CartesianImpedance_Task_B.sqds_j);
        CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qjj_a - 1] =
          CartesianImpedance_Task_B.rt_b;
        CartesianImpedance_Task_B.rt_b =
          CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qjj_a - 1] *
          CartesianImpedance_Task_B.r_d + CartesianImpedance_Task_B.sqds_j *
          CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qjj_a];
        CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qjj_a] =
          CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qjj_a - 1] *
          -CartesianImpedance_Task_B.sqds_j + CartesianImpedance_Task_B.r_d *
          CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qjj_a];
        CartesianImpedance_Task_B.smm1_e = CartesianImpedance_Task_B.sqds_j *
          CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qjj_a];
        CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.qjj_a] *=
          CartesianImpedance_Task_B.r_d;
        CartesianImpedance_Task_xrot_i(U, 6 * (CartesianImpedance_Task_B.qjj_a -
          1) + 1, 6 * CartesianImpedance_Task_B.qjj_a + 1,
          CartesianImpedance_Task_B.r_d, CartesianImpedance_Task_B.sqds_j);
        CartesianImpedance_Task_B.qjj_a++;
      }

      CartesianImpedance_Task_B.e_p[CartesianImpedance_Task_B.i_l] =
        CartesianImpedance_Task_B.rt_b;
      CartesianImpedance_Task_B.qq_e++;
      break;

     default:
      if (CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1q_i] <
          0.0) {
        CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1q_i] =
          -CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1q_i];
        CartesianImpedance_Task_xscal(-1.0, V, 6 *
          CartesianImpedance_Task_B.qp1q_i + 1);
      }

      CartesianImpedance_Task_B.qq_e = CartesianImpedance_Task_B.qp1q_i + 1;
      while ((CartesianImpedance_Task_B.qp1q_i + 1 < 6) &&
             (CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1q_i] <
              CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qq_e]))
      {
        CartesianImpedance_Task_B.rt_b =
          CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1q_i];
        CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qp1q_i] =
          CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qq_e];
        CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.qq_e] =
          CartesianImpedance_Task_B.rt_b;
        CartesianImpedance_Task_xswap(V, 6 * CartesianImpedance_Task_B.qp1q_i +
          1, 6 * (CartesianImpedance_Task_B.qp1q_i + 1) + 1);
        CartesianImpedance_Task_xswap(U, 6 * CartesianImpedance_Task_B.qp1q_i +
          1, 6 * (CartesianImpedance_Task_B.qp1q_i + 1) + 1);
        CartesianImpedance_Task_B.qp1q_i = CartesianImpedance_Task_B.qq_e;
        CartesianImpedance_Task_B.qq_e++;
      }

      CartesianImpedance_Task_B.qq_e = 0;
      CartesianImpedance_Task_B.i_l--;
      break;
    }
  }

  for (CartesianImpedance_Task_B.i_l = 0; CartesianImpedance_Task_B.i_l < 6;
       CartesianImpedance_Task_B.i_l++) {
    s[CartesianImpedance_Task_B.i_l] =
      CartesianImpedance_Task_B.b_s_n[CartesianImpedance_Task_B.i_l];
  }
}

// Function for MATLAB Function: '<Root>/M_PINV1'
void modelModelClass::CartesianImpedance_Task_svd_ij(const real_T A[36], real_T
  U[36], real_T s[6], real_T V[36])
{
  boolean_T exitg1;
  std::memcpy(&CartesianImpedance_Task_B.b_A[0], &A[0], 36U * sizeof(real_T));
  for (CartesianImpedance_Task_B.i_p = 0; CartesianImpedance_Task_B.i_p < 6;
       CartesianImpedance_Task_B.i_p++) {
    CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.i_p] = 0.0;
    CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p] = 0.0;
    CartesianImpedance_Task_B.work[CartesianImpedance_Task_B.i_p] = 0.0;
  }

  std::memset(&U[0], 0, 36U * sizeof(real_T));
  std::memset(&CartesianImpedance_Task_B.Vf[0], 0, 36U * sizeof(real_T));
  for (CartesianImpedance_Task_B.i_p = 0; CartesianImpedance_Task_B.i_p < 5;
       CartesianImpedance_Task_B.i_p++) {
    CartesianImpedance_Task_B.qq = 6 * CartesianImpedance_Task_B.i_p +
      CartesianImpedance_Task_B.i_p;
    CartesianImpedance_Task_B.apply_transform = false;
    CartesianImpedance_Task_B.nrm = CartesianImpedance_Task_xnrm2_g(6 -
      CartesianImpedance_Task_B.i_p, CartesianImpedance_Task_B.b_A,
      CartesianImpedance_Task_B.qq + 1);
    if (CartesianImpedance_Task_B.nrm > 0.0) {
      CartesianImpedance_Task_B.apply_transform = true;
      if (CartesianImpedance_Task_B.b_A[CartesianImpedance_Task_B.qq] < 0.0) {
        CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.i_p] =
          -CartesianImpedance_Task_B.nrm;
      } else {
        CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.i_p] =
          CartesianImpedance_Task_B.nrm;
      }

      if (std::abs(CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.i_p])
          >= 1.0020841800044864E-292) {
        CartesianImpedance_Task_B.nrm = 1.0 /
          CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.i_p];
        CartesianImpedance_Task_B.qp1q = (CartesianImpedance_Task_B.qq -
          CartesianImpedance_Task_B.i_p) + 6;
        CartesianImpedance_Task_B.qjj = CartesianImpedance_Task_B.qq;
        while (CartesianImpedance_Task_B.qjj + 1 <=
               CartesianImpedance_Task_B.qp1q) {
          CartesianImpedance_Task_B.b_A[CartesianImpedance_Task_B.qjj] *=
            CartesianImpedance_Task_B.nrm;
          CartesianImpedance_Task_B.qjj++;
        }
      } else {
        CartesianImpedance_Task_B.qp1q = (CartesianImpedance_Task_B.qq -
          CartesianImpedance_Task_B.i_p) + 6;
        CartesianImpedance_Task_B.qjj = CartesianImpedance_Task_B.qq;
        while (CartesianImpedance_Task_B.qjj + 1 <=
               CartesianImpedance_Task_B.qp1q) {
          CartesianImpedance_Task_B.b_A[CartesianImpedance_Task_B.qjj] /=
            CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.i_p];
          CartesianImpedance_Task_B.qjj++;
        }
      }

      CartesianImpedance_Task_B.b_A[CartesianImpedance_Task_B.qq]++;
      CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.i_p] =
        -CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.i_p];
    } else {
      CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.i_p] = 0.0;
    }

    CartesianImpedance_Task_B.qp1q = CartesianImpedance_Task_B.i_p + 1;
    while (CartesianImpedance_Task_B.qp1q + 1 < 7) {
      CartesianImpedance_Task_B.qjj = 6 * CartesianImpedance_Task_B.qp1q +
        CartesianImpedance_Task_B.i_p;
      if (CartesianImpedance_Task_B.apply_transform) {
        CartesianImpedance_Task_xaxpy(6 - CartesianImpedance_Task_B.i_p,
          -(CartesianImpedance_Task_xdotc(6 - CartesianImpedance_Task_B.i_p,
          CartesianImpedance_Task_B.b_A, CartesianImpedance_Task_B.qq + 1,
          CartesianImpedance_Task_B.b_A, CartesianImpedance_Task_B.qjj + 1) /
            CartesianImpedance_Task_B.b_A[CartesianImpedance_Task_B.i_p + 6 *
            CartesianImpedance_Task_B.i_p]), CartesianImpedance_Task_B.qq + 1,
          CartesianImpedance_Task_B.b_A, CartesianImpedance_Task_B.qjj + 1);
      }

      CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qp1q] =
        CartesianImpedance_Task_B.b_A[CartesianImpedance_Task_B.qjj];
      CartesianImpedance_Task_B.qp1q++;
    }

    CartesianImpedance_Task_B.qq = CartesianImpedance_Task_B.i_p;
    while (CartesianImpedance_Task_B.qq + 1 < 7) {
      U[CartesianImpedance_Task_B.qq + 6 * CartesianImpedance_Task_B.i_p] =
        CartesianImpedance_Task_B.b_A[6 * CartesianImpedance_Task_B.i_p +
        CartesianImpedance_Task_B.qq];
      CartesianImpedance_Task_B.qq++;
    }

    if (CartesianImpedance_Task_B.i_p + 1 <= 4) {
      CartesianImpedance_Task_B.nrm = CartesianImpedance_Tas_xnrm2_gh(5 -
        CartesianImpedance_Task_B.i_p, CartesianImpedance_Task_B.e,
        CartesianImpedance_Task_B.i_p + 2);
      if (CartesianImpedance_Task_B.nrm == 0.0) {
        CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p] = 0.0;
      } else {
        if (CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p + 1] < 0.0)
        {
          CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p] =
            -CartesianImpedance_Task_B.nrm;
        } else {
          CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p] =
            CartesianImpedance_Task_B.nrm;
        }

        CartesianImpedance_Task_B.nrm =
          CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p];
        if (std::abs(CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p])
            >= 1.0020841800044864E-292) {
          CartesianImpedance_Task_B.nrm = 1.0 /
            CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p];
          CartesianImpedance_Task_B.qq = CartesianImpedance_Task_B.i_p + 1;
          while (CartesianImpedance_Task_B.qq + 1 <= 6) {
            CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qq] *=
              CartesianImpedance_Task_B.nrm;
            CartesianImpedance_Task_B.qq++;
          }
        } else {
          CartesianImpedance_Task_B.qq = CartesianImpedance_Task_B.i_p + 1;
          while (CartesianImpedance_Task_B.qq + 1 <= 6) {
            CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qq] /=
              CartesianImpedance_Task_B.nrm;
            CartesianImpedance_Task_B.qq++;
          }
        }

        CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p + 1]++;
        CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p] =
          -CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p];
        CartesianImpedance_Task_B.qq = CartesianImpedance_Task_B.i_p + 1;
        while (CartesianImpedance_Task_B.qq + 1 < 7) {
          CartesianImpedance_Task_B.work[CartesianImpedance_Task_B.qq] = 0.0;
          CartesianImpedance_Task_B.qq++;
        }

        CartesianImpedance_Task_B.qq = CartesianImpedance_Task_B.i_p + 1;
        while (CartesianImpedance_Task_B.qq + 1 < 7) {
          CartesianImpedance_Task_xaxpy_a(5 - CartesianImpedance_Task_B.i_p,
            CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qq],
            CartesianImpedance_Task_B.b_A, (CartesianImpedance_Task_B.i_p + 6 *
            CartesianImpedance_Task_B.qq) + 2, CartesianImpedance_Task_B.work,
            CartesianImpedance_Task_B.i_p + 2);
          CartesianImpedance_Task_B.qq++;
        }

        CartesianImpedance_Task_B.qq = CartesianImpedance_Task_B.i_p + 1;
        while (CartesianImpedance_Task_B.qq + 1 < 7) {
          CartesianImpedance_Tas_xaxpy_ag(5 - CartesianImpedance_Task_B.i_p,
            -CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qq] /
            CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p + 1],
            CartesianImpedance_Task_B.work, CartesianImpedance_Task_B.i_p + 2,
            CartesianImpedance_Task_B.b_A, (CartesianImpedance_Task_B.i_p + 6 *
            CartesianImpedance_Task_B.qq) + 2);
          CartesianImpedance_Task_B.qq++;
        }
      }

      CartesianImpedance_Task_B.qq = CartesianImpedance_Task_B.i_p + 1;
      while (CartesianImpedance_Task_B.qq + 1 < 7) {
        CartesianImpedance_Task_B.Vf[CartesianImpedance_Task_B.qq + 6 *
          CartesianImpedance_Task_B.i_p] =
          CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qq];
        CartesianImpedance_Task_B.qq++;
      }
    }
  }

  CartesianImpedance_Task_B.i_p = 4;
  CartesianImpedance_Task_B.b_s[5] = CartesianImpedance_Task_B.b_A[35];
  CartesianImpedance_Task_B.e[4] = CartesianImpedance_Task_B.b_A[34];
  CartesianImpedance_Task_B.e[5] = 0.0;
  for (CartesianImpedance_Task_B.qq = 0; CartesianImpedance_Task_B.qq < 6;
       CartesianImpedance_Task_B.qq++) {
    U[CartesianImpedance_Task_B.qq + 30] = 0.0;
  }

  U[35] = 1.0;
  for (CartesianImpedance_Task_B.qp1q = 4; CartesianImpedance_Task_B.qp1q >= 0;
       CartesianImpedance_Task_B.qp1q--) {
    CartesianImpedance_Task_B.qq = 6 * CartesianImpedance_Task_B.qp1q +
      CartesianImpedance_Task_B.qp1q;
    if (CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1q] != 0.0) {
      CartesianImpedance_Task_B.qp1jj = CartesianImpedance_Task_B.qp1q + 1;
      while (CartesianImpedance_Task_B.qp1jj + 1 < 7) {
        CartesianImpedance_Task_B.qjj = (6 * CartesianImpedance_Task_B.qp1jj +
          CartesianImpedance_Task_B.qp1q) + 1;
        CartesianImpedance_Task_xaxpy(6 - CartesianImpedance_Task_B.qp1q,
          -(CartesianImpedance_Task_xdotc(6 - CartesianImpedance_Task_B.qp1q, U,
          CartesianImpedance_Task_B.qq + 1, U, CartesianImpedance_Task_B.qjj) /
            U[CartesianImpedance_Task_B.qq]), CartesianImpedance_Task_B.qq + 1,
          U, CartesianImpedance_Task_B.qjj);
        CartesianImpedance_Task_B.qp1jj++;
      }

      CartesianImpedance_Task_B.qjj = CartesianImpedance_Task_B.qp1q;
      while (CartesianImpedance_Task_B.qjj + 1 < 7) {
        CartesianImpedance_Task_B.qp1jj = 6 * CartesianImpedance_Task_B.qp1q +
          CartesianImpedance_Task_B.qjj;
        U[CartesianImpedance_Task_B.qp1jj] = -U[CartesianImpedance_Task_B.qp1jj];
        CartesianImpedance_Task_B.qjj++;
      }

      U[CartesianImpedance_Task_B.qq]++;
      CartesianImpedance_Task_B.qq = 0;
      while (CartesianImpedance_Task_B.qq <= CartesianImpedance_Task_B.qp1q - 1)
      {
        U[CartesianImpedance_Task_B.qq + 6 * CartesianImpedance_Task_B.qp1q] =
          0.0;
        CartesianImpedance_Task_B.qq++;
      }
    } else {
      for (CartesianImpedance_Task_B.qjj = 0; CartesianImpedance_Task_B.qjj < 6;
           CartesianImpedance_Task_B.qjj++) {
        U[CartesianImpedance_Task_B.qjj + 6 * CartesianImpedance_Task_B.qp1q] =
          0.0;
      }

      U[CartesianImpedance_Task_B.qq] = 1.0;
    }
  }

  for (CartesianImpedance_Task_B.qq = 5; CartesianImpedance_Task_B.qq >= 0;
       CartesianImpedance_Task_B.qq--) {
    if ((CartesianImpedance_Task_B.qq + 1 <= 4) &&
        (CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qq] != 0.0)) {
      CartesianImpedance_Task_B.qp1q = (6 * CartesianImpedance_Task_B.qq +
        CartesianImpedance_Task_B.qq) + 2;
      CartesianImpedance_Task_B.qjj = CartesianImpedance_Task_B.qq + 1;
      while (CartesianImpedance_Task_B.qjj + 1 < 7) {
        CartesianImpedance_Task_B.qp1jj = (6 * CartesianImpedance_Task_B.qjj +
          CartesianImpedance_Task_B.qq) + 2;
        CartesianImpedance_Task_xaxpy(5 - CartesianImpedance_Task_B.qq,
          -(CartesianImpedance_Task_xdotc(5 - CartesianImpedance_Task_B.qq,
          CartesianImpedance_Task_B.Vf, CartesianImpedance_Task_B.qp1q,
          CartesianImpedance_Task_B.Vf, CartesianImpedance_Task_B.qp1jj) /
            CartesianImpedance_Task_B.Vf[CartesianImpedance_Task_B.qp1q - 1]),
          CartesianImpedance_Task_B.qp1q, CartesianImpedance_Task_B.Vf,
          CartesianImpedance_Task_B.qp1jj);
        CartesianImpedance_Task_B.qjj++;
      }
    }

    for (CartesianImpedance_Task_B.qp1q = 0; CartesianImpedance_Task_B.qp1q < 6;
         CartesianImpedance_Task_B.qp1q++) {
      CartesianImpedance_Task_B.Vf[CartesianImpedance_Task_B.qp1q + 6 *
        CartesianImpedance_Task_B.qq] = 0.0;
    }

    CartesianImpedance_Task_B.Vf[CartesianImpedance_Task_B.qq + 6 *
      CartesianImpedance_Task_B.qq] = 1.0;
  }

  for (CartesianImpedance_Task_B.qq = 0; CartesianImpedance_Task_B.qq < 6;
       CartesianImpedance_Task_B.qq++) {
    CartesianImpedance_Task_B.nrm =
      CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qq];
    if (CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qq] != 0.0) {
      CartesianImpedance_Task_B.rt = std::abs
        (CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qq]);
      CartesianImpedance_Task_B.r =
        CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qq] /
        CartesianImpedance_Task_B.rt;
      CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qq] =
        CartesianImpedance_Task_B.rt;
      if (CartesianImpedance_Task_B.qq + 1 < 6) {
        CartesianImpedance_Task_B.nrm =
          CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qq] /
          CartesianImpedance_Task_B.r;
      }

      CartesianImpedance_Task_xscal(CartesianImpedance_Task_B.r, U, 6 *
        CartesianImpedance_Task_B.qq + 1);
    }

    if ((CartesianImpedance_Task_B.qq + 1 < 6) && (CartesianImpedance_Task_B.nrm
         != 0.0)) {
      CartesianImpedance_Task_B.rt = std::abs(CartesianImpedance_Task_B.nrm);
      CartesianImpedance_Task_B.r = CartesianImpedance_Task_B.rt /
        CartesianImpedance_Task_B.nrm;
      CartesianImpedance_Task_B.nrm = CartesianImpedance_Task_B.rt;
      CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qq + 1] *=
        CartesianImpedance_Task_B.r;
      CartesianImpedance_Task_xscal(CartesianImpedance_Task_B.r,
        CartesianImpedance_Task_B.Vf, 6 * (CartesianImpedance_Task_B.qq + 1) + 1);
    }

    CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qq] =
      CartesianImpedance_Task_B.nrm;
  }

  CartesianImpedance_Task_B.qq = 0;
  CartesianImpedance_Task_B.nrm = 0.0;
  for (CartesianImpedance_Task_B.qp1q = 0; CartesianImpedance_Task_B.qp1q < 6;
       CartesianImpedance_Task_B.qp1q++) {
    CartesianImpedance_Task_B.r = std::abs
      (CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1q]);
    CartesianImpedance_Task_B.rt = std::abs
      (CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qp1q]);
    if ((CartesianImpedance_Task_B.r > CartesianImpedance_Task_B.rt) || rtIsNaN
        (CartesianImpedance_Task_B.rt)) {
      CartesianImpedance_Task_B.rt = CartesianImpedance_Task_B.r;
    }

    if ((!(CartesianImpedance_Task_B.nrm > CartesianImpedance_Task_B.rt)) &&
        (!rtIsNaN(CartesianImpedance_Task_B.rt))) {
      CartesianImpedance_Task_B.nrm = CartesianImpedance_Task_B.rt;
    }
  }

  while ((CartesianImpedance_Task_B.i_p + 2 > 0) &&
         (CartesianImpedance_Task_B.qq < 75)) {
    CartesianImpedance_Task_B.qp1q = CartesianImpedance_Task_B.i_p + 1;
    exitg1 = false;
    while (!(exitg1 || (CartesianImpedance_Task_B.qp1q == 0))) {
      CartesianImpedance_Task_B.rt = std::abs
        (CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qp1q - 1]);
      if (CartesianImpedance_Task_B.rt <= (std::abs
           (CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1q - 1]) +
           std::abs(CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1q]))
          * 2.2204460492503131E-16) {
        CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qp1q - 1] = 0.0;
        exitg1 = true;
      } else if ((CartesianImpedance_Task_B.rt <= 1.0020841800044864E-292) ||
                 ((CartesianImpedance_Task_B.qq > 20) &&
                  (CartesianImpedance_Task_B.rt <= 2.2204460492503131E-16 *
                   CartesianImpedance_Task_B.nrm))) {
        CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qp1q - 1] = 0.0;
        exitg1 = true;
      } else {
        CartesianImpedance_Task_B.qp1q--;
      }
    }

    if (CartesianImpedance_Task_B.i_p + 1 == CartesianImpedance_Task_B.qp1q) {
      CartesianImpedance_Task_B.qp1jj = 4;
    } else {
      CartesianImpedance_Task_B.qjj = CartesianImpedance_Task_B.i_p + 2;
      CartesianImpedance_Task_B.qp1jj = CartesianImpedance_Task_B.i_p + 2;
      exitg1 = false;
      while ((!exitg1) && (CartesianImpedance_Task_B.qp1jj >=
                           CartesianImpedance_Task_B.qp1q)) {
        CartesianImpedance_Task_B.qjj = CartesianImpedance_Task_B.qp1jj;
        if (CartesianImpedance_Task_B.qp1jj == CartesianImpedance_Task_B.qp1q) {
          exitg1 = true;
        } else {
          CartesianImpedance_Task_B.rt = 0.0;
          if (CartesianImpedance_Task_B.qp1jj < CartesianImpedance_Task_B.i_p +
              2) {
            CartesianImpedance_Task_B.rt = std::abs
              (CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qp1jj - 1]);
          }

          if (CartesianImpedance_Task_B.qp1jj > CartesianImpedance_Task_B.qp1q +
              1) {
            CartesianImpedance_Task_B.rt += std::abs
              (CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qp1jj - 2]);
          }

          CartesianImpedance_Task_B.r = std::abs
            (CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1jj - 1]);
          if ((CartesianImpedance_Task_B.r <= 2.2204460492503131E-16 *
               CartesianImpedance_Task_B.rt) || (CartesianImpedance_Task_B.r <=
               1.0020841800044864E-292)) {
            CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1jj - 1] =
              0.0;
            exitg1 = true;
          } else {
            CartesianImpedance_Task_B.qp1jj--;
          }
        }
      }

      if (CartesianImpedance_Task_B.qjj == CartesianImpedance_Task_B.qp1q) {
        CartesianImpedance_Task_B.qp1jj = 3;
      } else if (CartesianImpedance_Task_B.i_p + 2 ==
                 CartesianImpedance_Task_B.qjj) {
        CartesianImpedance_Task_B.qp1jj = 1;
      } else {
        CartesianImpedance_Task_B.qp1jj = 2;
        CartesianImpedance_Task_B.qp1q = CartesianImpedance_Task_B.qjj;
      }
    }

    switch (CartesianImpedance_Task_B.qp1jj) {
     case 1:
      CartesianImpedance_Task_B.rt =
        CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p];
      CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p] = 0.0;
      CartesianImpedance_Task_B.qjj = CartesianImpedance_Task_B.i_p;
      while (CartesianImpedance_Task_B.qjj + 1 >= CartesianImpedance_Task_B.qp1q
             + 1) {
        CartesianImpedance_Task_xrotg
          (&CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qjj],
           &CartesianImpedance_Task_B.rt, &CartesianImpedance_Task_B.r,
           &CartesianImpedance_Task_B.sqds);
        if (CartesianImpedance_Task_B.qjj + 1 > CartesianImpedance_Task_B.qp1q +
            1) {
          CartesianImpedance_Task_B.smm1 =
            CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qjj - 1];
          CartesianImpedance_Task_B.rt = CartesianImpedance_Task_B.smm1 *
            -CartesianImpedance_Task_B.sqds;
          CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qjj - 1] =
            CartesianImpedance_Task_B.smm1 * CartesianImpedance_Task_B.r;
        }

        CartesianImpedance_Task_xrot_i(CartesianImpedance_Task_B.Vf, 6 *
          CartesianImpedance_Task_B.qjj + 1, 6 * (CartesianImpedance_Task_B.i_p
          + 1) + 1, CartesianImpedance_Task_B.r, CartesianImpedance_Task_B.sqds);
        CartesianImpedance_Task_B.qjj--;
      }
      break;

     case 2:
      CartesianImpedance_Task_B.rt =
        CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qp1q - 1];
      CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qp1q - 1] = 0.0;
      CartesianImpedance_Task_B.qjj = CartesianImpedance_Task_B.qp1q;
      while (CartesianImpedance_Task_B.qjj + 1 <= CartesianImpedance_Task_B.i_p
             + 2) {
        CartesianImpedance_Task_xrotg
          (&CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qjj],
           &CartesianImpedance_Task_B.rt, &CartesianImpedance_Task_B.r,
           &CartesianImpedance_Task_B.sqds);
        CartesianImpedance_Task_B.rt = -CartesianImpedance_Task_B.sqds *
          CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qjj];
        CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qjj] *=
          CartesianImpedance_Task_B.r;
        CartesianImpedance_Task_xrot_i(U, 6 * CartesianImpedance_Task_B.qjj + 1,
          6 * (CartesianImpedance_Task_B.qp1q - 1) + 1,
          CartesianImpedance_Task_B.r, CartesianImpedance_Task_B.sqds);
        CartesianImpedance_Task_B.qjj++;
      }
      break;

     case 3:
      CartesianImpedance_Task_B.sqds =
        CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.i_p + 1];
      CartesianImpedance_Task_B.r = std::abs(CartesianImpedance_Task_B.sqds);
      CartesianImpedance_Task_B.rt = std::abs
        (CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.i_p]);
      if ((CartesianImpedance_Task_B.r > CartesianImpedance_Task_B.rt) ||
          rtIsNaN(CartesianImpedance_Task_B.rt)) {
        CartesianImpedance_Task_B.rt = CartesianImpedance_Task_B.r;
      }

      CartesianImpedance_Task_B.r = std::abs
        (CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p]);
      if ((CartesianImpedance_Task_B.rt > CartesianImpedance_Task_B.r) ||
          rtIsNaN(CartesianImpedance_Task_B.r)) {
        CartesianImpedance_Task_B.r = CartesianImpedance_Task_B.rt;
      }

      CartesianImpedance_Task_B.rt = std::abs
        (CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1q]);
      if ((CartesianImpedance_Task_B.r > CartesianImpedance_Task_B.rt) ||
          rtIsNaN(CartesianImpedance_Task_B.rt)) {
        CartesianImpedance_Task_B.rt = CartesianImpedance_Task_B.r;
      }

      CartesianImpedance_Task_B.r = std::abs
        (CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qp1q]);
      if ((CartesianImpedance_Task_B.rt > CartesianImpedance_Task_B.r) ||
          rtIsNaN(CartesianImpedance_Task_B.r)) {
        CartesianImpedance_Task_B.r = CartesianImpedance_Task_B.rt;
      }

      CartesianImpedance_Task_B.rt = CartesianImpedance_Task_B.sqds /
        CartesianImpedance_Task_B.r;
      CartesianImpedance_Task_B.smm1 =
        CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.i_p] /
        CartesianImpedance_Task_B.r;
      CartesianImpedance_Task_B.emm1 =
        CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p] /
        CartesianImpedance_Task_B.r;
      CartesianImpedance_Task_B.sqds =
        CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1q] /
        CartesianImpedance_Task_B.r;
      CartesianImpedance_Task_B.smm1 = ((CartesianImpedance_Task_B.smm1 +
        CartesianImpedance_Task_B.rt) * (CartesianImpedance_Task_B.smm1 -
        CartesianImpedance_Task_B.rt) + CartesianImpedance_Task_B.emm1 *
        CartesianImpedance_Task_B.emm1) / 2.0;
      CartesianImpedance_Task_B.emm1 *= CartesianImpedance_Task_B.rt;
      CartesianImpedance_Task_B.emm1 *= CartesianImpedance_Task_B.emm1;
      if ((CartesianImpedance_Task_B.smm1 != 0.0) ||
          (CartesianImpedance_Task_B.emm1 != 0.0)) {
        CartesianImpedance_Task_B.shift = std::sqrt
          (CartesianImpedance_Task_B.smm1 * CartesianImpedance_Task_B.smm1 +
           CartesianImpedance_Task_B.emm1);
        if (CartesianImpedance_Task_B.smm1 < 0.0) {
          CartesianImpedance_Task_B.shift = -CartesianImpedance_Task_B.shift;
        }

        CartesianImpedance_Task_B.shift = CartesianImpedance_Task_B.emm1 /
          (CartesianImpedance_Task_B.smm1 + CartesianImpedance_Task_B.shift);
      } else {
        CartesianImpedance_Task_B.shift = 0.0;
      }

      CartesianImpedance_Task_B.rt = (CartesianImpedance_Task_B.sqds +
        CartesianImpedance_Task_B.rt) * (CartesianImpedance_Task_B.sqds -
        CartesianImpedance_Task_B.rt) + CartesianImpedance_Task_B.shift;
      CartesianImpedance_Task_B.smm1 =
        CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qp1q] /
        CartesianImpedance_Task_B.r * CartesianImpedance_Task_B.sqds;
      CartesianImpedance_Task_B.qjj = CartesianImpedance_Task_B.qp1q + 1;
      while (CartesianImpedance_Task_B.qjj <= CartesianImpedance_Task_B.i_p + 1)
      {
        CartesianImpedance_Task_xrotg(&CartesianImpedance_Task_B.rt,
          &CartesianImpedance_Task_B.smm1, &CartesianImpedance_Task_B.r,
          &CartesianImpedance_Task_B.sqds);
        if (CartesianImpedance_Task_B.qjj > CartesianImpedance_Task_B.qp1q + 1)
        {
          CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qjj - 2] =
            CartesianImpedance_Task_B.rt;
        }

        CartesianImpedance_Task_B.smm1 =
          CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qjj - 1];
        CartesianImpedance_Task_B.emm1 =
          CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qjj - 1];
        CartesianImpedance_Task_B.rt = CartesianImpedance_Task_B.emm1 *
          CartesianImpedance_Task_B.r + CartesianImpedance_Task_B.smm1 *
          CartesianImpedance_Task_B.sqds;
        CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qjj - 1] =
          CartesianImpedance_Task_B.smm1 * CartesianImpedance_Task_B.r -
          CartesianImpedance_Task_B.emm1 * CartesianImpedance_Task_B.sqds;
        CartesianImpedance_Task_B.smm1 = CartesianImpedance_Task_B.sqds *
          CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qjj];
        CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qjj] *=
          CartesianImpedance_Task_B.r;
        CartesianImpedance_Task_xrot_i(CartesianImpedance_Task_B.Vf, 6 *
          (CartesianImpedance_Task_B.qjj - 1) + 1, 6 *
          CartesianImpedance_Task_B.qjj + 1, CartesianImpedance_Task_B.r,
          CartesianImpedance_Task_B.sqds);
        CartesianImpedance_Task_xrotg(&CartesianImpedance_Task_B.rt,
          &CartesianImpedance_Task_B.smm1, &CartesianImpedance_Task_B.r,
          &CartesianImpedance_Task_B.sqds);
        CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qjj - 1] =
          CartesianImpedance_Task_B.rt;
        CartesianImpedance_Task_B.rt =
          CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qjj - 1] *
          CartesianImpedance_Task_B.r + CartesianImpedance_Task_B.sqds *
          CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qjj];
        CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qjj] =
          CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qjj - 1] *
          -CartesianImpedance_Task_B.sqds + CartesianImpedance_Task_B.r *
          CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qjj];
        CartesianImpedance_Task_B.smm1 = CartesianImpedance_Task_B.sqds *
          CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qjj];
        CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.qjj] *=
          CartesianImpedance_Task_B.r;
        CartesianImpedance_Task_xrot_i(U, 6 * (CartesianImpedance_Task_B.qjj - 1)
          + 1, 6 * CartesianImpedance_Task_B.qjj + 1,
          CartesianImpedance_Task_B.r, CartesianImpedance_Task_B.sqds);
        CartesianImpedance_Task_B.qjj++;
      }

      CartesianImpedance_Task_B.e[CartesianImpedance_Task_B.i_p] =
        CartesianImpedance_Task_B.rt;
      CartesianImpedance_Task_B.qq++;
      break;

     default:
      if (CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1q] < 0.0) {
        CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1q] =
          -CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1q];
        CartesianImpedance_Task_xscal(-1.0, CartesianImpedance_Task_B.Vf, 6 *
          CartesianImpedance_Task_B.qp1q + 1);
      }

      CartesianImpedance_Task_B.qq = CartesianImpedance_Task_B.qp1q + 1;
      while ((CartesianImpedance_Task_B.qp1q + 1 < 6) &&
             (CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1q] <
              CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qq])) {
        CartesianImpedance_Task_B.rt =
          CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1q];
        CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qp1q] =
          CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qq];
        CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qq] =
          CartesianImpedance_Task_B.rt;
        CartesianImpedance_Task_xswap(CartesianImpedance_Task_B.Vf, 6 *
          CartesianImpedance_Task_B.qp1q + 1, 6 *
          (CartesianImpedance_Task_B.qp1q + 1) + 1);
        CartesianImpedance_Task_xswap(U, 6 * CartesianImpedance_Task_B.qp1q + 1,
          6 * (CartesianImpedance_Task_B.qp1q + 1) + 1);
        CartesianImpedance_Task_B.qp1q = CartesianImpedance_Task_B.qq;
        CartesianImpedance_Task_B.qq++;
      }

      CartesianImpedance_Task_B.qq = 0;
      CartesianImpedance_Task_B.i_p--;
      break;
    }
  }

  for (CartesianImpedance_Task_B.qq = 0; CartesianImpedance_Task_B.qq < 6;
       CartesianImpedance_Task_B.qq++) {
    s[CartesianImpedance_Task_B.qq] =
      CartesianImpedance_Task_B.b_s[CartesianImpedance_Task_B.qq];
    for (CartesianImpedance_Task_B.i_p = 0; CartesianImpedance_Task_B.i_p < 6;
         CartesianImpedance_Task_B.i_p++) {
      V[CartesianImpedance_Task_B.i_p + 6 * CartesianImpedance_Task_B.qq] =
        CartesianImpedance_Task_B.Vf[6 * CartesianImpedance_Task_B.qq +
        CartesianImpedance_Task_B.i_p];
    }
  }
}

// Function for MATLAB Function: '<Root>/D1'
void modelModelClass::CartesianImpedance_Task_svd(const real_T A[36], real_T U
  [36], real_T S[36], real_T V[36])
{
  CartesianImpedance_Task_B.p = true;
  for (CartesianImpedance_Task_B.i_a = 0; CartesianImpedance_Task_B.i_a < 36;
       CartesianImpedance_Task_B.i_a++) {
    if (CartesianImpedance_Task_B.p && (rtIsInf(A[CartesianImpedance_Task_B.i_a])
         || rtIsNaN(A[CartesianImpedance_Task_B.i_a]))) {
      CartesianImpedance_Task_B.p = false;
    }
  }

  if (CartesianImpedance_Task_B.p) {
    CartesianImpedance_Task_svd_b(A, U, CartesianImpedance_Task_B.s_m, V);
  } else {
    for (CartesianImpedance_Task_B.i_a = 0; CartesianImpedance_Task_B.i_a < 36;
         CartesianImpedance_Task_B.i_a++) {
      U[CartesianImpedance_Task_B.i_a] = (rtNaN);
    }

    for (CartesianImpedance_Task_B.i_a = 0; CartesianImpedance_Task_B.i_a < 6;
         CartesianImpedance_Task_B.i_a++) {
      CartesianImpedance_Task_B.s_m[CartesianImpedance_Task_B.i_a] = (rtNaN);
    }

    for (CartesianImpedance_Task_B.i_a = 0; CartesianImpedance_Task_B.i_a < 36;
         CartesianImpedance_Task_B.i_a++) {
      V[CartesianImpedance_Task_B.i_a] = (rtNaN);
    }
  }

  std::memset(&S[0], 0, 36U * sizeof(real_T));
  for (CartesianImpedance_Task_B.i_a = 0; CartesianImpedance_Task_B.i_a < 6;
       CartesianImpedance_Task_B.i_a++) {
    S[CartesianImpedance_Task_B.i_a + 6 * CartesianImpedance_Task_B.i_a] =
      CartesianImpedance_Task_B.s_m[CartesianImpedance_Task_B.i_a];
  }
}

// Model step function
void modelModelClass::step()
{

  // MATLAB Function: '<Root>/K'
  std::memset(&CartesianImpedance_Task_B.K[0], 0, 36U * sizeof(real_T));
  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 6;
       CartesianImpedance_Task_B.i++) {
    CartesianImpedance_Task_B.K[CartesianImpedance_Task_B.i + 6 *
      CartesianImpedance_Task_B.i] =
      CartesianImpedance_Task_ConstB.MatrixConcatenate2[CartesianImpedance_Task_B.i];
  }

  // End of MATLAB Function: '<Root>/K'

  // S-Function (BlockFactory): '<Root>/getJointPosition'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.getJointPosition_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.getJointPosition_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/getJointPosition

  // S-Function (BlockFactory): '<Root>/setPositionReference1'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.setPositionReference1_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.setPositionReference1_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/setPositionReference1

  // S-Function (BlockFactory): '<S10>/getPoseFun'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.getPoseFun_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.getPoseFun_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <S10>/getPoseFun

  // S-Function (BlockFactory): '<S5>/getPoseFun'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.getPoseFun_PWORK_h.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.getPoseFun_PWORK_h.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <S5>/getPoseFun

  // S-Function (BlockFactory): '<Root>/getJacobian'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.getJacobian_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.getJacobian_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/getJacobian

  // S-Function (BlockFactory): '<Root>/getInertiaInverse'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.getInertiaInverse_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.getInertiaInverse_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/getInertiaInverse
  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 6;
       CartesianImpedance_Task_B.i++) {
    for (CartesianImpedance_Task_B.b_j = 0; CartesianImpedance_Task_B.b_j < 5;
         CartesianImpedance_Task_B.b_j++) {
      // Math: '<Root>/Math Function' incorporates:
      //   Math: '<Root>/Math Function1'

      CartesianImpedance_Task_B.rtb_MultiportSwitch_tmp_tmp[CartesianImpedance_Task_B.b_j
        + 5 * CartesianImpedance_Task_B.i] =
        CartesianImpedance_Task_B.getJacobian_o1[6 *
        CartesianImpedance_Task_B.b_j + CartesianImpedance_Task_B.i];
    }
  }

  // Product: '<Root>/Product of Elements' incorporates:
  //   Math: '<Root>/Math Function'

  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 6;
       CartesianImpedance_Task_B.i++) {
    for (CartesianImpedance_Task_B.b_j = 0; CartesianImpedance_Task_B.b_j < 5;
         CartesianImpedance_Task_B.b_j++) {
      CartesianImpedance_Task_B.ar = CartesianImpedance_Task_B.b_j + 5 *
        CartesianImpedance_Task_B.i;
      CartesianImpedance_Task_B.dv[CartesianImpedance_Task_B.ar] = 0.0;
      for (CartesianImpedance_Task_B.rtb_ProductofElements1_tmp = 0;
           CartesianImpedance_Task_B.rtb_ProductofElements1_tmp < 5;
           CartesianImpedance_Task_B.rtb_ProductofElements1_tmp++) {
        CartesianImpedance_Task_B.dv[CartesianImpedance_Task_B.ar] +=
          CartesianImpedance_Task_B.getInertiaInverse[5 *
          CartesianImpedance_Task_B.rtb_ProductofElements1_tmp +
          CartesianImpedance_Task_B.b_j] *
          CartesianImpedance_Task_B.rtb_MultiportSwitch_tmp_tmp[5 *
          CartesianImpedance_Task_B.i +
          CartesianImpedance_Task_B.rtb_ProductofElements1_tmp];
      }
    }
  }

  // End of Product: '<Root>/Product of Elements'

  // Product: '<Root>/Product of Elements1'
  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 6;
       CartesianImpedance_Task_B.i++) {
    for (CartesianImpedance_Task_B.b_j = 0; CartesianImpedance_Task_B.b_j < 6;
         CartesianImpedance_Task_B.b_j++) {
      CartesianImpedance_Task_B.rtb_ProductofElements1_tmp =
        CartesianImpedance_Task_B.b_j + 6 * CartesianImpedance_Task_B.i;
      CartesianImpedance_Task_B.ProductofElements1[CartesianImpedance_Task_B.rtb_ProductofElements1_tmp]
        = 0.0;
      for (CartesianImpedance_Task_B.ar = 0; CartesianImpedance_Task_B.ar < 5;
           CartesianImpedance_Task_B.ar++) {
        CartesianImpedance_Task_B.ProductofElements1[CartesianImpedance_Task_B.rtb_ProductofElements1_tmp]
          += CartesianImpedance_Task_B.getJacobian_o1[6 *
          CartesianImpedance_Task_B.ar + CartesianImpedance_Task_B.b_j] *
          CartesianImpedance_Task_B.dv[5 * CartesianImpedance_Task_B.i +
          CartesianImpedance_Task_B.ar];
      }
    }
  }

  // End of Product: '<Root>/Product of Elements1'

  // MATLAB Function: '<Root>/M_PINV1'
  if (!CartesianImpedance_anyNonFinite
      (CartesianImpedance_Task_B.ProductofElements1)) {
    CartesianImpedance_Task_svd_b(CartesianImpedance_Task_B.ProductofElements1,
      CartesianImpedance_Task_B.U, CartesianImpedance_Task_B.s,
      CartesianImpedance_Task_B.D_e);
  } else {
    for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 36;
         CartesianImpedance_Task_B.i++) {
      CartesianImpedance_Task_B.U[CartesianImpedance_Task_B.i] = (rtNaN);
    }

    for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 6;
         CartesianImpedance_Task_B.i++) {
      CartesianImpedance_Task_B.s[CartesianImpedance_Task_B.i] = (rtNaN);
    }

    for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 36;
         CartesianImpedance_Task_B.i++) {
      CartesianImpedance_Task_B.D_e[CartesianImpedance_Task_B.i] = (rtNaN);
    }
  }

  std::memset(&CartesianImpedance_Task_B.Sinv_sat[0], 0, 36U * sizeof(real_T));
  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 6;
       CartesianImpedance_Task_B.i++) {
    CartesianImpedance_Task_B.Sinv_sat[CartesianImpedance_Task_B.i + 6 *
      CartesianImpedance_Task_B.i] =
      CartesianImpedance_Task_B.s[CartesianImpedance_Task_B.i];
  }

  std::memset(&CartesianImpedance_Task_B.R[0], 0, 36U * sizeof(real_T));
  if (CartesianImpedance_anyNonFinite(CartesianImpedance_Task_B.Sinv_sat)) {
    for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 36;
         CartesianImpedance_Task_B.i++) {
      CartesianImpedance_Task_B.R[CartesianImpedance_Task_B.i] = (rtNaN);
    }
  } else {
    CartesianImpedance_Task_svd_ij(CartesianImpedance_Task_B.Sinv_sat,
      CartesianImpedance_Task_B.ProductofElements1, CartesianImpedance_Task_B.s,
      CartesianImpedance_Task_B.b_V);
    CartesianImpedance_Task_B.absx = std::abs(CartesianImpedance_Task_B.s[0]);
    if ((!rtIsInf(CartesianImpedance_Task_B.absx)) && (!rtIsNaN
         (CartesianImpedance_Task_B.absx))) {
      if (CartesianImpedance_Task_B.absx <= 2.2250738585072014E-308) {
        CartesianImpedance_Task_B.absx = 4.94065645841247E-324;
      } else {
        frexp(CartesianImpedance_Task_B.absx, &CartesianImpedance_Task_B.vcol);
        CartesianImpedance_Task_B.absx = std::ldexp(1.0,
          CartesianImpedance_Task_B.vcol - 53);
      }
    } else {
      CartesianImpedance_Task_B.absx = (rtNaN);
    }

    CartesianImpedance_Task_B.absx *= 6.0;
    CartesianImpedance_Task_B.i = -1;
    CartesianImpedance_Task_B.vcol = 0;
    while ((CartesianImpedance_Task_B.vcol < 6) &&
           (CartesianImpedance_Task_B.s[CartesianImpedance_Task_B.vcol] >
            CartesianImpedance_Task_B.absx)) {
      CartesianImpedance_Task_B.i++;
      CartesianImpedance_Task_B.vcol++;
    }

    if (CartesianImpedance_Task_B.i + 1 > 0) {
      CartesianImpedance_Task_B.vcol = 0;
      CartesianImpedance_Task_B.b_j = 0;
      while (CartesianImpedance_Task_B.b_j <= CartesianImpedance_Task_B.i) {
        CartesianImpedance_Task_B.absx = 1.0 /
          CartesianImpedance_Task_B.s[CartesianImpedance_Task_B.b_j];
        CartesianImpedance_Task_B.ar = CartesianImpedance_Task_B.vcol;
        while (CartesianImpedance_Task_B.ar + 1 <=
               CartesianImpedance_Task_B.vcol + 6) {
          CartesianImpedance_Task_B.b_V[CartesianImpedance_Task_B.ar] *=
            CartesianImpedance_Task_B.absx;
          CartesianImpedance_Task_B.ar++;
        }

        CartesianImpedance_Task_B.vcol += 6;
        CartesianImpedance_Task_B.b_j++;
      }

      for (CartesianImpedance_Task_B.vcol = 0; CartesianImpedance_Task_B.vcol <=
           31; CartesianImpedance_Task_B.vcol += 6) {
        CartesianImpedance_Task_B.b_j = CartesianImpedance_Task_B.vcol;
        while (CartesianImpedance_Task_B.b_j + 1 <=
               CartesianImpedance_Task_B.vcol + 6) {
          CartesianImpedance_Task_B.R[CartesianImpedance_Task_B.b_j] = 0.0;
          CartesianImpedance_Task_B.b_j++;
        }
      }

      CartesianImpedance_Task_B.vcol = 0;
      for (CartesianImpedance_Task_B.b_j = 0; CartesianImpedance_Task_B.b_j <=
           31; CartesianImpedance_Task_B.b_j += 6) {
        CartesianImpedance_Task_B.ar = -1;
        CartesianImpedance_Task_B.vcol++;
        CartesianImpedance_Task_B.rtb_ProductofElements1_tmp = 6 *
          CartesianImpedance_Task_B.i + CartesianImpedance_Task_B.vcol;
        CartesianImpedance_Task_B.ib = CartesianImpedance_Task_B.vcol;
        while (CartesianImpedance_Task_B.ib <=
               CartesianImpedance_Task_B.rtb_ProductofElements1_tmp) {
          CartesianImpedance_Task_B.ia = CartesianImpedance_Task_B.ar;
          CartesianImpedance_Task_B.b_ic = CartesianImpedance_Task_B.b_j;
          while (CartesianImpedance_Task_B.b_ic + 1 <=
                 CartesianImpedance_Task_B.b_j + 6) {
            CartesianImpedance_Task_B.ia++;
            CartesianImpedance_Task_B.R[CartesianImpedance_Task_B.b_ic] +=
              CartesianImpedance_Task_B.ProductofElements1[CartesianImpedance_Task_B.ib
              - 1] * CartesianImpedance_Task_B.b_V[CartesianImpedance_Task_B.ia];
            CartesianImpedance_Task_B.b_ic++;
          }

          CartesianImpedance_Task_B.ar += 6;
          CartesianImpedance_Task_B.ib += 6;
        }
      }
    }
  }

  for (CartesianImpedance_Task_B.vcol = 0; CartesianImpedance_Task_B.vcol < 6;
       CartesianImpedance_Task_B.vcol++) {
    // MATLAB Function: '<Root>/D3'
    for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 6;
         CartesianImpedance_Task_B.i++) {
      CartesianImpedance_Task_B.rtb_ProductofElements1_tmp = 6 *
        CartesianImpedance_Task_B.i + CartesianImpedance_Task_B.vcol;
      CartesianImpedance_Task_B.ProductofElements1[CartesianImpedance_Task_B.i +
        6 * CartesianImpedance_Task_B.vcol] =
        CartesianImpedance_Task_B.U[CartesianImpedance_Task_B.rtb_ProductofElements1_tmp];
      CartesianImpedance_Task_B.b_V[CartesianImpedance_Task_B.rtb_ProductofElements1_tmp]
        = 0.0;
      for (CartesianImpedance_Task_B.b_j = 0; CartesianImpedance_Task_B.b_j < 6;
           CartesianImpedance_Task_B.b_j++) {
        CartesianImpedance_Task_B.b_V[CartesianImpedance_Task_B.rtb_ProductofElements1_tmp]
          += CartesianImpedance_Task_B.D_e[6 * CartesianImpedance_Task_B.b_j +
          CartesianImpedance_Task_B.vcol] * CartesianImpedance_Task_B.R[6 *
          CartesianImpedance_Task_B.i + CartesianImpedance_Task_B.b_j];
      }
    }

    // End of MATLAB Function: '<Root>/D3'
  }

  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 6;
       CartesianImpedance_Task_B.i++) {
    for (CartesianImpedance_Task_B.b_j = 0; CartesianImpedance_Task_B.b_j < 6;
         CartesianImpedance_Task_B.b_j++) {
      CartesianImpedance_Task_B.vcol = CartesianImpedance_Task_B.b_j + 6 *
        CartesianImpedance_Task_B.i;
      CartesianImpedance_Task_B.Sinv_sat[CartesianImpedance_Task_B.vcol] = 0.0;
      for (CartesianImpedance_Task_B.ar = 0; CartesianImpedance_Task_B.ar < 6;
           CartesianImpedance_Task_B.ar++) {
        CartesianImpedance_Task_B.Sinv_sat[CartesianImpedance_Task_B.vcol] +=
          CartesianImpedance_Task_B.b_V[6 * CartesianImpedance_Task_B.ar +
          CartesianImpedance_Task_B.b_j] *
          CartesianImpedance_Task_B.ProductofElements1[6 *
          CartesianImpedance_Task_B.i + CartesianImpedance_Task_B.ar];
      }
    }
  }

  // End of MATLAB Function: '<Root>/M_PINV1'

  // MATLAB Function: '<Root>/D'
  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 6;
       CartesianImpedance_Task_B.i++) {
    CartesianImpedance_Task_B.vcol = 6 * CartesianImpedance_Task_B.i +
      CartesianImpedance_Task_B.i;
    CartesianImpedance_Task_B.s[CartesianImpedance_Task_B.i] = std::sqrt
      (CartesianImpedance_Task_B.K[CartesianImpedance_Task_B.vcol] *
       CartesianImpedance_Task_B.Sinv_sat[CartesianImpedance_Task_B.vcol]) * 1.4;
  }

  std::memset(&CartesianImpedance_Task_B.D_e[0], 0, 36U * sizeof(real_T));

  // MATLAB Function: '<Root>/D1'
  CartesianImpedance_Task_svd(CartesianImpedance_Task_B.Sinv_sat,
    CartesianImpedance_Task_B.ProductofElements1, CartesianImpedance_Task_B.U,
    CartesianImpedance_Task_B.R);
  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 6;
       CartesianImpedance_Task_B.i++) {
    // MATLAB Function: '<Root>/D' incorporates:
    //   MATLAB Function: '<Root>/D1'

    CartesianImpedance_Task_B.vcol = CartesianImpedance_Task_B.i + 6 *
      CartesianImpedance_Task_B.i;
    CartesianImpedance_Task_B.D_e[CartesianImpedance_Task_B.vcol] =
      CartesianImpedance_Task_B.s[CartesianImpedance_Task_B.i];

    // MATLAB Function: '<Root>/D1'
    CartesianImpedance_Task_B.s[CartesianImpedance_Task_B.i] = std::sqrt(1.0 /
      CartesianImpedance_Task_B.U[CartesianImpedance_Task_B.vcol]);
  }

  // Math: '<S10>/Math Function'
  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 4;
       CartesianImpedance_Task_B.i++) {
    CartesianImpedance_Task_B.vcol = CartesianImpedance_Task_B.i << 2;
    CartesianImpedance_Task_B.MathFunction[CartesianImpedance_Task_B.vcol] =
      CartesianImpedance_Task_B.MatrixConcatenate[CartesianImpedance_Task_B.i];
    CartesianImpedance_Task_B.MathFunction[CartesianImpedance_Task_B.vcol + 1] =
      CartesianImpedance_Task_B.MatrixConcatenate[CartesianImpedance_Task_B.i +
      4];
    CartesianImpedance_Task_B.MathFunction[CartesianImpedance_Task_B.vcol + 2] =
      CartesianImpedance_Task_B.MatrixConcatenate[CartesianImpedance_Task_B.i +
      8];
    CartesianImpedance_Task_B.MathFunction[CartesianImpedance_Task_B.vcol + 3] =
      CartesianImpedance_Task_B.MatrixConcatenate[CartesianImpedance_Task_B.i +
      12];
  }

  // End of Math: '<S10>/Math Function'
  CoordinateTransformationConvers(CartesianImpedance_Task_B.MathFunction,
    &CartesianImpedance_Task_B.CoordinateTransformationConv_pn);

  // Math: '<S5>/Math Function'
  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 4;
       CartesianImpedance_Task_B.i++) {
    CartesianImpedance_Task_B.vcol = CartesianImpedance_Task_B.i << 2;
    CartesianImpedance_Task_B.MathFunction_b[CartesianImpedance_Task_B.vcol] =
      CartesianImpedance_Task_B.MatrixConcatenate_k[CartesianImpedance_Task_B.i];
    CartesianImpedance_Task_B.MathFunction_b[CartesianImpedance_Task_B.vcol + 1]
      =
      CartesianImpedance_Task_B.MatrixConcatenate_k[CartesianImpedance_Task_B.i
      + 4];
    CartesianImpedance_Task_B.MathFunction_b[CartesianImpedance_Task_B.vcol + 2]
      =
      CartesianImpedance_Task_B.MatrixConcatenate_k[CartesianImpedance_Task_B.i
      + 8];
    CartesianImpedance_Task_B.MathFunction_b[CartesianImpedance_Task_B.vcol + 3]
      =
      CartesianImpedance_Task_B.MatrixConcatenate_k[CartesianImpedance_Task_B.i
      + 12];
  }

  // End of Math: '<S5>/Math Function'
  CoordinateTransformationConvers(CartesianImpedance_Task_B.MathFunction_b,
    &CartesianImpedance_Task_B.CoordinateTransformationConve_p);

  // MATLAB Function: '<S4>/QuaternionOrientationError '
  CartesianImpedance_Task_B.absx =
    CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_i
    [0];
  CartesianImpedance_Task_B.quat_ref_idx_1 =
    CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_i
    [1];
  CartesianImpedance_Task_B.quat_ref_idx_2 =
    CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_i
    [2];
  CartesianImpedance_Task_B.quat_ref_idx_3 =
    CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_i
    [3];
  if (((CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_i
        [0] *
        CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
        [0] +
        CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_i
        [1] *
        CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
        [1]) +
       CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_i
       [2] *
       CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
       [2]) +
      CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_i
      [3] *
      CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
      [3] < 0.0) {
    CartesianImpedance_Task_B.absx =
      -CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_i
      [0];
    CartesianImpedance_Task_B.quat_ref_idx_1 =
      -CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_i
      [1];
    CartesianImpedance_Task_B.quat_ref_idx_2 =
      -CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_i
      [2];
    CartesianImpedance_Task_B.quat_ref_idx_3 =
      -CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_i
      [3];
  }

  // Gain: '<S4>/Gain' incorporates:
  //   MATLAB Function: '<S4>/QuaternionOrientationError '

  CartesianImpedance_Task_B.s[3] = ((CartesianImpedance_Task_B.absx *
    CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
    [1] -
    CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
    [0] * CartesianImpedance_Task_B.quat_ref_idx_1) -
    (CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
     [2] * CartesianImpedance_Task_B.quat_ref_idx_3 -
     CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
     [3] * CartesianImpedance_Task_B.quat_ref_idx_2)) * 2.0;

  // Sum: '<S4>/Sum' incorporates:
  //   Selector: '<S4>/Selector'
  //   Selector: '<S4>/Selector1'

  CartesianImpedance_Task_B.s[0] = CartesianImpedance_Task_B.MathFunction[12] -
    CartesianImpedance_Task_B.MathFunction_b[12];

  // Gain: '<S4>/Gain' incorporates:
  //   MATLAB Function: '<S4>/QuaternionOrientationError '

  CartesianImpedance_Task_B.s[4] = ((CartesianImpedance_Task_B.absx *
    CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
    [2] -
    CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
    [0] * CartesianImpedance_Task_B.quat_ref_idx_2) -
    (CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
     [3] * CartesianImpedance_Task_B.quat_ref_idx_1 -
     CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
     [1] * CartesianImpedance_Task_B.quat_ref_idx_3)) * 2.0;

  // Sum: '<S4>/Sum' incorporates:
  //   Selector: '<S4>/Selector'
  //   Selector: '<S4>/Selector1'

  CartesianImpedance_Task_B.s[1] = CartesianImpedance_Task_B.MathFunction[13] -
    CartesianImpedance_Task_B.MathFunction_b[13];

  // Gain: '<S4>/Gain' incorporates:
  //   MATLAB Function: '<S4>/QuaternionOrientationError '

  CartesianImpedance_Task_B.s[5] = ((CartesianImpedance_Task_B.absx *
    CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
    [3] -
    CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
    [0] * CartesianImpedance_Task_B.quat_ref_idx_3) -
    (CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
     [1] * CartesianImpedance_Task_B.quat_ref_idx_2 -
     CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_i
     [2] * CartesianImpedance_Task_B.quat_ref_idx_1)) * 2.0;

  // Sum: '<S4>/Sum' incorporates:
  //   Selector: '<S4>/Selector'
  //   Selector: '<S4>/Selector1'

  CartesianImpedance_Task_B.s[2] = CartesianImpedance_Task_B.MathFunction[14] -
    CartesianImpedance_Task_B.MathFunction_b[14];

  // S-Function (BlockFactory): '<Root>/getJointVelocity'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.getJointVelocity_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.getJointVelocity_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/getJointVelocity

  // S-Function (BlockFactory): '<Root>/computeGravityCompensation'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.computeGravityCompensation_PWOR.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.computeGravityCompensation_PWOR.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/computeGravityCompensation

  // Product: '<Root>/Product of Elements4'
  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 6;
       CartesianImpedance_Task_B.i++) {
    CartesianImpedance_Task_B.dv1[CartesianImpedance_Task_B.i] = 0.0;
    for (CartesianImpedance_Task_B.b_j = 0; CartesianImpedance_Task_B.b_j < 5;
         CartesianImpedance_Task_B.b_j++) {
      CartesianImpedance_Task_B.dv1[CartesianImpedance_Task_B.i] +=
        CartesianImpedance_Task_B.getJacobian_o1[6 *
        CartesianImpedance_Task_B.b_j + CartesianImpedance_Task_B.i] *
        CartesianImpedance_Task_B.getJointVelocity[CartesianImpedance_Task_B.b_j];
    }
  }

  // End of Product: '<Root>/Product of Elements4'
  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 6;
       CartesianImpedance_Task_B.i++) {
    // Product: '<Root>/Product of Elements3'
    CartesianImpedance_Task_B.rtb_D_e_p[CartesianImpedance_Task_B.i] = 0.0;

    // Sum: '<Root>/Sum'
    CartesianImpedance_Task_B.absx = 0.0;
    for (CartesianImpedance_Task_B.b_j = 0; CartesianImpedance_Task_B.b_j < 6;
         CartesianImpedance_Task_B.b_j++) {
      // Sum: '<Root>/Sum' incorporates:
      //   Product: '<Root>/Product of Elements2'
      //   Product: '<Root>/Product of Elements3'

      CartesianImpedance_Task_B.ar = 6 * CartesianImpedance_Task_B.b_j +
        CartesianImpedance_Task_B.i;
      CartesianImpedance_Task_B.absx +=
        CartesianImpedance_Task_B.K[CartesianImpedance_Task_B.ar] *
        CartesianImpedance_Task_B.s[CartesianImpedance_Task_B.b_j];

      // Product: '<Root>/Product of Elements3'
      CartesianImpedance_Task_B.rtb_D_e_p[CartesianImpedance_Task_B.i] +=
        CartesianImpedance_Task_B.D_e[CartesianImpedance_Task_B.ar] *
        CartesianImpedance_Task_B.dv1[CartesianImpedance_Task_B.b_j];
    }

    // Sum: '<Root>/Sum' incorporates:
    //   Product: '<Root>/Product of Elements2'

    CartesianImpedance_Task_B.rtb_K_c[CartesianImpedance_Task_B.i] =
      CartesianImpedance_Task_B.absx +
      CartesianImpedance_Task_B.rtb_D_e_p[CartesianImpedance_Task_B.i];
  }

  // Sum: '<Root>/Sum1' incorporates:
  //   Math: '<Root>/Math Function1'
  //   Product: '<Root>/Product of Elements5'

  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 5;
       CartesianImpedance_Task_B.i++) {
    CartesianImpedance_Task_B.absx = 0.0;
    for (CartesianImpedance_Task_B.b_j = 0; CartesianImpedance_Task_B.b_j < 6;
         CartesianImpedance_Task_B.b_j++) {
      CartesianImpedance_Task_B.absx +=
        CartesianImpedance_Task_B.rtb_MultiportSwitch_tmp_tmp[5 *
        CartesianImpedance_Task_B.b_j + CartesianImpedance_Task_B.i] *
        CartesianImpedance_Task_B.rtb_K_c[CartesianImpedance_Task_B.b_j];
    }

    CartesianImpedance_Task_B.Sum1[CartesianImpedance_Task_B.i] =
      CartesianImpedance_Task_B.computeGravityCompensation[CartesianImpedance_Task_B.i]
      - CartesianImpedance_Task_B.absx;
  }

  // End of Sum: '<Root>/Sum1'

  // S-Function (BlockFactory): '<Root>/setEffortReference'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.setEffortReference_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.setEffortReference_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/setEffortReference

  // S-Function (BlockFactory): '<Root>/getStiffness'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.getStiffness_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.getStiffness_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/getStiffness

  // Gain: '<Root>/Gain'
  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 5;
       CartesianImpedance_Task_B.i++) {
    CartesianImpedance_Task_B.Gain[CartesianImpedance_Task_B.i] = 0.0 *
      CartesianImpedance_Task_B.getStiffness[CartesianImpedance_Task_B.i];
  }

  // End of Gain: '<Root>/Gain'

  // S-Function (BlockFactory): '<Root>/setStiffness1'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.setStiffness1_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.setStiffness1_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/setStiffness1

  // S-Function (BlockFactory): '<Root>/getDamping'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.getDamping_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.getDamping_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/getDamping

  // Gain: '<Root>/Gain1'
  for (CartesianImpedance_Task_B.i = 0; CartesianImpedance_Task_B.i < 5;
       CartesianImpedance_Task_B.i++) {
    CartesianImpedance_Task_B.Gain1[CartesianImpedance_Task_B.i] = 0.0 *
      CartesianImpedance_Task_B.getDamping[CartesianImpedance_Task_B.i];
  }

  // End of Gain: '<Root>/Gain1'

  // S-Function (BlockFactory): '<Root>/setDamping'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.setDamping_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.setDamping_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/setDamping

  // S-Function (BlockFactory): '<Root>/getInertiaMatrix'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (CartesianImpedance_Task_DW.getInertiaMatrix_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (CartesianImpedance_Task_DW.getInertiaMatrix_PWORK.blockPWork[0]);

    // Calculate the output
    // --------------------
    bool ok;
    ok = blockPtr->output(blockInfo);

    // Report errors
    if (!ok) {
      std::string error = blockfactory::core::Log::getSingleton().getErrors();
      error = "[Output]" + error;

      // Trim the message if needed
      if (error.length() >= 1024) {
        error = error.substr(0, 1024-1);
      }

      // This shouldn't happen
      //if (getRTM()->errorStatus) {
      //    delete getRTM()->errorStatus;
      //    getRTM()->errorStatus = nullptr;
      //}

      //getRTM()->errorStatus = new char[1024];
      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
      printf("%s\n", error.c_str());
      return;
    }
  }

  // End of S-Function Block: <Root>/getInertiaMatrix
}

// Model initialize function
void modelModelClass::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // block I/O
  (void) std::memset((static_cast<void *>(&CartesianImpedance_Task_B)), 0,
                     sizeof(B_CartesianImpedance_Task_T));

  // states (dwork)
  (void) std::memset(static_cast<void *>(&CartesianImpedance_Task_DW), 0,
                     sizeof(DW_CartesianImpedance_Task_T));

  // Start for S-Function (BlockFactory): '<Root>/getJointPosition'
  {
    // Create and store the CoderBlockInformation object
    blockfactory::coder::CoderBlockInformation* blockInfo = new blockfactory::
      coder::CoderBlockInformation();
    CartesianImpedance_Task_DW.getJointPosition_PWORK.blockPWork[1] =
      static_cast<void*>(blockInfo);

    // Initialize the parameters
    // -------------------------
    blockfactory::core::Parameters params;
    params.storeParameter<std::string>("Off",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 6.0, 1.0, 1.0, "ModelUpdateType"));
    params.storeParameter<std::string>("OpenLoop",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 5.0, 1.0, 1.0, "SenseType"));
    params.storeParameter<std::string>("Robot",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 4.0, 1.0, 1.0, "GetType"));
    params.storeParameter<std::string>("XBotBlock_getJointPosition",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 0.0, 1.0, 1.0, "className"));
    params.storeParameter<std::string>("off",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 7.0, 1.0, 1.0, "OptimizeOperations"));
    params.storeParameter<std::string>("getJointPosition",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 1.0, 1.0, 1.0, "libName"));
    params.storeParameter<std::string>("DefaultModel",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 3.0, 1.0, 1.0, "ModelName"));
    params.storeParameter<std::string>("DefaultRobot",
      blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
      STRING, 2.0, 1.0, 1.0, "RobotName"));

    // Store the block name
    blockInfo->setUniqueBlockName("CartesianImpedance_Task/getJointPosition");

    // Store the parameters in the CoderBlockInformation object
    blockInfo->storeRTWParameters(params);

    // Initialize input / output Signals
    // ---------------------------------

    // Inputs

    // Outputs
    blockInfo->setOutputPort(
    {
      0, {
        1, 5
      }, blockfactory::core::Port::DataType::DOUBLE
    }

      ,
        static_cast<void*>(&CartesianImpedance_Task_B.getJointPosition[0]));

      // Initialize the class
      // --------------------

      // Get the block factory
      auto factory = blockfactory::core::ClassFactorySingleton::getInstance().
        getClassFactory(
                        {
                        "getJointPosition", "XBotBlock_getJointPosition"
                        } );

      if (!factory) {
        bfError << "Failed to get factory object (className=" <<
          "XBotBlock_getJointPosition"
          << ",libName=" << "getJointPosition" << ")";
        std::string error = blockfactory::core::Log::getSingleton().getErrors();
        error = "[Initialize]" + error;

        // Trim the message if needed
        if (error.length() >= 1024) {
          error = error.substr(0, 1024-1);
        }

        // This shouldn't happen
        //if (getRTM()->errorStatus) {
        //    delete getRTM()->errorStatus;
        //    getRTM()->errorStatus = nullptr;
        //}

        //getRTM()->errorStatus = new char[1024];
        //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
        printf("%s\n", error.c_str());
        return;
      }

      if (!factory->isValid()) {
        bfError << "Factory error (" << static_cast<std::uint32_t>
          (factory->getStatus())
          << "): " << factory->getError().c_str();
        std::string error = blockfactory::core::Log::getSingleton().getErrors();
        error = "[Initialize]" + error;

        // Trim the message if needed
        if (error.length() >= 1024) {
          error = error.substr(0, 1024-1);
        }

        // This shouldn't happen
        //if (getRTM()->errorStatus) {
        //    delete getRTM()->errorStatus;
        //    getRTM()->errorStatus = nullptr;
        //}

        //getRTM()->errorStatus = new char[1024];
        //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
        printf("%s\n", error.c_str());
        return;
      }

      // Run a dummy configureSizeAndPorts step. This is currently required for properly
      // handling optional input / outputs static variables.
      // TODO: find a better way to handle them.
      {
        // Create a new class. This object will be destroyed at the end of the scope.
        shlibpp::SharedLibraryClass<blockfactory::core::Block> blockPtr(*factory);
        auto tmpCoderBlockInfo = std::unique_ptr<blockfactory::coder::
          CoderBlockInformation>(
          new blockfactory::coder::CoderBlockInformation);
        tmpCoderBlockInfo->storeRTWParameters(params);
        blockPtr->configureSizeAndPorts(tmpCoderBlockInfo.get());
      }

      // Allocate the block
      blockfactory::core::Block* blockPtr = factory->create();
      factory->addRef();

      // Initialize the block
      bool ok = blockPtr->initialize(blockInfo);

      // Report errors
      if (!ok) {
        std::string error = blockfactory::core::Log::getSingleton().getErrors();
        error = "[Initialize]" + error;

        // Trim the message if needed
        if (error.length() >= 1024) {
          error = error.substr(0, 1024-1);
        }

        // This shouldn't happen
        //if (getRTM()->errorStatus) {
        //    delete getRTM()->errorStatus;
        //    getRTM()->errorStatus = nullptr;
        //}

        //getRTM()->errorStatus = new char[1024];
        //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
        printf("%s\n", error.c_str());
        return;
      }

      // Call the initializeInitialConditions() method
      ok = blockPtr->initializeInitialConditions(blockInfo);

      // Report errors
      if (!ok) {
        std::string error = blockfactory::core::Log::getSingleton().getErrors();
        error = "[InitializeInitialConditions]" + error;

        // Trim the message if needed
        if (error.length() >= 1024) {
          error = error.substr(0, 1024-1);
        }

        // This shouldn't happen
        //if (getRTM()->errorStatus) {
        //    delete getRTM()->errorStatus;
        //    getRTM()->errorStatus = nullptr;
        //}

        //getRTM()->errorStatus = new char[1024];
        //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
        printf("%s\n", error.c_str());
        return;
      }

      // Store the block in the PWork vector
      CartesianImpedance_Task_DW.getJointPosition_PWORK.blockPWork[0] =
        static_cast<void*>(blockPtr);
    }
    // End of S-Function Block: <Root>/getJointPosition
    // Start for S-Function (BlockFactory): '<Root>/setPositionReference1'
{
      // Create and store the CoderBlockInformation object
      blockfactory::coder::CoderBlockInformation* blockInfo = new blockfactory::
        coder::CoderBlockInformation();
      CartesianImpedance_Task_DW.setPositionReference1_PWORK.blockPWork[1] =
        static_cast<void*>(blockInfo);

      // Initialize the parameters
      // -------------------------
      blockfactory::core::Parameters params;
      params.storeParameter<std::string>("DefaultRobot",
        blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
        STRING, 2.0, 1.0, 1.0, "RobotName"));
      params.storeParameter<std::string>("setPositionReference",
        blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
        STRING, 1.0, 1.0, 1.0, "libName"));
      params.storeParameter<std::string>("Off",
        blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
        STRING, 3.0, 1.0, 1.0, "MoveRobot"));
      params.storeParameter<std::string>("XBotBlock_setPositionReference",
        blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
        STRING, 0.0, 1.0, 1.0, "className"));

      // Store the block name
      blockInfo->setUniqueBlockName(
        "CartesianImpedance_Task/setPositionReference1");

      // Store the parameters in the CoderBlockInformation object
      blockInfo->storeRTWParameters(params);

      // Initialize input / output Signals
      // ---------------------------------

      // Inputs
      blockInfo->setInputPort(
      {
        0, {
                              1, 5
        }, blockfactory::core::Port::DataType::DOUBLE
      }

        ,
                              static_cast<void*>
                              (&CartesianImpedance_Task_B.getJointPosition[0]));

        // Outputs

        // Initialize the class
        // --------------------

        // Get the block factory
        auto factory = blockfactory::core::ClassFactorySingleton::getInstance().
          getClassFactory(
                          {
                          "setPositionReference",
                          "XBotBlock_setPositionReference"
                          } );

        if (!factory) {
          bfError << "Failed to get factory object (className=" <<
            "XBotBlock_setPositionReference"
            << ",libName=" << "setPositionReference" << ")";
          std::string error = blockfactory::core::Log::getSingleton().getErrors();
          error = "[Initialize]" + error;

          // Trim the message if needed
          if (error.length() >= 1024) {
            error = error.substr(0, 1024-1);
          }

          // This shouldn't happen
          //if (getRTM()->errorStatus) {
          //    delete getRTM()->errorStatus;
          //    getRTM()->errorStatus = nullptr;
          //}

          //getRTM()->errorStatus = new char[1024];
          //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
          printf("%s\n", error.c_str());
          return;
        }

        if (!factory->isValid()) {
          bfError << "Factory error (" << static_cast<std::uint32_t>
            (factory->getStatus())
            << "): " << factory->getError().c_str();
          std::string error = blockfactory::core::Log::getSingleton().getErrors();
          error = "[Initialize]" + error;

          // Trim the message if needed
          if (error.length() >= 1024) {
            error = error.substr(0, 1024-1);
          }

          // This shouldn't happen
          //if (getRTM()->errorStatus) {
          //    delete getRTM()->errorStatus;
          //    getRTM()->errorStatus = nullptr;
          //}

          //getRTM()->errorStatus = new char[1024];
          //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
          printf("%s\n", error.c_str());
          return;
        }

        // Run a dummy configureSizeAndPorts step. This is currently required for properly
        // handling optional input / outputs static variables.
        // TODO: find a better way to handle them.
        {
          // Create a new class. This object will be destroyed at the end of the scope.
          shlibpp::SharedLibraryClass<blockfactory::core::Block> blockPtr
            (*factory);
          auto tmpCoderBlockInfo = std::unique_ptr<blockfactory::coder::
            CoderBlockInformation>(
            new blockfactory::coder::CoderBlockInformation);
          tmpCoderBlockInfo->storeRTWParameters(params);
          blockPtr->configureSizeAndPorts(tmpCoderBlockInfo.get());
        }

        // Allocate the block
        blockfactory::core::Block* blockPtr = factory->create();
        factory->addRef();

        // Initialize the block
        bool ok = blockPtr->initialize(blockInfo);

        // Report errors
        if (!ok) {
          std::string error = blockfactory::core::Log::getSingleton().getErrors();
          error = "[Initialize]" + error;

          // Trim the message if needed
          if (error.length() >= 1024) {
            error = error.substr(0, 1024-1);
          }

          // This shouldn't happen
          //if (getRTM()->errorStatus) {
          //    delete getRTM()->errorStatus;
          //    getRTM()->errorStatus = nullptr;
          //}

          //getRTM()->errorStatus = new char[1024];
          //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
          printf("%s\n", error.c_str());
          return;
        }

        // Call the initializeInitialConditions() method
        ok = blockPtr->initializeInitialConditions(blockInfo);

        // Report errors
        if (!ok) {
          std::string error = blockfactory::core::Log::getSingleton().getErrors();
          error = "[InitializeInitialConditions]" + error;

          // Trim the message if needed
          if (error.length() >= 1024) {
            error = error.substr(0, 1024-1);
          }

          // This shouldn't happen
          //if (getRTM()->errorStatus) {
          //    delete getRTM()->errorStatus;
          //    getRTM()->errorStatus = nullptr;
          //}

          //getRTM()->errorStatus = new char[1024];
          //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
          printf("%s\n", error.c_str());
          return;
        }

        // Store the block in the PWork vector
        CartesianImpedance_Task_DW.setPositionReference1_PWORK.blockPWork[0] =
          static_cast<void*>(blockPtr);
      }
      // End of S-Function Block: <Root>/setPositionReference1
      // Start for S-Function (BlockFactory): '<S10>/getPoseFun'
{
        // Create and store the CoderBlockInformation object
        blockfactory::coder::CoderBlockInformation* blockInfo = new blockfactory::
          coder::CoderBlockInformation();
        CartesianImpedance_Task_DW.getPoseFun_PWORK.blockPWork[1] = static_cast<
          void*>(blockInfo);

        // Initialize the parameters
        // -------------------------
        blockfactory::core::Parameters params;
        params.storeParameter<std::string>("CloseLoop",
          blockfactory::core::ParameterMetadata(blockfactory::core::
          ParameterType::STRING, 6.0, 1.0, 1.0, "SenseType"));
        params.storeParameter<std::string>("DefaultRobot",
          blockfactory::core::ParameterMetadata(blockfactory::core::
          ParameterType::STRING, 5.0, 1.0, 1.0, "RobotName"));
        params.storeParameter<std::string>("teleop_link0",
          blockfactory::core::ParameterMetadata(blockfactory::core::
          ParameterType::STRING, 4.0, 1.0, 1.0, "TargetFrame"));
        params.storeParameter<std::string>("XBotBlock_getPose",
          blockfactory::core::ParameterMetadata(blockfactory::core::
          ParameterType::STRING, 0.0, 1.0, 1.0, "className"));
        params.storeParameter<std::string>("Off",
          blockfactory::core::ParameterMetadata(blockfactory::core::
          ParameterType::STRING, 7.0, 1.0, 1.0, "ModelUpdateType"));
        params.storeParameter<std::string>("TCP",
          blockfactory::core::ParameterMetadata(blockfactory::core::
          ParameterType::STRING, 3.0, 1.0, 1.0, "SourceFrame"));
        params.storeParameter<std::string>("off",
          blockfactory::core::ParameterMetadata(blockfactory::core::
          ParameterType::STRING, 8.0, 1.0, 1.0, "OptimizeOperations"));
        params.storeParameter<std::string>("getPose",
          blockfactory::core::ParameterMetadata(blockfactory::core::
          ParameterType::STRING, 1.0, 1.0, 1.0, "libName"));
        params.storeParameter<std::string>("DefaultModel",
          blockfactory::core::ParameterMetadata(blockfactory::core::
          ParameterType::STRING, 2.0, 1.0, 1.0, "ModelName"));

        // Store the block name
        blockInfo->setUniqueBlockName(
          "CartesianImpedance_Task/TargetPose/getPoseFun");

        // Store the parameters in the CoderBlockInformation object
        blockInfo->storeRTWParameters(params);

        // Initialize input / output Signals
        // ---------------------------------

        // Inputs

        // Outputs
        blockInfo->setOutputPort(
        {
          0, {
            1, 4
          }, blockfactory::core::Port::DataType::DOUBLE
        }

          ,
            static_cast<void*>(&CartesianImpedance_Task_B.MatrixConcatenate[0]));
          blockInfo->setOutputPort(
          {
            1, {
              1, 4
            }, blockfactory::core::Port::DataType::DOUBLE
          }

            ,
              static_cast<void*>(&CartesianImpedance_Task_B.MatrixConcatenate[4]));
            blockInfo->setOutputPort(
            {
              2, {
                1, 4
              }, blockfactory::core::Port::DataType::DOUBLE
            }

              ,
                static_cast<void*>(&CartesianImpedance_Task_B.MatrixConcatenate
                                   [8]));
              blockInfo->setOutputPort(
              {
                3, {
                  1, 4
                }, blockfactory::core::Port::DataType::DOUBLE
              }

                ,
                  static_cast<void*>
                  (&CartesianImpedance_Task_B.MatrixConcatenate[12]));

                // Initialize the class
                // --------------------

                // Get the block factory
                auto factory = blockfactory::core::ClassFactorySingleton::
                  getInstance().getClassFactory(
                {
                  "getPose", "XBotBlock_getPose"
                } );

                if (!factory) {
                  bfError << "Failed to get factory object (className=" <<
                    "XBotBlock_getPose"
                    << ",libName=" << "getPose" << ")";
                  std::string error = blockfactory::core::Log::getSingleton().
                    getErrors();
                  error = "[Initialize]" + error;

                  // Trim the message if needed
                  if (error.length() >= 1024) {
                    error = error.substr(0, 1024-1);
                  }

                  // This shouldn't happen
                  //if (getRTM()->errorStatus) {
                  //    delete getRTM()->errorStatus;
                  //    getRTM()->errorStatus = nullptr;
                  //}

                  //getRTM()->errorStatus = new char[1024];
                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                  printf("%s\n", error.c_str());
                  return;
                }

                if (!factory->isValid()) {
                  bfError << "Factory error (" << static_cast<std::uint32_t>
                    (factory->getStatus())
                    << "): " << factory->getError().c_str();
                  std::string error = blockfactory::core::Log::getSingleton().
                    getErrors();
                  error = "[Initialize]" + error;

                  // Trim the message if needed
                  if (error.length() >= 1024) {
                    error = error.substr(0, 1024-1);
                  }

                  // This shouldn't happen
                  //if (getRTM()->errorStatus) {
                  //    delete getRTM()->errorStatus;
                  //    getRTM()->errorStatus = nullptr;
                  //}

                  //getRTM()->errorStatus = new char[1024];
                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                  printf("%s\n", error.c_str());
                  return;
                }

                // Run a dummy configureSizeAndPorts step. This is currently required for properly
                // handling optional input / outputs static variables.
                // TODO: find a better way to handle them.
                {
                  // Create a new class. This object will be destroyed at the end of the scope.
                  shlibpp::SharedLibraryClass<blockfactory::core::Block>
                    blockPtr(*factory);
                  auto tmpCoderBlockInfo = std::unique_ptr<blockfactory::coder::
                    CoderBlockInformation>(
                    new blockfactory::coder::CoderBlockInformation);
                  tmpCoderBlockInfo->storeRTWParameters(params);
                  blockPtr->configureSizeAndPorts(tmpCoderBlockInfo.get());
                }

                // Allocate the block
                blockfactory::core::Block* blockPtr = factory->create();
                factory->addRef();

                // Initialize the block
                bool ok = blockPtr->initialize(blockInfo);

                // Report errors
                if (!ok) {
                  std::string error = blockfactory::core::Log::getSingleton().
                    getErrors();
                  error = "[Initialize]" + error;

                  // Trim the message if needed
                  if (error.length() >= 1024) {
                    error = error.substr(0, 1024-1);
                  }

                  // This shouldn't happen
                  //if (getRTM()->errorStatus) {
                  //    delete getRTM()->errorStatus;
                  //    getRTM()->errorStatus = nullptr;
                  //}

                  //getRTM()->errorStatus = new char[1024];
                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                  printf("%s\n", error.c_str());
                  return;
                }

                // Call the initializeInitialConditions() method
                ok = blockPtr->initializeInitialConditions(blockInfo);

                // Report errors
                if (!ok) {
                  std::string error = blockfactory::core::Log::getSingleton().
                    getErrors();
                  error = "[InitializeInitialConditions]" + error;

                  // Trim the message if needed
                  if (error.length() >= 1024) {
                    error = error.substr(0, 1024-1);
                  }

                  // This shouldn't happen
                  //if (getRTM()->errorStatus) {
                  //    delete getRTM()->errorStatus;
                  //    getRTM()->errorStatus = nullptr;
                  //}

                  //getRTM()->errorStatus = new char[1024];
                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                  printf("%s\n", error.c_str());
                  return;
                }

                // Store the block in the PWork vector
                CartesianImpedance_Task_DW.getPoseFun_PWORK.blockPWork[0] =
                  static_cast<void*>(blockPtr);
              }
              // End of S-Function Block: <S10>/getPoseFun
              // Start for S-Function (BlockFactory): '<S5>/getPoseFun'
{
                // Create and store the CoderBlockInformation object
                blockfactory::coder::CoderBlockInformation* blockInfo = new
                  blockfactory::coder::CoderBlockInformation();
                CartesianImpedance_Task_DW.getPoseFun_PWORK_h.blockPWork[1] =
                  static_cast<void*>(blockInfo);

                // Initialize the parameters
                // -------------------------
                blockfactory::core::Parameters params;
                params.storeParameter<std::string>("OpenLoop",
                  blockfactory::core::ParameterMetadata(blockfactory::core::
                  ParameterType::STRING, 6.0, 1.0, 1.0, "SenseType"));
                params.storeParameter<std::string>("DefaultRobot",
                  blockfactory::core::ParameterMetadata(blockfactory::core::
                  ParameterType::STRING, 5.0, 1.0, 1.0, "RobotName"));
                params.storeParameter<std::string>("teleop_link0",
                  blockfactory::core::ParameterMetadata(blockfactory::core::
                  ParameterType::STRING, 4.0, 1.0, 1.0, "TargetFrame"));
                params.storeParameter<std::string>("XBotBlock_getPose",
                  blockfactory::core::ParameterMetadata(blockfactory::core::
                  ParameterType::STRING, 0.0, 1.0, 1.0, "className"));
                params.storeParameter<std::string>("Off",
                  blockfactory::core::ParameterMetadata(blockfactory::core::
                  ParameterType::STRING, 7.0, 1.0, 1.0, "ModelUpdateType"));
                params.storeParameter<std::string>("TCP",
                  blockfactory::core::ParameterMetadata(blockfactory::core::
                  ParameterType::STRING, 3.0, 1.0, 1.0, "SourceFrame"));
                params.storeParameter<std::string>("off",
                  blockfactory::core::ParameterMetadata(blockfactory::core::
                  ParameterType::STRING, 8.0, 1.0, 1.0, "OptimizeOperations"));
                params.storeParameter<std::string>("getPose",
                  blockfactory::core::ParameterMetadata(blockfactory::core::
                  ParameterType::STRING, 1.0, 1.0, 1.0, "libName"));
                params.storeParameter<std::string>("DefaultModel",
                  blockfactory::core::ParameterMetadata(blockfactory::core::
                  ParameterType::STRING, 2.0, 1.0, 1.0, "ModelName"));

                // Store the block name
                blockInfo->setUniqueBlockName(
                  "CartesianImpedance_Task/GetPose/getPoseFun");

                // Store the parameters in the CoderBlockInformation object
                blockInfo->storeRTWParameters(params);

                // Initialize input / output Signals
                // ---------------------------------

                // Inputs

                // Outputs
                blockInfo->setOutputPort(
                {
                  0, {
                    1, 4
                  }, blockfactory::core::Port::DataType::DOUBLE
                }

                  ,
                    static_cast<void*>
                    (&CartesianImpedance_Task_B.MatrixConcatenate_k[0]));
                  blockInfo->setOutputPort(
                  {
                    1, {
                      1, 4
                    }, blockfactory::core::Port::DataType::DOUBLE
                  }

                    ,
                      static_cast<void*>
                      (&CartesianImpedance_Task_B.MatrixConcatenate_k[4]));
                    blockInfo->setOutputPort(
                    {
                      2, {
                        1, 4
                      }, blockfactory::core::Port::DataType::DOUBLE
                    }

                      ,
                        static_cast<void*>
                        (&CartesianImpedance_Task_B.MatrixConcatenate_k[8]));
                      blockInfo->setOutputPort(
                      {
                        3, {
                          1, 4
                        }, blockfactory::core::Port::DataType::DOUBLE
                      }

                        ,
                          static_cast<void*>
                          (&CartesianImpedance_Task_B.MatrixConcatenate_k[12]));

                        // Initialize the class
                        // --------------------

                        // Get the block factory
                        auto factory = blockfactory::core::ClassFactorySingleton::
                          getInstance().getClassFactory(
                        {
                          "getPose", "XBotBlock_getPose"
                        } );

                        if (!factory) {
                          bfError << "Failed to get factory object (className=" <<
                            "XBotBlock_getPose"
                            << ",libName=" << "getPose" << ")";
                          std::string error = blockfactory::core::Log::
                            getSingleton().getErrors();
                          error = "[Initialize]" + error;

                          // Trim the message if needed
                          if (error.length() >= 1024) {
                            error = error.substr(0, 1024-1);
                          }

                          // This shouldn't happen
                          //if (getRTM()->errorStatus) {
                          //    delete getRTM()->errorStatus;
                          //    getRTM()->errorStatus = nullptr;
                          //}

                          //getRTM()->errorStatus = new char[1024];
                          //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                          printf("%s\n", error.c_str());
                          return;
                        }

                        if (!factory->isValid()) {
                          bfError << "Factory error (" << static_cast<std::
                            uint32_t>(factory->getStatus())
                            << "): " << factory->getError().c_str();
                          std::string error = blockfactory::core::Log::
                            getSingleton().getErrors();
                          error = "[Initialize]" + error;

                          // Trim the message if needed
                          if (error.length() >= 1024) {
                            error = error.substr(0, 1024-1);
                          }

                          // This shouldn't happen
                          //if (getRTM()->errorStatus) {
                          //    delete getRTM()->errorStatus;
                          //    getRTM()->errorStatus = nullptr;
                          //}

                          //getRTM()->errorStatus = new char[1024];
                          //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                          printf("%s\n", error.c_str());
                          return;
                        }

                        // Run a dummy configureSizeAndPorts step. This is currently required for properly
                        // handling optional input / outputs static variables.
                        // TODO: find a better way to handle them.
                        {
                          // Create a new class. This object will be destroyed at the end of the scope.
                          shlibpp::SharedLibraryClass<blockfactory::core::Block>
                            blockPtr(*factory);
                          auto tmpCoderBlockInfo = std::unique_ptr<blockfactory::
                            coder::CoderBlockInformation>(
                            new blockfactory::coder::CoderBlockInformation);
                          tmpCoderBlockInfo->storeRTWParameters(params);
                          blockPtr->configureSizeAndPorts(tmpCoderBlockInfo.get());
                        }

                        // Allocate the block
                        blockfactory::core::Block* blockPtr = factory->create();
                        factory->addRef();

                        // Initialize the block
                        bool ok = blockPtr->initialize(blockInfo);

                        // Report errors
                        if (!ok) {
                          std::string error = blockfactory::core::Log::
                            getSingleton().getErrors();
                          error = "[Initialize]" + error;

                          // Trim the message if needed
                          if (error.length() >= 1024) {
                            error = error.substr(0, 1024-1);
                          }

                          // This shouldn't happen
                          //if (getRTM()->errorStatus) {
                          //    delete getRTM()->errorStatus;
                          //    getRTM()->errorStatus = nullptr;
                          //}

                          //getRTM()->errorStatus = new char[1024];
                          //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                          printf("%s\n", error.c_str());
                          return;
                        }

                        // Call the initializeInitialConditions() method
                        ok = blockPtr->initializeInitialConditions(blockInfo);

                        // Report errors
                        if (!ok) {
                          std::string error = blockfactory::core::Log::
                            getSingleton().getErrors();
                          error = "[InitializeInitialConditions]" + error;

                          // Trim the message if needed
                          if (error.length() >= 1024) {
                            error = error.substr(0, 1024-1);
                          }

                          // This shouldn't happen
                          //if (getRTM()->errorStatus) {
                          //    delete getRTM()->errorStatus;
                          //    getRTM()->errorStatus = nullptr;
                          //}

                          //getRTM()->errorStatus = new char[1024];
                          //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                          printf("%s\n", error.c_str());
                          return;
                        }

                        // Store the block in the PWork vector
                        CartesianImpedance_Task_DW.getPoseFun_PWORK_h.blockPWork[
                          0] = static_cast<void*>(blockPtr);
                      }
                      // End of S-Function Block: <S5>/getPoseFun
                      // Start for S-Function (BlockFactory): '<Root>/getJacobian' 
{
                        // Create and store the CoderBlockInformation object
                        blockfactory::coder::CoderBlockInformation* blockInfo =
                          new blockfactory::coder::CoderBlockInformation();
                        CartesianImpedance_Task_DW.getJacobian_PWORK.blockPWork
                          [1] = static_cast<void*>(blockInfo);

                        // Initialize the parameters
                        // -------------------------
                        blockfactory::core::Parameters params;
                        params.storeParameter<std::string>("Off",
                          blockfactory::core::ParameterMetadata(blockfactory::
                          core::ParameterType::STRING, 8.0, 1.0, 1.0,
                          "ModelUpdateType"));
                        params.storeParameter<std::string>("DefaultRobot",
                          blockfactory::core::ParameterMetadata(blockfactory::
                          core::ParameterType::STRING, 6.0, 1.0, 1.0,
                          "RobotName"));
                        params.storeParameter<std::string>("teleop_link0",
                          blockfactory::core::ParameterMetadata(blockfactory::
                          core::ParameterType::STRING, 5.0, 1.0, 1.0,
                          "TargetFrame"));
                        params.storeParameter<std::string>("Normal",
                          blockfactory::core::ParameterMetadata(blockfactory::
                          core::ParameterType::STRING, 4.0, 1.0, 1.0, "GetType"));
                        params.storeParameter<std::string>(
                          "XBotBlock_getJacobian",
                          blockfactory::core::ParameterMetadata(blockfactory::
                          core::ParameterType::STRING, 0.0, 1.0, 1.0,
                          "className"));
                        params.storeParameter<std::string>("off",
                          blockfactory::core::ParameterMetadata(blockfactory::
                          core::ParameterType::STRING, 9.0, 1.0, 1.0,
                          "OptimizeOperations"));
                        params.storeParameter<std::string>("getJacobian",
                          blockfactory::core::ParameterMetadata(blockfactory::
                          core::ParameterType::STRING, 1.0, 1.0, 1.0, "libName"));
                        params.storeParameter<std::string>("DefaultModel",
                          blockfactory::core::ParameterMetadata(blockfactory::
                          core::ParameterType::STRING, 2.0, 1.0, 1.0,
                          "ModelName"));
                        params.storeParameter<std::string>("CloseLoop",
                          blockfactory::core::ParameterMetadata(blockfactory::
                          core::ParameterType::STRING, 7.0, 1.0, 1.0,
                          "SenseType"));
                        params.storeParameter<std::string>("TCP",
                          blockfactory::core::ParameterMetadata(blockfactory::
                          core::ParameterType::STRING, 3.0, 1.0, 1.0, "LinkName"));

                        // Store the block name
                        blockInfo->setUniqueBlockName(
                          "CartesianImpedance_Task/getJacobian");

                        // Store the parameters in the CoderBlockInformation object
                        blockInfo->storeRTWParameters(params);

                        // Initialize input / output Signals
                        // ---------------------------------

                        // Inputs

                        // Outputs
                        blockInfo->setOutputPort(
                        {
                          0, {
                            6, 5
                          }, blockfactory::core::Port::DataType::DOUBLE
                        }

                          ,
                            static_cast<void*>
                            (&CartesianImpedance_Task_B.getJacobian_o1[0]));
                          blockInfo->setOutputPort(
                          {
                            1, {
                              1, 3
                            }, blockfactory::core::Port::DataType::DOUBLE
                          }

                            ,
                              static_cast<void*>
                              (&CartesianImpedance_Task_B.getJacobian_o2[0]));

                            // Initialize the class
                            // --------------------

                            // Get the block factory
                            auto factory = blockfactory::core::
                              ClassFactorySingleton::getInstance().
                              getClassFactory(
                                              {
                                              "getJacobian",
                                              "XBotBlock_getJacobian"
                                              } );

                            if (!factory) {
                              bfError <<
                                "Failed to get factory object (className=" <<
                                "XBotBlock_getJacobian"
                                << ",libName=" << "getJacobian" << ")";
                              std::string error = blockfactory::core::Log::
                                getSingleton().getErrors();
                              error = "[Initialize]" + error;

                              // Trim the message if needed
                              if (error.length() >= 1024) {
                                error = error.substr(0, 1024-1);
                              }

                              // This shouldn't happen
                              //if (getRTM()->errorStatus) {
                              //    delete getRTM()->errorStatus;
                              //    getRTM()->errorStatus = nullptr;
                              //}

                              //getRTM()->errorStatus = new char[1024];
                              //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                              printf("%s\n", error.c_str());
                              return;
                            }

                            if (!factory->isValid()) {
                              bfError << "Factory error (" << static_cast<std::
                                uint32_t>(factory->getStatus())
                                << "): " << factory->getError().c_str();
                              std::string error = blockfactory::core::Log::
                                getSingleton().getErrors();
                              error = "[Initialize]" + error;

                              // Trim the message if needed
                              if (error.length() >= 1024) {
                                error = error.substr(0, 1024-1);
                              }

                              // This shouldn't happen
                              //if (getRTM()->errorStatus) {
                              //    delete getRTM()->errorStatus;
                              //    getRTM()->errorStatus = nullptr;
                              //}

                              //getRTM()->errorStatus = new char[1024];
                              //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                              printf("%s\n", error.c_str());
                              return;
                            }

                            // Run a dummy configureSizeAndPorts step. This is currently required for properly
                            // handling optional input / outputs static variables.
                            // TODO: find a better way to handle them.
                            {
                              // Create a new class. This object will be destroyed at the end of the scope.
                              shlibpp::SharedLibraryClass<blockfactory::core::
                                Block> blockPtr(*factory);
                              auto tmpCoderBlockInfo = std::unique_ptr<
                                blockfactory::coder::CoderBlockInformation>(
                                new blockfactory::coder::CoderBlockInformation);
                              tmpCoderBlockInfo->storeRTWParameters(params);
                              blockPtr->configureSizeAndPorts
                                (tmpCoderBlockInfo.get());
                            }

                            // Allocate the block
                            blockfactory::core::Block* blockPtr =
                              factory->create();
                            factory->addRef();

                            // Initialize the block
                            bool ok = blockPtr->initialize(blockInfo);

                            // Report errors
                            if (!ok) {
                              std::string error = blockfactory::core::Log::
                                getSingleton().getErrors();
                              error = "[Initialize]" + error;

                              // Trim the message if needed
                              if (error.length() >= 1024) {
                                error = error.substr(0, 1024-1);
                              }

                              // This shouldn't happen
                              //if (getRTM()->errorStatus) {
                              //    delete getRTM()->errorStatus;
                              //    getRTM()->errorStatus = nullptr;
                              //}

                              //getRTM()->errorStatus = new char[1024];
                              //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                              printf("%s\n", error.c_str());
                              return;
                            }

                            // Call the initializeInitialConditions() method
                            ok = blockPtr->initializeInitialConditions(blockInfo);

                            // Report errors
                            if (!ok) {
                              std::string error = blockfactory::core::Log::
                                getSingleton().getErrors();
                              error = "[InitializeInitialConditions]" + error;

                              // Trim the message if needed
                              if (error.length() >= 1024) {
                                error = error.substr(0, 1024-1);
                              }

                              // This shouldn't happen
                              //if (getRTM()->errorStatus) {
                              //    delete getRTM()->errorStatus;
                              //    getRTM()->errorStatus = nullptr;
                              //}

                              //getRTM()->errorStatus = new char[1024];
                              //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                              printf("%s\n", error.c_str());
                              return;
                            }

                            // Store the block in the PWork vector
                            CartesianImpedance_Task_DW.getJacobian_PWORK.blockPWork
                              [0] = static_cast<void*>(blockPtr);
                          }
                          // End of S-Function Block: <Root>/getJacobian
                          // Start for S-Function (BlockFactory): '<Root>/getInertiaInverse' 
{
                            // Create and store the CoderBlockInformation object
                            blockfactory::coder::CoderBlockInformation*
                              blockInfo = new blockfactory::coder::
                              CoderBlockInformation();
                            CartesianImpedance_Task_DW.getInertiaInverse_PWORK.blockPWork
                              [1] = static_cast<void*>(blockInfo);

                            // Initialize the parameters
                            // -------------------------
                            blockfactory::core::Parameters params;
                            params.storeParameter<std::string>("Off",
                              blockfactory::core::ParameterMetadata(blockfactory::
                              core::ParameterType::STRING, 5.0, 1.0, 1.0,
                              "ModelUpdateType"));
                            params.storeParameter<std::string>("CloseLoop",
                              blockfactory::core::ParameterMetadata(blockfactory::
                              core::ParameterType::STRING, 4.0, 1.0, 1.0,
                              "SenseType"));
                            params.storeParameter<std::string>(
                              "XBotBlock_getInertiaInverse",
                              blockfactory::core::ParameterMetadata(blockfactory::
                              core::ParameterType::STRING, 0.0, 1.0, 1.0,
                              "className"));
                            params.storeParameter<std::string>("off",
                              blockfactory::core::ParameterMetadata(blockfactory::
                              core::ParameterType::STRING, 6.0, 1.0, 1.0,
                              "OptimizeOperations"));
                            params.storeParameter<std::string>(
                              "getInertiaInverse",
                              blockfactory::core::ParameterMetadata(blockfactory::
                              core::ParameterType::STRING, 1.0, 1.0, 1.0,
                              "libName"));
                            params.storeParameter<std::string>("DefaultModel",
                              blockfactory::core::ParameterMetadata(blockfactory::
                              core::ParameterType::STRING, 2.0, 1.0, 1.0,
                              "ModelName"));
                            params.storeParameter<std::string>("DefaultRobot",
                              blockfactory::core::ParameterMetadata(blockfactory::
                              core::ParameterType::STRING, 3.0, 1.0, 1.0,
                              "RobotName"));

                            // Store the block name
                            blockInfo->setUniqueBlockName(
                              "CartesianImpedance_Task/getInertiaInverse");

                            // Store the parameters in the CoderBlockInformation object
                            blockInfo->storeRTWParameters(params);

                            // Initialize input / output Signals
                            // ---------------------------------

                            // Inputs

                            // Outputs
                            blockInfo->setOutputPort(
                            {
                              0, {
                                5, 5
                              }, blockfactory::core::Port::DataType::DOUBLE
                            }

                              ,
                                static_cast<void*>
                                (&CartesianImpedance_Task_B.getInertiaInverse[0]));

                              // Initialize the class
                              // --------------------

                              // Get the block factory
                              auto factory = blockfactory::core::
                                ClassFactorySingleton::getInstance().
                                getClassFactory(
                                                {
                                                "getInertiaInverse",
                                                "XBotBlock_getInertiaInverse"
                                                } );

                              if (!factory) {
                                bfError <<
                                  "Failed to get factory object (className=" <<
                                  "XBotBlock_getInertiaInverse"
                                  << ",libName=" << "getInertiaInverse" << ")";
                                std::string error = blockfactory::core::Log::
                                  getSingleton().getErrors();
                                error = "[Initialize]" + error;

                                // Trim the message if needed
                                if (error.length() >= 1024) {
                                  error = error.substr(0, 1024-1);
                                }

                                // This shouldn't happen
                                //if (getRTM()->errorStatus) {
                                //    delete getRTM()->errorStatus;
                                //    getRTM()->errorStatus = nullptr;
                                //}

                                //getRTM()->errorStatus = new char[1024];
                                //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                printf("%s\n", error.c_str());
                                return;
                              }

                              if (!factory->isValid()) {
                                bfError << "Factory error (" << static_cast<std::
                                  uint32_t>(factory->getStatus())
                                  << "): " << factory->getError().c_str();
                                std::string error = blockfactory::core::Log::
                                  getSingleton().getErrors();
                                error = "[Initialize]" + error;

                                // Trim the message if needed
                                if (error.length() >= 1024) {
                                  error = error.substr(0, 1024-1);
                                }

                                // This shouldn't happen
                                //if (getRTM()->errorStatus) {
                                //    delete getRTM()->errorStatus;
                                //    getRTM()->errorStatus = nullptr;
                                //}

                                //getRTM()->errorStatus = new char[1024];
                                //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                printf("%s\n", error.c_str());
                                return;
                              }

                              // Run a dummy configureSizeAndPorts step. This is currently required for properly
                              // handling optional input / outputs static variables.
                              // TODO: find a better way to handle them.
                              {
                                // Create a new class. This object will be destroyed at the end of the scope.
                                shlibpp::SharedLibraryClass<blockfactory::core::
                                  Block> blockPtr(*factory);
                                auto tmpCoderBlockInfo = std::unique_ptr<
                                  blockfactory::coder::CoderBlockInformation>(
                                  new blockfactory::coder::CoderBlockInformation);
                                tmpCoderBlockInfo->storeRTWParameters(params);
                                blockPtr->configureSizeAndPorts
                                  (tmpCoderBlockInfo.get());
                              }

                              // Allocate the block
                              blockfactory::core::Block* blockPtr =
                                factory->create();
                              factory->addRef();

                              // Initialize the block
                              bool ok = blockPtr->initialize(blockInfo);

                              // Report errors
                              if (!ok) {
                                std::string error = blockfactory::core::Log::
                                  getSingleton().getErrors();
                                error = "[Initialize]" + error;

                                // Trim the message if needed
                                if (error.length() >= 1024) {
                                  error = error.substr(0, 1024-1);
                                }

                                // This shouldn't happen
                                //if (getRTM()->errorStatus) {
                                //    delete getRTM()->errorStatus;
                                //    getRTM()->errorStatus = nullptr;
                                //}

                                //getRTM()->errorStatus = new char[1024];
                                //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                printf("%s\n", error.c_str());
                                return;
                              }

                              // Call the initializeInitialConditions() method
                              ok = blockPtr->initializeInitialConditions
                                (blockInfo);

                              // Report errors
                              if (!ok) {
                                std::string error = blockfactory::core::Log::
                                  getSingleton().getErrors();
                                error = "[InitializeInitialConditions]" + error;

                                // Trim the message if needed
                                if (error.length() >= 1024) {
                                  error = error.substr(0, 1024-1);
                                }

                                // This shouldn't happen
                                //if (getRTM()->errorStatus) {
                                //    delete getRTM()->errorStatus;
                                //    getRTM()->errorStatus = nullptr;
                                //}

                                //getRTM()->errorStatus = new char[1024];
                                //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                printf("%s\n", error.c_str());
                                return;
                              }

                              // Store the block in the PWork vector
                              CartesianImpedance_Task_DW.getInertiaInverse_PWORK.blockPWork
                                [0] = static_cast<void*>(blockPtr);
                            }
                            // End of S-Function Block: <Root>/getInertiaInverse
                              CoordinateTransformationC_Start
                              (&CartesianImpedance_Task_DW.CoordinateTransformationConv_pn);

                            CoordinateTransformationC_Start
                              (&CartesianImpedance_Task_DW.CoordinateTransformationConve_p);

                            // Start for S-Function (BlockFactory): '<Root>/getJointVelocity' 
                            {
                              // Create and store the CoderBlockInformation object
                              blockfactory::coder::CoderBlockInformation*
                                blockInfo = new blockfactory::coder::
                                CoderBlockInformation();
                              CartesianImpedance_Task_DW.getJointVelocity_PWORK.blockPWork
                                [1] = static_cast<void*>(blockInfo);

                              // Initialize the parameters
                              // -------------------------
                              blockfactory::core::Parameters params;
                              params.storeParameter<std::string>("Off",
                                blockfactory::core::ParameterMetadata
                                (blockfactory::core::ParameterType::STRING, 6.0,
                                 1.0, 1.0, "ModelUpdateType"));
                              params.storeParameter<std::string>("CloseLoop",
                                blockfactory::core::ParameterMetadata
                                (blockfactory::core::ParameterType::STRING, 5.0,
                                 1.0, 1.0, "SenseType"));
                              params.storeParameter<std::string>("Robot",
                                blockfactory::core::ParameterMetadata
                                (blockfactory::core::ParameterType::STRING, 4.0,
                                 1.0, 1.0, "GetType"));
                              params.storeParameter<std::string>(
                                "XBotBlock_getJointVelocity",
                                blockfactory::core::ParameterMetadata
                                (blockfactory::core::ParameterType::STRING, 0.0,
                                 1.0, 1.0, "className"));
                              params.storeParameter<std::string>("off",
                                blockfactory::core::ParameterMetadata
                                (blockfactory::core::ParameterType::STRING, 7.0,
                                 1.0, 1.0, "OptimizeOperations"));
                              params.storeParameter<std::string>(
                                "getJointVelocity",
                                blockfactory::core::ParameterMetadata
                                (blockfactory::core::ParameterType::STRING, 1.0,
                                 1.0, 1.0, "libName"));
                              params.storeParameter<std::string>("DefaultModel",
                                blockfactory::core::ParameterMetadata
                                (blockfactory::core::ParameterType::STRING, 3.0,
                                 1.0, 1.0, "ModelName"));
                              params.storeParameter<std::string>("DefaultRobot",
                                blockfactory::core::ParameterMetadata
                                (blockfactory::core::ParameterType::STRING, 2.0,
                                 1.0, 1.0, "RobotName"));

                              // Store the block name
                              blockInfo->setUniqueBlockName(
                                "CartesianImpedance_Task/getJointVelocity");

                              // Store the parameters in the CoderBlockInformation object
                              blockInfo->storeRTWParameters(params);

                              // Initialize input / output Signals
                              // ---------------------------------

                              // Inputs

                              // Outputs
                              blockInfo->setOutputPort(
                              {
                                0, {
                                  1, 5
                                }, blockfactory::core::Port::DataType::DOUBLE
                              }

                                ,
                                  static_cast<void*>
                                  (&CartesianImpedance_Task_B.getJointVelocity[0]));

                                // Initialize the class
                                // --------------------

                                // Get the block factory
                                auto factory = blockfactory::core::
                                  ClassFactorySingleton::getInstance().
                                  getClassFactory(
                                                  {
                                                  "getJointVelocity",
                                                  "XBotBlock_getJointVelocity"
                                                  } );

                                if (!factory) {
                                  bfError <<
                                    "Failed to get factory object (className=" <<
                                    "XBotBlock_getJointVelocity"
                                    << ",libName=" << "getJointVelocity" << ")";
                                  std::string error = blockfactory::core::Log::
                                    getSingleton().getErrors();
                                  error = "[Initialize]" + error;

                                  // Trim the message if needed
                                  if (error.length() >= 1024) {
                                    error = error.substr(0, 1024-1);
                                  }

                                  // This shouldn't happen
                                  //if (getRTM()->errorStatus) {
                                  //    delete getRTM()->errorStatus;
                                  //    getRTM()->errorStatus = nullptr;
                                  //}

                                  //getRTM()->errorStatus = new char[1024];
                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                  printf("%s\n", error.c_str());
                                  return;
                                }

                                if (!factory->isValid()) {
                                  bfError << "Factory error (" <<
                                    static_cast<std::uint32_t>
                                    (factory->getStatus())
                                    << "): " << factory->getError().c_str();
                                  std::string error = blockfactory::core::Log::
                                    getSingleton().getErrors();
                                  error = "[Initialize]" + error;

                                  // Trim the message if needed
                                  if (error.length() >= 1024) {
                                    error = error.substr(0, 1024-1);
                                  }

                                  // This shouldn't happen
                                  //if (getRTM()->errorStatus) {
                                  //    delete getRTM()->errorStatus;
                                  //    getRTM()->errorStatus = nullptr;
                                  //}

                                  //getRTM()->errorStatus = new char[1024];
                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                  printf("%s\n", error.c_str());
                                  return;
                                }

                                // Run a dummy configureSizeAndPorts step. This is currently required for properly
                                // handling optional input / outputs static variables.
                                // TODO: find a better way to handle them.
                                {
                                  // Create a new class. This object will be destroyed at the end of the scope.
                                  shlibpp::SharedLibraryClass<blockfactory::core::
                                    Block> blockPtr(*factory);
                                  auto tmpCoderBlockInfo = std::unique_ptr<
                                    blockfactory::coder::CoderBlockInformation>(
                                    new blockfactory::coder::
                                    CoderBlockInformation);
                                  tmpCoderBlockInfo->storeRTWParameters(params);
                                  blockPtr->configureSizeAndPorts
                                    (tmpCoderBlockInfo.get());
                                }

                                // Allocate the block
                                blockfactory::core::Block* blockPtr =
                                  factory->create();
                                factory->addRef();

                                // Initialize the block
                                bool ok = blockPtr->initialize(blockInfo);

                                // Report errors
                                if (!ok) {
                                  std::string error = blockfactory::core::Log::
                                    getSingleton().getErrors();
                                  error = "[Initialize]" + error;

                                  // Trim the message if needed
                                  if (error.length() >= 1024) {
                                    error = error.substr(0, 1024-1);
                                  }

                                  // This shouldn't happen
                                  //if (getRTM()->errorStatus) {
                                  //    delete getRTM()->errorStatus;
                                  //    getRTM()->errorStatus = nullptr;
                                  //}

                                  //getRTM()->errorStatus = new char[1024];
                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                  printf("%s\n", error.c_str());
                                  return;
                                }

                                // Call the initializeInitialConditions() method
                                ok = blockPtr->initializeInitialConditions
                                  (blockInfo);

                                // Report errors
                                if (!ok) {
                                  std::string error = blockfactory::core::Log::
                                    getSingleton().getErrors();
                                  error = "[InitializeInitialConditions]" +
                                    error;

                                  // Trim the message if needed
                                  if (error.length() >= 1024) {
                                    error = error.substr(0, 1024-1);
                                  }

                                  // This shouldn't happen
                                  //if (getRTM()->errorStatus) {
                                  //    delete getRTM()->errorStatus;
                                  //    getRTM()->errorStatus = nullptr;
                                  //}

                                  //getRTM()->errorStatus = new char[1024];
                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                  printf("%s\n", error.c_str());
                                  return;
                                }

                                // Store the block in the PWork vector
                                CartesianImpedance_Task_DW.getJointVelocity_PWORK.blockPWork
                                  [0] = static_cast<void*>(blockPtr);
                              }
                              // End of S-Function Block: <Root>/getJointVelocity
                              // Start for S-Function (BlockFactory): '<Root>/computeGravityCompensation' 
{
                                // Create and store the CoderBlockInformation object
                                blockfactory::coder::CoderBlockInformation*
                                  blockInfo = new blockfactory::coder::
                                  CoderBlockInformation();
                                CartesianImpedance_Task_DW.computeGravityCompensation_PWOR.blockPWork
                                  [1] = static_cast<void*>(blockInfo);

                                // Initialize the parameters
                                // -------------------------
                                blockfactory::core::Parameters params;
                                params.storeParameter<std::string>("Off",
                                  blockfactory::core::ParameterMetadata
                                  (blockfactory::core::ParameterType::STRING,
                                   5.0, 1.0, 1.0, "ModelUpdateType"));
                                params.storeParameter<std::string>("CloseLoop",
                                  blockfactory::core::ParameterMetadata
                                  (blockfactory::core::ParameterType::STRING,
                                   4.0, 1.0, 1.0, "SenseType"));
                                params.storeParameter<std::string>(
                                  "XBotBlock_computeGravityCompensation",
                                  blockfactory::core::ParameterMetadata
                                  (blockfactory::core::ParameterType::STRING,
                                   0.0, 1.0, 1.0, "className"));
                                params.storeParameter<std::string>("off",
                                  blockfactory::core::ParameterMetadata
                                  (blockfactory::core::ParameterType::STRING,
                                   6.0, 1.0, 1.0, "OptimizeOperations"));
                                params.storeParameter<std::string>(
                                  "computeGravityCompensation",
                                  blockfactory::core::ParameterMetadata
                                  (blockfactory::core::ParameterType::STRING,
                                   1.0, 1.0, 1.0, "libName"));
                                params.storeParameter<std::string>(
                                  "DefaultModel",
                                  blockfactory::core::ParameterMetadata
                                  (blockfactory::core::ParameterType::STRING,
                                   2.0, 1.0, 1.0, "ModelName"));
                                params.storeParameter<std::string>(
                                  "DefaultRobot",
                                  blockfactory::core::ParameterMetadata
                                  (blockfactory::core::ParameterType::STRING,
                                   3.0, 1.0, 1.0, "RobotName"));

                                // Store the block name
                                blockInfo->setUniqueBlockName(
                                  "CartesianImpedance_Task/computeGravityCompensation");

                                // Store the parameters in the CoderBlockInformation object
                                blockInfo->storeRTWParameters(params);

                                // Initialize input / output Signals
                                // ---------------------------------

                                // Inputs

                                // Outputs
                                blockInfo->setOutputPort(
                                {
                                  0, {
                                    1, 5
                                  }, blockfactory::core::Port::DataType::DOUBLE
                                }

                                  ,
                                    static_cast<void*>
                                    (&CartesianImpedance_Task_B.computeGravityCompensation
                                     [0]));

                                  // Initialize the class
                                  // --------------------

                                  // Get the block factory
                                  auto factory = blockfactory::core::
                                    ClassFactorySingleton::getInstance().
                                    getClassFactory(
                                                    {
                                                    "computeGravityCompensation",
                                                    "XBotBlock_computeGravityCompensation"
                                                    } );

                                  if (!factory) {
                                    bfError <<
                                      "Failed to get factory object (className="
                                      << "XBotBlock_computeGravityCompensation"
                                      << ",libName=" <<
                                      "computeGravityCompensation" << ")";
                                    std::string error = blockfactory::core::Log::
                                      getSingleton().getErrors();
                                    error = "[Initialize]" + error;

                                    // Trim the message if needed
                                    if (error.length() >= 1024) {
                                      error = error.substr(0, 1024-1);
                                    }

                                    // This shouldn't happen
                                    //if (getRTM()->errorStatus) {
                                    //    delete getRTM()->errorStatus;
                                    //    getRTM()->errorStatus = nullptr;
                                    //}

                                    //getRTM()->errorStatus = new char[1024];
                                    //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                    printf("%s\n", error.c_str());
                                    return;
                                  }

                                  if (!factory->isValid()) {
                                    bfError << "Factory error (" <<
                                      static_cast<std::uint32_t>
                                      (factory->getStatus())
                                      << "): " << factory->getError().c_str();
                                    std::string error = blockfactory::core::Log::
                                      getSingleton().getErrors();
                                    error = "[Initialize]" + error;

                                    // Trim the message if needed
                                    if (error.length() >= 1024) {
                                      error = error.substr(0, 1024-1);
                                    }

                                    // This shouldn't happen
                                    //if (getRTM()->errorStatus) {
                                    //    delete getRTM()->errorStatus;
                                    //    getRTM()->errorStatus = nullptr;
                                    //}

                                    //getRTM()->errorStatus = new char[1024];
                                    //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                    printf("%s\n", error.c_str());
                                    return;
                                  }

                                  // Run a dummy configureSizeAndPorts step. This is currently required for properly
                                  // handling optional input / outputs static variables.
                                  // TODO: find a better way to handle them.
                                  {
                                    // Create a new class. This object will be destroyed at the end of the scope.
                                    shlibpp::SharedLibraryClass<blockfactory::
                                      core::Block> blockPtr(*factory);
                                    auto tmpCoderBlockInfo = std::unique_ptr<
                                      blockfactory::coder::CoderBlockInformation>
                                      (
                                       new blockfactory::coder::
                                       CoderBlockInformation);
                                    tmpCoderBlockInfo->storeRTWParameters(params);
                                    blockPtr->configureSizeAndPorts
                                      (tmpCoderBlockInfo.get());
                                  }

                                  // Allocate the block
                                  blockfactory::core::Block* blockPtr =
                                    factory->create();
                                  factory->addRef();

                                  // Initialize the block
                                  bool ok = blockPtr->initialize(blockInfo);

                                  // Report errors
                                  if (!ok) {
                                    std::string error = blockfactory::core::Log::
                                      getSingleton().getErrors();
                                    error = "[Initialize]" + error;

                                    // Trim the message if needed
                                    if (error.length() >= 1024) {
                                      error = error.substr(0, 1024-1);
                                    }

                                    // This shouldn't happen
                                    //if (getRTM()->errorStatus) {
                                    //    delete getRTM()->errorStatus;
                                    //    getRTM()->errorStatus = nullptr;
                                    //}

                                    //getRTM()->errorStatus = new char[1024];
                                    //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                    printf("%s\n", error.c_str());
                                    return;
                                  }

                                  // Call the initializeInitialConditions() method
                                  ok = blockPtr->initializeInitialConditions
                                    (blockInfo);

                                  // Report errors
                                  if (!ok) {
                                    std::string error = blockfactory::core::Log::
                                      getSingleton().getErrors();
                                    error = "[InitializeInitialConditions]" +
                                      error;

                                    // Trim the message if needed
                                    if (error.length() >= 1024) {
                                      error = error.substr(0, 1024-1);
                                    }

                                    // This shouldn't happen
                                    //if (getRTM()->errorStatus) {
                                    //    delete getRTM()->errorStatus;
                                    //    getRTM()->errorStatus = nullptr;
                                    //}

                                    //getRTM()->errorStatus = new char[1024];
                                    //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                    printf("%s\n", error.c_str());
                                    return;
                                  }

                                  // Store the block in the PWork vector
                                  CartesianImpedance_Task_DW.computeGravityCompensation_PWOR.blockPWork
                                    [0] = static_cast<void*>(blockPtr);
                                }
                                // End of S-Function Block: <Root>/computeGravityCompensation
                                // Start for S-Function (BlockFactory): '<Root>/setEffortReference' 
{
                                  // Create and store the CoderBlockInformation object
                                  blockfactory::coder::CoderBlockInformation*
                                    blockInfo = new blockfactory::coder::
                                    CoderBlockInformation();
                                  CartesianImpedance_Task_DW.setEffortReference_PWORK.blockPWork
                                    [1] = static_cast<void*>(blockInfo);

                                  // Initialize the parameters
                                  // -------------------------
                                  blockfactory::core::Parameters params;
                                  params.storeParameter<std::string>(
                                    "DefaultRobot",
                                    blockfactory::core::ParameterMetadata
                                    (blockfactory::core::ParameterType::STRING,
                                     2.0, 1.0, 1.0, "RobotName"));
                                  params.storeParameter<std::string>(
                                    "setEffortReference",
                                    blockfactory::core::ParameterMetadata
                                    (blockfactory::core::ParameterType::STRING,
                                     1.0, 1.0, 1.0, "libName"));
                                  params.storeParameter<std::string>("Off",
                                    blockfactory::core::ParameterMetadata
                                    (blockfactory::core::ParameterType::STRING,
                                     3.0, 1.0, 1.0, "MoveRobot"));
                                  params.storeParameter<std::string>(
                                    "XBotBlock_setEffortReference",
                                    blockfactory::core::ParameterMetadata
                                    (blockfactory::core::ParameterType::STRING,
                                     0.0, 1.0, 1.0, "className"));

                                  // Store the block name
                                  blockInfo->setUniqueBlockName(
                                    "CartesianImpedance_Task/setEffortReference");

                                  // Store the parameters in the CoderBlockInformation object
                                  blockInfo->storeRTWParameters(params);

                                  // Initialize input / output Signals
                                  // ---------------------------------

                                  // Inputs
                                  blockInfo->setInputPort(
                                  {
                                    0, {
                                                          1, 5
                                    }, blockfactory::core::Port::DataType::
                                                          DOUBLE
                                  }

                                    ,
                                                          static_cast<void*>
                                                          (&CartesianImpedance_Task_B.Sum1
                                      [0]));

                                    // Outputs

                                    // Initialize the class
                                    // --------------------

                                    // Get the block factory
                                    auto factory = blockfactory::core::
                                      ClassFactorySingleton::getInstance().
                                      getClassFactory(
                                                      {
                                                      "setEffortReference",
                                                      "XBotBlock_setEffortReference"
                                                      } );

                                    if (!factory) {
                                      bfError <<
                                        "Failed to get factory object (className="
                                        << "XBotBlock_setEffortReference"
                                        << ",libName=" << "setEffortReference" <<
                                        ")";
                                      std::string error = blockfactory::core::
                                        Log::getSingleton().getErrors();
                                      error = "[Initialize]" + error;

                                      // Trim the message if needed
                                      if (error.length() >= 1024) {
                                        error = error.substr(0, 1024-1);
                                      }

                                      // This shouldn't happen
                                      //if (getRTM()->errorStatus) {
                                      //    delete getRTM()->errorStatus;
                                      //    getRTM()->errorStatus = nullptr;
                                      //}

                                      //getRTM()->errorStatus = new char[1024];
                                      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                      printf("%s\n", error.c_str());
                                      return;
                                    }

                                    if (!factory->isValid()) {
                                      bfError << "Factory error (" <<
                                        static_cast<std::uint32_t>
                                        (factory->getStatus())
                                        << "): " << factory->getError().c_str();
                                      std::string error = blockfactory::core::
                                        Log::getSingleton().getErrors();
                                      error = "[Initialize]" + error;

                                      // Trim the message if needed
                                      if (error.length() >= 1024) {
                                        error = error.substr(0, 1024-1);
                                      }

                                      // This shouldn't happen
                                      //if (getRTM()->errorStatus) {
                                      //    delete getRTM()->errorStatus;
                                      //    getRTM()->errorStatus = nullptr;
                                      //}

                                      //getRTM()->errorStatus = new char[1024];
                                      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                      printf("%s\n", error.c_str());
                                      return;
                                    }

                                    // Run a dummy configureSizeAndPorts step. This is currently required for properly
                                    // handling optional input / outputs static variables.
                                    // TODO: find a better way to handle them.
                                    {
                                      // Create a new class. This object will be destroyed at the end of the scope.
                                      shlibpp::SharedLibraryClass<blockfactory::
                                        core::Block> blockPtr(*factory);
                                      auto tmpCoderBlockInfo = std::unique_ptr<
                                        blockfactory::coder::
                                        CoderBlockInformation>(
                                        new blockfactory::coder::
                                        CoderBlockInformation);
                                      tmpCoderBlockInfo->storeRTWParameters
                                        (params);
                                      blockPtr->configureSizeAndPorts
                                        (tmpCoderBlockInfo.get());
                                    }

                                    // Allocate the block
                                    blockfactory::core::Block* blockPtr =
                                      factory->create();
                                    factory->addRef();

                                    // Initialize the block
                                    bool ok = blockPtr->initialize(blockInfo);

                                    // Report errors
                                    if (!ok) {
                                      std::string error = blockfactory::core::
                                        Log::getSingleton().getErrors();
                                      error = "[Initialize]" + error;

                                      // Trim the message if needed
                                      if (error.length() >= 1024) {
                                        error = error.substr(0, 1024-1);
                                      }

                                      // This shouldn't happen
                                      //if (getRTM()->errorStatus) {
                                      //    delete getRTM()->errorStatus;
                                      //    getRTM()->errorStatus = nullptr;
                                      //}

                                      //getRTM()->errorStatus = new char[1024];
                                      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                      printf("%s\n", error.c_str());
                                      return;
                                    }

                                    // Call the initializeInitialConditions() method
                                    ok = blockPtr->initializeInitialConditions
                                      (blockInfo);

                                    // Report errors
                                    if (!ok) {
                                      std::string error = blockfactory::core::
                                        Log::getSingleton().getErrors();
                                      error = "[InitializeInitialConditions]" +
                                        error;

                                      // Trim the message if needed
                                      if (error.length() >= 1024) {
                                        error = error.substr(0, 1024-1);
                                      }

                                      // This shouldn't happen
                                      //if (getRTM()->errorStatus) {
                                      //    delete getRTM()->errorStatus;
                                      //    getRTM()->errorStatus = nullptr;
                                      //}

                                      //getRTM()->errorStatus = new char[1024];
                                      //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                      printf("%s\n", error.c_str());
                                      return;
                                    }

                                    // Store the block in the PWork vector
                                    CartesianImpedance_Task_DW.setEffortReference_PWORK.blockPWork
                                      [0] = static_cast<void*>(blockPtr);
                                  }
                                  // End of S-Function Block: <Root>/setEffortReference
                                  // Start for S-Function (BlockFactory): '<Root>/getStiffness' 
{
                                    // Create and store the CoderBlockInformation object
                                    blockfactory::coder::CoderBlockInformation*
                                      blockInfo = new blockfactory::coder::
                                      CoderBlockInformation();
                                    CartesianImpedance_Task_DW.getStiffness_PWORK.blockPWork
                                      [1] = static_cast<void*>(blockInfo);

                                    // Initialize the parameters
                                    // -------------------------
                                    blockfactory::core::Parameters params;
                                    params.storeParameter<std::string>("Off",
                                      blockfactory::core::ParameterMetadata
                                      (blockfactory::core::ParameterType::STRING,
                                       6.0, 1.0, 1.0, "ModelUpdateType"));
                                    params.storeParameter<std::string>(
                                      "OpenLoop",
                                      blockfactory::core::ParameterMetadata
                                      (blockfactory::core::ParameterType::STRING,
                                       5.0, 1.0, 1.0, "SenseType"));
                                    params.storeParameter<std::string>("Robot",
                                      blockfactory::core::ParameterMetadata
                                      (blockfactory::core::ParameterType::STRING,
                                       4.0, 1.0, 1.0, "GetType"));
                                    params.storeParameter<std::string>(
                                      "XBotBlock_getStiffness",
                                      blockfactory::core::ParameterMetadata
                                      (blockfactory::core::ParameterType::STRING,
                                       0.0, 1.0, 1.0, "className"));
                                    params.storeParameter<std::string>("off",
                                      blockfactory::core::ParameterMetadata
                                      (blockfactory::core::ParameterType::STRING,
                                       7.0, 1.0, 1.0, "OptimizeOperations"));
                                    params.storeParameter<std::string>(
                                      "getStiffness",
                                      blockfactory::core::ParameterMetadata
                                      (blockfactory::core::ParameterType::STRING,
                                       1.0, 1.0, 1.0, "libName"));
                                    params.storeParameter<std::string>(
                                      "DefaultModel",
                                      blockfactory::core::ParameterMetadata
                                      (blockfactory::core::ParameterType::STRING,
                                       3.0, 1.0, 1.0, "ModelName"));
                                    params.storeParameter<std::string>(
                                      "DefaultRobot",
                                      blockfactory::core::ParameterMetadata
                                      (blockfactory::core::ParameterType::STRING,
                                       2.0, 1.0, 1.0, "RobotName"));

                                    // Store the block name
                                    blockInfo->setUniqueBlockName(
                                      "CartesianImpedance_Task/getStiffness");

                                    // Store the parameters in the CoderBlockInformation object
                                    blockInfo->storeRTWParameters(params);

                                    // Initialize input / output Signals
                                    // ---------------------------------

                                    // Inputs

                                    // Outputs
                                    blockInfo->setOutputPort(
                                    {
                                      0, {
                                        1, 5
                                      }, blockfactory::core::Port::DataType::
                                        DOUBLE
                                    }

                                      ,
                                        static_cast<void*>
                                        (&CartesianImpedance_Task_B.getStiffness[
                                         0]));

                                      // Initialize the class
                                      // --------------------

                                      // Get the block factory
                                      auto factory = blockfactory::core::
                                        ClassFactorySingleton::getInstance().
                                        getClassFactory(
                                                        {
                                                        "getStiffness",
                                                        "XBotBlock_getStiffness"
                                                        } );

                                      if (!factory) {
                                        bfError <<
                                          "Failed to get factory object (className="
                                          << "XBotBlock_getStiffness"
                                          << ",libName=" << "getStiffness" <<
                                          ")";
                                        std::string error = blockfactory::core::
                                          Log::getSingleton().getErrors();
                                        error = "[Initialize]" + error;

                                        // Trim the message if needed
                                        if (error.length() >= 1024) {
                                          error = error.substr(0, 1024-1);
                                        }

                                        // This shouldn't happen
                                        //if (getRTM()->errorStatus) {
                                        //    delete getRTM()->errorStatus;
                                        //    getRTM()->errorStatus = nullptr;
                                        //}

                                        //getRTM()->errorStatus = new char[1024];
                                        //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                        printf("%s\n", error.c_str());
                                        return;
                                      }

                                      if (!factory->isValid()) {
                                        bfError << "Factory error (" <<
                                          static_cast<std::uint32_t>
                                          (factory->getStatus())
                                          << "): " << factory->getError().c_str();
                                        std::string error = blockfactory::core::
                                          Log::getSingleton().getErrors();
                                        error = "[Initialize]" + error;

                                        // Trim the message if needed
                                        if (error.length() >= 1024) {
                                          error = error.substr(0, 1024-1);
                                        }

                                        // This shouldn't happen
                                        //if (getRTM()->errorStatus) {
                                        //    delete getRTM()->errorStatus;
                                        //    getRTM()->errorStatus = nullptr;
                                        //}

                                        //getRTM()->errorStatus = new char[1024];
                                        //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                        printf("%s\n", error.c_str());
                                        return;
                                      }

                                      // Run a dummy configureSizeAndPorts step. This is currently required for properly
                                      // handling optional input / outputs static variables.
                                      // TODO: find a better way to handle them.
                                      {
                                        // Create a new class. This object will be destroyed at the end of the scope.
                                        shlibpp::SharedLibraryClass<blockfactory::
                                          core::Block> blockPtr(*factory);
                                        auto tmpCoderBlockInfo = std::unique_ptr<
                                          blockfactory::coder::
                                          CoderBlockInformation>(
                                          new blockfactory::coder::
                                          CoderBlockInformation);
                                        tmpCoderBlockInfo->storeRTWParameters
                                          (params);
                                        blockPtr->configureSizeAndPorts
                                          (tmpCoderBlockInfo.get());
                                      }

                                      // Allocate the block
                                      blockfactory::core::Block* blockPtr =
                                        factory->create();
                                      factory->addRef();

                                      // Initialize the block
                                      bool ok = blockPtr->initialize(blockInfo);

                                      // Report errors
                                      if (!ok) {
                                        std::string error = blockfactory::core::
                                          Log::getSingleton().getErrors();
                                        error = "[Initialize]" + error;

                                        // Trim the message if needed
                                        if (error.length() >= 1024) {
                                          error = error.substr(0, 1024-1);
                                        }

                                        // This shouldn't happen
                                        //if (getRTM()->errorStatus) {
                                        //    delete getRTM()->errorStatus;
                                        //    getRTM()->errorStatus = nullptr;
                                        //}

                                        //getRTM()->errorStatus = new char[1024];
                                        //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                        printf("%s\n", error.c_str());
                                        return;
                                      }

                                      // Call the initializeInitialConditions() method
                                      ok = blockPtr->initializeInitialConditions
                                        (blockInfo);

                                      // Report errors
                                      if (!ok) {
                                        std::string error = blockfactory::core::
                                          Log::getSingleton().getErrors();
                                        error = "[InitializeInitialConditions]"
                                          + error;

                                        // Trim the message if needed
                                        if (error.length() >= 1024) {
                                          error = error.substr(0, 1024-1);
                                        }

                                        // This shouldn't happen
                                        //if (getRTM()->errorStatus) {
                                        //    delete getRTM()->errorStatus;
                                        //    getRTM()->errorStatus = nullptr;
                                        //}

                                        //getRTM()->errorStatus = new char[1024];
                                        //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                        printf("%s\n", error.c_str());
                                        return;
                                      }

                                      // Store the block in the PWork vector
                                      CartesianImpedance_Task_DW.getStiffness_PWORK.blockPWork
                                        [0] = static_cast<void*>(blockPtr);
                                    }
                                    // End of S-Function Block: <Root>/getStiffness
                                    // Start for S-Function (BlockFactory): '<Root>/setStiffness1' 
{
                                      // Create and store the CoderBlockInformation object
                                      blockfactory::coder::CoderBlockInformation*
                                        blockInfo = new blockfactory::coder::
                                        CoderBlockInformation();
                                      CartesianImpedance_Task_DW.setStiffness1_PWORK.blockPWork
                                        [1] = static_cast<void*>(blockInfo);

                                      // Initialize the parameters
                                      // -------------------------
                                      blockfactory::core::Parameters params;
                                      params.storeParameter<std::string>("Off",
                                        blockfactory::core::ParameterMetadata
                                        (blockfactory::core::ParameterType::
                                         STRING, 5.0, 1.0, 1.0, "MoveRobot"));
                                      params.storeParameter<std::string>("Robot",
                                        blockfactory::core::ParameterMetadata
                                        (blockfactory::core::ParameterType::
                                         STRING, 4.0, 1.0, 1.0, "SetType"));
                                      params.storeParameter<std::string>(
                                        "XBotBlock_setStiffness",
                                        blockfactory::core::ParameterMetadata
                                        (blockfactory::core::ParameterType::
                                         STRING, 0.0, 1.0, 1.0, "className"));
                                      params.storeParameter<std::string>(
                                        "setStiffness",
                                        blockfactory::core::ParameterMetadata
                                        (blockfactory::core::ParameterType::
                                         STRING, 1.0, 1.0, 1.0, "libName"));
                                      params.storeParameter<std::string>(
                                        "DefaultModel",
                                        blockfactory::core::ParameterMetadata
                                        (blockfactory::core::ParameterType::
                                         STRING, 3.0, 1.0, 1.0, "ModelName"));
                                      params.storeParameter<std::string>(
                                        "DefaultRobot",
                                        blockfactory::core::ParameterMetadata
                                        (blockfactory::core::ParameterType::
                                         STRING, 2.0, 1.0, 1.0, "RobotName"));

                                      // Store the block name
                                      blockInfo->setUniqueBlockName(
                                        "CartesianImpedance_Task/setStiffness1");

                                      // Store the parameters in the CoderBlockInformation object
                                      blockInfo->storeRTWParameters(params);

                                      // Initialize input / output Signals
                                      // ---------------------------------

                                      // Inputs
                                      blockInfo->setInputPort(
                                      {
                                        0, {
                                          1, 5
                                        }, blockfactory::core::Port::DataType::
                                          DOUBLE
                                      }

                                        ,
                                          static_cast<void*>
                                          (&CartesianImpedance_Task_B.Gain[0]));

                                        // Outputs

                                        // Initialize the class
                                        // --------------------

                                        // Get the block factory
                                        auto factory = blockfactory::core::
                                          ClassFactorySingleton::getInstance().
                                          getClassFactory(
                                                          {
                                                          "setStiffness",
                                                          "XBotBlock_setStiffness"
                                                          } );

                                        if (!factory) {
                                          bfError <<
                                            "Failed to get factory object (className="
                                            << "XBotBlock_setStiffness"
                                            << ",libName=" << "setStiffness" <<
                                            ")";
                                          std::string error = blockfactory::core::
                                            Log::getSingleton().getErrors();
                                          error = "[Initialize]" + error;

                                          // Trim the message if needed
                                          if (error.length() >= 1024) {
                                            error = error.substr(0, 1024-1);
                                          }

                                          // This shouldn't happen
                                          //if (getRTM()->errorStatus) {
                                          //    delete getRTM()->errorStatus;
                                          //    getRTM()->errorStatus = nullptr;
                                          //}

                                          //getRTM()->errorStatus = new char[1024];
                                          //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                          printf("%s\n", error.c_str());
                                          return;
                                        }

                                        if (!factory->isValid()) {
                                          bfError << "Factory error (" <<
                                            static_cast<std::uint32_t>
                                            (factory->getStatus())
                                            << "): " << factory->getError().
                                            c_str();
                                          std::string error = blockfactory::core::
                                            Log::getSingleton().getErrors();
                                          error = "[Initialize]" + error;

                                          // Trim the message if needed
                                          if (error.length() >= 1024) {
                                            error = error.substr(0, 1024-1);
                                          }

                                          // This shouldn't happen
                                          //if (getRTM()->errorStatus) {
                                          //    delete getRTM()->errorStatus;
                                          //    getRTM()->errorStatus = nullptr;
                                          //}

                                          //getRTM()->errorStatus = new char[1024];
                                          //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                          printf("%s\n", error.c_str());
                                          return;
                                        }

                                        // Run a dummy configureSizeAndPorts step. This is currently required for properly
                                        // handling optional input / outputs static variables.
                                        // TODO: find a better way to handle them.
                                        {
                                          // Create a new class. This object will be destroyed at the end of the scope.
                                          shlibpp::SharedLibraryClass<
                                            blockfactory::core::Block> blockPtr(*
                                            factory);
                                          auto tmpCoderBlockInfo = std::
                                            unique_ptr<blockfactory::coder::
                                            CoderBlockInformation>(
                                            new blockfactory::coder::
                                            CoderBlockInformation);
                                          tmpCoderBlockInfo->storeRTWParameters
                                            (params);
                                          blockPtr->configureSizeAndPorts
                                            (tmpCoderBlockInfo.get());
                                        }

                                        // Allocate the block
                                        blockfactory::core::Block* blockPtr =
                                          factory->create();
                                        factory->addRef();

                                        // Initialize the block
                                        bool ok = blockPtr->initialize(blockInfo);

                                        // Report errors
                                        if (!ok) {
                                          std::string error = blockfactory::core::
                                            Log::getSingleton().getErrors();
                                          error = "[Initialize]" + error;

                                          // Trim the message if needed
                                          if (error.length() >= 1024) {
                                            error = error.substr(0, 1024-1);
                                          }

                                          // This shouldn't happen
                                          //if (getRTM()->errorStatus) {
                                          //    delete getRTM()->errorStatus;
                                          //    getRTM()->errorStatus = nullptr;
                                          //}

                                          //getRTM()->errorStatus = new char[1024];
                                          //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                          printf("%s\n", error.c_str());
                                          return;
                                        }

                                        // Call the initializeInitialConditions() method
                                        ok =
                                          blockPtr->initializeInitialConditions
                                          (blockInfo);

                                        // Report errors
                                        if (!ok) {
                                          std::string error = blockfactory::core::
                                            Log::getSingleton().getErrors();
                                          error =
                                            "[InitializeInitialConditions]" +
                                            error;

                                          // Trim the message if needed
                                          if (error.length() >= 1024) {
                                            error = error.substr(0, 1024-1);
                                          }

                                          // This shouldn't happen
                                          //if (getRTM()->errorStatus) {
                                          //    delete getRTM()->errorStatus;
                                          //    getRTM()->errorStatus = nullptr;
                                          //}

                                          //getRTM()->errorStatus = new char[1024];
                                          //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                          printf("%s\n", error.c_str());
                                          return;
                                        }

                                        // Store the block in the PWork vector
                                        CartesianImpedance_Task_DW.setStiffness1_PWORK.blockPWork
                                          [0] = static_cast<void*>(blockPtr);
                                      }
                                      // End of S-Function Block: <Root>/setStiffness1
                                      // Start for S-Function (BlockFactory): '<Root>/getDamping' 
{
                                        // Create and store the CoderBlockInformation object
                                        blockfactory::coder::
                                          CoderBlockInformation* blockInfo = new
                                          blockfactory::coder::
                                          CoderBlockInformation();
                                        CartesianImpedance_Task_DW.getDamping_PWORK.blockPWork
                                          [1] = static_cast<void*>(blockInfo);

                                        // Initialize the parameters
                                        // -------------------------
                                        blockfactory::core::Parameters params;
                                        params.storeParameter<std::string>("Off",
                                          blockfactory::core::ParameterMetadata
                                          (blockfactory::core::ParameterType::
                                           STRING, 6.0, 1.0, 1.0,
                                           "ModelUpdateType"));
                                        params.storeParameter<std::string>(
                                          "OpenLoop",
                                          blockfactory::core::ParameterMetadata
                                          (blockfactory::core::ParameterType::
                                           STRING, 5.0, 1.0, 1.0, "SenseType"));
                                        params.storeParameter<std::string>(
                                          "Robot",
                                          blockfactory::core::ParameterMetadata
                                          (blockfactory::core::ParameterType::
                                           STRING, 4.0, 1.0, 1.0, "GetType"));
                                        params.storeParameter<std::string>(
                                          "XBotBlock_getDamping",
                                          blockfactory::core::ParameterMetadata
                                          (blockfactory::core::ParameterType::
                                           STRING, 0.0, 1.0, 1.0, "className"));
                                        params.storeParameter<std::string>("off",
                                          blockfactory::core::ParameterMetadata
                                          (blockfactory::core::ParameterType::
                                           STRING, 7.0, 1.0, 1.0,
                                           "OptimizeOperations"));
                                        params.storeParameter<std::string>(
                                          "getDamping",
                                          blockfactory::core::ParameterMetadata
                                          (blockfactory::core::ParameterType::
                                           STRING, 1.0, 1.0, 1.0, "libName"));
                                        params.storeParameter<std::string>(
                                          "DefaultModel",
                                          blockfactory::core::ParameterMetadata
                                          (blockfactory::core::ParameterType::
                                           STRING, 3.0, 1.0, 1.0, "ModelName"));
                                        params.storeParameter<std::string>(
                                          "DefaultRobot",
                                          blockfactory::core::ParameterMetadata
                                          (blockfactory::core::ParameterType::
                                           STRING, 2.0, 1.0, 1.0, "RobotName"));

                                        // Store the block name
                                        blockInfo->setUniqueBlockName(
                                          "CartesianImpedance_Task/getDamping");

                                        // Store the parameters in the CoderBlockInformation object
                                        blockInfo->storeRTWParameters(params);

                                        // Initialize input / output Signals
                                        // ---------------------------------

                                        // Inputs

                                        // Outputs
                                        blockInfo->setOutputPort(
                                        {
                                          0, {
                                            1, 5
                                          }, blockfactory::core::Port::DataType::
                                            DOUBLE
                                        }

                                          ,
                                            static_cast<void*>
                                            (&CartesianImpedance_Task_B.getDamping
                                             [0]));

                                          // Initialize the class
                                          // --------------------

                                          // Get the block factory
                                          auto factory = blockfactory::core::
                                            ClassFactorySingleton::getInstance()
                                            .getClassFactory(
                                          {
                                            "getDamping", "XBotBlock_getDamping"
                                          } );

                                          if (!factory) {
                                            bfError <<
                                              "Failed to get factory object (className="
                                              << "XBotBlock_getDamping"
                                              << ",libName=" << "getDamping" <<
                                              ")";
                                            std::string error = blockfactory::
                                              core::Log::getSingleton().
                                              getErrors();
                                            error = "[Initialize]" + error;

                                            // Trim the message if needed
                                            if (error.length() >= 1024) {
                                              error = error.substr(0, 1024-1);
                                            }

                                            // This shouldn't happen
                                            //if (getRTM()->errorStatus) {
                                            //    delete getRTM()->errorStatus;
                                            //    getRTM()->errorStatus = nullptr;
                                            //}

                                            //getRTM()->errorStatus = new char[1024];
                                            //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                            printf("%s\n", error.c_str());
                                            return;
                                          }

                                          if (!factory->isValid()) {
                                            bfError << "Factory error (" <<
                                              static_cast<std::uint32_t>
                                              (factory->getStatus())
                                              << "): " << factory->getError().
                                              c_str();
                                            std::string error = blockfactory::
                                              core::Log::getSingleton().
                                              getErrors();
                                            error = "[Initialize]" + error;

                                            // Trim the message if needed
                                            if (error.length() >= 1024) {
                                              error = error.substr(0, 1024-1);
                                            }

                                            // This shouldn't happen
                                            //if (getRTM()->errorStatus) {
                                            //    delete getRTM()->errorStatus;
                                            //    getRTM()->errorStatus = nullptr;
                                            //}

                                            //getRTM()->errorStatus = new char[1024];
                                            //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                            printf("%s\n", error.c_str());
                                            return;
                                          }

                                          // Run a dummy configureSizeAndPorts step. This is currently required for properly
                                          // handling optional input / outputs static variables.
                                          // TODO: find a better way to handle them.
                                          {
                                            // Create a new class. This object will be destroyed at the end of the scope.
                                            shlibpp::SharedLibraryClass<
                                              blockfactory::core::Block>
                                              blockPtr(*factory);
                                            auto tmpCoderBlockInfo = std::
                                              unique_ptr<blockfactory::coder::
                                              CoderBlockInformation>(
                                              new blockfactory::coder::
                                              CoderBlockInformation);
                                            tmpCoderBlockInfo->storeRTWParameters
                                              (params);
                                            blockPtr->configureSizeAndPorts
                                              (tmpCoderBlockInfo.get());
                                          }

                                          // Allocate the block
                                          blockfactory::core::Block* blockPtr =
                                            factory->create();
                                          factory->addRef();

                                          // Initialize the block
                                          bool ok = blockPtr->initialize
                                            (blockInfo);

                                          // Report errors
                                          if (!ok) {
                                            std::string error = blockfactory::
                                              core::Log::getSingleton().
                                              getErrors();
                                            error = "[Initialize]" + error;

                                            // Trim the message if needed
                                            if (error.length() >= 1024) {
                                              error = error.substr(0, 1024-1);
                                            }

                                            // This shouldn't happen
                                            //if (getRTM()->errorStatus) {
                                            //    delete getRTM()->errorStatus;
                                            //    getRTM()->errorStatus = nullptr;
                                            //}

                                            //getRTM()->errorStatus = new char[1024];
                                            //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                            printf("%s\n", error.c_str());
                                            return;
                                          }

                                          // Call the initializeInitialConditions() method
                                          ok =
                                            blockPtr->initializeInitialConditions
                                            (blockInfo);

                                          // Report errors
                                          if (!ok) {
                                            std::string error = blockfactory::
                                              core::Log::getSingleton().
                                              getErrors();
                                            error =
                                              "[InitializeInitialConditions]" +
                                              error;

                                            // Trim the message if needed
                                            if (error.length() >= 1024) {
                                              error = error.substr(0, 1024-1);
                                            }

                                            // This shouldn't happen
                                            //if (getRTM()->errorStatus) {
                                            //    delete getRTM()->errorStatus;
                                            //    getRTM()->errorStatus = nullptr;
                                            //}

                                            //getRTM()->errorStatus = new char[1024];
                                            //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                            printf("%s\n", error.c_str());
                                            return;
                                          }

                                          // Store the block in the PWork vector
                                          CartesianImpedance_Task_DW.getDamping_PWORK.blockPWork
                                            [0] = static_cast<void*>(blockPtr);
                                        }
                                        // End of S-Function Block: <Root>/getDamping
                                        // Start for S-Function (BlockFactory): '<Root>/setDamping' 
{
                                          // Create and store the CoderBlockInformation object
                                          blockfactory::coder::
                                            CoderBlockInformation* blockInfo =
                                            new blockfactory::coder::
                                            CoderBlockInformation();
                                          CartesianImpedance_Task_DW.setDamping_PWORK.blockPWork
                                            [1] = static_cast<void*>(blockInfo);

                                          // Initialize the parameters
                                          // -------------------------
                                          blockfactory::core::Parameters params;
                                          params.storeParameter<std::string>(
                                            "On",
                                            blockfactory::core::
                                            ParameterMetadata(blockfactory::core::
                                            ParameterType::STRING, 5.0, 1.0, 1.0,
                                            "MoveRobot"));
                                          params.storeParameter<std::string>(
                                            "Robot",
                                            blockfactory::core::
                                            ParameterMetadata(blockfactory::core::
                                            ParameterType::STRING, 4.0, 1.0, 1.0,
                                            "SetType"));
                                          params.storeParameter<std::string>(
                                            "XBotBlock_setDamping",
                                            blockfactory::core::
                                            ParameterMetadata(blockfactory::core::
                                            ParameterType::STRING, 0.0, 1.0, 1.0,
                                            "className"));
                                          params.storeParameter<std::string>(
                                            "setDamping",
                                            blockfactory::core::
                                            ParameterMetadata(blockfactory::core::
                                            ParameterType::STRING, 1.0, 1.0, 1.0,
                                            "libName"));
                                          params.storeParameter<std::string>(
                                            "DefaultModel",
                                            blockfactory::core::
                                            ParameterMetadata(blockfactory::core::
                                            ParameterType::STRING, 3.0, 1.0, 1.0,
                                            "ModelName"));
                                          params.storeParameter<std::string>(
                                            "DefaultRobot",
                                            blockfactory::core::
                                            ParameterMetadata(blockfactory::core::
                                            ParameterType::STRING, 2.0, 1.0, 1.0,
                                            "RobotName"));

                                          // Store the block name
                                          blockInfo->setUniqueBlockName(
                                            "CartesianImpedance_Task/setDamping");

                                          // Store the parameters in the CoderBlockInformation object
                                          blockInfo->storeRTWParameters(params);

                                          // Initialize input / output Signals
                                          // ---------------------------------

                                          // Inputs
                                          blockInfo->setInputPort(
                                          {
                                            0, {
                                              1, 5
                                            }, blockfactory::core::Port::
                                              DataType::DOUBLE
                                          }

                                            ,
                                              static_cast<void*>
                                              (&CartesianImpedance_Task_B.Gain1
                                               [0]));

                                            // Outputs

                                            // Initialize the class
                                            // --------------------

                                            // Get the block factory
                                            auto factory = blockfactory::core::
                                              ClassFactorySingleton::getInstance
                                              ().getClassFactory(
                                            {
                                              "setDamping",
                                                "XBotBlock_setDamping"
                                            } );

                                            if (!factory) {
                                              bfError <<
                                                "Failed to get factory object (className="
                                                << "XBotBlock_setDamping"
                                                << ",libName=" << "setDamping" <<
                                                ")";
                                              std::string error = blockfactory::
                                                core::Log::getSingleton().
                                                getErrors();
                                              error = "[Initialize]" + error;

                                              // Trim the message if needed
                                              if (error.length() >= 1024) {
                                                error = error.substr(0, 1024-1);
                                              }

                                              // This shouldn't happen
                                              //if (getRTM()->errorStatus) {
                                              //    delete getRTM()->errorStatus;
                                              //    getRTM()->errorStatus = nullptr;
                                              //}

                                              //getRTM()->errorStatus = new char[1024];
                                              //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                              printf("%s\n", error.c_str());
                                              return;
                                            }

                                            if (!factory->isValid()) {
                                              bfError << "Factory error (" <<
                                                static_cast<std::uint32_t>
                                                (factory->getStatus())
                                                << "): " << factory->getError().
                                                c_str();
                                              std::string error = blockfactory::
                                                core::Log::getSingleton().
                                                getErrors();
                                              error = "[Initialize]" + error;

                                              // Trim the message if needed
                                              if (error.length() >= 1024) {
                                                error = error.substr(0, 1024-1);
                                              }

                                              // This shouldn't happen
                                              //if (getRTM()->errorStatus) {
                                              //    delete getRTM()->errorStatus;
                                              //    getRTM()->errorStatus = nullptr;
                                              //}

                                              //getRTM()->errorStatus = new char[1024];
                                              //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                              printf("%s\n", error.c_str());
                                              return;
                                            }

                                            // Run a dummy configureSizeAndPorts step. This is currently required for properly
                                            // handling optional input / outputs static variables.
                                            // TODO: find a better way to handle them.
                                            {
                                              // Create a new class. This object will be destroyed at the end of the scope.
                                              shlibpp::SharedLibraryClass<
                                                blockfactory::core::Block>
                                                blockPtr(*factory);
                                              auto tmpCoderBlockInfo = std::
                                                unique_ptr<blockfactory::coder::
                                                CoderBlockInformation>(
                                                new blockfactory::coder::
                                                CoderBlockInformation);
                                              tmpCoderBlockInfo->storeRTWParameters
                                                (params);
                                              blockPtr->configureSizeAndPorts
                                                (tmpCoderBlockInfo.get());
                                            }

                                            // Allocate the block
                                            blockfactory::core::Block* blockPtr =
                                              factory->create();
                                            factory->addRef();

                                            // Initialize the block
                                            bool ok = blockPtr->initialize
                                              (blockInfo);

                                            // Report errors
                                            if (!ok) {
                                              std::string error = blockfactory::
                                                core::Log::getSingleton().
                                                getErrors();
                                              error = "[Initialize]" + error;

                                              // Trim the message if needed
                                              if (error.length() >= 1024) {
                                                error = error.substr(0, 1024-1);
                                              }

                                              // This shouldn't happen
                                              //if (getRTM()->errorStatus) {
                                              //    delete getRTM()->errorStatus;
                                              //    getRTM()->errorStatus = nullptr;
                                              //}

                                              //getRTM()->errorStatus = new char[1024];
                                              //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                              printf("%s\n", error.c_str());
                                              return;
                                            }

                                            // Call the initializeInitialConditions() method
                                            ok =
                                              blockPtr->initializeInitialConditions
                                              (blockInfo);

                                            // Report errors
                                            if (!ok) {
                                              std::string error = blockfactory::
                                                core::Log::getSingleton().
                                                getErrors();
                                              error =
                                                "[InitializeInitialConditions]"
                                                + error;

                                              // Trim the message if needed
                                              if (error.length() >= 1024) {
                                                error = error.substr(0, 1024-1);
                                              }

                                              // This shouldn't happen
                                              //if (getRTM()->errorStatus) {
                                              //    delete getRTM()->errorStatus;
                                              //    getRTM()->errorStatus = nullptr;
                                              //}

                                              //getRTM()->errorStatus = new char[1024];
                                              //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                              printf("%s\n", error.c_str());
                                              return;
                                            }

                                            // Store the block in the PWork vector
                                            CartesianImpedance_Task_DW.setDamping_PWORK.blockPWork
                                              [0] = static_cast<void*>(blockPtr);
                                          }
                                          // End of S-Function Block: <Root>/setDamping
                                          // Start for S-Function (BlockFactory): '<Root>/getInertiaMatrix' 
{
                                            // Create and store the CoderBlockInformation object
                                            blockfactory::coder::
                                              CoderBlockInformation* blockInfo =
                                              new blockfactory::coder::
                                              CoderBlockInformation();
                                            CartesianImpedance_Task_DW.getInertiaMatrix_PWORK.blockPWork
                                              [1] = static_cast<void*>(blockInfo);

                                            // Initialize the parameters
                                            // -------------------------
                                            blockfactory::core::Parameters
                                              params;
                                            params.storeParameter<std::string>(
                                              "Off",
                                              blockfactory::core::
                                              ParameterMetadata(blockfactory::
                                              core::ParameterType::STRING, 5.0,
                                              1.0, 1.0, "ModelUpdateType"));
                                            params.storeParameter<std::string>(
                                              "CloseLoop",
                                              blockfactory::core::
                                              ParameterMetadata(blockfactory::
                                              core::ParameterType::STRING, 4.0,
                                              1.0, 1.0, "SenseType"));
                                            params.storeParameter<std::string>(
                                              "XBotBlock_getInertiaMatrix",
                                              blockfactory::core::
                                              ParameterMetadata(blockfactory::
                                              core::ParameterType::STRING, 0.0,
                                              1.0, 1.0, "className"));
                                            params.storeParameter<std::string>(
                                              "off",
                                              blockfactory::core::
                                              ParameterMetadata(blockfactory::
                                              core::ParameterType::STRING, 6.0,
                                              1.0, 1.0, "OptimizeOperations"));
                                            params.storeParameter<std::string>(
                                              "getInertiaMatrix",
                                              blockfactory::core::
                                              ParameterMetadata(blockfactory::
                                              core::ParameterType::STRING, 1.0,
                                              1.0, 1.0, "libName"));
                                            params.storeParameter<std::string>(
                                              "DefaultModel",
                                              blockfactory::core::
                                              ParameterMetadata(blockfactory::
                                              core::ParameterType::STRING, 2.0,
                                              1.0, 1.0, "ModelName"));
                                            params.storeParameter<std::string>(
                                              "DefaultRobot",
                                              blockfactory::core::
                                              ParameterMetadata(blockfactory::
                                              core::ParameterType::STRING, 3.0,
                                              1.0, 1.0, "RobotName"));

                                            // Store the block name
                                            blockInfo->setUniqueBlockName(
                                              "CartesianImpedance_Task/getInertiaMatrix");

                                            // Store the parameters in the CoderBlockInformation object
                                            blockInfo->storeRTWParameters(params);

                                            // Initialize input / output Signals
                                            // ---------------------------------

                                            // Inputs

                                            // Outputs
                                            blockInfo->setOutputPort(
                                            {
                                              0, {
                                                5, 5
                                              }, blockfactory::core::Port::
                                                DataType::DOUBLE
                                            }

                                              ,
                                                static_cast<void*>
                                                (&CartesianImpedance_Task_B.getInertiaMatrix
                                                 [0]));

                                              // Initialize the class
                                              // --------------------

                                              // Get the block factory
                                              auto factory = blockfactory::core::
                                                ClassFactorySingleton::
                                                getInstance().getClassFactory(
                                              {
                                                "getInertiaMatrix",
                                                  "XBotBlock_getInertiaMatrix"
                                              } );

                                              if (!factory) {
                                                bfError <<
                                                  "Failed to get factory object (className="
                                                  <<
                                                  "XBotBlock_getInertiaMatrix"
                                                  << ",libName=" <<
                                                  "getInertiaMatrix" << ")";
                                                std::string error = blockfactory::
                                                  core::Log::getSingleton().
                                                  getErrors();
                                                error = "[Initialize]" + error;

                                                // Trim the message if needed
                                                if (error.length() >= 1024) {
                                                  error = error.substr(0, 1024-1);
                                                }

                                                // This shouldn't happen
                                                //if (getRTM()->errorStatus) {
                                                //    delete getRTM()->errorStatus;
                                                //    getRTM()->errorStatus = nullptr;
                                                //}

                                                //getRTM()->errorStatus = new char[1024];
                                                //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                printf("%s\n", error.c_str());
                                                return;
                                              }

                                              if (!factory->isValid()) {
                                                bfError << "Factory error (" <<
                                                  static_cast<std::uint32_t>
                                                  (factory->getStatus())
                                                  << "): " << factory->getError()
                                                  .c_str();
                                                std::string error = blockfactory::
                                                  core::Log::getSingleton().
                                                  getErrors();
                                                error = "[Initialize]" + error;

                                                // Trim the message if needed
                                                if (error.length() >= 1024) {
                                                  error = error.substr(0, 1024-1);
                                                }

                                                // This shouldn't happen
                                                //if (getRTM()->errorStatus) {
                                                //    delete getRTM()->errorStatus;
                                                //    getRTM()->errorStatus = nullptr;
                                                //}

                                                //getRTM()->errorStatus = new char[1024];
                                                //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                printf("%s\n", error.c_str());
                                                return;
                                              }

                                              // Run a dummy configureSizeAndPorts step. This is currently required for properly
                                              // handling optional input / outputs static variables.
                                              // TODO: find a better way to handle them.
                                              {
                                                // Create a new class. This object will be destroyed at the end of the scope.
                                                shlibpp::SharedLibraryClass<
                                                  blockfactory::core::Block>
                                                  blockPtr(*factory);
                                                auto tmpCoderBlockInfo = std::
                                                  unique_ptr<blockfactory::coder::
                                                  CoderBlockInformation>(
                                                  new blockfactory::coder::
                                                  CoderBlockInformation);
                                                tmpCoderBlockInfo->storeRTWParameters
                                                  (params);
                                                blockPtr->configureSizeAndPorts
                                                  (tmpCoderBlockInfo.get());
                                              }

                                              // Allocate the block
                                              blockfactory::core::Block*
                                                blockPtr = factory->create();
                                              factory->addRef();

                                              // Initialize the block
                                              bool ok = blockPtr->initialize
                                                (blockInfo);

                                              // Report errors
                                              if (!ok) {
                                                std::string error = blockfactory::
                                                  core::Log::getSingleton().
                                                  getErrors();
                                                error = "[Initialize]" + error;

                                                // Trim the message if needed
                                                if (error.length() >= 1024) {
                                                  error = error.substr(0, 1024-1);
                                                }

                                                // This shouldn't happen
                                                //if (getRTM()->errorStatus) {
                                                //    delete getRTM()->errorStatus;
                                                //    getRTM()->errorStatus = nullptr;
                                                //}

                                                //getRTM()->errorStatus = new char[1024];
                                                //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                printf("%s\n", error.c_str());
                                                return;
                                              }

                                              // Call the initializeInitialConditions() method
                                              ok =
                                                blockPtr->initializeInitialConditions
                                                (blockInfo);

                                              // Report errors
                                              if (!ok) {
                                                std::string error = blockfactory::
                                                  core::Log::getSingleton().
                                                  getErrors();
                                                error =
                                                  "[InitializeInitialConditions]"
                                                  + error;

                                                // Trim the message if needed
                                                if (error.length() >= 1024) {
                                                  error = error.substr(0, 1024-1);
                                                }

                                                // This shouldn't happen
                                                //if (getRTM()->errorStatus) {
                                                //    delete getRTM()->errorStatus;
                                                //    getRTM()->errorStatus = nullptr;
                                                //}

                                                //getRTM()->errorStatus = new char[1024];
                                                //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                printf("%s\n", error.c_str());
                                                return;
                                              }

                                              // Store the block in the PWork vector
                                              CartesianImpedance_Task_DW.getInertiaMatrix_PWORK.blockPWork
                                                [0] = static_cast<void*>
                                                (blockPtr);
                                            }
                                            // End of S-Function Block: <Root>/getInertiaMatrix
                                          }

                                            // Model terminate function
                                            void modelModelClass::terminate()
                                            {
                                              // Terminate for S-Function (BlockFactory): '<Root>/getJointPosition' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.getJointPosition_PWORK.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.getJointPosition_PWORK.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "getJointPosition",
                                                    "XBotBlock_getJointPosition"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    <<
                                                    "XBotBlock_getJointPosition"
                                                    << ",libName=" <<
                                                    "getJointPosition" << ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"getJointPosition",
                                                       "XBotBlock_getJointPosition"
                                                       })) {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <Root>/getJointPosition

                                              // Terminate for S-Function (BlockFactory): '<Root>/setPositionReference1' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.setPositionReference1_PWORK.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.setPositionReference1_PWORK.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "setPositionReference",
                                                    "XBotBlock_setPositionReference"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    <<
                                                    "XBotBlock_setPositionReference"
                                                    << ",libName=" <<
                                                    "setPositionReference" <<
                                                    ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"setPositionReference",
                                                       "XBotBlock_setPositionReference"
                                                       })) {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <Root>/setPositionReference1

                                              // Terminate for S-Function (BlockFactory): '<S10>/getPoseFun' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.getPoseFun_PWORK.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.getPoseFun_PWORK.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "getPose", "XBotBlock_getPose"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    << "XBotBlock_getPose"
                                                    << ",libName=" << "getPose" <<
                                                    ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"getPose",
                                                       "XBotBlock_getPose"})) {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <S10>/getPoseFun

                                              // Terminate for S-Function (BlockFactory): '<S5>/getPoseFun' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.getPoseFun_PWORK_h.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.getPoseFun_PWORK_h.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "getPose", "XBotBlock_getPose"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    << "XBotBlock_getPose"
                                                    << ",libName=" << "getPose" <<
                                                    ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"getPose",
                                                       "XBotBlock_getPose"})) {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <S5>/getPoseFun

                                              // Terminate for S-Function (BlockFactory): '<Root>/getJacobian' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.getJacobian_PWORK.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.getJacobian_PWORK.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "getJacobian",
                                                    "XBotBlock_getJacobian"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    << "XBotBlock_getJacobian"
                                                    << ",libName=" <<
                                                    "getJacobian" << ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"getJacobian",
                                                       "XBotBlock_getJacobian"}))
                                                  {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <Root>/getJacobian

                                              // Terminate for S-Function (BlockFactory): '<Root>/getInertiaInverse' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.getInertiaInverse_PWORK.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.getInertiaInverse_PWORK.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "getInertiaInverse",
                                                    "XBotBlock_getInertiaInverse"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    <<
                                                    "XBotBlock_getInertiaInverse"
                                                    << ",libName=" <<
                                                    "getInertiaInverse" << ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"getInertiaInverse",
                                                       "XBotBlock_getInertiaInverse"
                                                       })) {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <Root>/getInertiaInverse

                                              // Terminate for S-Function (BlockFactory): '<Root>/getJointVelocity' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.getJointVelocity_PWORK.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.getJointVelocity_PWORK.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "getJointVelocity",
                                                    "XBotBlock_getJointVelocity"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    <<
                                                    "XBotBlock_getJointVelocity"
                                                    << ",libName=" <<
                                                    "getJointVelocity" << ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"getJointVelocity",
                                                       "XBotBlock_getJointVelocity"
                                                       })) {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <Root>/getJointVelocity

                                              // Terminate for S-Function (BlockFactory): '<Root>/computeGravityCompensation' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.computeGravityCompensation_PWOR.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.computeGravityCompensation_PWOR.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "computeGravityCompensation",
                                                    "XBotBlock_computeGravityCompensation"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    <<
                                                    "XBotBlock_computeGravityCompensation"
                                                    << ",libName=" <<
                                                    "computeGravityCompensation"
                                                    << ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {
                                                       "computeGravityCompensation",
                                                       "XBotBlock_computeGravityCompensation"
                                                       })) {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <Root>/computeGravityCompensation

                                              // Terminate for S-Function (BlockFactory): '<Root>/setEffortReference' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.setEffortReference_PWORK.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.setEffortReference_PWORK.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "setEffortReference",
                                                    "XBotBlock_setEffortReference"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    <<
                                                    "XBotBlock_setEffortReference"
                                                    << ",libName=" <<
                                                    "setEffortReference" << ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"setEffortReference",
                                                       "XBotBlock_setEffortReference"
                                                       })) {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <Root>/setEffortReference

                                              // Terminate for S-Function (BlockFactory): '<Root>/getStiffness' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.getStiffness_PWORK.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.getStiffness_PWORK.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "getStiffness",
                                                    "XBotBlock_getStiffness"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    << "XBotBlock_getStiffness"
                                                    << ",libName=" <<
                                                    "getStiffness" << ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"getStiffness",
                                                       "XBotBlock_getStiffness"}))
                                                  {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <Root>/getStiffness

                                              // Terminate for S-Function (BlockFactory): '<Root>/setStiffness1' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.setStiffness1_PWORK.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.setStiffness1_PWORK.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "setStiffness",
                                                    "XBotBlock_setStiffness"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    << "XBotBlock_setStiffness"
                                                    << ",libName=" <<
                                                    "setStiffness" << ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"setStiffness",
                                                       "XBotBlock_setStiffness"}))
                                                  {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <Root>/setStiffness1

                                              // Terminate for S-Function (BlockFactory): '<Root>/getDamping' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.getDamping_PWORK.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.getDamping_PWORK.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "getDamping",
                                                    "XBotBlock_getDamping"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    << "XBotBlock_getDamping"
                                                    << ",libName=" <<
                                                    "getDamping" << ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"getDamping",
                                                       "XBotBlock_getDamping"}))
                                                  {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <Root>/getDamping

                                              // Terminate for S-Function (BlockFactory): '<Root>/setDamping' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.setDamping_PWORK.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.setDamping_PWORK.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "setDamping",
                                                    "XBotBlock_setDamping"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    << "XBotBlock_setDamping"
                                                    << ",libName=" <<
                                                    "setDamping" << ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"setDamping",
                                                       "XBotBlock_setDamping"}))
                                                  {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <Root>/setDamping

                                              // Terminate for S-Function (BlockFactory): '<Root>/getInertiaMatrix' 
                                              {
                                                // Get the CoderBlockInformation from the PWork
                                                blockfactory::coder::
                                                  CoderBlockInformation*
                                                  blockInfo = nullptr;
                                                blockInfo =
                                                  static_cast<blockfactory::
                                                  coder::CoderBlockInformation*>
                                                  (CartesianImpedance_Task_DW.getInertiaMatrix_PWORK.blockPWork
                                                   [1]);

                                                // Get the Block from the PWork
                                                blockfactory::core::Block*
                                                  blockPtr = nullptr;
                                                blockPtr =
                                                  static_cast<blockfactory::core::
                                                  Block*>
                                                  (CartesianImpedance_Task_DW.getInertiaMatrix_PWORK.blockPWork
                                                   [0]);

                                                // Get the block factory
                                                auto factory = blockfactory::
                                                  core::ClassFactorySingleton::
                                                  getInstance().getClassFactory(
                                                {
                                                  "getInertiaMatrix",
                                                    "XBotBlock_getInertiaMatrix"
                                                } );

                                                if (!factory) {
                                                  bfError <<
                                                    "Failed to get factory object (className="
                                                    <<
                                                    "XBotBlock_getInertiaMatrix"
                                                    << ",libName=" <<
                                                    "getInertiaMatrix" << ")";
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                if (!factory->isValid()) {
                                                  bfError << "Factory error (" <<
                                                    static_cast<std::uint32_t>
                                                    (factory->getStatus())
                                                    << "): " <<
                                                    factory->getError().c_str();
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Initialize]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }

                                                // Terminate the class
                                                // -------------------
                                                bool ok;
                                                ok = blockPtr->terminate
                                                  (blockInfo);

                                                // Destroy the block
                                                factory->destroy(blockPtr);
                                                blockPtr = nullptr;

                                                // Decrease the counter of the factory
                                                factory->removeRef();
                                                if (factory->getReferenceCount()
                                                    == 1) {
                                                  // Delete the memory ownership of the shared pointer used in this function
                                                  factory.reset();

                                                  // Delete the factory object
                                                  if (!blockfactory::core::
                                                      ClassFactorySingleton::
                                                      getInstance().
                                                      destroyFactory(
                                                       {"getInertiaMatrix",
                                                       "XBotBlock_getInertiaMatrix"
                                                       })) {
                                                    bfError <<
                                                      "Failed to destroy the factory";

                                                    // Do not return since other actions need to be performed
                                                  }
                                                }

                                                // Delete the BlockInformation object
                                                delete blockInfo;
                                                blockInfo = nullptr;

                                                // Report errors
                                                if (!ok) {
                                                  std::string error =
                                                    blockfactory::core::Log::
                                                    getSingleton().getErrors();
                                                  error = "[Terminate]" + error;

                                                  // Trim the message if needed
                                                  if (error.length() >= 1024) {
                                                    error = error.substr(0, 1024
                                                      -1);
                                                  }

                                                  // This shouldn't happen
                                                  //if (getRTM()->errorStatus) {
                                                  //    delete getRTM()->errorStatus;
                                                  //    getRTM()->errorStatus = nullptr;
                                                  //}

                                                  //getRTM()->errorStatus = new char[1024];
                                                  //sprintf(const_cast<char_T*>(getRTM()->errorStatus), "%s", error.c_str());
                                                  printf("%s\n", error.c_str());
                                                  return;
                                                }
                                              }

                                              // End of S-Function Block: <Root>/getInertiaMatrix
                                            }

                                            // Constructor
                                            modelModelClass::modelModelClass() :
                                              CartesianImpedance_Task_M()
                                            {
                                              // Currently there is no constructor body generated.
                                            }

                                            // Destructor
                                            modelModelClass::~modelModelClass()
                                            {
                                              // Currently there is no destructor body generated.
                                            }

                                            // Real-Time Model get method
                                            RT_MODEL_CartesianImpedance_T_T
                                              * modelModelClass::getRTM()
                                            {
                                              return (&CartesianImpedance_Task_M);
                                            }

                                            //
                                            // File trailer for generated code.
                                            //
                                            // [EOF]
                                            //
