#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <stdlib.h>

uint8_t color = 0;
uint8_t ds = 0;

uint8_t led[3]= {11, 13, 15};
uint8_t r[10] = {10, 0, 0, 10, 0, 10, 10};
uint8_t g[10] = {0, 10, 0, 10, 10, 10, 0};
uint8_t b[10] = {0, 0, 10, 10, 10, 0, 10};
uint8_t current_color = 0;
int current_brightness = 0;

int change_brightness() {
    static int direction = 10;
    current_brightness += direction;
    if (current_brightness == 100 || current_brightness == 0) {
        direction = -direction;
    }
    softPwmWrite(led[0], r[current_color] * current_brightness / 10);
    softPwmWrite(led[1], g[current_color] * current_brightness / 10);
    softPwmWrite(led[2], b[current_color] * current_brightness / 10);
    return current_brightness;
}

void change_color() {
    static int direction1 = 1;
    current_color += direction1;
    if (current_color == 10|| current_color == 0 ) {
        direction1 = -direction1;
    }
    softPwmWrite(led[0], r[current_color] * current_brightness / 10);
    softPwmWrite(led[1], g[current_color] * current_brightness / 10);
    softPwmWrite(led[2], b[current_color] * current_brightness / 10);
    delay(500);
}

void sang_den(float do_sang ,float r,float g,float b)
{
    softPwmWrite(led[0], (int)(do_sang*r/100));
    softPwmWrite(led[1], (int)(do_sang*g/100));
    softPwmWrite(led[2], (int)(do_sang*b/100));
}


void randNumGen(void){
    srand(time(NULL));
    uint8_t randNum = (rand() % 81) + 20;
    printf("\r%d", randNum);
    fflush(stdout);
    if (randNum <= 80)  {
        change_color();    
    }
    else    {
        printf("\nWARNING\n");
        fflush(stdout);
        printf("Nhap 'c' de reset: ");
        fflush(stdout);
        time_t start_time = time(NULL);
        while(1){
            if(difftime(time(NULL),start_time) >= 3){
                printf("\nYeu cau nhap lai do sang va mau sac:\n");
                fflush(stdout);
                return;
            }
            if(getchar() == 'c'){
                current_brightness = 0;
                current_color = 0;
                softPwmWrite(led[0], 0);
                softPwmWrite(led[1], 0);
                softPwmWrite(led[2], 0);
                return;
            }
        }
    }
}

int main(void)
{
    wiringPiSetupPhys();    

    float do_sang,r,g,b;
    for(int i=0;i<3;i++)
    {
        pinMode(led[i], OUTPUT);
        digitalWrite(led[i], LOW); 
        softPwmCreate(led[i], 0, 100);
    }

    while(1) {

        printf("Nhap do sang: ");
        scanf("%f %f %f %f", &do_sang, &r, &g, &b);
        sang_den(do_sang, r, g, b); 

        delay(1000);

        while(1) {
            randNumGen();
            //break;
        }
    }

    return 0;
}
