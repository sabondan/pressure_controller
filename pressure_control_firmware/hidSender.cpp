#include <stdlib.h>
#include "Arduino.h"


//_________________________________________________________



String commSender::getCommand() {
  int n = RawHID.recv(in_buffer, 1); // 0 timeout = do not wait
  if (n > 0) {

    String in_str;
    for (char c : in_buffer) in_str += c;
    
    command = in_str;
    command.toUpperCase();
    //Serial.print("Recieved: ");
    //Serial.println(command);
    return command;
  }
  else {
    return "";
  }

}



void commSender::sendString(String bc_string){
  // Reset the buffer with zeros
  for (int i=0; i<64; i++) {
    out_buffer[i] = 0;
  }
  bc_string.getBytes(out_buffer, 64);
  int n = RawHID.send(out_buffer, 1);

}

