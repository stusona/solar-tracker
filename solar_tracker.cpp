/* Solar tracker
 * Stuart Sonatina
 * 2019-09-21
 *
 */
#include "solar_tracker.h"
using namespace std;
float angleBetweenVectors(vec_t vec1, vec_t vec2);

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
		} while(angleBetweenVectors(motorPlaneVec1, motorPlaneVec2) < pi/2);
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

/*
 * angleBetweenVectors
 *
 * Returns angle (in radians) between two 3D vectors
 */
float angleBetweenVectors(vec_t vec1, vec_t vec2)
{
	float dot = vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
	float mag1 = sqrt(vec1.x*vec1.x + vec1.y*vec1.y + vec1.z*vec.z);
	float mag2 = sqrt(pow(vec2.x,2) + pow(vec2.y,2) + pow(vec2.z,2));
	float angle = dot/(mag1*mag2);
	return angle;
}

/*
 * crossProduct
 *
 * Creates cross product of 2 vectors. Shamelessly copied from geeksforgeeks.
 */
void crossProduct(vec_t vect_A, vec_t vect_B, vec_t cross_P)
{
    cross_P.x = vect_A.y * vect_B.z - vect_A.z * vect_B.y;
    cross_P.y = vect_A.x * vect_B.z - vect_A.z * vect_B.x;
    cross_P.z = vect_A.x * vect_B.y - vect_A.y * vect_B.x;
}
