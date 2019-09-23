/*
 * solar_position.h
 */

#ifndef SOLAR_TRACKER_H
#define SOLAR_TRACKER_H
#include <iostream>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdio.h>
#include <fstream>

using namespace std;

// Struct for holding BNO055 return values
typedef struct
{
  float yaw, roll, pitch;
  float p, q, r;
  int sys, gyro, accel, mag;
  float x_acc, y_acc, z_acc;
} imu_t;

/******************************************************************************
 * Function Prototypes
 ******************************************************************************/
void start_read_imu(); 
imu_t read_imu_fifo();
int initialize_sensors(void);
#endif


