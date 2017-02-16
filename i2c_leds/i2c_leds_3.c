/* i2c_leds.c - write I2C messages to led controller

  created 2/17/2015 BD
	updated 2/18/15
	- working, as does i2c_leds_wq.c
Tried a more correct bipolar level shifter (from NXP app note), still didn't work
Operating ATTiny85 from 3.3v, running Radio Shack leds directly from ATTiny85
	- added color sequencing
	updated 2/19/15
	- added above comments
	- added color ramping example

  updated 2/4/17 Troy
  - added mode 2, rgb input on cl

*/

#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

main(int argc, char *argv[])
{
	int file;
	char filename[20];
	int addr = 0x04; // 0b000 0100 7 bit address
	uint8_t buff[3];
	int ret;
	int i;
	int mode = 1;
	int j;
	int done = 0;
	
	sprintf(filename, "/dev/i2c-1");
	if((file = open(filename, O_RDWR)) < 0) {
		printf("Couldn't open %s\n", filename);
		exit(1);
	}

	if(ioctl(file, I2C_SLAVE, addr) < 0) {
		printf("ioctl failed\n");
		exit(2);
	}

	if(argc == 4) {
		mode = 2;
	}
	
	i = 0;
	j = 0;
	buff[0] = buff[1] = buff[2] = 0;
	
	while(!done) {

		switch(mode) {
		case 0:
			buff[0] = 20 * (i % 2) * (((i >> 3) % 2) + 1);
			buff[1] = 20 * ((i >> 1) % 2) * (((i >> 3) % 2) + 1);
			buff[2] = 20 * ((i >> 2) % 2) * (((i >> 3) % 2) + 1);
			break;

		case 1:
			buff[j] = (i >= 20) ? 39 - i : i;
			// printf("i: %d  buff[j]: %d\n", i, buff[j]);
			break;
			
		case 2:
			done = 1;
			for(i = 0; i < 3; i++) {
				buff[i] = atoi(argv[i + 1]);
			}
			break;
		}
	
		ret = write(file, buff, 3);
		if(ret != 3) {
			printf("Write returned wrong size: %d - %s\n", ret, strerror(errno));
			exit(3);
		}

		switch(mode) {
		case 0:
			if(++i > 15) {
				i = 0;
			}
			usleep(500000);
			break;

		case 1:
			if(++i >= 40) {
				i = 0;
				buff[0] = buff[1] = buff[2] = 0;
				if(++j > 2) {
					j = 0;
				}
			}
			usleep(100000);
			break;
		}

	}
}
