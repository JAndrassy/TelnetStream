# TelnetStream

The library creates a TelnetStream object, which can be used the same way as Serial, but the output is sent to all connected telnet clients. It enables remote logging or debugging.

TelnetStream.h can be included not only in the ino file, but in cpp files of the sketch or in libraries to add debug prints for troubleshooting.

Version 1.2.0 introduced TelnetPrint object, a simpler and smaller alternative to TelnetStream. Basically it is only EthernetServer or WiFiServer instanced for use anywhere in your sketch or libraries.

TelnetStream/TelnetPrint works as it is with esp8266 and esp32 WiFi library, with the Ethernet and EthernetENC, with WiFiNINA, WiFi101, WiFiS3 and WiFiEspAT library. The RP2040 Pico Core networking libraries are supported as well. 

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