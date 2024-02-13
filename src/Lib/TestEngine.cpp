#include "TestEngine.h"

TestEngine::TestEngine(MockData *mockData, SeaTalk *seatalk)
{
    _mockData = mockData;
    _seaTalk = seatalk;
    _lastRun = 0;
}

void TestEngine::processTest()
{
    if (millis() > _lastRun + 1000)
    {
        sendApparentWind(_mockData->aws, _mockData->awa);
        delay(random(2, 50));
        sendSpeedThroughWater(_mockData->stw);
        delay(random(2, 50));
        sendSpeedOverGround(_mockData->sog);
        delay(random(2, 50));
        sendDepth(_mockData->dpt);
        _lastRun = millis();
        Serial.println("Test Run Processed");
    }
}

void TestEngine::sendDepth(float depth)
{
    Serial.println("Depth=");
    Serial.println(depth);
    u_int16_t dpt = depth * 10;
    u_int8_t x1 = (0xFF00 & dpt) >> 8;
    Serial.println(x1);
    u_int8_t x2 = 0x00FF & dpt;
    Serial.println(x2);
    u_int8_t y1 = 4 << 4 & 0xff00;
    Serial.println(y1);
    // Showing 256 Feet

    // Pack it up
    uint8_t stcmd[5] = {0x00, 0x02, 0x00, x2, x1};
    // Ship it out.
    _seaTalk->send2ST(stcmd, 5);
    Serial.println("Depth Sent TO ST");
}

void TestEngine::sendApparentWind(float windSpeed, float windAngle)
{
    Serial.println("Wind Speed=");
    Serial.println(windSpeed);
    Serial.println("Wind Angle=");
    Serial.println(windAngle);
    // Wind Angle
    u_int16_t angle = windAngle * 2;
    u_int8_t x1 = (0xFF00 & angle) >> 8;
    u_int8_t y1 = 0x00FF & angle;

    // Pack it up
    uint8_t stcmd[4] = {0x10, 0x01, x1, y1};
    // Ship it out.
    _seaTalk->send2ST(stcmd, 4);
    delay(random(2, 50));
    // Wind speed in knots
    u_int8_t x2 = windSpeed;

    // Ensure only using 7 bits. keep 8th bit clear to signify knots.
    if (x2 > 127)
    {
        x2 == 127;
    }

    // Fractions would be stored here but dropping
    // One Decimal place
     u_int8_t y2 = (windSpeed*10 ) - (static_cast<int>(windSpeed) * 10);
     // u_int8_t y2 = 0;
     //  Pack it up
     uint8_t stcmd2[4] = {0x11, 0x01, x2, y2};
     // Ship it out.
     _seaTalk->send2ST(stcmd2, 4);
     Serial.println("Wind Sent TO ST");
}

void TestEngine::sendSpeedThroughWater(float speedThroughWater)
{
    Serial.println("Speed Through Water=");
    Serial.println(speedThroughWater);

    u_int16_t stw = speedThroughWater * 10;

    u_int8_t x1 = (0xFF00 & stw) >> 8;
    Serial.println(x1);
    u_int8_t x2 = 0x00FF & stw;
    Serial.println(x2);

    // Pack it up
    uint8_t stcmd[4] = {0x20, 0x01, x2, x1};
    // Ship it out.
    _seaTalk->send2ST(stcmd, 4);
    Serial.println("Speed Through Water Sent");
}

void TestEngine::sendSpeedOverGround(float speedOverGround)
{
    Serial.println("Speed Over Ground=");
    Serial.println(speedOverGround);
    u_int16_t sog = speedOverGround * 10;
    u_int8_t x1 = (0xFF00 & sog) >> 8;
    u_int8_t x2 = 0x00FF & sog;

    // Pack it up
    uint8_t stcmd[4] = {0x52, 0x01, x2, x1};
    // Ship it out.
    _seaTalk->send2ST(stcmd, 4);
}
