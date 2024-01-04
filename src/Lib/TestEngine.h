#ifndef SEATALKCOMMANDGENERATOR_H
#define SEATALKCOMMANDGENERATOR_H
#include "SeaTalk.h"
#include <Arduino.h>

class TestEngine
{
public:
  TestEngine();

  void sendApparentWind(float windSpeed, float windAngle);
  void sendSpeedThroughWater(float speedThroughWater);
  void sendSpeedOverGround(float speedOverGround);

private:
  SeaTalk *_seaTalk;
};

#endif