/*
Đây là mã nguồn để điều khiển mạch Rasp sử dụng thư viện wiringPi để điều khiển các chân GPIO.
Chương trình này sẽ lắng nghe các lần nhấn nút trên các chân 24 và 25. Nếu nút 1 được nhấn, đèn LED trên chân 27 sẽ chuyển sang chế độ bật hoặc tắt tùy thuộc vào trạng thái hiện tại của nó.
Nếu nút 2 được nhấn, đèn LED sẽ nhấp nháy hoặc giữ cho đến khi tắt tùy thuộc vào chế độ hiện tại của nó.
Lưu ý rằng trong mã nguồn này, chúng tôi giả định rằng các nút được kết nối với một điện trở kéo lên (pull-up resistor),
điều này có nghĩa là khi nút không được nhấn, đầu vào sẽ đọc là HIGH. Nếu các nút của bạn được kết nối khác cách, bạn có thể cần điều chỉnh mã nguồn tương ứng.
 */
// Nhan nut BT1 den sang, nhan lan nua den tat. Khi den sang nhan BT2 den nhap nhay, nhan lan nua den sang binh thuong.

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
