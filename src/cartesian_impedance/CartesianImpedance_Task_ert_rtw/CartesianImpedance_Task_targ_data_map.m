  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 2;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (CartesianImpedance_Task_P)
    ;%
      section.nData     = 20;
      section.data(20)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_P.Gain3_Gain
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% CartesianImpedance_Task_P.Gain5_Gain
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% CartesianImpedance_Task_P.Constant5_Value
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 7;
	
	  ;% CartesianImpedance_Task_P.Constant1_Value
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 8;
	
	  ;% CartesianImpedance_Task_P.Constant2_Value
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 9;
	
	  ;% CartesianImpedance_Task_P.Constant3_Value
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 10;
	
	  ;% CartesianImpedance_Task_P.Constant6_Value
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 11;
	
	  ;% CartesianImpedance_Task_P.Constant7_Value
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 12;
	
	  ;% CartesianImpedance_Task_P.Constant8_Value
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 13;
	
	  ;% CartesianImpedance_Task_P.Constant10_Value
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 19;
	
	  ;% CartesianImpedance_Task_P.Constant_Value
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 20;
	
	  ;% CartesianImpedance_Task_P.Constant9_Value
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 21;
	
	  ;% CartesianImpedance_Task_P.Constant4_Value
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 22;
	
	  ;% CartesianImpedance_Task_P.Gain_Gain
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 25;
	
	  ;% CartesianImpedance_Task_P.Gain6_Gain
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 26;
	
	  ;% CartesianImpedance_Task_P.DiscreteTimeIntegrator_gainval
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 32;
	
	  ;% CartesianImpedance_Task_P.DiscreteTimeIntegrator_IC
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 33;
	
	  ;% CartesianImpedance_Task_P.Gain_Gain_n
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 34;
	
	  ;% CartesianImpedance_Task_P.Gain1_Gain
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 35;
	
	  ;% CartesianImpedance_Task_P.Constant4_Value_g
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 36;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_P.ManualSwitch_CurrentSetting
	  section.data(1).logicalSrcIdx = 20;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 5;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (CartesianImpedance_Task_B)
    ;%
      section.nData     = 2;
      section.data(2)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_B.getJacobian_o1
	  section.data(1).logicalSrcIdx = 1;
	  section.data(1).dtTransOffset = 0;
	
	  ;% CartesianImpedance_Task_B.MultiportSwitch
	  section.data(2).logicalSrcIdx = 5;
	  section.data(2).dtTransOffset = 30;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_B.MatrixConcatenate
	  section.data(1).logicalSrcIdx = 6;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
      section.nData     = 31;
      section.data(31)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_B.getJointPosition
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% CartesianImpedance_Task_B.getJacobian_o2
	  section.data(2).logicalSrcIdx = 2;
	  section.data(2).dtTransOffset = 5;
	
	  ;% CartesianImpedance_Task_B.getInertiaInverse
	  section.data(3).logicalSrcIdx = 3;
	  section.data(3).dtTransOffset = 8;
	
	  ;% CartesianImpedance_Task_B.ProductofElements1
	  section.data(4).logicalSrcIdx = 4;
	  section.data(4).dtTransOffset = 33;
	
	  ;% CartesianImpedance_Task_B.Selector
	  section.data(5).logicalSrcIdx = 7;
	  section.data(5).dtTransOffset = 69;
	
	  ;% CartesianImpedance_Task_B.MatrixConcatenate_n
	  section.data(6).logicalSrcIdx = 8;
	  section.data(6).dtTransOffset = 72;
	
	  ;% CartesianImpedance_Task_B.Selector1
	  section.data(7).logicalSrcIdx = 9;
	  section.data(7).dtTransOffset = 88;
	
	  ;% CartesianImpedance_Task_B.Sum
	  section.data(8).logicalSrcIdx = 10;
	  section.data(8).dtTransOffset = 91;
	
	  ;% CartesianImpedance_Task_B.Gain
	  section.data(9).logicalSrcIdx = 11;
	  section.data(9).dtTransOffset = 94;
	
	  ;% CartesianImpedance_Task_B.getJointVelocity
	  section.data(10).logicalSrcIdx = 12;
	  section.data(10).dtTransOffset = 97;
	
	  ;% CartesianImpedance_Task_B.computeGravityCompensation
	  section.data(11).logicalSrcIdx = 13;
	  section.data(11).dtTransOffset = 102;
	
	  ;% CartesianImpedance_Task_B.Gain6
	  section.data(12).logicalSrcIdx = 14;
	  section.data(12).dtTransOffset = 107;
	
	  ;% CartesianImpedance_Task_B.ManualSwitch
	  section.data(13).logicalSrcIdx = 15;
	  section.data(13).dtTransOffset = 113;
	
	  ;% CartesianImpedance_Task_B.getInertiaMatrix
	  section.data(14).logicalSrcIdx = 16;
	  section.data(14).dtTransOffset = 118;
	
	  ;% CartesianImpedance_Task_B.getStiffness
	  section.data(15).logicalSrcIdx = 17;
	  section.data(15).dtTransOffset = 143;
	
	  ;% CartesianImpedance_Task_B.Gain_g
	  section.data(16).logicalSrcIdx = 18;
	  section.data(16).dtTransOffset = 148;
	
	  ;% CartesianImpedance_Task_B.getDamping
	  section.data(17).logicalSrcIdx = 19;
	  section.data(17).dtTransOffset = 153;
	
	  ;% CartesianImpedance_Task_B.Gain1
	  section.data(18).logicalSrcIdx = 20;
	  section.data(18).dtTransOffset = 158;
	
	  ;% CartesianImpedance_Task_B.Selector2
	  section.data(19).logicalSrcIdx = 21;
	  section.data(19).dtTransOffset = 163;
	
	  ;% CartesianImpedance_Task_B.Selector_p
	  section.data(20).logicalSrcIdx = 22;
	  section.data(20).dtTransOffset = 166;
	
	  ;% CartesianImpedance_Task_B.Selector1_f
	  section.data(21).logicalSrcIdx = 23;
	  section.data(21).dtTransOffset = 169;
	
	  ;% CartesianImpedance_Task_B.L
	  section.data(22).logicalSrcIdx = 24;
	  section.data(22).dtTransOffset = 172;
	
	  ;% CartesianImpedance_Task_B.s
	  section.data(23).logicalSrcIdx = 25;
	  section.data(23).dtTransOffset = 208;
	
	  ;% CartesianImpedance_Task_B.L_sat
	  section.data(24).logicalSrcIdx = 26;
	  section.data(24).dtTransOffset = 214;
	
	  ;% CartesianImpedance_Task_B.s_sat
	  section.data(25).logicalSrcIdx = 27;
	  section.data(25).dtTransOffset = 250;
	
	  ;% CartesianImpedance_Task_B.L_p
	  section.data(26).logicalSrcIdx = 28;
	  section.data(26).dtTransOffset = 256;
	
	  ;% CartesianImpedance_Task_B.y
	  section.data(27).logicalSrcIdx = 29;
	  section.data(27).dtTransOffset = 292;
	
	  ;% CartesianImpedance_Task_B.error
	  section.data(28).logicalSrcIdx = 30;
	  section.data(28).dtTransOffset = 317;
	
	  ;% CartesianImpedance_Task_B.D
	  section.data(29).logicalSrcIdx = 31;
	  section.data(29).dtTransOffset = 320;
	
	  ;% CartesianImpedance_Task_B.D_l
	  section.data(30).logicalSrcIdx = 32;
	  section.data(30).dtTransOffset = 356;
	
	  ;% CartesianImpedance_Task_B.D_e
	  section.data(31).logicalSrcIdx = 33;
	  section.data(31).dtTransOffset = 392;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_B.CoordinateTransformationConv_pn.CoordinateTransformationConve_b
	  section.data(1).logicalSrcIdx = 34;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_B.CoordinateTransformationConve_p.CoordinateTransformationConve_b
	  section.data(1).logicalSrcIdx = 35;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(5) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 6;
    sectIdxOffset = 5;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (CartesianImpedance_Task_DW)
    ;%
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_DW.DiscreteTimeIntegrator_DSTATE
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 17;
      section.data(17)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_DW.getJointPosition_PWORK.blockPWork
	  section.data(1).logicalSrcIdx = 1;
	  section.data(1).dtTransOffset = 0;
	
	  ;% CartesianImpedance_Task_DW.setPositionReference1_PWORK.blockPWork
	  section.data(2).logicalSrcIdx = 2;
	  section.data(2).dtTransOffset = 2;
	
	  ;% CartesianImpedance_Task_DW.getPoseFun_PWORK.blockPWork
	  section.data(3).logicalSrcIdx = 3;
	  section.data(3).dtTransOffset = 4;
	
	  ;% CartesianImpedance_Task_DW.getPoseFun_PWORK_n.blockPWork
	  section.data(4).logicalSrcIdx = 4;
	  section.data(4).dtTransOffset = 6;
	
	  ;% CartesianImpedance_Task_DW.getJacobian_PWORK.blockPWork
	  section.data(5).logicalSrcIdx = 5;
	  section.data(5).dtTransOffset = 8;
	
	  ;% CartesianImpedance_Task_DW.getInertiaInverse_PWORK.blockPWork
	  section.data(6).logicalSrcIdx = 6;
	  section.data(6).dtTransOffset = 10;
	
	  ;% CartesianImpedance_Task_DW.Scope3_PWORK.LoggedData
	  section.data(7).logicalSrcIdx = 7;
	  section.data(7).dtTransOffset = 12;
	
	  ;% CartesianImpedance_Task_DW.getJointVelocity_PWORK.blockPWork
	  section.data(8).logicalSrcIdx = 8;
	  section.data(8).dtTransOffset = 15;
	
	  ;% CartesianImpedance_Task_DW.computeGravityCompensation_PWOR.blockPWork
	  section.data(9).logicalSrcIdx = 9;
	  section.data(9).dtTransOffset = 17;
	
	  ;% CartesianImpedance_Task_DW.setEffortReference_PWORK.blockPWork
	  section.data(10).logicalSrcIdx = 10;
	  section.data(10).dtTransOffset = 19;
	
	  ;% CartesianImpedance_Task_DW.getInertiaMatrix_PWORK.blockPWork
	  section.data(11).logicalSrcIdx = 11;
	  section.data(11).dtTransOffset = 21;
	
	  ;% CartesianImpedance_Task_DW.Scope4_PWORK.LoggedData
	  section.data(12).logicalSrcIdx = 12;
	  section.data(12).dtTransOffset = 23;
	
	  ;% CartesianImpedance_Task_DW.getStiffness_PWORK.blockPWork
	  section.data(13).logicalSrcIdx = 13;
	  section.data(13).dtTransOffset = 24;
	
	  ;% CartesianImpedance_Task_DW.setStiffness1_PWORK.blockPWork
	  section.data(14).logicalSrcIdx = 14;
	  section.data(14).dtTransOffset = 26;
	
	  ;% CartesianImpedance_Task_DW.getDamping_PWORK.blockPWork
	  section.data(15).logicalSrcIdx = 15;
	  section.data(15).dtTransOffset = 28;
	
	  ;% CartesianImpedance_Task_DW.setDamping_PWORK.blockPWork
	  section.data(16).logicalSrcIdx = 16;
	  section.data(16).dtTransOffset = 30;
	
	  ;% CartesianImpedance_Task_DW.Scope1_PWORK.LoggedData
	  section.data(17).logicalSrcIdx = 17;
	  section.data(17).dtTransOffset = 32;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_DW.CoordinateTransformationConv_pn.obj
	  section.data(1).logicalSrcIdx = 18;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_DW.CoordinateTransformationConv_pn.objisempty
	  section.data(1).logicalSrcIdx = 19;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_DW.CoordinateTransformationConve_p.obj
	  section.data(1).logicalSrcIdx = 20;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% CartesianImpedance_Task_DW.CoordinateTransformationConve_p.objisempty
	  section.data(1).logicalSrcIdx = 21;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(6) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 2519130242;
  targMap.checksum1 = 556040234;
  targMap.checksum2 = 2075234160;
  targMap.checksum3 = 2592979769;

