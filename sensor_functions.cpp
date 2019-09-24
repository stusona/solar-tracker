/******************************************************************************
 * sensor_functions.cpp
 *
 * Initializing and reading sensors
******************************************************************************/
#include "solar_tracker.h"

/******************************************************************************
 * int initialize_sensors(void)
 *
 * Initializes the IMU
******************************************************************************/
int initialize_sensors(void)
{
	printf("Initializing sensors...\n");
	start_read_imu();	// start IMU
	printf("IMU data is being read\n\n");

	return 0;
}

///////////////////////////////////////////////////////////////////////////////
//															IMU Functions
///////////////////////////////////////////////////////////////////////////////
/******************************************************************************
 * void start_read_imu
 *
 * Starts read_imu.py code
******************************************************************************/
void start_read_imu(void)
{
  // Create flag for continuing
  bool success = false;
  while (!success)
  {
    // clear fifo file //
    std::FILE* fd = fopen("imu.fifo","w");
    fclose(fd);
    printf("\nCreated and cleared imu.fifo\n");

    printf("Starting read_imu.py\n");
    char cmd[100];
    strcpy(cmd,"nohup python -u read_imu.py > read_imu.log 2>&1 < /dev/null & exit");
    system(cmd);
    printf("Started IMU using system(cmd)\n");
    usleep(3000000); // sleep to let python scrip start up

    // Check whether the python script wrote anything
    std::ifstream pFile("imu.fifo");
    if(pFile.peek() == std::ifstream::traits_type::eof())
    {
      printf("\nERROR: -----> read_imu.py has NOT written to imu.fifo\n");
      printf("Retrying IMU initialization\n");
      // if it isn't printing values, restart initialization
    }
    else
    {
      printf("read_imu.py HAS written to imu.fifo\n");
      // success! continue
      printf("IMU Initialized\n");
      success = true;
    }
  }
  return;
}

/******************************************************************************
 * imu_t read_imu_fifo
 *
 * Reads IMU values from imu.fifo and write to the imu struct
******************************************************************************/
imu_t read_imu_fifo(void)
{
	imu_t imu;
	char buf[1000];
	FILE *fd = fopen( "imu.fifo", "r");
	fgets(buf,1000,fd);
	fclose(fd);
	sscanf(buf,"%f %f %f %f %f %f %i %i %i %i %f %f %f",
				 &imu.yaw,  &imu.roll,  &imu.pitch,
				 &imu.p,    &imu.q,     &imu.r,
				 &imu.sys,  &imu.gyro,  &imu.accel,
				 &imu.mag,  &imu.x_acc, &imu.y_acc, &imu.z_acc);

	return imu;
}
