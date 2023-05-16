/*Cho so do mach gom Raspberry va den led RGB. Lap trinh de thuc hien cac tac vu sau:
a. Yeu cau nguoi su dung nhap 1 lan 4 gia tri do sang va mau sac theo format: "do_sang r g b", 
sau do hien thi dung mau sac va do sang duoc nhap. (3d)
b. Chuyen qua lai giua 2 che do moi 2s-3s (thoi gian set ngau nhien). (5d)
	- tang giam do sang
	- chuyen mau qua lai giua cac mau - 10 mau
	Yeu cau giu duoc mau sac/do sang khi doi che do
c. Them chuc nang nhap thoi gian on/off cho he thong theo thoi gian thuc luc bat dau chay chuong trinh. (1d)
	vd: nhap "off 15:13" chuong trinh se off luc 15h13
	
Code gon gang, comment day du. (1d)*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <softPwm.h>
#include <wiringPi.h>
#include <time.h>

#define LEDR 0
#define LEDG 1
#define LEDB 2

uint8_t led[3]= {LEDR, LEDG, LEDB};
float brn, r, g, b;

uint8_t red[10]   = {10 , 0  , 0  , 10, 0  ,10 ,10 ,0  ,5  ,5 };
uint8_t green[10] = {0  , 10 , 0  , 10, 10 ,10 ,0  ,5  ,10 ,0 };
uint8_t blue[10]  = {0  , 0  , 10 , 10, 10 ,0  ,10 ,10 ,0  ,10};

// cau a
void brightness() {
    softPwmWrite(led[0], round(brn * r / 100.0)); // softpwm can dau vao la int
    softPwmWrite(led[1], round(brn * g / 100.0));
    softPwmWrite(led[2], round(brn * b / 100.0));
}

// cau b
void getTimeRandom() {
	return (rand() % 3)*1000;
}

void brightnessUpDown() {
	for (int i = 0; i < 101; i++)
	{
		softPwmWrite(led[0], i);
		softPwmWrite(led[1], i);
		softPwmWrite(led[2], i);
		delay(10); //10ms
	}
    for (int i = 100; i > -1; i--)
	{
		softPwmWrite(led[0], i);
		softPwmWrite(led[1], i);
		softPwmWrite(led[2], i);
		delay(10); //10ms
	}
}

void changeColor() {
	for (int i = 0; i < 10; i++)
	{
		softPwmWrite(led[0], red[i]); // softpwm can dau vao la int
    	softPwmWrite(led[1], green[i]);
    	softPwmWrite(led[2], blue[i]);
	}
}

void changeMode() {
	brightnessUpDown()
	delay(getTimeRandom());
	changeColor()
	delay(getTimeRandom());
}

// cau c
void scheduleOnOff() {
    char status[4];
    char timeStr[6];
    int hour, minute;
    time_t now;
    struct tm *tm_info;
    time(&now);
    tm_info = localtime(&now);
    strftime(timeStr, 6, "%H:%M", tm_info);

    printf("Nhap thoi gian va trang thai (on/off) theo format: status hh:mm\n");
    scanf("%s %d:%d", status, &hour, &minute);
    char inputStr[6];
    sprintf(inputStr, "%d:%d", hour, minute);
    if (strcmp(status, "on") == 0 && strcmp(inputStr, timeStr) == 0) {
        // bật hệ thống
    } else if (strcmp(status, "off") == 0 && strcmp(inputStr, timeStr) == 0) {
        // tắt hệ thống
    }
}


int main(void)
{
    // setup thư viện wiringPi
    wiringPiSetup();

    // khai báo I/O va softpwm
	for(int i=0; i<3; i++)
    {
        pinMode(led[i], OUTPUT);
        digitalWrite(led[i], LOW); // tat led khi start
        softPwmCreate(led[i], 0, 100);
    }

    while(1)
    {
        printf("Nhap gia tri theo format: do_sang r g b\n");
        scanf("%f %f %f %f",&brn, &r, &g, &b );  
        brightness(); // neu khong nhap cac gia tri brn, r, g, b = 0

		changeMode()

		scheduleOnOff();
    }
    return 0;
}


