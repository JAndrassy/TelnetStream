#include <Ethernet.h>
#include <TelnetPrint.h>
#include <TimeLib.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress myIP(192, 168, 1, 177);

void setup() {

  Serial.begin(115200);

  Ethernet.init(10);
  Ethernet.begin(mac, myIP);

  //TelnetPrint = NetServer(2323); // uncomment to change port
  TelnetPrint.begin();

  Serial.println("Test started");
}

void loop() {
  NetClient client = TelnetPrint.available();
  if (client) {
    int c = client.read();
    switch (c) {
      case 'C':
        client.println("bye bye");
        client.flush();
        client.stop();
        break;
      default:
         Serial.write(c);
    }
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

  TelnetPrint.print(i++);
  TelnetPrint.print(" ");
  TelnetPrint.print(timeStr);
  TelnetPrint.print(" A0: ");
  TelnetPrint.println(analogRead(A0));
}

