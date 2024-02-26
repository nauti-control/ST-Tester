#ifndef SEATALKCOMMANDGENERATOR_H
#define SEATALKCOMMANDGENERATOR_H
#include "SeaTalk.h"
#include <Arduino.h>
#include "Models\MockData.h"

class TestEngine
{
public:
  TestEngine(MockData *_mockData,SeaTalk *seatalk);

  void sendApparentWind(float windSpeed, float windAngle);
  void sendSpeedThroughWater(float speedThroughWater);
  void sendSpeedOverGround(float speedOverGround);
  void sendDepth(float depth);
  void sendHeading(int heading);
  void sendCourseOverGround(double courseOverGround);
  void processTest();

private:
  SeaTalk *_seaTalk;
  MockData *_mockData;
  long _lastRun;
};

#endif