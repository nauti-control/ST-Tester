#include "BoxWebServer.h"

BoxWebServer::BoxWebServer(MockData *mockData)
{

    Serial.println("Settign Up WEb Server");
    _mockData = mockData;
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

    webserver.on("/SetTestData.html", HTTP_POST, [&](AsyncWebServerRequest *request)
                 { SetTestData(request); });

    webserver.serveStatic("/", SPIFFS, "/");
    webserver.begin();
    Serial.println("Web Server Setup");
}

void BoxWebServer::SetTestData(AsyncWebServerRequest *request)
{

    Serial.println("Setting Test Data");
    if (request->hasParam("stwInput", true))
    {
        AsyncWebParameter *p = request->getParam("stwInput", true);
        _mockData->stw = p->value().toFloat();
        Serial.println("stw=");
        Serial.println(_mockData->stw);
    }

    if (request->hasParam("awaInput", true))
    {
        AsyncWebParameter *p = request->getParam("awaInput", true);
        _mockData->awa = p->value().toFloat();
        Serial.println("awa=");
        Serial.println(_mockData->awa);
    }

    if (request->hasParam("awsInput", true))
    {
        AsyncWebParameter *p = request->getParam("awsInput", true);
        _mockData->aws = p->value().toFloat();
        Serial.println("aws=");
        Serial.println(_mockData->aws);
    }

    if (request->hasParam("dptInput", true))
    {
        AsyncWebParameter *p = request->getParam("dptInput", true);
        _mockData->dpt = p->value().toFloat();
        Serial.println("dpt=");
        Serial.println(_mockData->dpt);
    }
    Serial.println("Test Data Set");
    request->send(200);
}

// Process Commands On Main Thread
