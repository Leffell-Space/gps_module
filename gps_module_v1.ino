#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// Create an instance of the TinyGPS++ object
TinyGPSPlus gps;

// Create a software serial connection (for GPS module)
SoftwareSerial ss(4, 3); // RX, TX pins (adjust as needed)

void setup() {
  // Start the serial communication
  Serial.begin(9600);
  ss.begin(9600); // GPS baud rate
}

void loop() {
  while (ss.available() > 0) {
    gps.encode(ss.read()); // Feed data to the GPS library
    
    if (gps.location.isUpdated()) {
      // Get location information
      double latitude = gps.location.lat();
      double longitude = gps.location.lng();
      double altitude = gps.altitude.meters(); // Altitude in meters

      // Get the number of satellites in view
      int satelliteCount = gps.satellites.value();

      // Get the timestamp (in hours, minutes, seconds)
      unsigned long timestamp = gps.time.value();
      int hours = gps.time.hour();
      int minutes = gps.time.minute();
      int seconds = gps.time.second();

      // Get the Horizontal Dilution of Precision (HDOP)
      float hdop = gps.hdop.value() / 100.0; // HDOP is returned in hundredths, so divide by 100

      // Print the data to the Serial Monitor with pipe separation
      Serial.print(hours); Serial.print(":");
      Serial.print(minutes); Serial.print(":");
      Serial.print(seconds); Serial.print(",");
      Serial.print(latitude, 6); Serial.print(",");
      Serial.print(longitude, 6); Serial.print(",");
      Serial.print(altitude, 1); Serial.print(",");
      Serial.print(satelliteCount); Serial.print(",");
      Serial.print(hdop, 2); Serial.print("\n");
    }
  }
}
