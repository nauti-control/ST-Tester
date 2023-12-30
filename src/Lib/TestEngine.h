#ifndef SEATALKCOMMANDGENERATOR_H
#define SEATALKCOMMANDGENERATOR_H
#include "SeaTalk.h"
#include <Arduino.h>

class TestEngine
{
public:
  TestEngine();
  void processUpdate();
  void sendTestEcho(uint8_t testNumber);
  void sendWindData(int windSpeed,int windAngle);
  void sendSpeedData(int speedThroughWater);
  

private:
  SeaTalk *_seaTalk;
  bool _testComplete;
  bool _testPassed;
  u_int8_t _currentTest;
  u_int8_t _lastTestNum;
  static void handleTestEcho(void *arg, uint8_t testNumber);
  void sendTestEcho(uint8_t testNumber);
  void checkEchoReply(uint8_t testNumber);
  void runNextTest();
};

#endif