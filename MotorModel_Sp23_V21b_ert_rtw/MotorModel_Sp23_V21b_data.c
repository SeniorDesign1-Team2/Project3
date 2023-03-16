/*
 * MotorModel_Sp23_V21b_data.c
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

/* Block parameters (default storage) */
P_MotorModel_Sp23_V21b_T MotorModel_Sp23_V21b_P = {
  /* Mask Parameter: PIDController_D
   * Referenced by: '<S31>/Derivative Gain'
   */
  0.0,

  /* Mask Parameter: PIDController_I
   * Referenced by: '<S34>/Integral Gain'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditionF
   * Referenced by: '<S32>/Filter'
   */
  0.0,

  /* Mask Parameter: PIDController_InitialConditio_o
   * Referenced by: '<S37>/Integrator'
   */
  0.0,

  /* Mask Parameter: PIDController_N
   * Referenced by: '<S40>/Filter Coefficient'
   */
  200.0,

  /* Mask Parameter: PIDController_P
   * Referenced by: '<S42>/Proportional Gain'
   */
  0.01,

  /* Expression: 0.001
   * Referenced by: '<S1>/MATLAB System'
   */
  0.001,

  /* Expression: 0
   * Referenced by: '<Root>/desiredPosition'
   */
  0.0,

  /* Expression: 5
   * Referenced by: '<S1>/Saturation'
   */
  5.0,

  /* Expression: -5
   * Referenced by: '<S1>/Saturation'
   */
  -5.0,

  /* Expression: 255/3
   * Referenced by: '<S1>/Gain'
   */
  85.0,

  /* Computed Parameter: angular_positionrelative_countC
   * Referenced by: '<S1>/angular_position =  [relative_count//COUNTS_PER_REV] *360 degrees'
   */
  1105604738,

  /* Start of '<S1>/Constant Position' */
  {
    /* Expression: 0
     * Referenced by: '<S3>/Constant'
     */
    0.0,

    /* Expression: 0
     * Referenced by: '<S3>/Constant1'
     */
    0.0
  }
  ,

  /* End of '<S1>/Constant Position' */

  /* Start of '<S1>/Motor Direction 2' */
  {
    /* Expression: 0
     * Referenced by: '<S4>/Constant'
     */
    0.0,

    /* Expression: 1
     * Referenced by: '<S4>/Constant1'
     */
    1.0
  }
  ,

  /* End of '<S1>/Motor Direction 2' */

  /* Start of '<S1>/Motor Direction1' */
  {
    /* Expression: 1
     * Referenced by: '<S5>/Constant'
     */
    1.0,

    /* Expression: 0
     * Referenced by: '<S5>/Constant1'
     */
    0.0
  }
  /* End of '<S1>/Motor Direction1' */
};
