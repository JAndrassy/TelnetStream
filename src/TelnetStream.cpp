#include "TelnetStream.h"

TelnetStreamClass::TelnetStreamClass(uint16_t port) :server(port) {
}

void TelnetStreamClass::begin(int port) {
  if (port) {
    server = NetServer(port);
  }
#if defined(_WIFI_ESP_AT_H_)
  server.begin(3, 3600);
#else
  server.begin();
#endif
  client = server.available();
}

void TelnetStreamClass::stop() {
  client.stop();
}

boolean TelnetStreamClass::disconnected() {
#if __has_include(<WiFiNINA.h>) || (defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED))
  if (server.status() == 0) // 0 is CLOSED
    return true;
#elif (__has_include(<Ethernet.h>) && !defined(ARDUINO_ARCH_MBED)) || __has_include(<EthernetENC.h>) || __has_include(<WiFiEspAT.h>) || defined(ESP32)
  if (!server)
    return true;
#else
  // no bool operator, no status() function
#endif

  if (!client || !client.available()) {
    client = server.available(); // try to get next client with data
  }
  return !client;
}

int TelnetStreamClass::read() {
  if (disconnected())
    return -1;
  return client.read();
}

int TelnetStreamClass::available() {
  if (disconnected())
    return 0;
  return client.available();
}

int TelnetStreamClass::peek() {
  if (disconnected())
    return -1;
  return client.peek();
}

size_t TelnetStreamClass::write(uint8_t val) {
  return server.write(val);
}

size_t TelnetStreamClass::write(const uint8_t *buf, size_t size) {
  return server.write(buf, size);
}

void TelnetStreamClass::flush() {
  server.flush();
}

TelnetStreamClass TelnetStream(23);
