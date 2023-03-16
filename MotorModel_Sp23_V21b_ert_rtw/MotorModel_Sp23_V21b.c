/*
 * MotorModel_Sp23_V21b.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "MotorModel_Sp23_V21b".
 *
 * Model version              : 7
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Wed Mar 15 19:14:06 2023
 *
 * Target selection: ert.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "MotorModel_Sp23_V21b.h"
#include "MotorModel_Sp23_V21b_private.h"

/* Block signals (default storage) */
B_MotorModel_Sp23_V21b_T MotorModel_Sp23_V21b_B;

/* Continuous states */
X_MotorModel_Sp23_V21b_T MotorModel_Sp23_V21b_X;

/* Block states (default storage) */
DW_MotorModel_Sp23_V21b_T MotorModel_Sp23_V21b_DW;

/* External outputs (root outports fed by signals with default storage) */
ExtY_MotorModel_Sp23_V21b_T MotorModel_Sp23_V21b_Y;

/* Real-time model */
static RT_MODEL_MotorModel_Sp23_V21b_T MotorModel_Sp23_V21b_M_;
RT_MODEL_MotorModel_Sp23_V21b_T *const MotorModel_Sp23_V21b_M =
  &MotorModel_Sp23_V21b_M_;
const int64m_T MotorModel_Sp23_V21b_sfix64_En3 = { { 0UL, 0UL }/* chunks */
};

void sMultiWordMul(const uint32_T u1[], int16_T n1, const uint32_T u2[], int16_T
                   n2, uint32_T y[], int16_T n)
{
  uint32_T a0;
  uint32_T a1;
  uint32_T b1;
  uint32_T cb;
  uint32_T cb1;
  uint32_T cb2;
  uint32_T u1i;
  uint32_T w01;
  uint32_T w10;
  uint32_T yk;
  int16_T i;
  int16_T j;
  int16_T k;
  int16_T ni;
  boolean_T isNegative1;
  boolean_T isNegative2;
  isNegative1 = ((u1[n1 - 1] & 2147483648UL) != 0UL);
  isNegative2 = ((u2[n2 - 1] & 2147483648UL) != 0UL);
  cb1 = 1UL;

  /* Initialize output to zero */
  for (k = 0; k < n; k++) {
    y[k] = 0UL;
  }

  for (i = 0; i < n1; i++) {
    cb = 0UL;
    u1i = u1[i];
    if (isNegative1) {
      u1i = ~u1i + cb1;
      cb1 = (uint32_T)(u1i < cb1);
    }

    a1 = u1i >> 16U;
    a0 = u1i & 65535UL;
    cb2 = 1UL;
    ni = n - i;
    ni = n2 <= ni ? n2 : ni;
    k = i;
    for (j = 0; j < ni; j++) {
      u1i = u2[j];
      if (isNegative2) {
        u1i = ~u1i + cb2;
        cb2 = (uint32_T)(u1i < cb2);
      }

      b1 = u1i >> 16U;
      u1i &= 65535UL;
      w10 = a1 * u1i;
      w01 = a0 * b1;
      yk = y[k] + cb;
      cb = (uint32_T)(yk < cb);
      u1i *= a0;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w10 << 16U;
      yk += u1i;
      cb += (yk < u1i);
      u1i = w01 << 16U;
      yk += u1i;
      cb += (yk < u1i);
      y[k] = yk;
      cb += w10 >> 16U;
      cb += w01 >> 16U;
      cb += a1 * b1;
      k++;
    }

    if (k < n) {
      y[k] = cb;
    }
  }

  /* Apply sign */
  if (isNegative1 != isNegative2) {
    cb = 1UL;
    for (k = 0; k < n; k++) {
      yk = ~y[k] + cb;
      y[k] = yk;
      cb = (uint32_T)(yk < cb);
    }
  }
}

real_T sMultiWord2Double(const uint32_T u1[], int16_T n1, int16_T e1)
{
  real_T y;
  uint32_T cb;
  uint32_T u1i;
  int16_T exp_0;
  int16_T i;
  y = 0.0;
  exp_0 = e1;
  if ((u1[n1 - 1] & 2147483648UL) != 0UL) {
    cb = 1UL;
    for (i = 0; i < n1; i++) {
      u1i = ~u1[i];
      cb += u1i;
      y -= ldexp(cb, exp_0);
      cb = (uint32_T)(cb < u1i);
      exp_0 += 32;
    }
  } else {
    for (i = 0; i < n1; i++) {
      y += ldexp(u1[i], exp_0);
      exp_0 += 32;
    }
  }

  return y;
}

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  MotorModel_Sp23_V21b_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  MotorModel_Sp23_V21b_step();
  MotorModel_Sp23_V21b_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  MotorModel_Sp23_V21b_step();
  MotorModel_Sp23_V21b_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/*
 * Output and update for action system:
 *    '<S1>/Motor Direction1'
 *    '<S1>/Motor Direction 2'
 *    '<S1>/Constant Position'
 */
void MotorModel_Sp23_MotorDirection1(RT_MODEL_MotorModel_Sp23_V21b_T * const
  MotorModel_Sp23_V21b_M, real_T *rty_IN1, real_T *rty_IN2,
  P_MotorDirection1_MotorModel__T *localP)
{
  if (rtmIsMajorTimeStep(MotorModel_Sp23_V21b_M)) {
    /* Constant: '<S5>/Constant' */
    *rty_IN1 = localP->Constant_Value;

    /* Constant: '<S5>/Constant1' */
    *rty_IN2 = localP->Constant1_Value;
  }
}

real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}

/* Model step function */
void MotorModel_Sp23_V21b_step(void)
{
  /* local block i/o variables */
  real_T rtb_Merge1;
  real_T rtb_Merge2;
  codertarget_arduinobase_inter_T *obj;
  int64m_T *tmp_2;
  real_T rtb_Abs1;
  real_T rtb_ErrorSignal;
  uint32_T tmp;
  uint32_T tmp_0;
  uint8_T tmp_1;
  if (rtmIsMajorTimeStep(MotorModel_Sp23_V21b_M)) {
    /* set solver stop time */
    if (!(MotorModel_Sp23_V21b_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&MotorModel_Sp23_V21b_M->solverInfo,
                            ((MotorModel_Sp23_V21b_M->Timing.clockTickH0 + 1) *
        MotorModel_Sp23_V21b_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&MotorModel_Sp23_V21b_M->solverInfo,
                            ((MotorModel_Sp23_V21b_M->Timing.clockTick0 + 1) *
        MotorModel_Sp23_V21b_M->Timing.stepSize0 +
        MotorModel_Sp23_V21b_M->Timing.clockTickH0 *
        MotorModel_Sp23_V21b_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(MotorModel_Sp23_V21b_M)) {
    MotorModel_Sp23_V21b_M->Timing.t[0] = rtsiGetT
      (&MotorModel_Sp23_V21b_M->solverInfo);
  }

  /* Reset subsysRan breadcrumbs */
  srClearBC(MotorModel_Sp23_V21b_DW.MotorDirection1.MotorDirection1_SubsysRanBC);
  if (rtmIsMajorTimeStep(MotorModel_Sp23_V21b_M)) {
    /* MATLABSystem: '<S1>/MATLAB System' */
    if (MotorModel_Sp23_V21b_DW.obj.SampleTime !=
        MotorModel_Sp23_V21b_P.MATLABSystem_SampleTime) {
      MotorModel_Sp23_V21b_DW.obj.SampleTime =
        MotorModel_Sp23_V21b_P.MATLABSystem_SampleTime;
    }

    /* MATLABSystem: '<S1>/MATLAB System' */
    /*         %% Define output properties */
    /*  Call: int enc_output(int enc) */
    MotorModel_Sp23_V21b_B.MATLABSystem = enc_output(0.0);

    /* Gain: '<S1>/angular_position =  [relative_count//COUNTS_PER_REV] *360 degrees' */
    tmp = (uint32_T)MotorModel_Sp23_V21b_P.angular_positionrelative_countC;
    tmp_0 = (uint32_T)MotorModel_Sp23_V21b_B.MATLABSystem;
    sMultiWordMul(&tmp, 1, &tmp_0, 1,
                  &MotorModel_Sp23_V21b_B.angular_positionrelative_countC.chunks[
                  0U], 2);

    /* Outport: '<Root>/motorPos_Out' incorporates:
     *  Gain: '<S1>/angular_position =  [relative_count//COUNTS_PER_REV] *360 degrees'
     */
    MotorModel_Sp23_V21b_Y.motorPos_Out =
      MotorModel_Sp23_V21b_B.angular_positionrelative_countC;

    /* Sum: '<Root>/Sum1' incorporates:
     *  Constant: '<Root>/desiredPosition'
     *  Gain: '<S1>/angular_position =  [relative_count//COUNTS_PER_REV] *360 degrees'
     */
    tmp_2 = &MotorModel_Sp23_V21b_B.angular_positionrelative_countC;
    rtb_ErrorSignal = MotorModel_Sp23_V21b_P.desiredPosition_Value -
      sMultiWord2Double(&tmp_2->chunks[0U], 2, 0) * 1.1641532182693481E-10;

    /* Gain: '<S42>/Proportional Gain' */
    MotorModel_Sp23_V21b_B.ProportionalGain =
      MotorModel_Sp23_V21b_P.PIDController_P * rtb_ErrorSignal;

    /* Gain: '<S31>/Derivative Gain' */
    MotorModel_Sp23_V21b_B.DerivativeGain =
      MotorModel_Sp23_V21b_P.PIDController_D * rtb_ErrorSignal;
  }

  /* Gain: '<S40>/Filter Coefficient' incorporates:
   *  Integrator: '<S32>/Filter'
   *  Sum: '<S32>/SumD'
   */
  MotorModel_Sp23_V21b_B.FilterCoefficient =
    (MotorModel_Sp23_V21b_B.DerivativeGain -
     MotorModel_Sp23_V21b_X.Filter_CSTATE) *
    MotorModel_Sp23_V21b_P.PIDController_N;

  /* Sum: '<S46>/Sum' incorporates:
   *  Integrator: '<S37>/Integrator'
   */
  MotorModel_Sp23_V21b_B.Abs = (MotorModel_Sp23_V21b_B.ProportionalGain +
    MotorModel_Sp23_V21b_X.Integrator_CSTATE) +
    MotorModel_Sp23_V21b_B.FilterCoefficient;

  /* Abs: '<S1>/Abs1' */
  rtb_Abs1 = fabs(MotorModel_Sp23_V21b_B.Abs);

  /* Saturate: '<S1>/Saturation' */
  if (MotorModel_Sp23_V21b_B.Abs > MotorModel_Sp23_V21b_P.Saturation_UpperSat) {
    MotorModel_Sp23_V21b_B.Abs = MotorModel_Sp23_V21b_P.Saturation_UpperSat;
  } else if (MotorModel_Sp23_V21b_B.Abs <
             MotorModel_Sp23_V21b_P.Saturation_LowerSat) {
    MotorModel_Sp23_V21b_B.Abs = MotorModel_Sp23_V21b_P.Saturation_LowerSat;
  }

  /* End of Saturate: '<S1>/Saturation' */

  /* If: '<S1>/Choose Direction' */
  if (rtmIsMajorTimeStep(MotorModel_Sp23_V21b_M)) {
    if ((MotorModel_Sp23_V21b_B.Abs > 0.0) && (rtb_Abs1 > 3.0)) {
      MotorModel_Sp23_V21b_DW.ChooseDirection_ActiveSubsystem = 0;
    } else if ((MotorModel_Sp23_V21b_B.Abs < 0.0) && (rtb_Abs1 > 3.0)) {
      MotorModel_Sp23_V21b_DW.ChooseDirection_ActiveSubsystem = 1;
    } else {
      MotorModel_Sp23_V21b_DW.ChooseDirection_ActiveSubsystem = 2;
    }
  }

  switch (MotorModel_Sp23_V21b_DW.ChooseDirection_ActiveSubsystem) {
   case 0:
    /* Outputs for IfAction SubSystem: '<S1>/Motor Direction1' incorporates:
     *  ActionPort: '<S5>/Action Port'
     */
    MotorModel_Sp23_MotorDirection1(MotorModel_Sp23_V21b_M, &rtb_Merge1,
      &rtb_Merge2, &MotorModel_Sp23_V21b_P.MotorDirection1);
    if (rtmIsMajorTimeStep(MotorModel_Sp23_V21b_M)) {
      srUpdateBC
        (MotorModel_Sp23_V21b_DW.MotorDirection1.MotorDirection1_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S1>/Motor Direction1' */
    break;

   case 1:
    /* Outputs for IfAction SubSystem: '<S1>/Motor Direction 2' incorporates:
     *  ActionPort: '<S4>/Action Port'
     */
    MotorModel_Sp23_MotorDirection1(MotorModel_Sp23_V21b_M, &rtb_Merge1,
      &rtb_Merge2, &MotorModel_Sp23_V21b_P.MotorDirection2);
    if (rtmIsMajorTimeStep(MotorModel_Sp23_V21b_M)) {
      srUpdateBC
        (MotorModel_Sp23_V21b_DW.MotorDirection2.MotorDirection1_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S1>/Motor Direction 2' */
    break;

   case 2:
    /* Outputs for IfAction SubSystem: '<S1>/Constant Position' incorporates:
     *  ActionPort: '<S3>/Action Port'
     */
    MotorModel_Sp23_MotorDirection1(MotorModel_Sp23_V21b_M, &rtb_Merge1,
      &rtb_Merge2, &MotorModel_Sp23_V21b_P.ConstantPosition);
    if (rtmIsMajorTimeStep(MotorModel_Sp23_V21b_M)) {
      srUpdateBC
        (MotorModel_Sp23_V21b_DW.ConstantPosition.MotorDirection1_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S1>/Constant Position' */
    break;
  }

  /* End of If: '<S1>/Choose Direction' */

  /* MATLABSystem: '<S1>/Enable' */
  obj = &MotorModel_Sp23_V21b_DW.obj_b;
  obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(5UL);

  /* Gain: '<S1>/Gain' incorporates:
   *  Abs: '<S1>/Abs'
   */
  MotorModel_Sp23_V21b_B.Abs = MotorModel_Sp23_V21b_P.Gain_Gain * fabs
    (MotorModel_Sp23_V21b_B.Abs);

  /* MATLABSystem: '<S1>/Enable' */
  if (!(MotorModel_Sp23_V21b_B.Abs <= 255.0)) {
    MotorModel_Sp23_V21b_B.Abs = 255.0;
  }

  if (!(MotorModel_Sp23_V21b_B.Abs >= 0.0)) {
    MotorModel_Sp23_V21b_B.Abs = 0.0;
  }

  MW_PWM_SetDutyCycle(MotorModel_Sp23_V21b_DW.obj_b.PWMDriverObj.MW_PWM_HANDLE,
                      MotorModel_Sp23_V21b_B.Abs);
  if (rtmIsMajorTimeStep(MotorModel_Sp23_V21b_M)) {
    /* Gain: '<S34>/Integral Gain' */
    MotorModel_Sp23_V21b_B.IntegralGain = MotorModel_Sp23_V21b_P.PIDController_I
      * rtb_ErrorSignal;

    /* MATLABSystem: '<S1>/Driver In1' */
    rtb_ErrorSignal = rt_roundd_snf(rtb_Merge1);
    if (rtb_ErrorSignal < 256.0) {
      if (rtb_ErrorSignal >= 0.0) {
        tmp_1 = (uint8_T)rtb_ErrorSignal;
      } else {
        tmp_1 = 0U;
      }
    } else {
      tmp_1 = MAX_uint8_T;
    }

    writeDigitalPin(30, tmp_1);

    /* End of MATLABSystem: '<S1>/Driver In1' */

    /* MATLABSystem: '<S1>/Driver In2' */
    rtb_ErrorSignal = rt_roundd_snf(rtb_Merge2);
    if (rtb_ErrorSignal < 256.0) {
      if (rtb_ErrorSignal >= 0.0) {
        tmp_1 = (uint8_T)rtb_ErrorSignal;
      } else {
        tmp_1 = 0U;
      }
    } else {
      tmp_1 = MAX_uint8_T;
    }

    writeDigitalPin(31, tmp_1);

    /* End of MATLABSystem: '<S1>/Driver In2' */
  }

  if (rtmIsMajorTimeStep(MotorModel_Sp23_V21b_M)) {
    {                                  /* Sample time: [0.0s, 0.0s] */
      extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
      extmodeSimulationTime_T currentTime = (extmodeSimulationTime_T)
        (((MotorModel_Sp23_V21b_M->Timing.clockTick0+
           MotorModel_Sp23_V21b_M->Timing.clockTickH0* 4294967296.0) * 1) + 0)
        ;

      /* Trigger External Mode event */
      errorCode = extmodeEvent(0,currentTime);
      if (errorCode != EXTMODE_SUCCESS) {
        /* Code to handle External Mode event errors
           may be added here */
      }
    }

    if (rtmIsMajorTimeStep(MotorModel_Sp23_V21b_M)) {/* Sample time: [0.001s, 0.0s] */
      extmodeErrorCode_T errorCode = EXTMODE_SUCCESS;
      extmodeSimulationTime_T currentTime = (extmodeSimulationTime_T)
        (((MotorModel_Sp23_V21b_M->Timing.clockTick1+
           MotorModel_Sp23_V21b_M->Timing.clockTickH1* 4294967296.0) * 1) + 0)
        ;

      /* Trigger External Mode event */
      errorCode = extmodeEvent(1,currentTime);
      if (errorCode != EXTMODE_SUCCESS) {
        /* Code to handle External Mode event errors
           may be added here */
      }
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(MotorModel_Sp23_V21b_M)) {
    rt_ertODEUpdateContinuousStates(&MotorModel_Sp23_V21b_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++MotorModel_Sp23_V21b_M->Timing.clockTick0)) {
      ++MotorModel_Sp23_V21b_M->Timing.clockTickH0;
    }

    MotorModel_Sp23_V21b_M->Timing.t[0] = rtsiGetSolverStopTime
      (&MotorModel_Sp23_V21b_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.001s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.001, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      MotorModel_Sp23_V21b_M->Timing.clockTick1++;
      if (!MotorModel_Sp23_V21b_M->Timing.clockTick1) {
        MotorModel_Sp23_V21b_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void MotorModel_Sp23_V21b_derivatives(void)
{
  XDot_MotorModel_Sp23_V21b_T *_rtXdot;
  _rtXdot = ((XDot_MotorModel_Sp23_V21b_T *) MotorModel_Sp23_V21b_M->derivs);

  /* Derivatives for Integrator: '<S37>/Integrator' */
  _rtXdot->Integrator_CSTATE = MotorModel_Sp23_V21b_B.IntegralGain;

  /* Derivatives for Integrator: '<S32>/Filter' */
  _rtXdot->Filter_CSTATE = MotorModel_Sp23_V21b_B.FilterCoefficient;
}

/* Model initialize function */
void MotorModel_Sp23_V21b_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)MotorModel_Sp23_V21b_M, 0,
                sizeof(RT_MODEL_MotorModel_Sp23_V21b_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&MotorModel_Sp23_V21b_M->solverInfo,
                          &MotorModel_Sp23_V21b_M->Timing.simTimeStep);
    rtsiSetTPtr(&MotorModel_Sp23_V21b_M->solverInfo, &rtmGetTPtr
                (MotorModel_Sp23_V21b_M));
    rtsiSetStepSizePtr(&MotorModel_Sp23_V21b_M->solverInfo,
                       &MotorModel_Sp23_V21b_M->Timing.stepSize0);
    rtsiSetdXPtr(&MotorModel_Sp23_V21b_M->solverInfo,
                 &MotorModel_Sp23_V21b_M->derivs);
    rtsiSetContStatesPtr(&MotorModel_Sp23_V21b_M->solverInfo, (real_T **)
                         &MotorModel_Sp23_V21b_M->contStates);
    rtsiSetNumContStatesPtr(&MotorModel_Sp23_V21b_M->solverInfo,
      &MotorModel_Sp23_V21b_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&MotorModel_Sp23_V21b_M->solverInfo,
      &MotorModel_Sp23_V21b_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&MotorModel_Sp23_V21b_M->solverInfo,
      &MotorModel_Sp23_V21b_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&MotorModel_Sp23_V21b_M->solverInfo,
      &MotorModel_Sp23_V21b_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&MotorModel_Sp23_V21b_M->solverInfo,
                          (&rtmGetErrorStatus(MotorModel_Sp23_V21b_M)));
    rtsiSetRTModelPtr(&MotorModel_Sp23_V21b_M->solverInfo,
                      MotorModel_Sp23_V21b_M);
  }

  rtsiSetSimTimeStep(&MotorModel_Sp23_V21b_M->solverInfo, MAJOR_TIME_STEP);
  MotorModel_Sp23_V21b_M->intgData.y = MotorModel_Sp23_V21b_M->odeY;
  MotorModel_Sp23_V21b_M->intgData.f[0] = MotorModel_Sp23_V21b_M->odeF[0];
  MotorModel_Sp23_V21b_M->intgData.f[1] = MotorModel_Sp23_V21b_M->odeF[1];
  MotorModel_Sp23_V21b_M->intgData.f[2] = MotorModel_Sp23_V21b_M->odeF[2];
  MotorModel_Sp23_V21b_M->contStates = ((X_MotorModel_Sp23_V21b_T *)
    &MotorModel_Sp23_V21b_X);
  rtsiSetSolverData(&MotorModel_Sp23_V21b_M->solverInfo, (void *)
                    &MotorModel_Sp23_V21b_M->intgData);
  rtsiSetSolverName(&MotorModel_Sp23_V21b_M->solverInfo,"ode3");
  rtmSetTPtr(MotorModel_Sp23_V21b_M, &MotorModel_Sp23_V21b_M->Timing.tArray[0]);
  rtmSetTFinal(MotorModel_Sp23_V21b_M, -1);
  MotorModel_Sp23_V21b_M->Timing.stepSize0 = 0.001;

  /* External mode info */
  MotorModel_Sp23_V21b_M->Sizes.checksums[0] = (648340397U);
  MotorModel_Sp23_V21b_M->Sizes.checksums[1] = (2742848687U);
  MotorModel_Sp23_V21b_M->Sizes.checksums[2] = (90490302U);
  MotorModel_Sp23_V21b_M->Sizes.checksums[3] = (2134395989U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[8];
    MotorModel_Sp23_V21b_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)
      &MotorModel_Sp23_V21b_DW.ConstantPosition.MotorDirection1_SubsysRanBC;
    systemRan[2] = &rtAlwaysEnabled;
    systemRan[3] = &rtAlwaysEnabled;
    systemRan[4] = &rtAlwaysEnabled;
    systemRan[5] = &rtAlwaysEnabled;
    systemRan[6] = (sysRanDType *)
      &MotorModel_Sp23_V21b_DW.MotorDirection2.MotorDirection1_SubsysRanBC;
    systemRan[7] = (sysRanDType *)
      &MotorModel_Sp23_V21b_DW.MotorDirection1.MotorDirection1_SubsysRanBC;
    rteiSetModelMappingInfoPtr(MotorModel_Sp23_V21b_M->extModeInfo,
      &MotorModel_Sp23_V21b_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(MotorModel_Sp23_V21b_M->extModeInfo,
                        MotorModel_Sp23_V21b_M->Sizes.checksums);
    rteiSetTPtr(MotorModel_Sp23_V21b_M->extModeInfo, rtmGetTPtr
                (MotorModel_Sp23_V21b_M));
  }

  /* block I/O */
  (void) memset(((void *) &MotorModel_Sp23_V21b_B), 0,
                sizeof(B_MotorModel_Sp23_V21b_T));

  /* states (continuous) */
  {
    (void) memset((void *)&MotorModel_Sp23_V21b_X, 0,
                  sizeof(X_MotorModel_Sp23_V21b_T));
  }

  /* states (dwork) */
  (void) memset((void *)&MotorModel_Sp23_V21b_DW, 0,
                sizeof(DW_MotorModel_Sp23_V21b_T));

  /* external outputs */
  MotorModel_Sp23_V21b_Y.motorPos_Out = MotorModel_Sp23_V21b_sfix64_En3;

  {
    codertarget_arduinobase_inter_T *obj;

    /* Start for MATLABSystem: '<S1>/MATLAB System' */
    /*  Constructor */
    /*  Support name-value pair arguments when constructing the object. */
    MotorModel_Sp23_V21b_DW.obj.matlabCodegenIsDeleted = false;
    MotorModel_Sp23_V21b_DW.objisempty = true;

    /*  Do not generate code for sprintf */
    MotorModel_Sp23_V21b_DW.obj.SampleTime =
      MotorModel_Sp23_V21b_P.MATLABSystem_SampleTime;
    MotorModel_Sp23_V21b_DW.obj.isInitialized = 1L;

    /*         %% Define output properties */
    /*  Call: void enc_init(int enc, int pinA, int pinB) */
    enc_init(0.0, 2.0, 3.0);
    MotorModel_Sp23_V21b_DW.obj.isSetupComplete = true;

    /* Start for If: '<S1>/Choose Direction' */
    MotorModel_Sp23_V21b_DW.ChooseDirection_ActiveSubsystem = -1;

    /* Start for MATLABSystem: '<S1>/Enable' */
    MotorModel_Sp23_V21b_DW.obj_b.matlabCodegenIsDeleted = true;
    MotorModel_Sp23_V21b_DW.obj_b.isInitialized = 0L;
    MotorModel_Sp23_V21b_DW.obj_b.matlabCodegenIsDeleted = false;
    MotorModel_Sp23_V21b_DW.objisempty_k = true;
    obj = &MotorModel_Sp23_V21b_DW.obj_b;
    MotorModel_Sp23_V21b_DW.obj_b.isSetupComplete = false;
    MotorModel_Sp23_V21b_DW.obj_b.isInitialized = 1L;
    obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_Open(5UL, 0.0, 0.0);
    MotorModel_Sp23_V21b_DW.obj_b.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/Driver In1' */
    MotorModel_Sp23_V21b_DW.obj_l.matlabCodegenIsDeleted = false;
    MotorModel_Sp23_V21b_DW.objisempty_b = true;
    MotorModel_Sp23_V21b_DW.obj_l.isInitialized = 1L;
    digitalIOSetup(30, 1);
    MotorModel_Sp23_V21b_DW.obj_l.isSetupComplete = true;

    /* Start for MATLABSystem: '<S1>/Driver In2' */
    MotorModel_Sp23_V21b_DW.obj_f.matlabCodegenIsDeleted = false;
    MotorModel_Sp23_V21b_DW.objisempty_e = true;
    MotorModel_Sp23_V21b_DW.obj_f.isInitialized = 1L;
    digitalIOSetup(31, 1);
    MotorModel_Sp23_V21b_DW.obj_f.isSetupComplete = true;
  }

  /* InitializeConditions for Integrator: '<S37>/Integrator' */
  MotorModel_Sp23_V21b_X.Integrator_CSTATE =
    MotorModel_Sp23_V21b_P.PIDController_InitialConditio_o;

  /* InitializeConditions for Integrator: '<S32>/Filter' */
  MotorModel_Sp23_V21b_X.Filter_CSTATE =
    MotorModel_Sp23_V21b_P.PIDController_InitialConditionF;
}

/* Model terminate function */
void MotorModel_Sp23_V21b_terminate(void)
{
  codertarget_arduinobase_inter_T *obj;

  /* Terminate for MATLABSystem: '<S1>/MATLAB System' */
  if (!MotorModel_Sp23_V21b_DW.obj.matlabCodegenIsDeleted) {
    MotorModel_Sp23_V21b_DW.obj.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/MATLAB System' */
  /* Terminate for MATLABSystem: '<S1>/Enable' */
  obj = &MotorModel_Sp23_V21b_DW.obj_b;
  if (!MotorModel_Sp23_V21b_DW.obj_b.matlabCodegenIsDeleted) {
    MotorModel_Sp23_V21b_DW.obj_b.matlabCodegenIsDeleted = true;
    if ((MotorModel_Sp23_V21b_DW.obj_b.isInitialized == 1L) &&
        MotorModel_Sp23_V21b_DW.obj_b.isSetupComplete) {
      obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(5UL);
      MW_PWM_SetDutyCycle
        (MotorModel_Sp23_V21b_DW.obj_b.PWMDriverObj.MW_PWM_HANDLE, 0.0);
      obj->PWMDriverObj.MW_PWM_HANDLE = MW_PWM_GetHandle(5UL);
      MW_PWM_Close(MotorModel_Sp23_V21b_DW.obj_b.PWMDriverObj.MW_PWM_HANDLE);
    }
  }

  /* End of Terminate for MATLABSystem: '<S1>/Enable' */
  /* Terminate for MATLABSystem: '<S1>/Driver In1' */
  if (!MotorModel_Sp23_V21b_DW.obj_l.matlabCodegenIsDeleted) {
    MotorModel_Sp23_V21b_DW.obj_l.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Driver In1' */

  /* Terminate for MATLABSystem: '<S1>/Driver In2' */
  if (!MotorModel_Sp23_V21b_DW.obj_f.matlabCodegenIsDeleted) {
    MotorModel_Sp23_V21b_DW.obj_f.matlabCodegenIsDeleted = true;
  }

  /* End of Terminate for MATLABSystem: '<S1>/Driver In2' */
}
