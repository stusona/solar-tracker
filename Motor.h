/*
 * Motor.h
 */
#ifndef MOTOR_H
#define MOTOR_H

class Motor
{
private:
	int speed; // 0-100
	bool direction;
	vec_t homeVec; // should this default to current vec in fifo? Maybe the constructor sets it.
public:
	Motor();
	void moveForward(int speed);
	void moveBackward(int speed);
	void stop();
	int home();
	void setHomeVec(vec_t homeVec);
	vec_t getHomeVec();
};
#endif
