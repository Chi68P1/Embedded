/*Để tạo một thư viện riêng cho hàm setup(), bạn có thể thực hiện các bước sau:

    Tạo một tệp header mới với tên my_setup.h.
    Trong tệp my_setup.h, định nghĩa hàm my_setup() và đặt mã của hàm setup() vào đó.
    Để sử dụng hàm my_setup() trong chương trình chính, bạn cần bao gồm tệp my_setup.h bằng cách thêm đoạn mã #include "my_setup.h" vào đầu chương trình.
*/

#ifndef MY_SETUP_H_
#define MY_SETUP_H_

#include <wiringPi.h>

#define LED_R 0
#define LED_G 1
#define LED_B 2
#define BUTTON 3

void my_setup() {
  wiringPiSetup();
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUTTON, INPUT);
}

#endif // MY_SETUP_H_
