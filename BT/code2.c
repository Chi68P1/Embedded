// Tinh trung binh 2 so nguyen
#include <stdio.h>

int main(void)
{
	float c,a,b;
	//printf("Enter 2 integers, seperate by a space\n");
  	//scanf("%d %d",&a,&b);
	printf("Nhap a:\n");
	scanf("%f",&a);

	printf("Nhap b:\n");
	scanf("%f",&b);

	c = (a+b)/2;

	printf("trung binh cua hai so la:%.2f \n",c); // %.2f lay 2 gia tri thap phan
	return 0;
}
