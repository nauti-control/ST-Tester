
#include "SeaTalk.h"

/// @brief Seatalk class constructor
/// @param signalManager Signal manager to send messages to other systems
SeaTalk::SeaTalk()
{
    _mySerial.begin(4800, SWSERIAL_8S1, RX_IN, TX_OUT, true, 95, 11);
}



/// @brief Method to run messages
void SeaTalk::processMessages()
{
    checkBus();
}

/// @brief Checks the seatalk bus for messages
/// @return if valid
int SeaTalk::checkBus()
{

    static std::vector<uint8_t> message;

    while (_mySerial.available())
    {
        uint8_t inByte = _mySerial.read();
        bool parity = _mySerial.readParity();

        if (parity) // Command byte received
        {
            message.clear(); // Clear previous message
            message.push_back(inByte);
        }
        else if (!message.empty()) // Data byte received
        {
            message.push_back(inByte);

            // Process messages
            // Echo Message Received Check to ensure it's the response signified by second byte.
            if (message[0] == 0xAC && message.size() == 4)
            {
                // Check Mode
                if (message[1] == 0x01)
                {
                  
            
                }
            }
        }
    }

    return -1;
}

/// @brief Send to seatalk Bus
/// @param cmd cmd
/// @param bytes length
/// @return did send
bool SeaTalk::send2ST(const uint8_t cmd[], int bytes)
{
    int j = 0;
    boolean ok = true;
    // Retry 5 Times
    while (j < 5)
    {
        checkClearToWrite();
        digitalWrite(LED_PIN, HIGH);
        for (int i = 0; (i < bytes) & (ok); i++)
        {
            (i == 0) ? _mySerial.write(cmd[i], SWSERIAL_PARITY_MARK) : _mySerial.write(cmd[i], SWSERIAL_PARITY_SPACE);
            delay(1);
            if (_mySerial.available())
            {
                uint8_t nextByte = _mySerial.read();
                if (nextByte != cmd[i])
                {
                    Serial.printf("Failed Byte Sent = %x byte received= %x \n", cmd[i], nextByte);
                    ok = false;
                }
            }
            else
            {
                Serial.println("Serial Not Available");
                ok = false;
            }
        }

        if (ok)
        {
            digitalWrite(LED_PIN, LOW);
            delay(100);

            Serial.println("Command Sent");
            return ok;
        }
        j++; // Collision detected
        Serial.println("Collision Detected");
        delay(random(2, 50));
        ok = true;
    }

    Serial.println("Send Failed");
    return false;
}

/// @brief Checks bus clear to write
void SeaTalk::checkClearToWrite()
{

    while (_mySerial.available())
    { // Wait for silence on the bus
        uint8_t inbyte = _mySerial.read();
        delay(3);
    }
    Serial.println("Clear To Send");
}
