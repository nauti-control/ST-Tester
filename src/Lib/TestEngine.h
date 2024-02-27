#ifndef SEATALKCOMMANDGENERATOR_H
#define SEATALKCOMMANDGENERATOR_H
#include "SeaTalk.h"
#include <Arduino.h>
#include "Models\MockData.h"

class TestEngine
{
public:
  TestEngine(MockData *_mockData,SeaTalk *seatalk);

  void sendApparentWind(double windSpeed, double windAngle);
  void sendSpeedThroughWater(double speedThroughWater);
  void sendSpeedOverGround(double speedOverGround);
  void sendDepth(double depth);
  void sendHeading(double heading);
  void sendCourseOverGround(double courseOverGround);
  void processTest();

private:
  SeaTalk *_seaTalk;
  MockData *_mockData;
  long _lastRun;
};

#endif