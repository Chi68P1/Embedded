/*
 */
//

#include <stdio.h>
#include <wiringPi.h>

#define BT1  24
#define BT2  25
#define LED  27

unsigned char isOn = 0; // 1: On, 0: Off
unsigned char mode = 0; // 1: always On, 0: blink

int main(void){
	// Khoi tao thu vien
	wiringPiSetup();

	// Khai bao IO
	pinMode(BT1, INPUT);
	pinMode(BT2, INPUT);
	pinMode(LED, OUTPUT);

	// Loop
	while (1){
		if(digitalRead(BT1) == 1){	// nhan nut BT1
			// Dao bien isOn
			isOn = ~isOn;
		}
		if(digitalRead(BT2) == 1){	// nhan nut BT2
			// Dao bien mode
			mode = ~mode;
		}
		if(isOn == 0){			// den Off
			digitalWrite(LED, LOW);
		}
		else{
			if(mode == 0){
				digitalWrite(LED, HIGH); // den On
			}
			else{
				digitalWrite(LED, HIGH); // den sang 250ms
				delay(250);
				digitalWrite(LED, LOW); // den tat 250ms
                delay(250);
			}
		}
	}
	return 0;
}
