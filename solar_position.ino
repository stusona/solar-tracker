/* Solar tracker
 * Stuart Sonatina
 * 2019-09-21
 *
 * Using a simplified, yet accurate sun
 * position calculator based on Blanco-Muriel et al.'s SPA algorithm closely
 * matches altitude, azimuth values returned by NOAA calculator. This variation was
 * converted from Javascript
*/
	#include <math.h>
	#include <stdio.h>

  float UTHours=20., UTMinutes=0., UTSeconds=0.;
  float Lat=37.9., Lon=-122., TZ = -7;
  int year=2014,month=6,day=14;  //UTC date

// accuracy tests... double precision algorithm said to be accurate to 0.5 arcmin (.0083 deg) until 2015
// 2003/1/1 Lat,Lon = (0,0) @12:00 UTC: if double precision get alt=66.9713, az=177.9905, zenith=23.0287
//                       for above NOAA says                        66.98       177.99
// 2023/1/1 (0,0) @12:00 UTC: get 66.9847, 177.9738 NOAA says 66.99 177.97
// local test Eugene OR:
//   float UTHours=20., UTMinutes=0., UTSeconds=0.; //(local  hours - TZ)
//   float Lat=44.052, Lon=-123.087; // (44 3' 7" -123 5' 13") @12:00 local time no DST => 20:00 UT get alt = 68.97 az = 172.14 NOAA sez 68.98 172.12
//   int year=2014,month=6,day=12;  //UTC date

	void get_sun_pos(float latitude, float longitude, float *altitude, float *azimuth)
	{

		float zenith;
		float pi =3.14159265358979323;
		float twopi=(2*pi);
		float rad=(pi/180);
		float EarthMeanRadius=6371.01;	// In km
		float AstronomicalUnit=149597890.;	// In km
		float DecimalHours = UTHours + (UTMinutes + UTSeconds / 60.0 ) / 60.0;
		long liAux1 =(month-14)/12;
		long liAux2=(1461*(year + 4800 + liAux1))/4 + (367*(month - 2-12*liAux1))/12- (3*(year + 4900 + liAux1)/100)/4+day-32075;
		float JulianDate=(liAux2)-0.5+ DecimalHours/24.0;
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
		UTSunCoordinatesAzimuth = UTSunCoordinatesAzimuth/rad;
		float Parallax=(EarthMeanRadius/AstronomicalUnit)*sin(UTSunCoordinatesZenithAngle);
		UTSunCoordinatesZenithAngle=(UTSunCoordinatesZenithAngle + Parallax)/rad;
		*azimuth=UTSunCoordinatesAzimuth;
		zenith=UTSunCoordinatesZenithAngle;
		*altitude=90.-UTSunCoordinatesZenithAngle;
}

int main()
{
	float alt, az;
	get_sun_pos(Lat, Lon, &alt, &az);
	printf("At Lat = %7.2f, Lon = %7.2f \r\n",Lat,Lon);
	printf("UTC Date: %02i/%02i/%4i local time: %2i:%02i \r\n",month,day,year,(int)(UTHours+TZ),(int)UTMinutes);
	printf("Sun altitude = %7.2f, azimuth = %7.2f",alt,az);

	return 0;
}
