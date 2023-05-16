#include <stdio.h>
#include <wiringPi>
#include <wiringPiI2C>

int mpu;
void MPU() {
    
}


int main(void) {
    // setup I2C interface
    mpu = wiringPiI2CSetup(0x68);
    // initialize mpu 6050
    initMPU;
}