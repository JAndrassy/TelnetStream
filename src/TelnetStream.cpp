#include <Arduino.h> // to include MCU specific includes for networking library
#include "TelnetStream.h"

TelnetStreamClass::TelnetStreamClass(uint16_t port) :server(port) {
}

void TelnetStreamClass::begin(int port) {
  if (port) {
#if USE_ETHERNET
    server = EthernetServer(port);
#else
    server = WiFiServer(port);
#endif
  }
  server.begin();
  client = server.available();
}

void TelnetStreamClass::stop() {
  client.stop();
}

boolean TelnetStreamClass::disconnected() {
#if defined(ESP32) || defined(USE_ETHERNET)
  if (!server)
    return true;
#else
  if (server.status() == 0) // 0 is CLOSED
    return true;
#endif
  if (!client) {
#if defined(USE_ETHERNET)
    client = server.accept();
#else
    client = server.available();
#endif
  }
  if (client) {
    if (client.connected())
      return false;
    client.stop();
#if defined(USE_ETHERNET)
    client = server.accept();
#else
    client = server.available();
#endif
  }
  return true;
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
  if (disconnected())
    return 1;
  return client.write(val);
}

void TelnetStreamClass::flush() {
  if (disconnected())
    return;
  client.flush();
}

TelnetStreamClass TelnetStream(23);
