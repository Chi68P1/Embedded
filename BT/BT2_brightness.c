
// Bài 2: Viết code để 4 nút nhấn điều khiển độ sáng của đèn, với BT1 -> sáng yếu nhất, BT4 sáng nhất. //

#include <stdio.h>
#include <wiringPi.h>

#define BT1  7
#define BT2  11
#define BT3  13
#define BT4  15
#define LED  12

//int brightnessLevels[] = {25, 50, 75, 100}; // các mức độ sáng 

int main(void)
{
        // Khoi tao thu vien
        wiringPiSetupPhys();

        // Khai bao IO
        pinMode(BT1, INPUT);
        pinMode(BT2, INPUT);
        pinMode(BT3, INPUT);
        pinMode(BT4, INPUT);
        pinMode(LED, PWM_OUTPUT);

        // set chế độ hoạt động cho module pwm0
        pwmSetMode(PWM_MODE_MS);
        pwmSetClock(15);
        pwmSetRange(128); // pwm frequency = 19.2 Mhz/(15x128)

        // Vòng lặp
        while (1)
        {

            if(digitalRead(BT1) == 1){      // nhan nut BT1
                    pwmWrite(LED, 32); // verylow
                    delay(100); // đợi để hạn chế bounce
            }
            else if(digitalRead(BT2) == 1){      // nhan nut BT2
                    pwmWrite(LED, 64; // low
                    delay(100); // đợi để hạn chế bounce
            }
            else if(digitalRead(BT3) == 1){      // nhan nut BT3
                    pwmWrite(LED, 96); // lmedium
                    delay(100); // đợi để hạn chế bounce
            }
            else if(digitalRead(BT4) == 1){      // nhan nut BT4
                    pwmWrite(LED, 128); // high
                    delay(100); // đợi để hạn chế bounce
            }
            else{
                do nothing;
            }
        
        }
}