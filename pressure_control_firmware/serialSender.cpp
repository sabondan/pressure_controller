#include <stdlib.h>
#include "Arduino.h"


//_________________________________________________________



String commSender::getCommand() {
  //unsigned long start_time = micros();
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // Add new byte to the inputString:
    command += inChar;
    // If the incoming character is a newline, set a flag so we can process it
    if (inChar == '\n') {
      command.toUpperCase();
      return command;
    }
  }
  return "";
}


void commSender::sendString(String bc_string){
  Serial.println("using serial");
  Serial.println(bc_string);
}

