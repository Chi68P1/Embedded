#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>


#define s_pwm1 12
#define s_pwm2 16
#define s_pwm3 18

void lightUpDown(int s_pwm) // 1000ms
{
	for (int i = 0; i < 101; i++)
	{
		softPwmWrite(s_pwm, i);
		delay(10); //10ms
	}
    for (int i = 100; i > -1; i--)
	{
		softPwmWrite(s_pwm, i);
		delay(10); //10ms
	}
}
void color(number)
    if (number ==1){
        softPwmWrite(s_pwm1, 100);
        softPwmWrite(s_pwm2, 100);
        softPwmWrite(s_pwm3, 100);
    }
    elif (number ==1){
        softPwmWrite(s_pwm1, 100);
        softPwmWrite(s_pwm2, 100);
        softPwmWrite(s_pwm3, 100);
    }


int main()
{
	// setup thư viện wiringPi
	wiringPiSetupPhys();

    float brn;
    float r,g,b;
    int maxr, maxg, maxb;

    printf("Nhap cac gia tri brightness r g b:");
    scanf("%f %f %f %f", &brn, &r, &g, &b);

	// khai báo I/O
	softPwmCreate(s_pwm1, 0, 100); // (int pin, int initialValue, int pwmRange)
    softPwmCreate(s_pwm2, 0, 100); 
    softPwmCreate(s_pwm3, 0, 100); 

	while(1)
	{
        softPwmWrite(s_pwm1, (brn*r/100));
        softPwmWrite(s_pwm2, (brn*r/100));
        softPwmWrite(s_pwm3, (brn*r/100));
	}
	return 0;
}