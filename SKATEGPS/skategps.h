#ifndef skategps_h
#define skategps_h

#include "Arduino.h"
#define DEFAULT_BAUD_RATE	9600

#define RX_BUFFER_SIZE	15




class skategps
{


	public:
		int year_;
		int month_;
		int day_;
		int hour_;
		int minute_;
		int second_;
		int latDegrees;
		double latMinutes;
		char nsIndicator;
		int lonDegrees;
		double lonMinutes;
		char ewIndicator;
		int positionIndicator;
		int satellitesUsed;
		double hdop_;
		double altitude_;
		char altitudeUnits;
		double geoidalSeperation;
		char geoidalUnits;
		int differencialCorrectionAge;
		char status_;
		double speedInKnots;
		double heading;
		char headingReference;
		double magneticVariation;
		char magneticVariationDirection;
		int mode;
		double pdop;
		double vdop;
		double speedInKmh;
		int glonassSatellitesInView;
		int gpsSatellitesInView;
		double lat;
		double lon;
		
		long gpsDataTS;
		boolean nmeaProccessed;
		
		skategps(int serialSelect);
		void parseNmea();
		void gpsData(char byte_);
	    boolean isDataValid() ;
	
	void init();
	
	
	
	private:
		char buffer[RX_BUFFER_SIZE][100];
		char data[20][13];
		char tmpBuf[13];
		int linePos;
		int lineBuffer;
		int lineReader;
		boolean cr;
		boolean nl;
		
		long dataAge;
	
		void calcLatLon();
	
		int SplitStringData(  char * ptr);

		









};







#endif