#ifndef BOXWEBSERVER_H
#define BOXWEBSERVER_H

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "Models/MockData.h"

#include <SPIFFS.h>


class BoxWebServer {

    public:
      BoxWebServer(MockData *mockData);
      

    private:   
      AsyncWebServer webserver = AsyncWebServer(80);
      void SetTestData(AsyncWebServerRequest *request);
      MockData *_mockData;
  

};

#endif