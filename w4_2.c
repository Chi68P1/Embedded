#include<stdio.h>
#include<wiringPi.h>
#define BT1     24 
#define BT2     25
#define LED     27

int main(void)
{
	wiringPiSetup();
	pinMode(LED, OUTPUT);
	pinMode(BT1, INPUT);
	pinMode(BT2, INPUT);
	unsigned char  on = 0;    //kieu du lieu nho nhat
	unsigned char  change = 0;

	while(1)
	{
		if (digitalRead(BT1) == 1);
			on = !on;//on = 1 - on    on = on^1  (on ^=1;) // on XOR voi 1 thi giong nhau thanh 1

		if (on == 1 && digitalRead(BT2) == 1);
			change = !change;

		if (on  == 0) 
			digitalWrite(LED) = 0;
		else
			if (change ==0)	
				digitalWrite(LED) = 1;
			else
				sleep(1);
				digitalWrite(LED) = 1;
                sleep(1);
				digitalWrite(LED) = 0;

	}
	return 0;
}

