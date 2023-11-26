# TelnetStream

The library creates a TelnetStream object, which can be used the same way as Serial, but the output is sent to all connected telnet clients. It enables remote logging or debugging.

TelnetStream.h can be included not only in the ino file, but in cpp files of the sketch or in libraries to add debug prints for troubleshooting.

Version 1.2.0 introduced TelnetPrint object, a simpler and smaller alternative to TelnetStream. Basically it is only EthernetServer or WiFiServer instanced for use anywhere in your sketch or libraries.

TelnetStream/TelnetPrint works as it is with:

* esp8266 and esp32 WiFi library (including the wired network interfaces)
* Ethernet and EthernetENC library
* WiFiNINA, WiFi101 and WiFiEspAT library 
* Renesas Core WiFiS3 and WiFiC3 libraries
* WiFi library of the RP2040 Pico Core (including the wired network interfaces)
* WiFi and PortentaEthernet library of the Mbed Core 

Version 1.3.0 has NetApiHelpers library as dependency. NetApiHelpers library provides Arduino Server for networking libraries without print-to-all-clients functionality in their Server implementation: ESP8266WiFi, ESP32 WiFi, RP2040 Core and Mbed Core.

The library is in Library Manager. You can install it there.

Output of example:

```
juraj@nuc ~ $ telnet 192.168.1.114
Trying 192.168.1.114...
Connected to 192.168.1.114.
Escape character is '^]'.
54 2020-07-19 16:50:43 A0: 355
55 2020-07-19 16:50:48 A0: 335
56 2020-07-19 16:50:53 A0: 223
C
bye bye
Connection closed by foreign host.
```