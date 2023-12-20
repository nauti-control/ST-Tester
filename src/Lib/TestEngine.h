#ifndef SEATALKCOMMANDGENERATOR_H
#define SEATALKCOMMANDGENERATOR_H
#include "SeaTalk.h"
#include <Arduino.h>

class TestEngine
{
public:
  TestEngine();
  void startTest();
  void processUpdate();

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