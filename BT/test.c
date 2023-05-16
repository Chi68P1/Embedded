#include <wiringPiSPI.h>
#include <stdio.h>
#include <stdint.h>

#define spi0 0
unsigned char buf[2];
uint8_t mssv[8] = {2,0,1,4,6,5,0,6};

void sendData(unsigned char address, unsigned char data){
buf[0] = address;
buf[1] = data;
wiringPiSPIDataRW(spi0, buf, 2);
}

void Init(void){
// decode mode 0x09FF
sendData(0x09, 0xFF);
// intensity 0x0A09
sendData(0x0A, 9);
//scAN limit
sendData(0x0B, 7);
// not shutdown, turn off display test
sendData(0x0C, 1);
sendData(0x0F, 0);
}

int main(void){
//setup SPI interface
wiringPiSPISetup(spi0, 10000000);
//set operational max for max7219
Init();
//display student number

for(int i=0; i<8; i++){
sendData(i+1, mssv[7-i]);
}
return 0;
}