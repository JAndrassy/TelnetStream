#include <EthernetEspAT.h>
#include <TimeLib.h>
#include <TelnetStream.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

void setup() {

  Serial.begin(115200);
  while (!Serial);

  Serial1.begin(115200);
  Ethernet.init(Serial1);

  if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }

  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    while (true) {
      delay(1); // do nothing, no point running without Ethernet hardware
    }
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }

  WiFi.sntp("us.pool.ntp.org");
  Serial.println("Waiting for SNTP");
  while (!Ethernet.getTime()) {
    delay(1000);
    Serial.print('.');
  }
  setTime(Ethernet.getTime());

  IPAddress ip = Ethernet.localIP();
  Serial.println();
  Serial.print("Connect with Telnet client to ");
  Serial.println(ip);

  TelnetStream.begin();
}

void loop() {

  switch (TelnetStream.read()) {
    case 'C':
      TelnetStream.println("bye bye");
      TelnetStream.flush();
      TelnetStream.stop();
      break;
  }

  static unsigned long next;
  if (millis() - next > 5000) {
    next = millis();
    log();
  }
}

void log() {
  static int i = 0;

  char timeStr[20];
  sprintf(timeStr, "%02d-%02d-%02d %02d:%02d:%02d", year(), month(), day(), hour(), minute(), second());

  TelnetStream.print(i++);
  TelnetStream.print(" ");
  TelnetStream.print(timeStr);
  TelnetStream.print(" A0: ");
  TelnetStream.println(analogRead(A0));
  TelnetStream.flush();
}
