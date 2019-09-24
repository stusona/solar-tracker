/*
 * Sun class
 */
#ifndef SUN_H
#define SUN_H
#include "solar_tracker.h"

class Sun
{
private:
	float elevation;
	float azimuth;
	const std::string currentDateTime();
public:
	Sun();
	void get_sun_pos(float latitude, float longitude, float *altitude, float *azimuth);
};
#endif
