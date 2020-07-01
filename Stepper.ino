// THIS FUNCTION MOVES THE XY STAGE TO A SPECIFIC TARGET
  void MoveToTarget(){
    
    stepDistX = XStepTarget - (XStepCount - XOffset);
    stepDistY = YStepTarget - (YStepCount - YOffset);
  
    distX = XTarget - XPos;
    distY = YTarget - YPos;
        
    if(stepDistX > 0) {
      XStep(defStep);
    }
    else if(stepDistX < 0) {
      XStep(-defStep);
    }

    if(stepDistY > 0) {
      YStep(defStep);
    }
    else if(stepDistY < 0) {
      YStep(-defStep);
    }

    if (stepDistX == 0 && stepDistY == 0){
      targetReached = 1;
    }
    else {           
      targetReached = 0;
    }
  }

// THIS FUNCTION UPDATES MOTOR POSITIONS, CONVERTED TO REVOLUTIONS
  void GetPos(){
    
    XRev = (XStepCount - XOffset)/stepsPerRev;
    YRev = (YStepCount - YOffset)/stepsPerRev;

    XPos = XRev*PI*pulleyDiam;
    YPos = YRev*PI*pulleyDiam;

  }
  void XStep(int numSteps){
    X1.step(numSteps);       // Accounts for mounting of stepper motor vs. desired positive x direction
    //X2.step(numSteps);
    XStepCount += numSteps;
  }
  void YStep(int numSteps){
    Y1.step(numSteps);
    Y2.step(numSteps);
    //Y3.step(-numSteps);
    //Y4.step(-numSteps);
    YStepCount += numSteps;
  }
  void Stop(){
    XStep(0);
    YStep(0);
  }
 
