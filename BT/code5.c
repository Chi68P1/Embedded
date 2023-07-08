//==============================================
// In gia tri nhiet do CPU may tinh len man hinh
//==============================================

#include <stdio.h>
#include <unistd.h>
#include <time.h>    //time_t, struct tm, time, local time

int main(void)
{
	while(1)
	{
		FILE *tempfile;
		float temp;
		tempfile =  fopen("/sys/class/thermal/thermal_zone0/temp","r"); // lay data tu file
		fscanf(tempfile, "%f", &temp);
		temp = temp/1000; // don vi do C
		fclose(tempfile); // dong file

		// Xu ly thoi gian
		time_t rawtime;
		struct tm *ct;
		time (&rawtime);
		ct = localtime (&rawtime);

		//dd//mm//yyyy hh:mm:ss temp
		printf("\r %02d/%02d/%04d %02d:%02d:%02d temp:%.2f", ct->tm_mday, ct->tm_mon + 1, ct->tm_year + 1900, ct->tm_hour, ct->tm_min, ct->tm_sec, temp);
		fflush(stdout);

		// Tren google
		//printf("Current local time and date: %s Temp: %.2f", asctime(ct),temp);
		//fflush(stdout);

		sleep(1);
	}
	return 0;
}

