#include "BoxWebServer.h"

BoxWebServer::BoxWebServer()
{

 
    Serial.println("Settign Up WEb Server");
    webserver.on("/", HTTP_GET, [&](AsyncWebServerRequest *request)
                 {
                     request->send(SPIFFS, "/index.html", "text/html");
                     Serial.println("Index Sent"); });

    webserver.on("/index.html", HTTP_GET, [&](AsyncWebServerRequest *request)
                 {
                    
                      request->send(SPIFFS, "/index.html", "text/html");
                     Serial.println("Index Sent"); });

    webserver.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
                 {
                     request->send(SPIFFS, "/style.css", "text/css");
                     Serial.println("CSS Sent"); });

    webserver.on("/jquery-3.6.3.min.js", HTTP_GET, [](AsyncWebServerRequest *request)
                 {
                     request->send(SPIFFS, "/jquery-3.6.3.min.js", "application/javascript");
                     Serial.println("JS Sent"); });


    webserver.serveStatic("/", SPIFFS, "/");
    webserver.begin();
}



// Process Commands On Main Thread
