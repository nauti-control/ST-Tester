#ifndef REMOTECONTROL_H
#define REMOTECONTROL_H
#include <Arduino.h>
#include <RCSwitch.h>

#define KEY_DELAY 300 // 300 ms break between keys
#define BEEP_DURATION 150  // 150 ms beep time



class RemoteControl
{

public:
    RemoteControl();
    void processRemote();

private:
    
    RCSwitch _mySwitch = RCSwitch();
    const unsigned long _button1= 2548136;
    const unsigned long _button2= 2548132;
    const unsigned long _button3= 2548140;
    const unsigned long _button4= 2548130;
    const unsigned long _button5= 2548138;
    const unsigned long _button6= 2548134;
    const unsigned long _button7= 2548142;
    const unsigned long _button8= 2548129;
    


};

#endif