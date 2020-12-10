//
// Non-Degree Granting Education License -- for use at non-degree
// granting, nonprofit, educational organizations only. Not for
// government, commercial, or other organizational use.
//
// File: JointSpace_Task.cpp
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
#include "JointSpace_Task.h"
#include "JointSpace_Task_private.h"

real_T rt_powd_snf(real_T u0, real_T u1)
{
  real_T y;
  real_T tmp;
  real_T tmp_0;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = (rtNaN);
  } else {
    tmp = std::abs(u0);
    tmp_0 = std::abs(u1);
    if (rtIsInf(u1)) {
      if (tmp == 1.0) {
        y = 1.0;
      } else if (tmp > 1.0) {
        if (u1 > 0.0) {
          y = (rtInf);
        } else {
          y = 0.0;
        }
      } else if (u1 > 0.0) {
        y = 0.0;
      } else {
        y = (rtInf);
      }
    } else if (tmp_0 == 0.0) {
      y = 1.0;
    } else if (tmp_0 == 1.0) {
      if (u1 > 0.0) {
        y = u0;
      } else {
        y = 1.0 / u0;
      }
    } else if (u1 == 2.0) {
      y = u0 * u0;
    } else if ((u1 == 0.5) && (u0 >= 0.0)) {
      y = std::sqrt(u0);
    } else if ((u0 < 0.0) && (u1 > std::floor(u1))) {
      y = (rtNaN);
    } else {
      y = pow(u0, u1);
    }
  }

  return y;
}

// Model step function
void modelModelClass::step()
{
  real_T rtb_MathFunction1;
  real_T rtb_q_diff_idx_0;
  real_T rtb_q_diff_idx_1;
  real_T rtb_q_diff_idx_2;
  real_T rtb_q_diff_idx_3;

  // S-Function (BlockFactory): '<Root>/getJointPosition'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (JointSpace_Task_DW.getJointPosition_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (JointSpace_Task_DW.getJointPosition_PWORK.blockPWork[0]);

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

  // S-Function (BlockFactory): '<Root>/getJointLimits'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (JointSpace_Task_DW.getJointLimits_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (JointSpace_Task_DW.getJointLimits_PWORK.blockPWork[0]);

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

  // End of S-Function Block: <Root>/getJointLimits

  // Sum: '<S1>/Sum1' incorporates:
  //   Constant: '<S1>/Constant'
  //   Product: '<S1>/Divide'
  //   Sum: '<S1>/Sum'

  rtb_q_diff_idx_0 = (JointSpace_Task_B.getJointLimits_o1[0] +
                      JointSpace_Task_B.getJointLimits_o2[0]) / 2.0 -
    JointSpace_Task_B.getJointPosition[0];
  rtb_q_diff_idx_1 = (JointSpace_Task_B.getJointLimits_o1[1] +
                      JointSpace_Task_B.getJointLimits_o2[1]) / 2.0 -
    JointSpace_Task_B.getJointPosition[1];
  rtb_q_diff_idx_2 = (JointSpace_Task_B.getJointLimits_o1[2] +
                      JointSpace_Task_B.getJointLimits_o2[2]) / 2.0 -
    JointSpace_Task_B.getJointPosition[2];
  rtb_q_diff_idx_3 = (JointSpace_Task_B.getJointLimits_o1[3] +
                      JointSpace_Task_B.getJointLimits_o2[3]) / 2.0 -
    JointSpace_Task_B.getJointPosition[3];

  // Switch: '<S2>/Switch' incorporates:
  //   Constant: '<Root>/Constant2'
  //   Constant: '<S2>/Constant1'
  //   Delay: '<S2>/Delay'

  if (JointSpace_Task_DW.Delay_DSTATE != 0.0) {
    rtb_MathFunction1 = 0.05;
  } else {
    rtb_MathFunction1 = 0.0;
  }

  // End of Switch: '<S2>/Switch'

  // Sum: '<S2>/Sum' incorporates:
  //   UnitDelay: '<S2>/Unit Delay'

  JointSpace_Task_DW.UnitDelay_DSTATE += rtb_MathFunction1;

  // Switch: '<S3>/Switch2' incorporates:
  //   Constant: '<Root>/Constant1'
  //   Constant: '<S2>/Constant3'
  //   RelationalOperator: '<S3>/LowerRelop1'
  //   RelationalOperator: '<S3>/UpperRelop'
  //   Switch: '<S3>/Switch'
  //   UnitDelay: '<S2>/Unit Delay'

  if (JointSpace_Task_DW.UnitDelay_DSTATE > 5.0) {
    JointSpace_Task_DW.UnitDelay_DSTATE = 5.0;
  } else {
    if (JointSpace_Task_DW.UnitDelay_DSTATE < 0.0) {
      // Switch: '<S3>/Switch' incorporates:
      //   Constant: '<S2>/Constant3'
      //   UnitDelay: '<S2>/Unit Delay'

      JointSpace_Task_DW.UnitDelay_DSTATE = 0.0;
    }
  }

  // End of Switch: '<S3>/Switch2'

  // Math: '<S2>/Math Function' incorporates:
  //   Constant: '<S2>/Constant4'
  //   UnitDelay: '<S2>/Unit Delay'

  rtb_MathFunction1 = rt_powd_snf(JointSpace_Task_DW.UnitDelay_DSTATE, 2.0);

  // Product: '<S1>/Divide6' incorporates:
  //   Product: '<S1>/Divide2'

  JointSpace_Task_B.Sum2[0] = rtb_q_diff_idx_0 * JointSpace_Task_ConstB.Divide1 *
    rtb_MathFunction1;
  JointSpace_Task_B.Sum2[1] = rtb_q_diff_idx_1 * JointSpace_Task_ConstB.Divide1 *
    rtb_MathFunction1;
  JointSpace_Task_B.Sum2[2] = rtb_q_diff_idx_2 * JointSpace_Task_ConstB.Divide1 *
    rtb_MathFunction1;
  JointSpace_Task_B.Sum2[3] = rtb_q_diff_idx_3 * JointSpace_Task_ConstB.Divide1 *
    rtb_MathFunction1;

  // Math: '<S2>/Math Function1' incorporates:
  //   Constant: '<S2>/Constant5'
  //   UnitDelay: '<S2>/Unit Delay'

  rtb_MathFunction1 = rt_powd_snf(JointSpace_Task_DW.UnitDelay_DSTATE, 3.0);

  // Sum: '<S1>/Sum2' incorporates:
  //   Product: '<S1>/Divide4'
  //   Product: '<S1>/Divide5'

  JointSpace_Task_B.Sum2[0] = rtb_q_diff_idx_0 * JointSpace_Task_ConstB.Divide3 *
    rtb_MathFunction1 + (JointSpace_Task_B.getJointPosition[0] +
    JointSpace_Task_B.Sum2[0]);
  JointSpace_Task_B.Sum2[1] = rtb_q_diff_idx_1 * JointSpace_Task_ConstB.Divide3 *
    rtb_MathFunction1 + (JointSpace_Task_B.getJointPosition[1] +
    JointSpace_Task_B.Sum2[1]);
  JointSpace_Task_B.Sum2[2] = rtb_q_diff_idx_2 * JointSpace_Task_ConstB.Divide3 *
    rtb_MathFunction1 + (JointSpace_Task_B.getJointPosition[2] +
    JointSpace_Task_B.Sum2[2]);
  JointSpace_Task_B.Sum2[3] = rtb_q_diff_idx_3 * JointSpace_Task_ConstB.Divide3 *
    rtb_MathFunction1 + (JointSpace_Task_B.getJointPosition[3] +
    JointSpace_Task_B.Sum2[3]);

  // S-Function (BlockFactory): '<Root>/setPositionReference'
  {
    // Get the CoderBlockInformation from the PWork
    blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
    blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
      (JointSpace_Task_DW.setPositionReference_PWORK.blockPWork[1]);

    // Get the Block from the PWork
    blockfactory::core::Block* blockPtr = nullptr;
    blockPtr = static_cast<blockfactory::core::Block*>
      (JointSpace_Task_DW.setPositionReference_PWORK.blockPWork[0]);

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

  // End of S-Function Block: <Root>/setPositionReference

  // Update for Delay: '<S2>/Delay' incorporates:
  //   Constant: '<S2>/Constant2'

  JointSpace_Task_DW.Delay_DSTATE = 1.0;
}

// Model initialize function
void modelModelClass::initialize()
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  // block I/O
  (void) std::memset((static_cast<void *>(&JointSpace_Task_B)), 0,
                     sizeof(B_JointSpace_Task_T));

  // states (dwork)
  (void) std::memset(static_cast<void *>(&JointSpace_Task_DW), 0,
                     sizeof(DW_JointSpace_Task_T));

  // Start for S-Function (BlockFactory): '<Root>/getJointPosition'
  {
    // Create and store the CoderBlockInformation object
    blockfactory::coder::CoderBlockInformation* blockInfo = new blockfactory::
      coder::CoderBlockInformation();
    JointSpace_Task_DW.getJointPosition_PWORK.blockPWork[1] = static_cast<void*>
      (blockInfo);

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
    blockInfo->setUniqueBlockName("JointSpace_Task/getJointPosition");

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
        static_cast<void*>(&JointSpace_Task_B.getJointPosition[0]));

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
      JointSpace_Task_DW.getJointPosition_PWORK.blockPWork[0] = static_cast<void*>
        (blockPtr);
    }
    // End of S-Function Block: <Root>/getJointPosition
    // Start for S-Function (BlockFactory): '<Root>/getJointLimits'
{
      // Create and store the CoderBlockInformation object
      blockfactory::coder::CoderBlockInformation* blockInfo = new blockfactory::
        coder::CoderBlockInformation();
      JointSpace_Task_DW.getJointLimits_PWORK.blockPWork[1] = static_cast<void*>
        (blockInfo);

      // Initialize the parameters
      // -------------------------
      blockfactory::core::Parameters params;
      params.storeParameter<std::string>("Robot",
        blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
        STRING, 4.0, 1.0, 1.0, "GetType"));
      params.storeParameter<std::string>("XBotBlock_getJointLimits",
        blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
        STRING, 0.0, 1.0, 1.0, "className"));
      params.storeParameter<std::string>("getJointLimits",
        blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
        STRING, 1.0, 1.0, 1.0, "libName"));
      params.storeParameter<std::string>("DefaultModel",
        blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
        STRING, 3.0, 1.0, 1.0, "ModelName"));
      params.storeParameter<std::string>("DefaultRobot",
        blockfactory::core::ParameterMetadata(blockfactory::core::ParameterType::
        STRING, 2.0, 1.0, 1.0, "RobotName"));

      // Store the block name
      blockInfo->setUniqueBlockName("JointSpace_Task/getJointLimits");

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
          static_cast<void*>(&JointSpace_Task_B.getJointLimits_o1[0]));
        blockInfo->setOutputPort(
        {
          1, {
            1, 4
          }, blockfactory::core::Port::DataType::DOUBLE
        }

          ,
            static_cast<void*>(&JointSpace_Task_B.getJointLimits_o2[0]));

          // Initialize the class
          // --------------------

          // Get the block factory
          auto factory = blockfactory::core::ClassFactorySingleton::getInstance()
            .getClassFactory(
                             {
                             "getJointLimits", "XBotBlock_getJointLimits"
                             } );

          if (!factory) {
            bfError << "Failed to get factory object (className=" <<
              "XBotBlock_getJointLimits"
              << ",libName=" << "getJointLimits" << ")";
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
          JointSpace_Task_DW.getJointLimits_PWORK.blockPWork[0] = static_cast<
            void*>(blockPtr);
        }
        // End of S-Function Block: <Root>/getJointLimits
        // Start for S-Function (BlockFactory): '<Root>/setPositionReference'
{
          // Create and store the CoderBlockInformation object
          blockfactory::coder::CoderBlockInformation* blockInfo = new
            blockfactory::coder::CoderBlockInformation();
          JointSpace_Task_DW.setPositionReference_PWORK.blockPWork[1] =
            static_cast<void*>(blockInfo);

          // Initialize the parameters
          // -------------------------
          blockfactory::core::Parameters params;
          params.storeParameter<std::string>("DefaultRobot",
            blockfactory::core::ParameterMetadata(blockfactory::core::
            ParameterType::STRING, 2.0, 1.0, 1.0, "RobotName"));
          params.storeParameter<std::string>("setPositionReference",
            blockfactory::core::ParameterMetadata(blockfactory::core::
            ParameterType::STRING, 1.0, 1.0, 1.0, "libName"));
          params.storeParameter<std::string>("On",
            blockfactory::core::ParameterMetadata(blockfactory::core::
            ParameterType::STRING, 3.0, 1.0, 1.0, "MoveRobot"));
          params.storeParameter<std::string>("XBotBlock_setPositionReference",
            blockfactory::core::ParameterMetadata(blockfactory::core::
            ParameterType::STRING, 0.0, 1.0, 1.0, "className"));

          // Store the block name
          blockInfo->setUniqueBlockName("JointSpace_Task/setPositionReference");

          // Store the parameters in the CoderBlockInformation object
          blockInfo->storeRTWParameters(params);

          // Initialize input / output Signals
          // ---------------------------------

          // Inputs
          blockInfo->setInputPort(
          {
            0, {
                                  1, 4
            }, blockfactory::core::Port::DataType::DOUBLE
          }

            ,
                                  static_cast<void*>(&JointSpace_Task_B.Sum2[0]));

            // Outputs

            // Initialize the class
            // --------------------

            // Get the block factory
            auto factory = blockfactory::core::ClassFactorySingleton::
              getInstance().getClassFactory(
            {
              "setPositionReference", "XBotBlock_setPositionReference"
            } );

            if (!factory) {
              bfError << "Failed to get factory object (className=" <<
                "XBotBlock_setPositionReference"
                << ",libName=" << "setPositionReference" << ")";
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
            JointSpace_Task_DW.setPositionReference_PWORK.blockPWork[0] =
              static_cast<void*>(blockPtr);
          }
          // End of S-Function Block: <Root>/setPositionReference
        }

          // Model terminate function
          void modelModelClass::terminate()
          {
            // Terminate for S-Function (BlockFactory): '<Root>/getJointPosition' 
            {
              // Get the CoderBlockInformation from the PWork
              blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
              blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
                (JointSpace_Task_DW.getJointPosition_PWORK.blockPWork[1]);

              // Get the Block from the PWork
              blockfactory::core::Block* blockPtr = nullptr;
              blockPtr = static_cast<blockfactory::core::Block*>
                (JointSpace_Task_DW.getJointPosition_PWORK.blockPWork[0]);

              // Get the block factory
              auto factory = blockfactory::core::ClassFactorySingleton::
                getInstance().getClassFactory(
              {
                "getJointPosition", "XBotBlock_getJointPosition"
              } );

              if (!factory) {
                bfError << "Failed to get factory object (className=" <<
                  "XBotBlock_getJointPosition"
                  << ",libName=" << "getJointPosition" << ")";
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

              // Terminate the class
              // -------------------
              bool ok;
              ok = blockPtr->terminate(blockInfo);

              // Destroy the block
              factory->destroy(blockPtr);
              blockPtr = nullptr;

              // Decrease the counter of the factory
              factory->removeRef();
              if (factory->getReferenceCount() == 1) {
                // Delete the memory ownership of the shared pointer used in this function
                factory.reset();

                // Delete the factory object
                if (!blockfactory::core::ClassFactorySingleton::getInstance().
                    destroyFactory(
                                   {"getJointPosition",
                                   "XBotBlock_getJointPosition"})) {
                  bfError << "Failed to destroy the factory";

                  // Do not return since other actions need to be performed
                }
              }

              // Delete the BlockInformation object
              delete blockInfo;
              blockInfo = nullptr;

              // Report errors
              if (!ok) {
                std::string error = blockfactory::core::Log::getSingleton().
                  getErrors();
                error = "[Terminate]" + error;

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

            // Terminate for S-Function (BlockFactory): '<Root>/getJointLimits'
            {
              // Get the CoderBlockInformation from the PWork
              blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
              blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
                (JointSpace_Task_DW.getJointLimits_PWORK.blockPWork[1]);

              // Get the Block from the PWork
              blockfactory::core::Block* blockPtr = nullptr;
              blockPtr = static_cast<blockfactory::core::Block*>
                (JointSpace_Task_DW.getJointLimits_PWORK.blockPWork[0]);

              // Get the block factory
              auto factory = blockfactory::core::ClassFactorySingleton::
                getInstance().getClassFactory(
              {
                "getJointLimits", "XBotBlock_getJointLimits"
              } );

              if (!factory) {
                bfError << "Failed to get factory object (className=" <<
                  "XBotBlock_getJointLimits"
                  << ",libName=" << "getJointLimits" << ")";
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

              // Terminate the class
              // -------------------
              bool ok;
              ok = blockPtr->terminate(blockInfo);

              // Destroy the block
              factory->destroy(blockPtr);
              blockPtr = nullptr;

              // Decrease the counter of the factory
              factory->removeRef();
              if (factory->getReferenceCount() == 1) {
                // Delete the memory ownership of the shared pointer used in this function
                factory.reset();

                // Delete the factory object
                if (!blockfactory::core::ClassFactorySingleton::getInstance().
                    destroyFactory(
                                   {"getJointLimits", "XBotBlock_getJointLimits"
                                   })) {
                  bfError << "Failed to destroy the factory";

                  // Do not return since other actions need to be performed
                }
              }

              // Delete the BlockInformation object
              delete blockInfo;
              blockInfo = nullptr;

              // Report errors
              if (!ok) {
                std::string error = blockfactory::core::Log::getSingleton().
                  getErrors();
                error = "[Terminate]" + error;

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

            // End of S-Function Block: <Root>/getJointLimits

            // Terminate for S-Function (BlockFactory): '<Root>/setPositionReference' 
            {
              // Get the CoderBlockInformation from the PWork
              blockfactory::coder::CoderBlockInformation* blockInfo = nullptr;
              blockInfo = static_cast<blockfactory::coder::CoderBlockInformation*>
                (JointSpace_Task_DW.setPositionReference_PWORK.blockPWork[1]);

              // Get the Block from the PWork
              blockfactory::core::Block* blockPtr = nullptr;
              blockPtr = static_cast<blockfactory::core::Block*>
                (JointSpace_Task_DW.setPositionReference_PWORK.blockPWork[0]);

              // Get the block factory
              auto factory = blockfactory::core::ClassFactorySingleton::
                getInstance().getClassFactory(
              {
                "setPositionReference", "XBotBlock_setPositionReference"
              } );

              if (!factory) {
                bfError << "Failed to get factory object (className=" <<
                  "XBotBlock_setPositionReference"
                  << ",libName=" << "setPositionReference" << ")";
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

              // Terminate the class
              // -------------------
              bool ok;
              ok = blockPtr->terminate(blockInfo);

              // Destroy the block
              factory->destroy(blockPtr);
              blockPtr = nullptr;

              // Decrease the counter of the factory
              factory->removeRef();
              if (factory->getReferenceCount() == 1) {
                // Delete the memory ownership of the shared pointer used in this function
                factory.reset();

                // Delete the factory object
                if (!blockfactory::core::ClassFactorySingleton::getInstance().
                    destroyFactory(
                                   {"setPositionReference",
                                   "XBotBlock_setPositionReference"})) {
                  bfError << "Failed to destroy the factory";

                  // Do not return since other actions need to be performed
                }
              }

              // Delete the BlockInformation object
              delete blockInfo;
              blockInfo = nullptr;

              // Report errors
              if (!ok) {
                std::string error = blockfactory::core::Log::getSingleton().
                  getErrors();
                error = "[Terminate]" + error;

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

            // End of S-Function Block: <Root>/setPositionReference
          }

          // Constructor
          modelModelClass::modelModelClass() : JointSpace_Task_M()
          {
            // Currently there is no constructor body generated.
          }

          // Destructor
          modelModelClass::~modelModelClass()
          {
            // Currently there is no destructor body generated.
          }

          // Real-Time Model get method
          RT_MODEL_JointSpace_Task_T * modelModelClass::getRTM()
          {
            return (&JointSpace_Task_M);
          }

          //
          // File trailer for generated code.
          //
          // [EOF]
          //
