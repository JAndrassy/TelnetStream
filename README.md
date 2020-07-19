# TelnetStream

The library creates a TelnetStream object, which can be used the same way as Serial, but the output is sent to a connected telnet client. It enables remote logging or debugging.

TelnetStream.h can be included not only in the ino file, but in cpp files of the sketch or in libraries to add debug prints for troubleshooting.

TelnetStream works as it is with esp8266 and esp32 WiFi library, with the Ethernet library, with WiFiNINA and with WiFiEspAT library.

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