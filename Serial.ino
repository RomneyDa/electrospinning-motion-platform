
  void SerialPrint(){

    Serial.print("[CMD = ");
    Serial.print(command.charAt(0));

    Serial.print("]  ");
    Serial.print(message);

     // IR

      //Serial.print("\t IR Status: ");
      //Serial.print(IRHeld);
    if(IRValue != "None"){
      Serial.print("\t IR Value: ");
      Serial.print(IRValue);

      Serial.print("\t Last IR Value: ");
      Serial.print(LastIRValue);
    }
    // Powers
    //  Serial.print("\tPwr: X = ");
    //  Serial.print(XSpeed);
    //  Serial.print(",\tY = ");
    //  Serial.print(YSpeed);

   // Position
      Serial.print("\tXsc: ");
      Serial.print(XStepCount);
      Serial.print("\tXRev: ");
      Serial.print(XRev);
      
      Serial.print("\tPos [X, Y]: [");
      Serial.print(XPos);
      Serial.print(", ");
      Serial.print(YPos);
      Serial.print("]");

   // Pattern
      Serial.print("  PatternID: ");
      Serial.print(patternID);
      Serial.print("\tWord: ");
      Serial.print(WORD);
      
    if (command == CMD_Moving || command == CMD_Patterning) {
      Serial.print("\tTarget [X, Y]: [");
      Serial.print(XTarget);
      Serial.print(", ");
      Serial.print(YTarget);
      Serial.print("]\t");

      Serial.print("\t (step): [");
      Serial.print(XStepTarget);
      Serial.print(", ");
      Serial.print(YStepTarget);
      Serial.print("]");

      Serial.print("  SDX: ");
      Serial.print(stepDistX);
      Serial.print("  SDY: ");
      Serial.print(stepDistY);
      //Serial.print("\tOFFSET: ");
      //Serial.print(XOffset);

    }
  
    Serial.println();

    
    
  }
