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
public:
	void motorForward(int speed);
	void motorBackward(int speed);
	void motorStop();
};
#endif
