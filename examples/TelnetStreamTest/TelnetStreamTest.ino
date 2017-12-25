#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>
#include <WiFiManager.h>
#include <NtpClientLib.h>
#include <TelnetStream.h>

void setup()
{
  Serial.begin(115200);
  ArduinoOTA.begin();

  WiFiManager wifiManager;
  wifiManager.autoConnect();

  TelnetStream.begin();
  NTP.begin("pool.ntp.org", 1, false);
}

void loop()
{
  ArduinoOTA.handle();

  if (TelnetStream.read() == 'R') {
    TelnetStream.stop();
    delay(100);
    ESP.reset();
  }

  static unsigned long next = millis();
  if (millis() > next) {
    next += 5000;
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
