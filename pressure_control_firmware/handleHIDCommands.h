#include <stdlib.h>
#include "allSettings.h"
#include "eeprom_handler.h"


#ifndef __handleHIDCommands_H__
#define __handleHIDCommands_H__


class handleHIDCommands
{
  private:

    byte in_buffer[64];
    byte out_buffer[64];

    
    int numSensors;
    int comm_type = 0;
    String command;
    bool broadcast = false;
    eepromHandler saveHandler;

    bool getCommand();
    bool getCommandHID();
    bool getCommandSerial();

    void sendStringHID(String);
    void sendStringSerial(String);

    bool processCommand(globalSettings &, controlSettings *, trajectory &);
    String getStringValue(String, char, int);
  
  public:
    void initialize(int, int);
    bool go(globalSettings &, controlSettings *, trajectory &);
    void startBroadcast();
    void stopBroadcast();
    void sendString(String);
};

#endif
