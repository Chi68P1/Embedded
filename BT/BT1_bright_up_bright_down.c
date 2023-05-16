// Bài 1: Viết code để các đèn led R,G,B lần lượt sáng dần rồi tối dần. Thời gian sáng dần và tối dần là 2s.

#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include<unistd.h> // su dung ham sleep

#define s_pwm1 12
#define s_pwm2 16
#define s_pwm3 18

void lightUp(int s_pwm) // 1000ms
{
	for (int i = 0; i < 101; i++)
	{
		softPwmWrite(s_pwm, i);
		delay(10); //10ms
	}
}

void lightDown(int s_pwm) // 1000ms
{
	for (int i = 100; i > -1; i--)
	{
		softPwmWrite(s_pwm, i);
		delay(10); //10ms
	}
}

int main()
{
	// setup thư viện wiringPi
	wiringPiSetupPhys();
    
	// khai báo I/O
	softPwmCreate(s_pwm1, 0, 100); // (int pin, int initialValue, int pwmRange)
    softPwmCreate(s_pwm2, 0, 100); 
    softPwmCreate(s_pwm3, 0, 100); 

	while(1)
	{
        lightUp(s_pwm1);
		lightDown(s_pwm1);

		lightUp(s_pwm2);
		lightDown(s_pwm2);

		lightUp(s_pwm3);
		lightDown(s_pwm3);
	}
	return 0;
}

/*
#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>

#define s_pwm1 12
#define s_pwm2 16
#define s_pwm3 18

typedef int s_pwm;

void lightUp(s_pwm s_pwm_num)
{
    for (int i = 0; i < 101; i++)
    {
        softPwmWrite(s_pwm_num, i);
        usleep(20000); // sử dụng hàm usleep() để tạm dừng 20ms
    }
}

void lightDown(s_pwm s_pwm_num)
{
    for (int i = 100; i >= 0; i--)
    {
        softPwmWrite(s_pwm_num, i);
        usleep(20000); // sử dụng hàm usleep() để tạm dừng 20ms
    }
}

int main()
{
    wiringPiSetupPhys();
    softPwmCreate(s_pwm1, 0, 100);
    softPwmCreate(s_pwm2, 0, 100);
    softPwmCreate(s_pwm3, 0, 100);

    while (1)
    {
        lightUp(s_pwm1);
        lightDown(s_pwm1);

        lightUp(s_pwm2);
        lightDown(s_pwm2);

        lightUp(s_pwm3);
        lightDown(s_pwm3);
    }

    return 0;
}

*/
