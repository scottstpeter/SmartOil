/*
 Oil Well Prototype Firmware
 Developed by Malik Enterprise
 Copyright © 2012 Malik Enterprise. All rights reserved.
 */

// include necessary to convert float to string
#include <stdlib.h>


//--------------------------------------------------------------------------------------
// VARIABLES FOR DATA HANDLING
//--------------------------------------------------------------------------------------

// declare sensor pins for analog read
const int dpflowrate_pin = 1;
//For comparison, holds value of last received analog read
int prev_voltage = 0;

//--------------------------------------------------------------------------------------
// SETUP
//--------------------------------------------------------------------------------------
void setup()
{  

  Serial.begin(9600);
  
}

//--------------------------------------------------------------------------------------
// MAIN LOOP
//--------------------------------------------------------------------------------------
void loop()
{
  
  if(Serial.available()) {  //check if the python software has any commands to issue to the arduino

  }
  else {  // otherwise continue to collect data from sensors

    
    int dpflowrate_in = analogRead(dpflowrate_pin); // take voltage reading from sensor via arduino analog pin
    
    if ((dpflowrate_in != prev_voltage) && (dpflowrate_in+1 != prev_voltage) && (dpflowrate_in-1 != prev_voltage) ) // new voltage is different from previous
    { 
      
      prev_voltage = dpflowrate_in; // set the value of prev_volate equal to the new voltage
      
      float dpflowrate = calculate_dp(dpflowrate_in); // convert arduino analog in to a DP value
      
      // convert the value into a string
      char s[32];
      String dataString = dtostrf(dpflowrate, 2, 4, s); 
      
      Serial.println ("The pressure is: " + dataString);    
      
      delay(1000);  // THIS VALUE WILL BE CHANGED TO GET MAX DATA POINTS WITHOUT FAILURE
    }
    else {  // no change in flow rate, unecessary to pass the data on

      Serial.println("false");
      delay(1000);

    }

  }

}


//--------------------------------------------------------------------------------------
// Calculates Differential Pressure from Arduino Analog Read
// **see derivation documents for origin of the used equation
//--------------------------------------------------------------------------------------
float calculate_dp(int x) {
  float result = (((.4344520474)*x)-80.0);
  return result; 
}

