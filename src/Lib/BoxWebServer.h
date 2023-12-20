#ifndef BOXWEBSERVER_H
#define BOXWEBSERVER_H

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include <SPIFFS.h>


class BoxWebServer {

    public:
      BoxWebServer();
      

    private:   
      AsyncWebServer webserver = AsyncWebServer(80);
  

};

#endif