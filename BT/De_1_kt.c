/*Cho so do mach gom Raspberry, 2 nut nhan BT1 va BT2 va den led RGB. Lap trinh de thuc hien cac tac vu sau:
a. Nhan BT1 de thay doi do sang cua LED. (3d)
b. Nhan BT2 de chuyen qua lai giua 2 che do. (5d)
	- chop tat LED o tan so 3Hz
	- chuyen mau qua lai giua cac mau - 10 mau
c. Nhan giu BT1 2s de tat LED (1d)

Code gon gang, comment day du. (1d)*/

#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdint.h>

#define BT1 23
#define BT2 24

int ledOn=0; 

uint8_t color = 0;
uint8_t ds = 0;

uint8_t led[3]= {16, 20, 21};
uint8_t r[10] = {10, 0  , 0  , 10, 0  ,10 ,10 ,0  ,5  ,5 };
uint8_t g[10] = {0 , 10 , 0  , 10, 10 ,10 , 0 ,5  ,10 ,0 };
uint8_t b[10] = {0 , 0  , 10 , 10, 10 ,0  ,10 ,10 ,0  ,10};

void ngat_bt1_color() //chinh do sang
{
    ds=ds+1;
    if (ds==10)
    {
        ds=0;
    }
}

void ngat_bt2_color() // 2 trang thai
{
    ledOn = !ledOn;
    softPwmWrite(led[0], 0 );
    softPwmWrite(led[1], 0 );
    softPwmWrite(led[2], 0 );
    while(1)
    {
        
        if(ledOn)
        {
            for(color=0;color<11;color++)
            {
                softPwmWrite(led[0], r[color]*ds );
                softPwmWrite(led[1], g[color]*ds );
                softPwmWrite(led[2], b[color]*ds );
                delay(1000);
            }
        }
        else
        {
            softPwmWrite(led[1], 10*ds );
            delay(167); // f = 3Hz
            softPwmWrite(led[1], 0 );
            delay(167);
        }
    }
}

int main(void)
{
    wiringPiSetupGpio();
    pinMode(BT1,INPUT);
    // Khai báo IO, tạo softpwm
    
    for(int i=0;i<3;i++)
    {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW); // tắt đèn led
    softPwmCreate(led[i], 0, 100);
    }

    // interrupt
    wiringPiISR(BT2, INT_EDGE_RISING, &ngat_bt2_color);
    wiringPiISR(BT1, INT_EDGE_RISING, &ngat_bt1_color);

    while (1)
    {   
    }

    return 0;
}


