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
  _mockData->dpt = 0;
  _mockData->stw = 0;
  _mockData->sog = 0;
  _boxWifi = new BoxWifi();
  _boxWebServer = new BoxWebServer(_mockData);
  _seaTalk = new SeaTalk();
  _testEngine = new TestEngine(_mockData, _seaTalk);

  Serial.println("\n##################################");
  Serial.println(F("ESP32 Information:"));
  Serial.printf("Internal Total Heap %d, Internal Used Heap %d, Internal Free Heap %d\n", ESP.getHeapSize(), ESP.getHeapSize() - ESP.getFreeHeap(), ESP.getFreeHeap());
  Serial.printf("Sketch Size %d, Free Sketch Space %d\n", ESP.getSketchSize(), ESP.getFreeSketchSpace());
  Serial.printf("SPIRam Total heap %d, SPIRam Free Heap %d\n", ESP.getPsramSize(), ESP.getFreePsram());
  Serial.printf("Chip Model %s, ChipRevision %d, Cpu Freq %d, SDK Version %s\n", ESP.getChipModel(), ESP.getChipRevision(), ESP.getCpuFreqMHz(), ESP.getSdkVersion());
  Serial.printf("Flash Size %d, Flash Speed %d\n", ESP.getFlashChipSize(), ESP.getFlashChipSpeed());
  Serial.println("##################################\n");
}

void loop()
{
  _seaTalk->processMessages();
  _testEngine->processTest();
}