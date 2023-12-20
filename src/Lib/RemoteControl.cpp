#include "RemoteControl.h"

/// @brief REmote Control Constructor
/// @param seaTalk seatalk reference to send commands
/// @param options options reference to map controls
RemoteControl::RemoteControl()
{
  
    _mySwitch.enableReceive(19); // RF Receiver on pin 18
    _mySwitch.enableTransmit(18);
    
}

/// @brief hit point for main thread 
void RemoteControl::processRemote()
{
    unsigned long value = 0;

    if (_mySwitch.available())
    {
        value = _mySwitch.getReceivedValue();
        Serial.println("Keypad Received");
        Serial.printf("Keypad Value %lu", value);
        Serial.println("Received");
     
        _mySwitch.resetAvailable();
    }
}

