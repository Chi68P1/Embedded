/*Bài 4: Ngẫu nhiên một trong 3 đèn R,G,B sáng mỗi 3s. Nếu trong 500ms người chơi kịp nhấn nút tương
ứng thì đèn led sẽ tắt và cả 3 đèn sẽ chớp nháy trong 1s. Nếu người chơi không kịp nhấn nút thì đèn tắt.
Kết quả sẽ được cập nhập trên terminal sau mỗi lần đèn sáng.*/

#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LED_R 0
#define LED_G 1
#define LED_B 2
#define BUTTON_R 3
#define BUTTON_G 4
#define BUTTON_B 5
#define BUTTON_RESET 6

int button_pins[3] = {BUTTON_R, BUTTON_G, BUTTON_B};

void toggle_led(int led_pin, int value) {
  digitalWrite(led_pin, value);
}

void toggle_all_leds(int value) {
  toggle_led(LED_R, value);
  toggle_led(LED_G, value);
  toggle_led(LED_B, value);
}

void flash_all_leds() {
  toggle_all_leds(LOW);
  delay(500);
  toggle_all_leds(HIGH);
  delay(500);
  toggle_all_leds(LOW);
  delay(500);
  toggle_all_leds(HIGH);
  delay(500);
  toggle_all_leds(LOW);
  delay(500);
}

void blink_led(int led_pin, int blink_time) {
  toggle_led(led_pin, HIGH);
  delay(blink_time);
  toggle_led(led_pin, LOW);
}

void flash_leds(int led_pins[], int num_leds, int blink_time) {
  for (int i = 0; i < num_leds; i++) {
    blink_led(led_pins[i], blink_time);
  }
}

void reset_button_callback() {
  toggle_all_leds(LOW);
}

void random_led() {
  int led_pin = rand() % 3;
  toggle_led(led_pin, HIGH);
  printf("LED %d is ON\n", led_pin);
}

void setup() {
  wiringPiSetup();
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(button_pins[i], INPUT);
  }

  pinMode(BUTTON_RESET, INPUT);
  wiringPiISR(BUTTON_RESET, INT_EDGE_RISING, reset_button_callback);

  srand(time(0));
}

int main() {
  setup();

  while (true) {
    random_led();

    int button_pressed = -1;
    int start_time = millis();
    while (millis() - start_time < 3000) {
      for (int i = 0; i < 3; i++) {
        if (digitalRead(button_pins[i]) == HIGH) {
          button_pressed = i;
          break;
        }
      }
      if (button_pressed != -1) {
        break;
      }
    }

    if (button_pressed == -1) {
      toggle_all_leds(LOW);
      printf("Time's up! No button pressed.\n");
    } else {
      toggle_led(button_pins[button_pressed], LOW);
      printf("Button %d pressed!\n", button_pressed);
      flash_all_leds();
    }

    delay(1000);
  }

  return 0;
}

/*#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LED_R 0
#define LED_G 1
#define LED_B 2
#define BUTTON_R 3
#define BUTTON_G 4
#define BUTTON_B 5
#define BUTTON_RESET 6

int button_pins[3] = {BUTTON_R, BUTTON_G, BUTTON_B};

void toggle_led(int led_pin, int value) {
  digitalWrite(led_pin, value);
}

void toggle_all_leds(int value) {
  toggle_led(LED_R, value);
  toggle_led(LED_G, value);
  toggle_led(LED_B, value);
}

void flash_all_leds() {
  toggle_all_leds(LOW);
  delay(500);
  toggle_all_leds(HIGH);
  delay(500);
  toggle_all_leds(LOW);
  delay(500);
  toggle_all_leds(HIGH);
  delay(500);
  toggle_all_leds(LOW);
  delay(500);
}

void blink_led(int led_pin, int blink_time) {
  toggle_led(led_pin, HIGH);
  delay(blink_time);
  toggle_led(led_pin, LOW);
}

void flash_leds(int led_pins[], int num_leds, int blink_time) {
  for (int i = 0; i < num_leds; i++) {
    blink_led(led_pins[i], blink_time);
  }
}

void reset_button_callback() {
  toggle_all_leds(LOW);
}

int get_random_led_pin() {
  return rand() % 3;
}

int get_pressed_button() {
  for (int i = 0; i < 3; i++) {
    if (digitalRead(button_pins[i]) == HIGH) {
      return i;
    }
  }
  return -1;
}

void play_game() {
  int led_pin = get_random_led_pin();
  toggle_led(led_pin, HIGH);
  printf("LED %d is ON\n", led_pin);

  int button_pressed = -1;
  int start_time = millis();
  while (millis() - start_time < 3000) {
    button_pressed = get_pressed_button();
    if (button_pressed != -1) {
      break;
    }
  }

  if (button_pressed == -1) {
    toggle_all_leds(LOW);
    printf("Time's up! No button pressed.\n");
  } else {
    toggle_led(button_pins[button_pressed], LOW);
    printf("Button %d pressed!\n", button_pressed);
    flash_all_leds();
  }
}

void setup() {
  wiringPiSetup();
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  for (int i = 0; i < 3; i++) {
    pinMode(button_pins[i], INPUT);
  }

  pinMode(BUTTON_RESET, INPUT);
  wiringPiISR(BUTTON_RESET, INT_EDGE_RISING, reset_button_callback);

  srand(time(0));
}

int main() {
  setup();

  while (true) {
    play_game();
    delay(1000);
  }

  return 0;
}
*/