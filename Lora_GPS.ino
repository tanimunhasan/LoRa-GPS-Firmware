#include "Lora.h"
#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

static const int RXPin = 4, TXPin = 5; //White ---TX  | Orange ----RX

static const uint32_t GPSBaud = 9600;
//// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ss.begin(GPSBaud);
  loraInit();
  delay(500);
  Serial.println("Hi, I'm going to send message");
  delay(500);
  setConf(11, 22, 1, 0);
  delay(500);
  loraMode(0); // Normal Mode

}

void loop() {
  // put your main code here, to run repeatedly:
  //char* data = "Successful \n\r";
  while (ss.available() > 0) {
    gps.encode(ss.read());
    if (gps.location.isUpdated()) {
      String data =   String(gps.location.lat(), 6);
      String data2 =  String(gps.location.lng(), 6);
      String stringOne = "    Latitude =  "  ;
      stringOne += data;
      stringOne += " Longtitude = " + data2;
      Serial.println(stringOne);
      char Buf[300];
      stringOne.toCharArray(Buf, 300);
      sendData(11, 22, 01, stringOne.c_str());
      Serial.println("Successfully Sent");
      delay(10);
      multiSerial();

    }
  }
}
