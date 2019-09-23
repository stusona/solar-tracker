/*
 * solar_tracker.h
 */

#ifndef SOLAR_TRACKER_H
#define SOLAR_TRACKER_H
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <wiringPi.h>
#include "Motor.h"
#include "Sun.h"

using namespace std;

// Struct for PID Controllers
typedef struct pid_data_t
{
	float kp, ki, kd;
	float perr, ierr, derr;
	float setpoint;
	float output;
	float old;
	float sat;
	float dt;
	float isat;
	float period;
}pid_data_t;

// Holds constants and latest errors of single axis PID
extern pid_data_t motor_pid;

#endif
