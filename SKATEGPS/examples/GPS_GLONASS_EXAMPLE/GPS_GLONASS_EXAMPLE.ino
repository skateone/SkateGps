#include <skategps.h>

/*
SkateWorx (PTY) ltd South Africa
This example is freely distributed without any warranty.
please feel free the add to the GITHUB repository
*/

long t1;


//0: Serial
//1: Serial1
//2: Serial2
//3: Serial3
skategps gps(2) ;



void setup() {
  gps.init();
  Serial.begin(115200);
  t1 = millis();
}




void loop() {


  if((millis()-t1)>1000) {
    t1 = millis();
    displayData();
  }

  gps.parseNmea();
 

}

void serialEvent2() {
  gps.gpsData(Serial2.read()); 
}




void displayData() {
  Serial.print(gps.year_);
  Serial.print("\\");
  Serial.print(gps.month_);
  Serial.print("\\");
  Serial.print(gps.day_);
  Serial.print(" ");
  Serial.print(gps.hour_);
  Serial.print(":");
  Serial.print(gps.minute_);
  Serial.print(":");
  Serial.print(gps.second_);
  Serial.print("\r\n");

  Serial.println(gps.latDegrees);
  Serial.println(gps.latMinutes,4);
  Serial.println(gps.nsIndicator);
  Serial.println(gps.lonDegrees);
  Serial.println(gps.lonMinutes,4);
  Serial.println(gps.ewIndicator);
  Serial.print("position : ");
  Serial.println(gps.positionIndicator);
  Serial.print("SAT COUNT : ");
  Serial.println(gps.satellitesUsed);

  Serial.print("alt : ");
  Serial.println(gps.altitude_,2);
  Serial.print("alt units : ");
  Serial.println(gps.altitudeUnits);
  Serial.print("geoid : ");
  Serial.println(gps.geoidalSeperation,2);
  Serial.print("geo id unit : ");
  Serial.println(gps.geoidalUnits);
  Serial.print("Diff age : ");
  Serial.println(gps.differencialCorrectionAge);   
  Serial.print("BEARING: ");
  Serial.println(gps.heading);
  Serial.print("SPEED : ");
  Serial.println(gps.speedInKnots);
  Serial.print("MAGVER : ");
  Serial.println(gps.magneticVariationDirection);
  Serial.print("MODE : ");
  Serial.println(gps.mode);

  Serial.print("VDOP : ");
  Serial.println(gps.vdop);
  Serial.print("PDOP : ");
  Serial.println(gps.pdop);
  Serial.print("HDOP : ");
  Serial.println(gps.hdop_,2);

  Serial.print("GPS SAT IN VIEW: ");
  Serial.println(gps.gpsSatellitesInView);
  Serial.print("GLONASS SAT IN VIEW:");
  Serial.println(gps.glonassSatellitesInView);

  Serial.print("KNOTS :  ");
  Serial.println(gps.speedInKnots,2);
  Serial.print("KM/H : ");
  Serial.println(gps.speedInKmh,2);



  Serial.print("LAT:  ");
  Serial.println(gps.lat,9);
  Serial.print("LON : ");
  Serial.println(gps.lon,9);

}





