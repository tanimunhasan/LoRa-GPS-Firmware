#include "Lora.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(A3, A4); //Rx, Tx

#define M0 2
#define M1 3

void loraInit() {
  Serial.begin(9600);
  mySerial.begin(9600);
  ss.begin(9600);
}

void multiSerial() {
  if (mySerial.available()) {
    Serial.write(mySerial.read());
    Serial.write(ss.read());
  }
  
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

void loraMode(int mode) {
  
  pinMode(M0, OUTPUT); // M0
  pinMode(M1, OUTPUT); // M1

  if (mode == 0) {
    //Normal Mode
    digitalWrite(M0, LOW); //M0
    delay(1000);
    digitalWrite(M1, LOW); //M1
    delay(5000);
  }

  else if ( mode == 1) {
    //WOR Mode
    digitalWrite(M0, HIGH); //M0
    delay(1000);
    digitalWrite(M1, LOW); //M1
    delay(5000);

  }
  else if ( mode == 2) {
    //Configuration Mode
    digitalWrite(M0, LOW); //M0
    delay(1000);
    digitalWrite(M1, HIGH); //M1
    delay(5000);
  }
  else if ( mode == 3) {
    //Deep Sleep Mode
    digitalWrite(M0, HIGH); //M1
    delay(1000);
    digitalWrite(M1, HIGH); //M0
    delay(5000);
  }
}

void setConf(int addh, int addl, int ch, int netId) {
  
  loraMode(2);
  delay(500);

  mySerial.write((byte) 192);
  mySerial.write((byte) 00);
  mySerial.write((byte) 07);
  mySerial.write(addh);
  mySerial.write(addl);
  mySerial.write((byte) netId);
  mySerial.write((byte) 98); //2.4kbps
  mySerial.write((byte) 00);//0 for 30dbm, 01 for 27dbm
  mySerial.write((byte) ch);
  mySerial.write((byte) 67); //Fixed Transmission
  delay(100);

  loraMode(0);

}

void sendData(int addh, int addl, int ch, char* buf) {
  
  loraMode(0);
  delay(500);
  while (mySerial.available() > 0) {

    mySerial.write((byte) addh);
    mySerial.write((byte) addl);
    mySerial.write((byte) ch);
    mySerial.write(buf);
    delay(500);

  }

}
