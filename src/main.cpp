#include <Arduino.h>
#include "Lib\SeaTalk.h"
#include "Lib\BoxWifi.h"
#include "Lib\BoxWebServer.h"
#include <SPIFFS.h>
#include <Wire.h>
#include "Lib\Models\MockData.h"
#include "Lib\TestEngine.h"

SeaTalk *_seaTalk = nullptr;
BoxWifi *_boxWifi = nullptr;
BoxWebServer *_boxWebServer = nullptr;
MockData *_mockData = nullptr;
TestEngine *_testEngine = nullptr;

void setup()
{

  Serial.begin(9600); // Serial out put for function checks with PC
                      // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  _mockData = new MockData();
  _mockData->awa = 0;
  _mockData->aws = 0;
  _mockData->dpt = 1;
  _mockData->stw = 1;
  _mockData->sog = 1;
  _boxWifi = new BoxWifi();
  _boxWebServer = new BoxWebServer(_mockData);
  _seaTalk = new SeaTalk();
  _testEngine = new TestEngine(_mockData, _seaTalk);
}

void loop()
{
  _seaTalk->processMessages();
  _testEngine->processTest();
}