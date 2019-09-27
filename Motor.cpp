/*
 * Motor.cpp
 */
#include "Motor.h"
#include "solar_tracker.h"

/*
 * Motor constructor
 */
Motor::Motor()
{ }

/*
 * moveForward
 */
void Motor::moveForward(int speed)
{
	// go forward
	//
}

/*
 * moveBackward
 */
void Motor::moveBackward(int speed)
{
	// go backward
}

/*
 * stop
 */
void Motor::stop()
{
	printf("Motor stop");
}
/*
 * home
 */
void Motor::home()
{
	moveBackward(10);
	printf("Homing\n");
	while(digitalRead(HOME_PIN))
	{
		usleep(1);
	}
	stop();
}

/*
 * setHomeVec
 */
void setHomeVec(vec_t homeVec);
{
	// TODO check if I need anything here
}

/*
 * getHomeVec
 */
vec_t getHomeVec();
{
	return homeVec;
}
