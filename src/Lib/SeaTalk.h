#ifndef SEATALK_H
#define SEATALK_H
#define MAX_BUF_SIZE 20
#define RX_IN 32
#define TX_OUT 33
#define LED_PIN 2

#include <SoftwareSerial.h>
#include <vector>

typedef std::function<void(void *, uint8_t testNumber)> TestNumberHandler;

class SeaTalk
{

public:
    SeaTalk();
    const uint8_t ST_Minus_1[4] = {0x86, 0x11, 0x05, 0xFA};
    const uint8_t ST_Minus_10[4] = {0x86, 0x11, 0x06, 0xF9};
    const uint8_t ST_Plus_1[4] = {0x86, 0x11, 0x07, 0xF8};
    const uint8_t ST_Plus_10[4] = {0x86, 0x11, 0x08, 0xF7};
    const uint8_t ST_Auto[4] = {0x86, 0x11, 0x01, 0xFE};
    const uint8_t ST_Standby[4] = {0x86, 0x11, 0x02, 0xFD};
    const uint8_t ST_Wind[4] = {0x86, 0x11, 0x23, 0xDC};
    const uint8_t ST_TimerStart[5] = {0x59, 0x22, 0x00, 0x05, 0x80};
    void processMessages();
    bool send2ST(const uint8_t cmd[], int bytes);
    void onTestEcho(TestNumberHandler handler, void *arg);

private:
    SoftwareSerial _mySerial;
    TestNumberHandler _handlerTNH;
    void *_argTNH;
    int checkBus();
    void checkClearToWrite();
};

#endif