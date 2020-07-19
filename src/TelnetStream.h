/*
Copyright (C) 2017 Juraj Andrassy
repository https://github.com/jandrassy

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published
    by the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _TELNETSTREAM_H_
#define _TELNETSTREAM_H_

#if __has_include(<Ethernet.h>)
#include <Ethernet.h>
#define USE_ETHERNET 1
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif

class TelnetStreamClass : public Stream {

private:
#if USE_ETHERNET
  EthernetServer server;
  EthernetClient client;
#else
  WiFiServer server;
  WiFiClient client;
#endif

 boolean disconnected();

public:

  TelnetStreamClass(uint16_t port);

  void begin(int port = 0);
  void stop();

  // Stream implementation
  int read();
  int available();
  int peek();

  // Print implementation
  virtual size_t write(uint8_t val);
  using Print::write; // pull in write(str) and write(buf, size) from Print
  virtual void flush();

};

extern TelnetStreamClass TelnetStream;

#endif
