/*
Copyright (C) 2020 Juraj Andrassy
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

#ifndef _NETTYPES_H_
#define _NETTYPES_H_

#include <Arduino.h> // to include MCU specific includes for networking library

// esp doesn't support __has_include but it is defined

#if defined(ESP8266)
#include <ESP8266WiFi.h>
#if (ARDUINO_ESP8266_MAJOR < 3)
#include "ArduinoWiFiServerESP.h"
#else
#include <ArduinoWiFiServer.h> // in ESP8266WiFi library
#endif
#define NetClient WiFiClient
#define NetServer ArduinoWiFiServer

#elif defined(ESP32)
#include <WiFi.h>
#include "ArduinoWiFiServerESP.h"
#define NetClient WiFiClient
#define NetServer ArduinoWiFiServer

#elif defined __has_include

#if __has_include(<EthernetENC.h>)
#include <EthernetENC.h>
#define NetClient EthernetClient
#define NetServer EthernetServerPrint

#elif __has_include(<Ethernet.h>)
#include <Ethernet.h>
#define NetClient EthernetClient
#define NetServer EthernetServer

#elif __has_include(<WiFi101.h>)
#include <WiFi101.h>
#define NetClient WiFiClient
#define NetServer WiFiServer

#elif __has_include(<WiFiEspAT.h>)
#include <WiFiEspAT.h>
#define NetClient WiFiClient
#define NetServer WiFiServerPrint

#elif defined(ARDUINO_ARCH_RP2040) && !defined(ARDUINO_ARCH_MBED)
#include <WiFi.h>
#include <ArduinoWiFiServerESP.h>
#define NetClient WiFiClient
#define NetServer ArduinoWiFiServer

#else
#include <WiFi.h>
#include <WiFiServer.h>
#define NetClient WiFiClient
#define NetServer WiFiServer
#endif

#else // not defined __has_include
#include <WiFi.h>
#include <WiFiServer.h>
#define NetClient WiFiClient
#define NetServer WiFiServer
#endif

#endif
