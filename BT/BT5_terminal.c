/*Cho sơ đồ mạch bao gồm Rasp, Led RGB và Module 4 nút nhấn. Bài 5: Ban đầu cả 3 led đều tắt. Ngẫu nhiên led R sáng trong 1s rồi tắt. 
Người chơi được yêu cầu nhấn BT1 ngay sau khi led R sáng. Nếu người chơi kịp nhấn trong 1s, led R sẽ tắt, terminal hiển thị thời gian từ
lúc led R sáng cho đến khi BT1 được nhấn. Nếu người chơi không kịp nhấn, đèn đỏ sẽ tắt sau 1s, và
terminal hiển thị thông báo “...”. Sau khi led R tắt từ 1-3s, led R sẽ ngẫu nhiên sáng trở lại. Quá trình này
lặp đi lặp lại 10 lần. Sau 10 lần terminal hiển thị thời gian nhấn trung bình của người chơi.

Để giải quyết bài toán này, chúng ta sẽ cần sử dụng một số hàm và biến như sau:

    rand() để tạo ngẫu nhiên giá trị LED R sáng trong khoảng từ 1 đến 3 giây.
    digitalRead() để đọc trạng thái của nút nhấn BT1.
    millis() để đo thời gian trôi qua từ khi LED R được bật hoặc khi người chơi nhấn BT1.
    Biến led_r_on_time để lưu thời điểm bắt đầu LED R được bật.
    Biến button_pressed để lưu trạng thái nút nhấn BT1 (đã được nhấn hay chưa).
    Biến num_attempts để lưu số lần chơi.
    Biến total_time để lưu tổng thời gian của các lần chơi.
    Biến average_time để lưu thời gian trung bình của các lần chơi.*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LED_R 0
#define LED_G 1
#define LED_B 2
#define BUTTON 3

void toggle_led(int led_pin, int value) {
  digitalWrite(led_pin, value);
}

void flash_led(int led_pin, int flash_time) {
  toggle_led(led_pin, HIGH);
  delay(flash_time);
  toggle_led(led_pin, LOW);
  delay(flash_time);
}

void setup() {
  wiringPiSetup();
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  pinMode(BUTTON, INPUT);
  srand(time(0));
}

int main() {
  setup();

  int num_trials = 10;
  int sum_times = 0;
  for (int i = 0; i < num_trials; i++) {
    printf("Trial %d\n", i+1);
    int led_on_time = rand() % 3000 + 1000; // Random on time between 1-3s
    toggle_led(LED_R, HIGH);
    printf("LED R is ON\n");
    int button_pressed = -1;
    int start_time = millis();
    while (millis() - start_time < led_on_time) {
      if (digitalRead(BUTTON) == HIGH) {
        button_pressed = 1;
        break;
      }
    }
    int end_time = millis();
    if (button_pressed == -1) {
      printf("Time's up! No button pressed.\n");
      flash_led(LED_R, 500);
    } else {
      printf("Button pressed! Time: %d ms\n", end_time - start_time);
      toggle_led(LED_R, LOW);
    }
    sum_times += end_time - start_time;
    delay(rand() % 2000 + 1000); // Random off time between 1-3s
  }

  printf("Average time: %d ms\n", sum_times / num_trials);

  return 0;
}
