/*
 * Sun class
 */
#ifndef SUN_H
#define SUN_H
#include "solar_tracker.h" 

class Sun
{
private:
	vec_t position;
	const std::string currentDateTime();
public:
	Sun(); // TODO maybe add lat/long to this constructor
	vec_t getPosition(float latitude, float longitude);
};
#endif
