////////////////////////////////////////////////////////////
//  Senior Design Generating Programmable Nanofibers Team //
//  Final Electropinning Device Code                      //
//  4/4/19                                                //
////////////////////////////////////////////////////////////

#include <Stepper.h>
#include <IRremote.h>

///////////   COMMANDS   ////////////
  #define CMD_DoNothing   'A'  // Do nothing
  #define CMD_MoveToTar   'm'  // Move to a target
  #define CMD_Moving      "M"  // PLACEHOLDER, IGNORE
  #define CMD_Pattern     'p'  // Print a listed pattern e.g. p star
  #define CMD_Patterning  "P"  // PLACEHOLDER, IGNORE
  #define CMD_ResetPos    'r'  // Reset position to [0, 0]
  #define CMD_SerialOff   's'  // Stop printing - will be much faster
  #define CMD_SerialOn    'S'  // Start printing - will delay significantly
  #define CMD_WriteWord   'w'  // Pattern name, e.g. n Bob]
  #define CMD_XSpeed      'x'  // Adjust X stepper speed / 100, e.g. x 80
  #define CMD_YSpeed      'y'  // Adjust Y stepper speed / 100, e.g. y 80

  #define CMD_StepXPos   'B'
  #define CMD_StepXNeg   'C'
  
/////////////   PINS   //////////////
 
  #define X1Pin1 22             
  #define X1Pin2 24
  #define X1Pin3 26
  #define X1Pin4 28

  #define X2Pin1 23             
  #define X2Pin2 25
  #define X2Pin3 27
  #define X2Pin4 29

  #define Y1Pin1 30
  #define Y1Pin2 32
  #define Y1Pin3 34
  #define Y1Pin4 36

  #define Y2Pin1 38
  #define Y2Pin2 40
  #define Y2Pin3 42
  #define Y2Pin4 44

  #define Y3Pin1 31
  #define Y3Pin2 33
  #define Y3Pin3 35
  #define Y3Pin4 37

  #define Y4Pin1 39
  #define Y4Pin2 41
  #define Y4Pin3 43
  #define Y4Pin4 45

  #define IRPin  12
  #define LEDPin 13

//////////   VARIABLES   ////////////

  // Patterns
    // OLD const int p_A_Len = 18; double p_A[p_A_Len][2] = {{0, 0}, {0, 5}, {5, 10}, {10, 5}, {10, 0}, {8, 0}, {8, 4}, {5, 4}, {5, 6}, {7, 6}, {5, 8}, {3, 6}, {5, 6}, {5, 4}, {2, 4}, {2, 0}, {0, 0}, {10, 0}};
    
    const int p_A_Len = 18; double p_A[p_A_Len][2] = {{0, 0}, {0, 7}, {3, 10}, {3, 8}, {2, 7}, {2, 6}, {4, 6}, {4, 7}, {3, 8}, {3, 10}, {6, 7}, {6, 0}, {4, 0}, {4, 4}, {2, 4}, {2, 0}, {0, 0}, {6, 0}};
    const int p_B_Len = 23; double p_B[p_B_Len][2] = {{0, 0}, {0, 10}, {3, 10}, {3, 8}, {2, 8}, {2, 6}, {3, 6}, {4, 7}, {3, 8}, {3, 10}, {6, 7}, {4, 5}, {6, 3}, {3, 0}, {3, 2}, {4, 3}, {3, 4}, {2, 4}, {2, 2}, {3, 2}, {3, 0}, {0, 0}, {6, 0}};
    const int p_C_Len = 16; double p_C[p_C_Len][2] = {{0, 0}, {2, 0}, {0, 2}, {0, 8}, {2, 10}, {6, 10}, {6, 8}, {3, 8}, {2, 7}, {2, 3}, {3, 2}, {6, 2}, {6, 0}, {2, 0}, {0, 0}, {6, 0}};
    const int p_D_Len = 15; double p_D[p_D_Len][2] = {{0, 0}, {0, 10}, {2, 10}, {2, 8}, {2, 2}, {4, 4}, {4, 6}, {2, 8}, {2, 10}, {3, 10}, {6, 7}, {6, 3}, {3, 0}, {0, 0}, {6, 0}};
    const int p_E_Len = 14; double p_E[p_E_Len][2] = {{0, 0}, {0, 10}, {6, 10}, {6, 8}, {2, 8}, {2, 6}, {6, 6}, {4, 6}, {2, 4}, {2, 2}, {6, 2}, {6, 0}, {0, 0}, {6, 0}};
    const int p_F_Len = 12; double p_F[p_F_Len][2] = {{0, 0}, {0, 10}, {6, 10}, {6, 8}, {2, 8}, {2, 6}, {5, 6}, {5, 4}, {2, 4}, {2, 0}, {0, 0}, {6, 0}};
    const int p_G_Len = 23; double p_G[p_G_Len][2] = {{0, 0}, {2, 0}, {0, 2}, {0, 8}, {2, 10}, {4, 10}, {6, 8}, {6, 7}, {4, 7}, {3, 8}, {2, 7}, {2, 3}, {3, 2}, {4, 2}, {4, 3}, {3, 3}, {3, 5}, {5, 5}, {6, 4}, {6, 2}, {4, 0}, {2, 0}, {6, 0}};
    const int p_H_Len = 14; double p_H[p_H_Len][2] = {{0, 0}, {0, 10}, {2, 10}, {2, 6}, {4, 6}, {4, 10}, {6, 10}, {6, 0}, {4, 0}, {4, 4}, {2, 4}, {2, 0}, {0, 0}, {6, 0}};
    const int p_I_Len = 14; double p_I[p_I_Len][2] = {{0, 0}, {0, 2}, {2, 2}, {2, 8}, {0, 8}, {0, 10}, {6, 10}, {6, 8}, {4, 8}, {4, 2}, {6, 2}, {6, 0}, {0, 0}, {6, 0}};
    const int p_J_Len = 14; double p_J[p_J_Len][2] = {{0, 0}, {2, 0}, {0, 2}, {0, 5}, {2, 5}, {2, 3}, {3, 2}, {4, 3}, {4, 10}, {6, 10}, {6, 2}, {4, 0}, {2, 0}, {6, 0}};
    const int p_K_Len = 13; double p_K[p_K_Len][2] = {{0, 0}, {0, 10}, {2, 10}, {2, 6}, {6, 10}, {6, 7}, {4, 5}, {6, 3}, {6, 0}, {2, 4}, {2, 0}, {0, 0}, {6, 0}};
    const int p_L_Len = 8; double p_L[p_L_Len][2] = {{0, 0}, {0, 10}, {2, 10}, {2, 2}, {6, 2}, {6, 0}, {0, 0}, {6, 0}};
    const int p_M_Len = 14; double p_M[p_M_Len][2] = {{0, 0}, {0, 10}, {1, 10}, {3, 8}, {5, 10}, {6, 10}, {6, 0}, {4, 0}, {4, 6}, {3, 5}, {2, 6}, {2, 0}, {0, 0}, {6, 0}};
    const int p_N_Len = 14; double p_N[p_N_Len][2] = {{0, 0}, {0, 10}, {2, 10}, {2, 8}, {4, 6}, {4, 10}, {6, 10}, {6, 0}, {4, 0}, {4, 2}, {2, 4}, {2, 0}, {0, 0}, {6, 0}};
    const int p_O_Len = 20; double p_O[p_O_Len][2] = {{0, 0}, {2, 0}, {0, 2}, {0, 8}, {2, 10}, {3, 10}, {3, 8}, {2, 7}, {2, 3}, {3, 2}, {4, 3}, {4, 7}, {3, 8}, {3, 10}, {4, 10}, {6, 8}, {6, 2}, {4, 0}, {2, 0}, {6, 0}};
    const int p_P_Len = 18; double p_P[p_P_Len][2] = {{0, 0}, {0, 10}, {3, 10}, {3, 8}, {2, 8}, {2, 6}, {3, 6}, {4, 7}, {3, 8}, {3, 10}, {4, 10}, {6, 8}, {6, 6}, {4, 4}, {2, 4}, {2, 0}, {0, 0}, {6, 0}};
    const int p_Q_Len = 25; double p_Q[p_Q_Len][2] = {{0, 0}, {5, 0}, {4, 1}, {2, 1}, {0, 3}, {0, 8}, {2, 10}, {3, 10}, {3, 8}, {2, 7}, {2, 4}, {3, 3}, {4, 4}, {4, 7}, {3, 8}, {3, 10}, {4, 10}, {6, 8}, {6, 3}, {5, 2}, {6, 1}, {5, 0}, {6, 0}};
    const int p_R_Len = 23; double p_R[p_R_Len][2] = {{0, 0}, {0, 10}, {3, 10}, {3, 8}, {2, 8}, {2, 6}, {3, 6}, {4, 7}, {3, 8}, {3, 10}, {4, 10}, {6, 8}, {6, 6}, {5, 4}, {6, 2}, {6, 0}, {4, 2}, {2, 4}, {2, 0}, {0, 0}, {6, 0}};
    const int p_S_Len = 14; double p_S[p_S_Len][2] = {{0, 0}, {0, 2}, {4, 2}, {4, 4}, {0, 4}, {0, 10}, {6, 10}, {6, 8}, {2, 8}, {2, 6}, {6, 6}, {6, 0}, {0, 0}, {6, 0}};
    const int p_T_Len = 11; double p_T[p_T_Len][2] = {{0, 0}, {2, 0}, {2, 8}, {0, 8}, {0, 10}, {6, 10}, {6, 8}, {4, 8}, {4, 0}, {2, 0}, {6, 0}};
    const int p_U_Len = 10; double p_U[p_U_Len][2] = {{0, 0}, {0, 10}, {2, 10}, {2, 2}, {4, 2}, {4, 10}, {6, 10}, {6, 0}, {0, 0}, {6, 0}};
    const int p_V_Len = 13; double p_V[p_V_Len][2] = {{0, 0}, {3, 0}, {0, 3}, {0, 10}, {2, 8}, {2, 4}, {3, 3}, {4, 4}, {4, 8}, {6, 10}, {6, 3}, {3, 0}, {6, 0}};
    const int p_W_Len = 15; double p_W[p_W_Len][2] = {{0, 0}, {2, 0}, {0, 2}, {0, 10}, {2, 10}, {2, 3}, {3, 4}, {4, 3}, {4, 10}, {6, 10}, {6, 2}, {4, 0}, {3, 1}, {2, 0}, {6, 0}};
    const int p_X_Len = 14; double p_X[p_X_Len][2] = {{0, 0}, {0, 3}, {2, 5}, {0, 7}, {0, 10}, {3, 7}, {6, 10}, {6, 7}, {4, 5}, {6, 3}, {6, 0}, {3, 3}, {0, 0}, {6, 0}};
    const int p_Y_Len = 12; double p_Y[p_Y_Len][2] = {{0, 0}, {2, 0}, {2, 5}, {0, 7}, {0, 10}, {3, 7}, {6, 10}, {6, 7}, {4, 5}, {4, 0}, {2, 0}, {6, 0}};
    const int p_Z_Len = 14; double p_Z[p_Z_Len][2] = {{0, 0}, {0, 3}, {4, 7}, {4, 8}, {0, 8}, {0, 10}, {6, 10}, {6, 7}, {2, 3}, {2, 2}, {6, 2}, {6, 0}, {0, 0}, {6, 0}};
    
    const int p_0_Len = 14; double p_0[p_0_Len][2] = {{0, 0}, {0, 10}, {3, 10}, {3, 8}, {2, 8}, {2, 2}, {4, 2}, {4, 8}, {3, 8}, {3, 10}, {6, 10}, {6, 0}, {0, 0}, {6, 0}};
    const int p_1_Len = 11; double p_1[p_1_Len][2] = {{0, 0}, {0, 2}, {2, 2}, {2, 6}, {0, 6}, {4, 10}, {4, 2}, {6, 2}, {6, 0}, {0, 0}, {6, 0}};
    const int p_2_Len = 17; double p_2[p_2_Len][2] = {{0, 0}, {0, 2}, {4, 6}, {4, 8}, {2, 8}, {2, 6}, {0, 6}, {0, 8}, {3, 10}, {4, 10}, {6, 8}, {6, 6}, {2, 2}, {6, 2}, {6, 0}, {0, 0}, {0, 6}};
    const int p_3_Len = 14; double p_3[p_3_Len][2] = {{0, 0}, {0, 2}, {4, 2}, {4, 4}, {2, 4}, {2, 6}, {4, 6}, {4, 8}, {0, 8}, {0, 10}, {6, 10}, {6, 0}, {0, 0}, {6, 0}};
    const int p_4_Len = 13; double p_4[p_4_Len][2] = {{0, 0}, {4, 0}, {4, 4}, {0, 4}, {0, 10}, {2, 10}, {2, 6}, {4, 6}, {4, 10}, {6, 10}, {6, 0}, {4, 0}, {6, 0}};
    const int p_5_Len = 22; double p_5[p_5_Len][2] = {{0, 0}, {2, 0}, {0, 2}, {0, 4}, {2, 4}, {2, 3}, {3, 2}, {4, 3}, {4, 4}, {3, 5}, {0, 5}, {0, 10}, {6, 10}, {6, 8}, {2, 8}, {2, 7}, {4, 7}, {6, 5}, {6, 2}, {4, 0}, {2, 0}, {6, 0}};
    const int p_6_Len = 25; double p_6[p_6_Len][2] = {{0, 0}, {2, 0}, {0, 2}, {0, 8}, {2, 10}, {4, 10}, {6, 8}, {6, 7}, {4, 7}, {3, 8}, {2, 7}, {2, 6}, {4, 6}, {6, 4}, {6, 2}, {4, 0}, {3, 0}, {3, 2}, {4, 3}, {3, 4}, {2, 3}, {3, 2}, {3, 0}, {2, 0}, {6, 0}};
    const int p_7_Len = 11; double p_7[p_7_Len][2] = {{0, 0}, {0, 4}, {4, 8}, {0, 8}, {0, 10}, {6, 10}, {6, 7}, {2, 3}, {2, 0}, {0, 0}, {6, 0}};
    const int p_8_Len = 31; double p_8[p_8_Len][2] = {{0, 0}, {2, 0}, {0, 2}, {0, 4}, {1, 5}, {0, 6}, {0, 8}, {2, 10}, {3, 10}, {3, 8}, {2, 7}, {3, 6}, {4, 7}, {3, 8}, {3, 10}, {4, 10}, {6, 8}, {6, 6}, {5, 5}, {6, 4}, {6, 2}, {4, 0}, {3, 0}, {3, 2}, {4, 3}, {3, 4}, {2, 3}, {3, 2}, {3, 0}, {2, 0}, {6, 0}};
    const int p_9_Len = 19; double p_9[p_9_Len][2] = {{0, 0}, {4, 0}, {4, 4}, {2, 4}, {0, 6}, {0, 8}, {2, 10}, {4, 10}, {4, 8}, {2, 7}, {3, 6}, {4, 7}, {4, 8}, {3, 10}, {4, 10}, {6, 8}, {6, 0}, {4, 0}, {6, 0}};

    const int p_home_Len = 1; double p_home[p_home_Len][2] = {{0,0}};
    //const int p_Square_Len  =  6; int p_Square [p_Square_Len] [2] = {{10, 0}, {20, 0}, {20, -10}, {10, -10}, {10, 0}, {0, 0}}; 
    //const int p_Diamond_Len = 10; int p_Diamond[p_Diamond_Len][2] = {{0, -5}, {10, -5}, {15, 0}, {20, -5}, {15, -10}, {10, -5}, {0, -5}, {0, 0}};

    int patternPos = 0;
    String patternID = "";
    bool patternComplete = 1, targetReached = 0;

  // Writing Words
    double fontSize = 8;
    double fontSpacing = 2;
    
    int wordPos = 0, wordLength = 0, newLinePos = 0, initialXOffset = 0, initialYOffset = 0;
    String WORD = ""; 
    bool wordComplete = 1;

  // STEPPER
    #define stepsPerRev      2038.0   // (use 2048.0 for better divisibility)
    #define pulleyDiam       10.0     // Pulley diameter, mm

    Stepper X1(stepsPerRev, X1Pin1, X1Pin2, X1Pin3, X1Pin4);
    //Stepper X2(stepsPerRev, X2Pin1, X2Pin2, X2Pin3, X2Pin4);
    Stepper Y1(stepsPerRev, Y1Pin1, Y1Pin2, Y1Pin3, Y1Pin4);
    Stepper Y2(stepsPerRev, Y2Pin1, Y2Pin2, Y2Pin3, Y2Pin4);
    //Stepper Y3(stepsPerRev, Y3Pin1, Y3Pin2, Y3Pin3, Y3Pin4);
    //Stepper Y4(stepsPerRev, Y4Pin1, Y4Pin2, Y4Pin3, Y4Pin4);

    int XStepCount = 0, YStepCount = 0, XOffset = 0, YOffset = 0, XStepTarget = 0, YStepTarget = 0, stepDistX = 0, stepDistY = 0;
    double XRev = 0, YRev = 0, XPos = 0, YPos = 0, distX = 0, distY = 0;
    String XTargetString = "", YTargetString = "";
    double XTarget = 0, YTarget = 0;

    int defStep = 1; // Default step size
    int XSpeed = 3; String XSpeedString = " ";
    int YSpeed = 3; String YSpeedString = " ";
    int firstSpace = 0, lastSpace = 0;

  // IR Reciever
    IRrecv IRReciever(IRPin);
    decode_results results;
    double tOldIR = 0;
    double IRDelay = 250; // time between IR readings, ms
    String IRValue = "None"; String LastIRValue = "None";
    bool IRHeld = 0;
 
  // OTHER
    String message = "Tell me what to do!";   // Message to computer
    String command = "A";        // Command from Uno
    String oldCommand = command; // Previous Command
    String strEnd  = " ";        // Placeholder for end of string in longer commands
    bool SerialOn = true;        // Activates serial monitor
    double t = 0;

///////////////  SETUP  /////////////////

void setup() {

  // INITIATE PINS
    pinMode(LEDPin, OUTPUT);

  // INITIATE SERIAL PORTS
    Serial.begin(9600);       // COMPUTER
    Serial.println(message);  // STARTING MESSAGE
    Serial.setTimeout(50);

  // INITIATE IR REMOTE CONTROL RECIEVER
    IRReciever.enableIRIn();

    X1.setSpeed(XSpeed);
    //X2.setSpeed(XSpeed);
    Y1.setSpeed(YSpeed);
    Y2.setSpeed(YSpeed);
    //Y3.setSpeed(YSpeed);
    //Y4.setSpeed(YSpeed);
}

////////////////  LOOP  /////////////////

void loop(){

    t = millis();

    if (Serial.available())
      command = Serial.readString();
      
    GetIR();
    GetPos();

    // Change Motor Power
    if (IRValue == "left"){
        XStep(-defStep);
        message = "Moving left (-x)";
        command = CMD_DoNothing;
    }
    else if (IRValue == "right"){
        XStep(defStep);
        command = CMD_DoNothing;
    }
    else if (IRValue == "up"){
        YStep(defStep);
        message = "Moving up (+y)";
        command = CMD_DoNothing;
    }
    else if (IRValue == "down"){
        YStep(-defStep);
        message = "Moving down (-y)";
        command = CMD_DoNothing;
    }
    
    else if (IRValue == "1"){patternID = "1"; command = CMD_Pattern;}
    else if (IRValue == "2"){patternID = "2"; command = CMD_Pattern;}
    else if (IRValue == "3"){patternID = "3"; command = CMD_Pattern;}
    else if (IRValue == "4"){patternID = "4"; command = CMD_Pattern;}
    else if (IRValue == "5"){patternID = "5"; command = CMD_Pattern;}
    else if (IRValue == "6"){patternID = "6"; command = CMD_Pattern;}
    
    else if (IRValue == "#" || command.charAt(0) == CMD_ResetPos){
        XOffset = XStepCount;
        YOffset = YStepCount;
        command = CMD_DoNothing;
    }
    else if (command.charAt(0) == CMD_XSpeed) {
        XSpeedString = command.substring(1);
        XSpeed = XSpeedString.toInt();
        message = "Updated X Speed";
    }
    
    else if (command.charAt(0) == CMD_YSpeed) {
        YSpeedString = command.substring(1);
        YSpeed = YSpeedString.toInt();
        message = "Updated Y Speed";
    }
    else if (command.charAt(0) == CMD_StepXPos){
      XStep(1);
      message = "Turning Clockwise";
    }
    else if (command.charAt(0) == CMD_StepXNeg){
      XStep(-1);
      message = "Turning Counterclockwise";
    }
    else if (command.charAt(0) == CMD_MoveToTar) {
        firstSpace = command.indexOf(' ');
        lastSpace  = command.lastIndexOf(' ');

        XTargetString = command.substring(firstSpace + 1, lastSpace);
        YTargetString = command.substring(lastSpace  + 1);

        XTarget = XTargetString.toDouble();
        YTarget = YTargetString.toDouble();

        XStepTarget = (int)round(XTarget*stepsPerRev/(PI*pulleyDiam));
        YStepTarget = (int)round(YTarget*stepsPerRev/(PI*pulleyDiam));

        command = CMD_Moving;
    }
    else if (command == CMD_Moving){
        MoveToTarget();
        message = "Moving to Target";
    }
    else if (command.charAt(0) == CMD_Pattern){
        patternComplete = 0;
        patternPos = 0;
        command = CMD_Patterning;
    }
    else if (command == CMD_Patterning){
        SelectPattern();
    }
    else {
      Stop();
      message = "Stopped";
    }

  // Write a word

    WriteWord();
    if (command.charAt(0) != CMD_Pattern && command != CMD_Patterning && command.charAt(0) != CMD_WriteWord){
        WORD = "";
        wordComplete = 1;
    }


  // SERIAL MONITOR
  
    // This code simply allows the serial monitor to be turned off or on, without effecting anything else
    // Turning it off will speed up loop iteration significantly
  
    if (command.charAt(0) == CMD_SerialOn || command.charAt(0) == CMD_SerialOff){
      SerialOn = (command.charAt(0) == CMD_SerialOn);
      command = oldCommand;
    }
    
    if (SerialOn)
      SerialPrint();
  
    oldCommand = command; // Update old command

} 
