void GetIR(){

  if(t - tOldIR > IRDelay){ // CHECKS FOR IR WITH A DELAY BETWEEN CHECKS
    
    if (IRReciever.decode(&results)){ // IF THERE ARE IR RESULTS
      
        IRReciever.resume(); // CONTINUE LOOKING FOR IR SIGNAL
  
        if(results.value == 0xFFFFFFFF) { // IF THERE IS A BUTTON HELD DOWN
           IRHeld = 1;
        }    
        else {  // CONVERT EACH IR HEX READING TO CORRESPONDING BUTTON VALUE
           switch (results.value) {
              case 0xFF9867:
                  IRValue = "0"; break;
              case 0xFFA25D:
                  IRValue = "1"; break;
              case 0xFF629D:
                  IRValue = "2"; break;
              case 0xFFE21D:
                  IRValue = "3"; break;
              case 0xFF22DD:
                  IRValue = "4"; break;
              case 0xFF02FD:
                  IRValue = "5"; break;
              case 0xFFC23D:
                  IRValue = "6"; break;
              case 0xFFE01F:
                  IRValue = "7"; break;
              case 0xFFA857:
                  IRValue = "8"; break;
              case 0xFF906F:
                  IRValue = "9"; break;
              case 0xFF6897:
                  IRValue = "*"; break;
              case 0xFFB04F:
                  IRValue = "#"; break;
              case 0xFF18E7:
                  IRValue = "up"; break;
              case 0xFF4AB5:
                  IRValue = "down"; break;
              case 0xFF10EF:
                  IRValue = "left"; break;
              case 0xFF5AA5:
                  IRValue = "right"; break;
              case 0xFF38C7:
                  IRValue = "ok"; break;
              default:
                  break;
           }
           IRHeld = 0;
           LastIRValue = IRValue;
        }
    }
    else {
      IRHeld = 0;
      IRValue = "None"; // NOTHING HELD DOWN
    }
  
     tOldIR = t; 
  }

}
