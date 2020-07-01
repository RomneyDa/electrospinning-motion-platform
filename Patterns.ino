
  void PrintPattern(double pattern[][2], int patternLength){
      if(!patternComplete){
          message = "Patterning";
          
          XTarget = pattern[patternPos][0]*fontSize/10.0;
          YTarget = pattern[patternPos][1]*fontSize/10.0;

          XStepTarget = int(round(XTarget*stepsPerRev/(PI*pulleyDiam)));
          YStepTarget = int(round(YTarget*stepsPerRev/(PI*pulleyDiam)));
          
          MoveToTarget();
          
          if(targetReached){
              if(patternPos == patternLength - 1){       
                  patternComplete = 1;
                  patternPos = 0;
                  message = "Pattern Complete";
                  command = CMD_DoNothing;
              }
              else {
                  patternPos++;
                  targetReached = 0;
              }
          }
      }
  }

  void WriteWord(){
      
      if(wordComplete && command.charAt(0) == CMD_WriteWord){
        
          firstSpace = command.indexOf(' ');
          newLinePos = command.indexOf('\n');
          WORD = command.substring(firstSpace + 1, newLinePos);
          wordLength = WORD.length();

          XOffset = XStepCount;
          YOffset = YStepCount;

          initialXOffset = XOffset;
          initialYOffset = YOffset;
          
          SerialOn = 0;
          wordComplete = 0;
          command = CMD_Pattern;
      }
      else if (!wordComplete) {

          if(patternComplete){
              if(wordPos == wordLength - 1){       
                  wordComplete = 1;
                  wordPos = 0;
                  message = "Word Complete";
                  
                  SerialOn = 1;

                  XOffset = initialXOffset;
                  YOffset = initialYOffset;

                  //patternID = "home";
                  //command = CMD_Pattern;
              }
              else {
                  wordPos++;
                  patternComplete = 0;
                  command = CMD_Pattern;

                  XOffset = XStepCount;
                  YOffset = YStepCount;
              }
          }
          patternID = WORD.substring(wordPos, wordPos + 1);
      }
  }

  void SelectPattern (){

             if (patternID == "home")   {PrintPattern(p_home, p_home_Len);}
      //else if (patternID == "square") {PrintPattern(p_Square, p_Square_Len);}
      //else if (patternID == "diamond"){PrintPattern(p_Diamond, p_Diamond_Len);}
      
        else if (patternID == "A" || patternID == "a"){PrintPattern(p_A, p_A_Len);}
      //else if (patternID == "B" || patternID == "b"){PrintPattern(p_B, p_B_Len);}
      //else if (patternID == "C" || patternID == "c"){PrintPattern(p_C, p_C_Len);}
      //else if (patternID == "D" || patternID == "d"){PrintPattern(p_D, p_D_Len);}
      //else if (patternID == "E" || patternID == "e"){PrintPattern(p_E, p_E_Len);}
      //else if (patternID == "F" || patternID == "f"){PrintPattern(p_F, p_F_Len);}
      //else if (patternID == "G" || patternID == "g"){PrintPattern(p_G, p_G_Len);}
      //else if (patternID == "H" || patternID == "h"){PrintPattern(p_H, p_H_Len);}
      //else if (patternID == "I" || patternID == "i"){PrintPattern(p_I, p_I_Len);}
      //else if (patternID == "J" || patternID == "j"){PrintPattern(p_J, p_J_Len);}
      //else if (patternID == "K" || patternID == "k"){PrintPattern(p_K, p_K_Len);}
      //else if (patternID == "L" || patternID == "l"){PrintPattern(p_L, p_L_Len);}
      //else if (patternID == "M" || patternID == "m"){PrintPattern(p_M, p_M_Len);}
      //else if (patternID == "N" || patternID == "n"){PrintPattern(p_N, p_N_Len);}
      //else if (patternID == "O" || patternID == "o"){PrintPattern(p_O, p_O_Len);}
      //else if (patternID == "P" || patternID == "p"){PrintPattern(p_P, p_P_Len);}
      //else if (patternID == "Q" || patternID == "q"){PrintPattern(p_Q, p_Q_Len);}
      //else if (patternID == "R" || patternID == "r"){PrintPattern(p_R, p_R_Len);}
      //else if (patternID == "S" || patternID == "s"){PrintPattern(p_S, p_S_Len);}
      //else if (patternID == "T" || patternID == "t"){PrintPattern(p_T, p_T_Len);}
      //else if (patternID == "U" || patternID == "u"){PrintPattern(p_U, p_U_Len);}
      //else if (patternID == "V" || patternID == "v"){PrintPattern(p_V, p_V_Len);}
      //else if (patternID == "W" || patternID == "w"){PrintPattern(p_W, p_W_Len);}
      //else if (patternID == "X" || patternID == "x"){PrintPattern(p_X, p_X_Len);}
      //else if (patternID == "Y" || patternID == "y"){PrintPattern(p_Y, p_Y_Len);}
      //else if (patternID == "Z" || patternID == "z"){PrintPattern(p_Z, p_Z_Len);}
      //else if (patternID == "0"){PrintPattern(p_0, p_0_Len);}
      //else if (patternID == "1"){PrintPattern(p_1, p_1_Len);}
      //else if (patternID == "2"){PrintPattern(p_2, p_2_Len);}
      //else if (patternID == "3"){PrintPattern(p_3, p_3_Len);}
      //else if (patternID == "4"){PrintPattern(p_4, p_4_Len);}
      //else if (patternID == "5"){PrintPattern(p_5, p_5_Len);}
      //else if (patternID == "6"){PrintPattern(p_6, p_6_Len);}
      //else if (patternID == "7"){PrintPattern(p_7, p_7_Len);}
      //else if (patternID == "8"){PrintPattern(p_8, p_8_Len);}
      //else if (patternID == "9"){PrintPattern(p_9, p_9_Len);}
      
  }
