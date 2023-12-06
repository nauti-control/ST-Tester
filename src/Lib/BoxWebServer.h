#ifndef BOXWEBSERVER_H
#define BOXWEBSERVER_H

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <SPIFFS.h>

#include "SeaTalk.h"

class BoxWebServer {

    public:
      BoxWebServer(SeaTalk *seaTalk);
      void ProcessCommands();

    private:
      SeaTalk *_seaTalk;
      
      AsyncWebServer webserver = AsyncWebServer(80);
  

};

#endif