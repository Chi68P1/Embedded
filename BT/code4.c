//==================================================================================
// Moi 1s in ra mot so A. So nay la gia tri trung binh cua 10 so ngau nhien tu 0-100
//==================================================================================

#include<stdio.h>
#include<stdlib.h> // su dung ham random
#include<unistd.h> // su dung ham sleep

int main(void)
{
	while(1)
	{
		float avg = 0;
		for(int i=0;i<10;i++)
		{
			avg = avg+ rand() % 100;
		}
		avg = avg / 10.0; // gia tri trung binh

		printf("\r value:%.2f ",avg); // in de len gia tri cu
		fflush(stdout);               //

		sleep(1); //delay 1s

	}
	return 0;
}
