/*
 * Motor.cpp
 */
#include "Motor.h"

/*
 * Motor constructor
 */
Motor::Motor()
{
	// TODO set home pin with this
}

/*
 * moveForward
 */
void Motor::move(int speed)
{
	// correct if speed out of range
	if(speed > 100)
		speed = 100;
	else if(speed < -100)
		speed = -100;
	// set direction
	if(speed >= 0)
		direction = 1;
	else
		direction = -1;

	// TODO map speed to PWM
}

/*
 * stop
 */
void Motor::stop()
{
	printf("Motor stop");
	direction = 0;
}
/*
 * home
 */
int Motor::home()
{
	move(-10);
	printf("Homing\n");
	while(digitalRead(HOME_PIN))
		usleep(1);
	stop();
	return 0;
}

/*
 * setHomeVec
 */
void Motor::setHomeVec(vec_t v)
{
	homeVec = v;
}

/*
 * getHomeVec
 */
vec_t Motor::getHomeVec()
{
	return homeVec;
}
/*
 * setPlaneVec
 */
void Motor::setPlaneVec(vec_t v)
{
	planeVec = v;
}
/*
 * getPlaneVec
 */
vec_t Motor::getPlaneVec()
{
	return planeVec;
}
