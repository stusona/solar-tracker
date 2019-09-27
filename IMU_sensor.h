/*
 * IMU class
 */
#ifndef IMU_SENSOR_H
#define IMU_SENSOR_H
#include "solar_tracker.h"

class IMU_sensor
{
private:
	vec_t magPosition;
public:
	void start_read_imu(void);
	imu_t read_fifo(void);
	vec_t getMagPosition(void)
};
#endif
