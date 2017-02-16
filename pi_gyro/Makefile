
##
## 
##

INCLUDES=
# INCLUDES=-I/usr/src/linux-headers-3.9.9-030909-generic/include/
# INCLUDES=-Iinclude/

CROSS=$(TARGET)-
CPP = g++
CC = gcc
AR = ar
LD = ld
STRIP = strip

DEBUG_OPTION =
OPT = -g
LIBS= -lm
CFLAGS += -Wall $(OPT) 

APPS = gyro_test

all: $(APPS)

gyro_test: gyro_test.o PiGyro.o
	$(CPP)  $(CFLAGS) gyro_test.o PiGyro.o -o  $@ 
	@echo "make $@ finished on `date`"

%.o:	%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<

%.o:	%.cpp
	$(CPP) $(CFLAGS) $(INCLUDES) -c $<

clean:
	rm -f *.o $(APPS)



