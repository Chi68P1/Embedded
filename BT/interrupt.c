#include <stdio.h>
#include <wiringPi.h>

#define Led 	12
#define BT 	    11

void xuly_ngat(void)
{
	if(digitalRead(BT)==1)
		digitalWrite(Led, HIGH);
	else
		digitalWrite(Led, LOW);
}

int main()
{
	// setup thư viện wiringPi
	wiringPiSetupPhys();
	// khai báo I/O
	pinMode(Led, OUTPUT);
	pinMode(BT, INPUT);
	
	// Interrupt
	wiringPiISR(BT,INT_EDGE_BOTH, &xuly_ngat);
	
	while(1)
	{

	}
	return 0;
}