//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, educational organizations only. Not for
// government, commercial, or other organizational use.
//
// File: JointSpace_Task.h
//
// Code generated for Simulink model 'JointSpace_Task'.
//
// Model version                  : 1.659
// Simulink Coder version         : 9.2 (R2019b) 18-Jul-2019
// C/C++ source code generated on : Wed Dec  9 17:37:16 2020
//
// Target selection: ert.tlc
// Embedded hardware selection: Intel->x86-64 (Linux 64)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef RTW_HEADER_JointSpace_Task_h_
#define RTW_HEADER_JointSpace_Task_h_
#include <cmath>
#include <math.h>
#include <cstring>
#ifndef JointSpace_Task_COMMON_INCLUDES_
# define JointSpace_Task_COMMON_INCLUDES_
#include <cstdio>
#include <BlockFactory/Core/Block.h>
#include <BlockFactory/Core/Log.h>
#include <BlockFactory/Core/Parameter.h>
#include <BlockFactory/Core/Parameters.h>
#include <BlockFactory/Core/FactorySingleton.h>
#include <BlockFactory/SimulinkCoder/CoderBlockInformation.h>
#include "rtwtypes.h"
#endif                                 // JointSpace_Task_COMMON_INCLUDES_

#include "JointSpace_Task_types.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

// Block signals (default storage)
typedef struct {
  real_T getJointPosition[4];          // '<Root>/getJointPosition'
  real_T getJointLimits_o1[4];         // '<Root>/getJointLimits'
  real_T getJointLimits_o2[4];         // '<Root>/getJointLimits'
  real_T Sum2[4];                      // '<S1>/Sum2'
} B_JointSpace_Task_T;

// Block states (default storage) for system '<Root>'
typedef struct {
  real_T Delay_DSTATE;                 // '<S2>/Delay'
  real_T UnitDelay_DSTATE;             // '<S2>/Unit Delay'
  struct {
    void *blockPWork[2];
  } getJointPosition_PWORK;            // '<Root>/getJointPosition'

  struct {
    void *blockPWork[2];
  } getJointLimits_PWORK;              // '<Root>/getJointLimits'

  struct {
    void *blockPWork[2];
  } setPositionReference_PWORK;        // '<Root>/setPositionReference'
} DW_JointSpace_Task_T;

// Invariant block signals (default storage)
typedef const struct tag_ConstB_JointSpace_Task_T {
  real_T MathFunction;                 // '<S1>/Math Function'
  real_T Divide1;                      // '<S1>/Divide1'
  real_T MathFunction1;                // '<S1>/Math Function1'
  real_T Divide3;                      // '<S1>/Divide3'
} ConstB_JointSpace_Task_T;

// Real-time Model Data Structure
struct tag_RTM_JointSpace_Task_T {
  const char_T *errorStatus;
};

extern const ConstB_JointSpace_Task_T JointSpace_Task_ConstB;// constant block i/o 

// Class declaration for model JointSpace_Task
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
  RT_MODEL_JointSpace_Task_T * getRTM();

  // private data and function members
 private:
  // Block signals
  B_JointSpace_Task_T JointSpace_Task_B;

  // Block states
  DW_JointSpace_Task_T JointSpace_Task_DW;

  // Real-Time Model
  RT_MODEL_JointSpace_Task_T JointSpace_Task_M;
};

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Scope2' : Unused code path elimination
//  Block '<S3>/Data Type Duplicate' : Unused code path elimination
//  Block '<S3>/Data Type Propagation' : Unused code path elimination
//  Block '<S2>/Scope2' : Unused code path elimination
//  Block '<S1>/Data Type Conversion' : Eliminate redundant data type conversion


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
//  '<Root>' : 'JointSpace_Task'
//  '<S1>'   : 'JointSpace_Task/ThirdOrderTrajectory'
//  '<S2>'   : 'JointSpace_Task/ThirdOrderTrajectory/CounterTime'
//  '<S3>'   : 'JointSpace_Task/ThirdOrderTrajectory/CounterTime/Saturation Dynamic'

#endif                                 // RTW_HEADER_JointSpace_Task_h_

//
// File trailer for generated code.
//
// [EOF]
//
