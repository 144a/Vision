/* gyro_test.cpp - test the I2C gyro

	 created 3/27/15 BD

*/

#include <stdio.h>
#include <unistd.h> // sleep()

#include "PiGyro.h"

int main(int argc, char *argv[])
{
	PiGyro gyro;
	double t_start;

	printf("Reg 0: 0x%2.2X\n", gyro.GetReg0());
	printf("Temp: %6.2lf\n", gyro.GetTemp());
	t_start = gyro.GetTime();
	for(int i = 0; i < 10000; i++) {
		// sleep(1);
		gyro.WaitForValues();
		gyro.Update();
		printf("[%6.3lf] Angles: %6.2lf %6.2lf %6.2lf\n", gyro.GetTime() - t_start,
					 gyro.GetAngle(0), gyro.GetAngle(1), gyro.GetAngle(2));
	}


	gyro.Close();
}
