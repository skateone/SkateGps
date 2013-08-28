#include <skategps.h>
#include "Arduino.h"




skategps::skategps(int serialSelect) {


switch(serialSelect) {

case 0: Serial.begin(DEFAULT_BAUD_RATE);
		break;

case 1: Serial1.begin(DEFAULT_BAUD_RATE);
		break;
		
case 2: Serial2.begin(DEFAULT_BAUD_RATE);
		break;
		
case 3: Serial3.begin(DEFAULT_BAUD_RATE);
		break;
}




		linePos = 0;
		lineBuffer = 0;
		lineReader = 0;
		cr = false;
		nl = false;

}

void skategps::init() {
		linePos = 0;
		lineBuffer = 0;
		lineReader = 0;
		cr = false;
		nl = false;

}

void skategps::calcLatLon() {
  lat = latDegrees + (latMinutes/60.0);
  if(nsIndicator == 'S') { 
   lat = lat*-1; 
  }
    lon = lonDegrees + (lonMinutes/60.0);
  if(ewIndicator == 'W') { 
   lon = lon*-1; 
  }
}

void skategps::parseNmea() {
  if(lineReader!=lineBuffer) {

  
 //Serial.println( buffer[lineReader]);

    int fieldCount = SplitStringData(buffer[lineReader]);
    if(strstr(data[0],"$GPGGA")!=NULL) {
      //UTC
      strncpy (tmpBuf,data[1],2);
      hour_ = atoi(tmpBuf);
      strncpy (tmpBuf,data[1]+2,2);
      minute_ = atoi(tmpBuf);       
      strncpy (tmpBuf,data[1]+4,2);
      second_ = atoi(tmpBuf);  
      //Latitude
      strncpy (tmpBuf,data[2],2);
      latDegrees = atoi(tmpBuf); 
      strncpy (tmpBuf,data[2]+2,7);
      latMinutes = atof(tmpBuf);   
      //Lat N/S Indicator
      strncpy (&nsIndicator,data[3],1);
      //Longitude
      strncpy (tmpBuf,data[4],3);
      tmpBuf[3] = '\0';
      lonDegrees = atoi(tmpBuf);  
      strncpy (tmpBuf,data[4]+3,7);
      lonMinutes = atof(tmpBuf);
      //Lon E/W Indicator
      strncpy (&ewIndicator,data[5],1);
      calcLatLon();
      //Position INdicator
      positionIndicator = atoi(data[6]); 
      //Satellites Used
      satellitesUsed = atoi(data[7]); 
      //HDOP
      hdop_ = atof(data[8]); 
      //Altitude
      altitude_ = atof(data[9]); 
      //Altitude Units
      strncpy (&altitudeUnits,data[10],1);
      //Geoidal Seperation
      geoidalSeperation = atof(data[11]); 
      //Geoidal Units
      strncpy (&geoidalUnits,data[12],1);
      //Age of Differential Correction
      differencialCorrectionAge = atoi(data[13]);
    } 
    else if( (strstr(data[0],"$GPRMC")!=NULL)||(strstr(data[0],"$GNRMC")!=NULL)   ) {
      //UTC
      strncpy (tmpBuf,data[1],2);
      hour_ = atoi(tmpBuf);
      strncpy (tmpBuf,data[1]+2,2);
      minute_ = atoi(tmpBuf);       
      strncpy (tmpBuf,data[1]+4,2);
      second_ = atoi(tmpBuf);  
      //Status
      strncpy (&status_,data[2],1);
      //Latitude
      strncpy (tmpBuf,data[3],2);
      latDegrees = atoi(tmpBuf);  
      strncpy (tmpBuf,data[3]+2,7);
      latMinutes = atof(tmpBuf);   
      //Lat N/S Indicator
      strncpy (&nsIndicator,data[4],1);
      //Longitude
      strncpy (tmpBuf,data[5],3);
      tmpBuf[3] = '\0';
      lonDegrees = atoi(tmpBuf);  
      strncpy (tmpBuf,data[5]+3,7);
      lonMinutes = atof(tmpBuf);   
      //Lon E/W Indicator
      strncpy (&ewIndicator,data[6],1);
      calcLatLon();
      //Speed over Ground
      speedInKnots = atof(data[7]);
      //Course over ground
      heading = atof(data[8]);
      //Date
      strncpy (tmpBuf,data[9],2);
      day_ = atoi(tmpBuf);
      strncpy (tmpBuf,data[9]+2,2);
      month_ = atoi(tmpBuf);       
      strncpy (tmpBuf,data[9]+4,2);
      year_ = atoi(tmpBuf);  
      //Magnetic Variation
      magneticVariation = atof(data[8]);
      //MagVariation direction
      strncpy (&magneticVariationDirection,data[9],1);
      //Mode
     // strncpy (&mode,data[10],1);  
    } 
    else if((strstr(data[0],"$GNGSA")!=NULL)||(strstr(data[0],"$GPGSA")!=NULL)   ) {
      //mode
     // strncpy (&mode,data[2],1);
	 
	  mode = atoi(data[2]);
	  
      //pdop
      pdop = atof(data[15]); 
      //hdop
      hdop_ = atof(data[16]); 
      //vdop
      vdop = atof(data[17]); 
    } 
    else if(strstr(data[0],"$GPGSV")!=NULL) {
      gpsSatellitesInView = atoi(data[3]);
    }
    else if(strstr(data[0],"$GLGSV")!=NULL) {
      glonassSatellitesInView = atoi(data[3]); 
    } 
    else if(strstr(data[0],"$GPVTG")!=NULL) {
      //Course over ground
      heading = atof(data[1]);
      //headingReference
      strncpy (&headingReference,data[2],1); 
      //speedInKnots
      speedInKnots = atof(data[5]);
      //speedInKmh
      speedInKmh = atof(data[7]);
    }
    lineReader++;
	
    if(lineReader>=RX_BUFFER_SIZE) {
      lineReader = 0;
    }
  } 

}




int skategps::SplitStringData(  char * ptr) {
  char ccount=0;
  char cc = 0;
  ptr = strtok(ptr,"\r");
  while(*ptr!='*') {
    if(*ptr!=',') {
      data[ccount][cc] = *ptr;
      cc++;
    } 
    else {
      data[ccount][cc] = '\0';
      cc = 0;
      ccount++;
    }
    ptr++;
  }
  return ccount;
}


void skategps::gpsData(char byte_) {
	buffer[lineBuffer][linePos] = byte_;
	  if (buffer[lineBuffer][linePos] == '\n') {
		nl = true;
	  } 
	  if (buffer[lineBuffer][linePos] == '\r') {
		cr = true;
	  }
	  if(nl&cr) {
	  dataAge=millis();
	    
		buffer[lineBuffer][linePos+1] = '\0';
		linePos = 0;
		lineBuffer++;
		if(lineBuffer>=RX_BUFFER_SIZE) {
		  lineBuffer = 0;
		}
		nl = false;
		cr = false;
	  } 
	  else {
		linePos++;
	  }


}


//checks if data is not older than 2 seconds... if so then the data is invalid... GPS serial stream not being recieved by Arduino
boolean skategps::isDataValid() {
	if((millis()-dataAge)<2000) {
		return true;
	} else {
		return false;
	}
}




