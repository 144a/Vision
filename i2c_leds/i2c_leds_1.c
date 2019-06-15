/* i2c_leds.c - write I2C messages to led controller

  created 2/17/2015 BD

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

sprintf(filename, "/dev/i2c-1");
if((file = open(filename, O_RDWR)) < 0) {
	printf("Couldn't open %s\n", filename);
	exit(1);
}

if(ioctl(file, I2C_SLAVE, addr) < 0) {
	printf("ioctl failed\n");
	exit(2);
} 

buff[0] = 20;
buff[1] = 0;
buff[2] = 0;

ret = write(file, buff, 3);
if(ret != 3) {
	printf("Write returned wrong size: %d - %s\n", ret, strerror(errno));
	exit(3);
}
}
