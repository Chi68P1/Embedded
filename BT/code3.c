//================================================================
// Nhap toa do 3 diem bat ki .Tinh dien tich va in kq ra man hinh
//================================================================
#include<stdio.h>
#include<math.h> //gcc code3.c -o demo -lm (-lm de su dung thu vien math)

struct point
{
	int x;
	int y;
};
struct triangle
{
	float a;
	float b;
	float c;
	float area;
	float s;
};

struct point pt1,pt2,pt3;
struct triangle tr;

int main(void)
{
	// Input
	printf("nhap toa do 1:\n");
	scanf("%d %d",&pt1.x,&pt1.y);
	printf("Nhap toa do 2:\n");
	scanf("%d %d",&pt2.x,&pt2.y);
	printf("nhap toa do 3:\n");
	scanf("%d %d",&pt3.x,&pt3.y);

	// Tinh toan cong thuc herong
	tr.a = sqrt(pow(pt1.x-pt2.x,2)+pow(pt1.y-pt2.y,2)); // canh a
        tr.b = sqrt(pow(pt3.x-pt2.x,2)+pow(pt3.y-pt2.y,2)); // canh b
        tr.c = sqrt(pow(pt1.x-pt3.x,2)+pow(pt1.y-pt3.y,2)); // canh c
	tr.s = 0.5*(tr.a+tr.b+tr.c); // 1/2 chu vi
	tr.area = sqrt(tr.s*(tr.s-tr.a)*(tr.s-tr.b)*(tr.s-tr.c)); // dien tich

	//Output
	printf("%0.2f\n",tr.area);

	return 0;
}
