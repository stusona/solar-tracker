/* Solar tracker
 * Stuart Sonatina
 * 2019-09-21
 *
 */
#include "solar_tracker.h"

int main()
{
	wiringPiSetupPhys(); // start wiringPi
	IMU_sensor IMU;
	IMU.start_read_imu();	// start IMU
	// pinmode for motor control
	//pinMode(12, OUTPUT);
	//pinMode(XX, OUTPUT);

	float Lat = 37.9, Lon = -122.; // solar panel position on the earth
	Sun mySun;
	vec_t sunPosition = mySun.getPosition(Lat, Lon);
	printf("At Lat = %7.2f, Lon = %7.2f \n", Lat, Lon);
	printf("Sun position: %7.0f, %7.0f, %7.0f\n", sunPosition.x, sunPosition.y, sunPosition.z);
	//printf("Sun altitude = %7.2f, azimuth = %7.2f \n", elev, azi);

	int input;
	do
	{
		imu_t imu = IMU.read_fifo();
		printf("%7.0f, %7.0f, %7.0f\n", imu.yaw, imu.roll, imu.pitch);
		cout << "Type 1 to repeat, anything else to end" << endl;
		cin >> input;
	} while(input == 1);


	return 0;
}
