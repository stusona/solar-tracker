/*
 * Motor.h
 */
#ifndef MOTOR_H
#define MOTOR_H
#include "solar_tracker.h"

class Motor
{
private:
	int speed; // 0-100
	bool direction;
	vec_t homeVec; // should this default to current vec in fifo? Maybe the constructor sets it.
	vec_t planeVec;
public:
	Motor();
	void move(int speed);
	void stop();
	int home();
	void setHomeVec(vec_t v);
	vec_t getHomeVec();
	void setPlaneVec(vec_t v);
	vec_t getPlaneVec();
};
#endif
