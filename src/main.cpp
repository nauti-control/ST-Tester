#include <Arduino.h>
#include "Lib\SeaTalk.h"
#include "Lib\BoxWifi.h"
#include "Lib\BoxWebServer.h"
#include <SPIFFS.h>
#include <Wire.h>

SeaTalk *_seaTalk = nullptr;
BoxWifi *_boxWifi = nullptr;
BoxWebServer *_boxWebServer = nullptr;

void setup()
{

  Serial.begin(9600); // Serial out put for function checks with PC
                      // Initialize SPIFFS
  if (!SPIFFS.begin(true))
  {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }
  _boxWifi = new BoxWifi();
  _seaTalk = new SeaTalk();
  _boxWebServer = new BoxWebServer(_seaTalk);
}

void loop()
{
  _seaTalk->processMessages();
  _boxWebServer->ProcessCommands();
}