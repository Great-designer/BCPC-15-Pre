#include<stdio.h>
#include<math.h>

int main()
{
	double x,y,a,b,c;
	scanf("%lf%lf%lf%lf",&x,&y,&a,&b);
	c=x+(1-1/sqrt(2))*a;
	printf("%lf",c);
}
