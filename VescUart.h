#ifndef _VESCUART_h
#define _VESCUART_h

#include <Arduino.h>
#include "datatypes.h"
#include "buffer.h"
#include "crc.h"

class VescUart
{
  public:
    VescUart(void);
    mc_values data;
    void setSerialPort(Stream* port);
    bool getVescValues(void);
  private:
    Stream* serialPort = NULL;
    int packSendPayload(uint8_t * payload, int lenPay);
    int receiveUartMessage(uint8_t * payloadReceived);
    bool unpackPayload(uint8_t * message, int lenMes, uint8_t * payload);
    bool processReadPacket(uint8_t * message);
};

#endif
