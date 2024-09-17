#include <HardwareSerial.h>
#include "TinyGPS++.h"
#include "AsyncSMS.h"
#include "SIM.h" //Includes various libraries required for the device operation
// SERIAL PORT DEF

HardwareSerial gpsSerial(2); //pin 43(rx) and 44 (tx)

TinyGPSPlus gps;

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 1800000; // send the location every 30 mins

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(9600, SERIAL_8N1, 43, 44);

  SIM.begin();
  smsHelper.init();
  smsHelper.smsReceived = &messageReceived;
}

void loop() {
  // Check GSM network status
  if (SIM.isNetworkConnected()) {
    Serial.println("GSM module connected to network.");
  } else {
    Serial.println("GSM module not connected to network.");
  }

  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isValid() && gps.location.age() < 2000) {
        unsigned long currentMillis = millis();
        if (currentMillis - lastSendTime >= sendInterval) {
          sendLocationSMS(gps.location.lat(), gps.location.lng());
          lastSendTime = currentMillis;
        }
      }
    }
  }
}

void sendLocationSMS(float latitude, float longitude) {
  String locationURL = "https://www.google.com/maps?q=" + String(latitude, 6) + "," + String(longitude, 6);
  String message = "Current Location: " + locationURL;
  smsHelper.send("10DigitNum", message.c_str(), 45);
}
