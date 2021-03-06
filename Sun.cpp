/*
 * Sun.cpp
 */
#include "Sun.h"
#include <math.h>

/*
 * Sun constructor
 */
Sun::Sun()
{ }

/*
 * Get current date/time, format is YYYY-MM-DD.HH:mm:ss
 */
const std::string Sun::currentDateTime()
{
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
	// for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  return buf;
}

/*
 * Sun's azimuth and elevation given a datetime and lat/long.
 *
 * Using a simplified, yet accurate sun
 * position calculator based on Blanco-Muriel et al.'s SPA algorithm closely
 * matches altitude, azimuth values returned by NOAA calculator. This variation was
 * converted from Javascript
 */
vec_t Sun::getPosition(float latitude, float longitude)
{
	vec_t cartesianPosition; // return vector
	std::string dateTime;
	dateTime = currentDateTime();

	int year = stoi(dateTime.substr(0,4));
	int month = stoi(dateTime.substr(5,2));
	int day = stoi(dateTime.substr(8,2));
	int UTHour = stoi(dateTime.substr(11,2));
	int UTMinute = stoi(dateTime.substr(14,2));

	float pi = 3.14159265358979323;
	float twopi = (2*pi);
	float rad = (pi/180);
	float EarthMeanRadius = 6371.01;	// In km
	float AstronomicalUnit = 149597890.;	// In km
	float DecimalHours = UTHour + (UTMinute ) / 60.0;
	long liAux1 = (month-14)/12;
	long liAux2=(1461*(year + 4800 + liAux1))/4 + (367*(month - 2-12*liAux1))/12- (3*(year + 4900 + liAux1)/100)/4 + day - 32075;
	float JulianDate = (liAux2) - 0.5 + DecimalHours/24.0;
	float ElapsedJulianDays = JulianDate-2451545.0;
	float Omega=2.1429-0.0010394594*ElapsedJulianDays;
	float MeanLongitude = 4.8950630+ 0.017202791698*ElapsedJulianDays; // Radians
	float MeanAnomaly = 6.2400600+ 0.0172019699*ElapsedJulianDays;
	float EclipticLongitude = MeanLongitude + 0.03341607*sin( MeanAnomaly ) + 0.00034894*sin( 2*MeanAnomaly )-0.0001134 -0.0000203*sin(Omega);
	float EclipticObliquity = 0.4090928 - 6.2140e-9*ElapsedJulianDays +0.0000396*cos(Omega);
	float Sin_EclipticLongitude= sin( EclipticLongitude );
	float Y = cos( EclipticObliquity ) * Sin_EclipticLongitude;
	float X = cos( EclipticLongitude );
	float RightAscension = atan2( Y, X );
	if ( RightAscension < 0.0 ) RightAscension = RightAscension + twopi;
	float Declination = asin( sin( EclipticObliquity )* Sin_EclipticLongitude );
	float GreenwichMeanSiderealTime = 6.6974243242 + 0.0657098283*ElapsedJulianDays + DecimalHours;
	float LocalMeanSiderealTime = (GreenwichMeanSiderealTime*15 + longitude)*rad;
	float HourAngle = LocalMeanSiderealTime - RightAscension;
	float LatitudeInRadians = latitude*rad;
	float Cos_Latitude = cos( LatitudeInRadians );
	float Sin_Latitude = sin( LatitudeInRadians );
	float Cos_HourAngle= cos( HourAngle );
	float UTSunCoordinatesZenithAngle = (acos( Cos_Latitude*Cos_HourAngle*cos(Declination) + sin( Declination )*Sin_Latitude));
	Y = -sin( HourAngle );
	X = tan( Declination )*Cos_Latitude - Sin_Latitude*Cos_HourAngle;
	float UTSunCoordinatesAzimuth = atan2( Y, X );
	if ( UTSunCoordinatesAzimuth < 0.0 )
		UTSunCoordinatesAzimuth = UTSunCoordinatesAzimuth + twopi;
	//UTSunCoordinatesAzimuth = UTSunCoordinatesAzimuth/rad;
	float Parallax = (EarthMeanRadius/AstronomicalUnit) * sin(UTSunCoordinatesZenithAngle);
	UTSunCoordinatesZenithAngle = (UTSunCoordinatesZenithAngle + Parallax);
	float elevation = pi/2. - UTSunCoordinatesZenithAngle;

	cartesianPosition.x = cos(UTSunCoordinatesAzimuth) * cos(elevation);
	cartesianPosition.y = sin(UTSunCoordinatesAzimuth) * cos(elevation);
	cartesianPosition.z = sin(elevation);
	return cartesianPosition;
}
