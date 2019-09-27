/* Solar tracker
 * Stuart Sonatina
 * 2019-09-21
 *
 */
#include "solar_tracker.h"
using namespace std;

int main()
{
	wiringPiSetupPhys(); // start wiringPi
	// pinmode for motor control
	//pinMode(12, OUTPUT);
	//pinMode(XX, OUTPUT);
	IMU_sensor IMU;
	IMU.start_read_imu();	// start IMU

	Motor motor1;
	initializeMotorPlane() // TODO throw this under main() for now, then maybe put it in motor class?
	{
		motor1.home(); // TODO create this in the motor class
		motorPlaneVec1 = IMU.getMagPosition();
		do // TODO: currently blocking
		{
			motor1.moveForward();
			motorPlaneVec2 = IMU.getMagPosition();
		} while(angleBetweenVectors(motorPlaneVec1, motorPlaneVec2) < pi/2); // TODO create this function
		// define motor plane using the two vectors.
		motor1.setMotorPlane(motorPlaneVec1, motorPlaneVec2); // create this func in motor class
	}

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
