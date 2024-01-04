#include "TestEngine.h"

TestEngine::TestEngine()
{

    _seaTalk = new SeaTalk();
}

void TestEngine::sendApparentWind(float windSpeed, float windAngle)
{
    // Wind Angle
    u_int16_t angle = windAngle * 2;
    u_int8_t x1 = (0xFF00 & angle) >> 4;
    u_int8_t y2 = 0x00FF & angle;

    // Pack it up
    uint8_t stcmd[4] = {0x10, 0x01, x1, y2};
    // Ship it out.
    _seaTalk->send2ST(stcmd, 4);

    // Wind speed in knots
    u_int8_t x2 = windSpeed;

    // Ensure only using 7 bits. keep 8th bit clear to signify knots.
    if (x2 > 127)
    {
        x2 == 127;
    }

    // Fractions would be stored here but dropping
    u_int8_t y2 = 0x00;

    // Pack it up
    uint8_t stcmd[4] = {0x11, 0x01, x2, y2};
    // Ship it out.
    _seaTalk->send2ST(stcmd, 4);
}

void TestEngine::sendSpeedThroughWater(float speedThroughWater)
{
    u_int16_t stw = speedThroughWater * 10;
    u_int8_t x1 = (0xFF00 & stw) >> 4;
    u_int8_t x2 = 0x00FF & stw;

    // Pack it up
    uint8_t stcmd[4] = {0x20, 0x01, x1, x2};
    // Ship it out.
    _seaTalk->send2ST(stcmd, 4);
}

void TestEngine::sendSpeedOverGround(float speedOverGround)
{
    u_int16_t sog = speedOverGround * 10;
    u_int8_t x1 = (0xFF00 & sog) >> 4;
    u_int8_t x2 = 0x00FF & sog;

    // Pack it up
    uint8_t stcmd[4] = {0x20, 0x01, x1, x2};
    // Ship it out.
    _seaTalk->send2ST(stcmd, 4);
}
