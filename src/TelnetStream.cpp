#include "TelnetStream.h"

TelnetStreamClass::TelnetStreamClass(uint16_t port) :server(port) {
}

void TelnetStreamClass::begin() {
  server.begin();
  client = server.available();
}

void TelnetStreamClass::stop() {
  client.stop();
}

boolean TelnetStreamClass::disconnected() {
#ifdef ESP32
  if (!server)
    return true;
#else
  if (server.status() == CLOSED)
    return true;
#endif
  if (!client) {
    client = server.available();
  }
  if (client) {
    if (client.connected())
      return false;
    client.stop();
    client = server.available();
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
