/*
 * MotorModel_Sp23_V21b.h
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

#ifndef RTW_HEADER_MotorModel_Sp23_V21b_h_
#define RTW_HEADER_MotorModel_Sp23_V21b_h_
#include <math.h>
#include <string.h>
#ifndef MotorModel_Sp23_V21b_COMMON_INCLUDES_
#define MotorModel_Sp23_V21b_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_extmode.h"
#include "sysran_types.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "ext_mode.h"
#include "MW_arduino_digitalio.h"
#include "MW_PWM.h"
#include "encoder_arduino.h"
#endif                               /* MotorModel_Sp23_V21b_COMMON_INCLUDES_ */

#include "MotorModel_Sp23_V21b_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "MW_target_hardware_resources.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
#define rtmGetRTWExtModeInfo(rtm)      ((rtm)->extModeInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block states (default storage) for system '<S1>/Motor Direction1' */
typedef struct {
  int8_T MotorDirection1_SubsysRanBC;  /* '<S1>/Motor Direction1' */
} DW_MotorDirection1_MotorModel_T;

/* Block signals (default storage) */
typedef struct {
  real_T DerivativeGain;               /* '<S31>/Derivative Gain' */
  real_T FilterCoefficient;            /* '<S40>/Filter Coefficient' */
  real_T IntegralGain;                 /* '<S34>/Integral Gain' */
  real_T Abs;                          /* '<S1>/Abs' */
  int64m_T angular_positionrelative_countC;
  /* '<S1>/angular_position =  [relative_count//COUNTS_PER_REV] *360 degrees' */
  real_T ProportionalGain;             /* '<S42>/Proportional Gain' */
  int32_T MATLABSystem;                /* '<S1>/MATLAB System' */
} B_MotorModel_Sp23_V21b_T;

/* Block states (default storage) for system '<Root>' */
typedef struct {
  Encoder_arduino_MotorModel_Sp_T obj; /* '<S1>/MATLAB System' */
  codertarget_arduinobase_block_T obj_f;/* '<S1>/Driver In2' */
  codertarget_arduinobase_block_T obj_l;/* '<S1>/Driver In1' */
  codertarget_arduinobase_inter_T obj_b;/* '<S1>/Enable' */
  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<Root>/Scope' */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_Motor;   /* synthesized block */

  struct {
    void *AQHandles;
  } TAQSigLogging_InsertedFor_MATLA;   /* synthesized block */

  int8_T ChooseDirection_ActiveSubsystem;/* '<S1>/Choose Direction' */
  boolean_T objisempty;                /* '<S1>/MATLAB System' */
  boolean_T objisempty_k;              /* '<S1>/Enable' */
  boolean_T objisempty_e;              /* '<S1>/Driver In2' */
  boolean_T objisempty_b;              /* '<S1>/Driver In1' */
  DW_MotorDirection1_MotorModel_T ConstantPosition;/* '<S1>/Constant Position' */
  DW_MotorDirection1_MotorModel_T MotorDirection2;/* '<S1>/Motor Direction 2' */
  DW_MotorDirection1_MotorModel_T MotorDirection1;/* '<S1>/Motor Direction1' */
} DW_MotorModel_Sp23_V21b_T;

/* Continuous states (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S37>/Integrator' */
  real_T Filter_CSTATE;                /* '<S32>/Filter' */
} X_MotorModel_Sp23_V21b_T;

/* State derivatives (default storage) */
typedef struct {
  real_T Integrator_CSTATE;            /* '<S37>/Integrator' */
  real_T Filter_CSTATE;                /* '<S32>/Filter' */
} XDot_MotorModel_Sp23_V21b_T;

/* State disabled  */
typedef struct {
  boolean_T Integrator_CSTATE;         /* '<S37>/Integrator' */
  boolean_T Filter_CSTATE;             /* '<S32>/Filter' */
} XDis_MotorModel_Sp23_V21b_T;

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
typedef struct {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
} ODE3_IntgData;

#endif

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  int64m_T motorPos_Out;               /* '<Root>/motorPos_Out' */
} ExtY_MotorModel_Sp23_V21b_T;

/* Parameters for system: '<S1>/Motor Direction1' */
struct P_MotorDirection1_MotorModel__T_ {
  real_T Constant_Value;               /* Expression: 1
                                        * Referenced by: '<S5>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<S5>/Constant1'
                                        */
};

/* Parameters (default storage) */
struct P_MotorModel_Sp23_V21b_T_ {
  real_T PIDController_D;              /* Mask Parameter: PIDController_D
                                        * Referenced by: '<S31>/Derivative Gain'
                                        */
  real_T PIDController_I;              /* Mask Parameter: PIDController_I
                                        * Referenced by: '<S34>/Integral Gain'
                                        */
  real_T PIDController_InitialConditionF;
                              /* Mask Parameter: PIDController_InitialConditionF
                               * Referenced by: '<S32>/Filter'
                               */
  real_T PIDController_InitialConditio_o;
                              /* Mask Parameter: PIDController_InitialConditio_o
                               * Referenced by: '<S37>/Integrator'
                               */
  real_T PIDController_N;              /* Mask Parameter: PIDController_N
                                        * Referenced by: '<S40>/Filter Coefficient'
                                        */
  real_T PIDController_P;              /* Mask Parameter: PIDController_P
                                        * Referenced by: '<S42>/Proportional Gain'
                                        */
  real_T MATLABSystem_SampleTime;      /* Expression: 0.001
                                        * Referenced by: '<S1>/MATLAB System'
                                        */
  real_T desiredPosition_Value;        /* Expression: 0
                                        * Referenced by: '<Root>/desiredPosition'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 5
                                        * Referenced by: '<S1>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -5
                                        * Referenced by: '<S1>/Saturation'
                                        */
  real_T Gain_Gain;                    /* Expression: 255/3
                                        * Referenced by: '<S1>/Gain'
                                        */
  int32_T angular_positionrelative_countC;
                          /* Computed Parameter: angular_positionrelative_countC
                           * Referenced by: '<S1>/angular_position =  [relative_count//COUNTS_PER_REV] *360 degrees'
                           */
  P_MotorDirection1_MotorModel__T ConstantPosition;/* '<S1>/Constant Position' */
  P_MotorDirection1_MotorModel__T MotorDirection2;/* '<S1>/Motor Direction 2' */
  P_MotorDirection1_MotorModel__T MotorDirection1;/* '<S1>/Motor Direction1' */
};

/* Real-time Model Data Structure */
struct tag_RTM_MotorModel_Sp23_V21b_T {
  const char_T *errorStatus;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  X_MotorModel_Sp23_V21b_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeY[2];
  real_T odeF[3][2];
  ODE3_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_MotorModel_Sp23_V21b_T MotorModel_Sp23_V21b_P;

/* Block signals (default storage) */
extern B_MotorModel_Sp23_V21b_T MotorModel_Sp23_V21b_B;

/* Continuous states (default storage) */
extern X_MotorModel_Sp23_V21b_T MotorModel_Sp23_V21b_X;

/* Block states (default storage) */
extern DW_MotorModel_Sp23_V21b_T MotorModel_Sp23_V21b_DW;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_MotorModel_Sp23_V21b_T MotorModel_Sp23_V21b_Y;

/* External data declarations for dependent source files */
extern const int64m_T MotorModel_Sp23_V21b_sfix64_En3;/* int64m_T ground */

/* Model entry point functions */
extern void MotorModel_Sp23_V21b_initialize(void);
extern void MotorModel_Sp23_V21b_step(void);
extern void MotorModel_Sp23_V21b_terminate(void);

/* Real-time Model object */
extern RT_MODEL_MotorModel_Sp23_V21b_T *const MotorModel_Sp23_V21b_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'MotorModel_Sp23_V21b'
 * '<S1>'   : 'MotorModel_Sp23_V21b/Motor'
 * '<S2>'   : 'MotorModel_Sp23_V21b/PID Controller'
 * '<S3>'   : 'MotorModel_Sp23_V21b/Motor/Constant Position'
 * '<S4>'   : 'MotorModel_Sp23_V21b/Motor/Motor Direction 2'
 * '<S5>'   : 'MotorModel_Sp23_V21b/Motor/Motor Direction1'
 * '<S6>'   : 'MotorModel_Sp23_V21b/PID Controller/Anti-windup'
 * '<S7>'   : 'MotorModel_Sp23_V21b/PID Controller/D Gain'
 * '<S8>'   : 'MotorModel_Sp23_V21b/PID Controller/Filter'
 * '<S9>'   : 'MotorModel_Sp23_V21b/PID Controller/Filter ICs'
 * '<S10>'  : 'MotorModel_Sp23_V21b/PID Controller/I Gain'
 * '<S11>'  : 'MotorModel_Sp23_V21b/PID Controller/Ideal P Gain'
 * '<S12>'  : 'MotorModel_Sp23_V21b/PID Controller/Ideal P Gain Fdbk'
 * '<S13>'  : 'MotorModel_Sp23_V21b/PID Controller/Integrator'
 * '<S14>'  : 'MotorModel_Sp23_V21b/PID Controller/Integrator ICs'
 * '<S15>'  : 'MotorModel_Sp23_V21b/PID Controller/N Copy'
 * '<S16>'  : 'MotorModel_Sp23_V21b/PID Controller/N Gain'
 * '<S17>'  : 'MotorModel_Sp23_V21b/PID Controller/P Copy'
 * '<S18>'  : 'MotorModel_Sp23_V21b/PID Controller/Parallel P Gain'
 * '<S19>'  : 'MotorModel_Sp23_V21b/PID Controller/Reset Signal'
 * '<S20>'  : 'MotorModel_Sp23_V21b/PID Controller/Saturation'
 * '<S21>'  : 'MotorModel_Sp23_V21b/PID Controller/Saturation Fdbk'
 * '<S22>'  : 'MotorModel_Sp23_V21b/PID Controller/Sum'
 * '<S23>'  : 'MotorModel_Sp23_V21b/PID Controller/Sum Fdbk'
 * '<S24>'  : 'MotorModel_Sp23_V21b/PID Controller/Tracking Mode'
 * '<S25>'  : 'MotorModel_Sp23_V21b/PID Controller/Tracking Mode Sum'
 * '<S26>'  : 'MotorModel_Sp23_V21b/PID Controller/Tsamp - Integral'
 * '<S27>'  : 'MotorModel_Sp23_V21b/PID Controller/Tsamp - Ngain'
 * '<S28>'  : 'MotorModel_Sp23_V21b/PID Controller/postSat Signal'
 * '<S29>'  : 'MotorModel_Sp23_V21b/PID Controller/preSat Signal'
 * '<S30>'  : 'MotorModel_Sp23_V21b/PID Controller/Anti-windup/Passthrough'
 * '<S31>'  : 'MotorModel_Sp23_V21b/PID Controller/D Gain/Internal Parameters'
 * '<S32>'  : 'MotorModel_Sp23_V21b/PID Controller/Filter/Cont. Filter'
 * '<S33>'  : 'MotorModel_Sp23_V21b/PID Controller/Filter ICs/Internal IC - Filter'
 * '<S34>'  : 'MotorModel_Sp23_V21b/PID Controller/I Gain/Internal Parameters'
 * '<S35>'  : 'MotorModel_Sp23_V21b/PID Controller/Ideal P Gain/Passthrough'
 * '<S36>'  : 'MotorModel_Sp23_V21b/PID Controller/Ideal P Gain Fdbk/Disabled'
 * '<S37>'  : 'MotorModel_Sp23_V21b/PID Controller/Integrator/Continuous'
 * '<S38>'  : 'MotorModel_Sp23_V21b/PID Controller/Integrator ICs/Internal IC'
 * '<S39>'  : 'MotorModel_Sp23_V21b/PID Controller/N Copy/Disabled'
 * '<S40>'  : 'MotorModel_Sp23_V21b/PID Controller/N Gain/Internal Parameters'
 * '<S41>'  : 'MotorModel_Sp23_V21b/PID Controller/P Copy/Disabled'
 * '<S42>'  : 'MotorModel_Sp23_V21b/PID Controller/Parallel P Gain/Internal Parameters'
 * '<S43>'  : 'MotorModel_Sp23_V21b/PID Controller/Reset Signal/Disabled'
 * '<S44>'  : 'MotorModel_Sp23_V21b/PID Controller/Saturation/Passthrough'
 * '<S45>'  : 'MotorModel_Sp23_V21b/PID Controller/Saturation Fdbk/Disabled'
 * '<S46>'  : 'MotorModel_Sp23_V21b/PID Controller/Sum/Sum_PID'
 * '<S47>'  : 'MotorModel_Sp23_V21b/PID Controller/Sum Fdbk/Disabled'
 * '<S48>'  : 'MotorModel_Sp23_V21b/PID Controller/Tracking Mode/Disabled'
 * '<S49>'  : 'MotorModel_Sp23_V21b/PID Controller/Tracking Mode Sum/Passthrough'
 * '<S50>'  : 'MotorModel_Sp23_V21b/PID Controller/Tsamp - Integral/Passthrough'
 * '<S51>'  : 'MotorModel_Sp23_V21b/PID Controller/Tsamp - Ngain/Passthrough'
 * '<S52>'  : 'MotorModel_Sp23_V21b/PID Controller/postSat Signal/Forward_Path'
 * '<S53>'  : 'MotorModel_Sp23_V21b/PID Controller/preSat Signal/Forward_Path'
 */
#endif                                 /* RTW_HEADER_MotorModel_Sp23_V21b_h_ */
