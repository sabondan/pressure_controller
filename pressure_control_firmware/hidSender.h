#include <stdlib.h>
#include "Arduino.h"


#ifndef __hidSender_H__
#define __hidSender_H__


class commSender
{
  private:

    byte in_buffer[64];
    byte out_buffer[64];

    String command;

  
  public:
    String getCommand();
    void sendString(String);
};

#endif
