/*
  ArduinoWiFiServer.h - Arduino compatible WiFiServer
  implementation for ESP8266/ESP32 Arduino Wifi library.
  Copyright (c) 2020 Juraj Andrassy

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef arduinowifiserver_h
#define arduinowifiserver_h

#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#if defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED)
#include "lwip/tcpbase.h"
#endif
#endif

#ifndef MAX_MONITORED_CLIENTS
#define MAX_MONITORED_CLIENTS 5
#endif

class ArduinoWiFiServer : public WiFiServer
#if defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED)
, public Print
#endif
{
public:

  ArduinoWiFiServer(const IPAddress& addr, uint16_t port) : WiFiServer(addr, port) {}
  ArduinoWiFiServer(uint16_t port) : WiFiServer(port) {}
  virtual ~ArduinoWiFiServer() {}

  // https://www.arduino.cc/en/Reference/EthernetServerAccept
  WiFiClient accept() {return WiFiServer::available();}

  // https://www.arduino.cc/en/Reference/WiFiServerAvailable
  WiFiClient available() {

    acceptClients();
 
    // find next client with data available
    for (uint8_t i = 0; i < MAX_MONITORED_CLIENTS; i++) {
      if (index == MAX_MONITORED_CLIENTS) {
        index = 0;
      }
      WiFiClient& client = connectedClients[index];
      index++;
      if (client.available())
        return client;
    }
    return WiFiClient(); // no client with data found
  }

  virtual size_t write(uint8_t b) override {
    return write(&b, 1);
  }

  virtual size_t write(const uint8_t *buf, size_t size) override {
    acceptClients();
    if (size == 0)
      return 0;
    size_t ret = 0;
#ifdef ESP8266
    size_t a = size;
    while (true) {
      uint8_t zeroACount = 0;
      for (uint8_t i = 0; i < MAX_MONITORED_CLIENTS; i++) {
        WiFiClient& client = connectedClients[i];
        if (client.status() == ESTABLISHED) {
          size_t afw = client.availableForWrite();
          if (afw == 0) {
            zeroACount++;
          } else if (afw < a) {
            a = afw;
          }
        }
      }
      if (zeroACount == MAX_MONITORED_CLIENTS)
        break;
      for (uint8_t i = 0; i < MAX_MONITORED_CLIENTS; i++) {
        WiFiClient& client = connectedClients[i];
        if (client.status() == ESTABLISHED && client.availableForWrite() > 0) {
          client.write(buf, a);
        }
      }
      ret += a;
      if (ret == size)
        break;
      buf += a;
      a = size - ret;
    }
#else
    for (uint8_t i = 0; i < MAX_MONITORED_CLIENTS; i++) {
      if (connectedClients[i]) {
        ret = connectedClients[i].write(buf, size);
      }
    }
#endif
    return ret;
  }

  using Print::write;

  virtual void flush() {
#ifndef ESP32 // has wrong client.flush()
    for (uint8_t i = 0; i < MAX_MONITORED_CLIENTS; i++) {
      if (connectedClients[i]) {
        connectedClients[i].flush();
      }
    }
#endif
  }

#if defined(ESP8266) || (defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED))
  operator bool() {return (status() == LISTEN);}
#endif

private:
  WiFiClient connectedClients[MAX_MONITORED_CLIENTS];
  uint8_t index = 0;

  void acceptClients() {
    for (uint8_t i = 0; i < MAX_MONITORED_CLIENTS; i++) {
      if (!connectedClients[i]) {
        connectedClients[i] = accept();
      }
    }
  }
};

#endif
