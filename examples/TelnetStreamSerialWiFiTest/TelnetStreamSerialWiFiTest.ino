#include <WiFiEspAT.h>
#include <TimeLib.h>
#include <TelnetStream.h>

const int8_t TIME_ZONE = 2; // UTC + 2

void setup() {
  Serial.begin(115200);

  Serial1.begin(115200);
  WiFi.init(Serial1);

  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println();
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  // waiting for connection to Wifi network set with the SetupWiFiConnection sketch
  Serial.println("Waiting for connection to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print('.');
  }
  Serial.println();

  WiFi.sntp(TIME_ZONE, "us.pool.ntp.org");

  Serial.println("Waiting for SNTP");
//  while (!WiFi.getTime()) {
//    delay(1000);
//    Serial.print('.');
//  }
  setTime(WiFi.getTime());

  IPAddress ip = WiFi.localIP();
  Serial.println();
  Serial.println("Connected to WiFi network.");
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
}
