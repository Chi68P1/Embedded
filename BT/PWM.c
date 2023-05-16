#include <stdio.h>
#include <wiringPi.h>

#define pwm0 12

int main()
{
	// setup thư viện wiringPi
	wiringPiSetupPhys();
	// khai báo I/O
	pinMode(pwm0, PWM_OUTPUT);
	
	// set chế độ hoạt động cho module pwm0
	pwmSetMode(PWM_MODE_MS);
	pwmSetClock(15);
	pwmSetRange(128); // pwm frequency = 19.2 Mhz/(15x128)

	// xuất xung 50%
	pwmWrite(64);

	return 0;
}
===================================================================
#include <stdio.h>
#include <softPwm.h>
#include <wiringPi.h>

#define s_pwm 12

int main()
{
	// setup thư viện wiringPi
	wiringPiSetupPhys();
	// khai báo I/O
	softPwmCreate(s_pwm, 30, 100); // (pin, giá trị đầu, max)
	softPwmWrite(s_pwm, 70); //(pin, giá trị mong muốn)
	
	while(1)
	{
	
	}
	return 0;
}