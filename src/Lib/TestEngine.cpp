#include "TestEngine.h"

TestEngine::TestEngine()
{

    _seaTalk = new SeaTalk();
    _seaTalk->onTestEcho(&handleTestEcho, this);
}

void TestEngine::sendWindData(int windSpeed, int windAngle)
{
}

void TestEngine::sendSpeedData(int speedThroughWater)
{
}

void TestEngine::sendTestEcho(uint8_t testNumber)
{
    _lastTestNum = testNumber;
    uint8_t message[] = {0xAC, 0x00, 0x00, testNumber};
    _seaTalk->send2ST(message, 4);
}

void TestEngine::checkEchoReply(uint8_t testNumber)
{
    if (testNumber == _lastTestNum)
    {
    }
}

void TestEngine::handleTestEcho(void *arg, uint8_t testNumber)
{
    TestEngine *engine = static_cast<TestEngine *>(arg);
    engine->checkEchoReply(testNumber);
}
