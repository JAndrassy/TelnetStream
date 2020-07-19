#include <Ethernet.h>
#include <NtpClientLib.h>
#include <TelnetStream.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

void setup() {

  Serial.begin(115200);

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

  TelnetStream.begin();
  NTP.begin("pool.ntp.org", 1, false);
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
  TelnetStream.print(i++);
  TelnetStream.print(" ");
  TelnetStream.print(NTP.getTimeDateString());
  TelnetStream.print(" ");
  TelnetStream.print("Uptime: ");
  TelnetStream.print(NTP.getUptimeString());
  TelnetStream.print(" since ");
  TelnetStream.println(NTP.getTimeDateString(NTP.getFirstSync()).c_str());
}
