/*
 * solar_tracker.h
 */

#ifndef SOLAR_TRACKER_H
#define SOLAR_TRACKER_H

// constants
const int HOME_PIN = 7; // Phys 7 is GPIO 4

// Struct for vectors
struct vec_t
{
	float x, y, z;
};

// Struct for holding BNO055 return values
typedef struct imu_t
{
  float yaw, roll, pitch;
  float magX, magY, magZ;
//  float p, q, r;
//  int sys, gyro, accel, mag;
//  float x_acc, y_acc, z_acc;
} imu;

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
} pid_data_t;

// Holds constants and latest errors of single axis PID
extern pid_data_t motor_pid;

#endif
