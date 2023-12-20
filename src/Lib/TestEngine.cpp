#include "TestEngine.h"

TestEngine::TestEngine()
{

    _seaTalk = new SeaTalk();
    _seaTalk->onTestEcho(&handleTestEcho, this);
}

void TestEngine::startTest()
{
    _lastTestNum = -1;
    _currentTest = 0;
    _testComplete = false;
    _testPassed = false;
}

void TestEngine::runNextTest()
{

    // Send 10
    if (_currentTest < 10)
    {
        uint8_t testNum = random(256);
        sendTestEcho(testNum);
    }
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

void TestEngine::processUpdate()
{
}
