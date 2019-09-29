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
void setHomeVec(vec_t v)
{
	homeVec = v;
}

/*
 * getHomeVec
 */
vec_t getHomeVec()
{
	return homeVec;
}
/*
 * setMotorPlane
 */
void setMotorPlane(vec_t v)
{
	planeVec = v;
}
/*
 * getHomeVec
 */
vec_t getHomeVec()
{
	return homeVec;
}
