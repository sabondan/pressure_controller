#include <stdlib.h>
#include "Arduino.h"


#ifndef __serialSender_H__
#define __serialSender_H__


class commSender
{
  private:

    String command;

  
  public:
    String getCommand();
    void sendString(String);
};

#endif
