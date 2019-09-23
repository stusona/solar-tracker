/* Solar tracker
 * Stuart Sonatina
 * 2019-09-21
 *
 */
#include "solar_tracker.h"


int main()
{
	wiringPiSetupPhys(void);
	// pinmode for motor control
	//pinMode(12, OUTPUT);
	//pinMode(XX, OUTPUT);

	float Lat = 37.9, Lon = -122., TZ = -7;
	float elev, azi;

	Sun.get_sun_pos(Lat, Lon, &elev, &azi);

	printf("At Lat = %7.2f, Lon = %7.2f \n", Lat, Lon);
	printf("UTC Date: %02i/%02i/%4i UTC Time: %02i:%02i \n", month, day, year, UTHour, UTMinute);
	printf("Sun altitude = %7.2f, azimuth = %7.2f \n", elev, azi);

	initialize_sensors();
	imu_t imu = read_imu_fifo();
	do
	{
		printf("%7.2f, %7.2f, %7.2f\n", imu.yaw, imu.roll, imu.pitch);
		int input;
		cout << "Type 1 to repeat, anything else to end" << endl;
		cin >> input;
	} while(input == 1);


	return 0;
}
