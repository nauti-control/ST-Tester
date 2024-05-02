#include "TestEngine.h"

TestEngine::TestEngine(MockData *mockData, SeaTalk *seatalk)
{
    _mockData = mockData;
    _seaTalk = seatalk;
    _lastRun = 0;
}

void TestEngine::processTest()
{
    if (millis() > _lastRun + 500)
    {
        sendApparentWind(_mockData->aws, _mockData->awa);
        delay(random(2, 100));
        sendSpeedThroughWater(_mockData->stw);
        delay(random(2, 100));
        sendSpeedOverGround(_mockData->sog);
        delay(random(2, 100));
        sendDepth(_mockData->dpt);
        delay(random(2, 100));
        sendHeading(_mockData->hdg);
        delay(random(2, 100));
        sendCourseOverGround(_mockData->cog);
        delay(random(2, 100));
        sendLat(_mockData->latdeg, _mockData->latmin, _mockData->isNorth);
        delay(random(2, 100));
        sendLat(_mockData->londeg, _mockData->lonmin, _mockData->isWest);
        _lastRun = millis();
        Serial.println("Test Run Processed");
    }
}

/// @brief Send Depth
/// @param depth
void TestEngine::sendDepth(double depth)
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

/// @brief send apparent wind
/// @param windSpeed
/// @param windAngle
void TestEngine::sendApparentWind(double windSpeed, double windAngle)
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
    u_int8_t y2 = (windSpeed * 10) - (static_cast<int>(windSpeed) * 10);
    // u_int8_t y2 = 0;
    //  Pack it up
    uint8_t stcmd2[4] = {0x11, 0x01, x2, y2};
    // Ship it out.
    _seaTalk->send2ST(stcmd2, 4);
    Serial.println("Wind Sent TO ST");
}

/// @brief Send speed through water
/// @param speedThroughWater
void TestEngine::sendSpeedThroughWater(double speedThroughWater)
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

/// @brief Send SOG
/// @param speedOverGround
void TestEngine::sendSpeedOverGround(double speedOverGround)
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

/// @brief send Heading HDG
/// @param heading
void TestEngine::sendHeading(double heading)
{
    Serial.println("Heading=");
    Serial.println(heading);
    u_int16_t hdg = heading;
    // 90 Degree segment to be held in 2 bits
    u_int8_t segment = heading / 90;
    // These six bits hold the 90 degrees in between in alternating degrees up to 45
    u_int8_t segmentDegree = (hdg % 90) / 2;
    // Either 1/0 weirdly by the docs it sets two bits will play about with this as it seems mixed up over the various degreee
    u_int8_t oddDegree = ((hdg % 90) % 2) == 1 ? 2 : 0;

    // Shift it All Across
    u_int8_t u2 = (((oddDegree << 6) & 0xC0) | ((segment << 4) & 0xF0)) | 0x2;
    // Mask off first 2 bits
    u_int8_t vw = segmentDegree & 0x3f;
    // Pack it up
    uint8_t stcmd[5] = {0x89, u2, vw, 0x00, 0x20};
    // Ship it out.
    _seaTalk->send2ST(stcmd, 5);
}

/// @brief Send Course over ground
/// @param courseoverground
void TestEngine::sendCourseOverGround(double courseOverGround)
{
    Serial.println("COG=");
    Serial.println(courseOverGround);
    u_int16_t cog = courseOverGround;
    // 90 Degree segment to be held in 2 bits
    u_int8_t segment = cog / 90;
    // These six bits hold the 90 degrees in between in alternating degrees up to 45
    u_int8_t segmentDegree = (cog % 90) / 2;
    // Either 1/0 weirdly by the docs it sets two bits will play about with this as it seems mixed up over the various degreee
    u_int8_t oddDegree = ((cog % 90) % 2) == 1 ? 2 : 0;

    // Shift it All Across
    u_int8_t u0 = (((oddDegree << 6) & 0xC0) | ((segment << 4) & 0xF0));
    // Mask off first 2 bits
    u_int8_t vw = segmentDegree & 0x3f;
    // Pack it up
    uint8_t stcmd[3] = {0x53, u0, vw};
    // Ship it out.
    _seaTalk->send2ST(stcmd, 3);
}

/// @brief Send Lat
/// @param latDeg Lat Degree
/// @param latMin Lat Minute
/// @param isSouth Is South
void TestEngine::sendLat(double latDeg, double latMin, bool isNorth)
{
    Serial.println("Lat=");
    Serial.println(latDeg);
    Serial.println(latMin);
    u_int8_t xx = latDeg;
    u_int16_t yyyy = (latMin * 100);
    if (!isNorth)
    {
        yyyy = yyyy | 0x8000;
    }
    else
    {
        yyyy = yyyy & 0x7FFF;
    }
    u_int8_t y1 = (0xFF00 & yyyy) >> 8;
    u_int8_t y2 = 0x00FF & yyyy;

    uint8_t stcmd[5] = {0x50, 0x02, xx, y1, y2};
    // Ship it out.
    _seaTalk->send2ST(stcmd, 5);
}

/// @brief Send Long
/// @param lonDeg Lon degrees
/// @param lonMin Lon minutes
/// @param isEast is east
void TestEngine::sendLon(double lonDeg, double lonMin, bool isWest)
{
    Serial.println("Lon=");
    Serial.println(lonDeg);
    Serial.println(lonMin);
    u_int8_t xx = lonDeg;
    u_int16_t yyyy = (lonMin * 100);
    if (!isWest)
    {
        yyyy = yyyy | 0x8000;
    }
    else
    {
        yyyy = yyyy & 0x7FFF;
    }
    u_int8_t y1 = (0xFF00 & yyyy) >> 8;
    u_int8_t y2 = 0x00FF & yyyy;

    uint8_t stcmd[5] = {0x51, 0x02, xx, y1, y2};
    // Ship it out.
    _seaTalk->send2ST(stcmd, 5);
}