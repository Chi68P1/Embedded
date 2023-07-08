
// Bài 2: Viết code để 4 nút nhấn điều khiển độ sáng của đèn, với BT1 -> sáng yếu nhất, BT4 sáng nhất. //

#include <stdio.h>
#include <wiringPi.h>

#define BT1  24
#define BT2  25
#define BT3  28
#define BT4  29
#define LED  27

int brightnessLevels[] = {25, 50, 75, 100}; // các mức độ sáng trong phần trăm
int currentLevel = 0; // mức độ sáng hiện tại
int numLevels = 4; // số mức độ sáng

int main(void){
        // Khoi tao thu vien
        wiringPiSetup();

        // Khai bao IO
        pinMode(BT1, INPUT);
        pinMode(BT2, INPUT);
        pinMode(BT3, INPUT);
        pinMode(BT4, INPUT);
        pinMode(LED, PWM_OUTPUT);

        // Vòng lặp
        while (1){
                if(digitalRead(BT1) == 1){      // nhan nut BT1
                        currentLevel = (currentLevel + 1) % numLevels; // lặp lại các mức độ sáng
                        pwmWrite(LED, brightnessLevels[currentLevel] * 10); // đặt mức độ sáng của LED
                        delay(100); // đợi để hạn chế bounce
                }
                else if(digitalRead(BT2) == 1){      // nhan nut BT2
                        currentLevel = (currentLevel + numLevels - 1) % numLevels; // lặp lại các mức độ sáng
                        pwmWrite(LED, brightnessLevels[currentLevel] * 10); // đặt mức độ sáng của LED
                        delay(100); // đợi để hạn chế bounce
                }
                else if(digitalRead(BT3) == 1){      // nhan nut BT3
                        currentLevel = 0; // đặt mức độ sáng về mức thấp nhất
                        pwmWrite(LED, brightnessLevels[currentLevel] * 10); // đặt mức độ sáng của LED
                        delay(100); // đợi để hạn chế bounce
                }
                else if(digitalRead(BT4) == 1){      // nhan nut BT4
                        currentLevel = numLevels - 1; // đặt mức độ sáng về mức cao nhất
                        pwmWrite(LED, brightnessLevels
