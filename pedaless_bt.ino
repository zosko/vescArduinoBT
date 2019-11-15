#include <SoftwareSerial.h>
#include "VescUart.h"

VescUart UART;

SoftwareSerial bluetooth(2, 3);

typedef struct {
  float v_in;
  float current_in;
  float rpm;
  float watt_hours;
  uint8_t tachometer_abs[4];
} mc_values_packet;

mc_values_packet packet;

void buffer_int32(uint8_t* buffer, int32_t number) {
  buffer[0] = number >> 24;
  buffer[1] = number >> 16;
  buffer[2] = number >> 8;
  buffer[3] = number;
}

void setup() {
  Serial.begin(115200);
  bluetooth.begin(9600);
  UART.setSerialPort(&Serial);
}

void loop() {
  if ( UART.getVescValues() ) {
    packet.v_in = UART.data.v_in;
    packet.current_in = UART.data.current_in;
    packet.rpm = UART.data.rpm;
    packet.watt_hours = UART.data.watt_hours;
    
//    buffer_int32(packet.tachometer_abs,UART.data.tachometer_abs);

    packet.tachometer_abs[0] = UART.data.tachometer_test[0];
    packet.tachometer_abs[1] = UART.data.tachometer_test[1];
    packet.tachometer_abs[2] = UART.data.tachometer_test[2];
    packet.tachometer_abs[3] = UART.data.tachometer_test[3];
    
    bluetooth.write((const uint8_t *)&packet, sizeof(mc_values_packet));
  }
  delay(50);
}
