#include<stdio.h>
#include<math.h>
#include<stdlib.h>

struct segment
{
	long long x,y;
	double ang;//辐角，在0到180（改记弧度）之间 
};

int compare(const void*p1,const void*p2)
{
	struct segment *a=(struct segment*)p1;
	struct segment *b=(struct segment*)p2;
	return a->ang>b->ang?1:-1;
}

struct segment templ[200005];
int top;//实际维数

struct point
{
	long long x,y;
};

struct point res[200005];//部分和 

int main()
{
	int n;
	scanf("%d",&n);
	int i;
	for(i=0;i<n;i++)
	{
		long long xa,ya,xb,yb; 
		scanf("%lld%lld%lld%lld",&xa,&ya,&xb,&yb);
		templ[top].x=xa-xb;
		templ[top].y=ya-yb;
		top++;
		if(templ[top-1].x==0&&templ[top-1].y==0)//重合则弃掉 
		{
			top--; 
		}
		else
		{
			if(templ[top-1].y<0)//规定向量总向上 
			{
				templ[top-1].y*=-1;
				templ[top-1].x*=-1;
			}
			else if(templ[top-1].y==0)//水平 
			{
				if(templ[top-1].x<0)//规定向右
				{
					templ[top-1].x*=-1;
				}
			}
			double rrr=templ[top-1].x*templ[top-1].x+templ[top-1].y*templ[top-1].y;
			templ[top-1].ang=acos(((double)templ[top-1].x)/sqrt((double)rrr));
		}
	}
	if(top==0)
	{
		printf("0\n");
		return 0;
	}
	qsort(templ,top,sizeof(struct segment),compare);//辐角从小到大
	res[0].x=0;
	res[0].y=-10000000000;
	for(i=1;i<=top;i++)
	{
		res[i].x=res[i-1].x+templ[i-1].x+templ[i-1].x;
		res[i].y=res[i-1].y+templ[i-1].y+templ[i-1].y;
	}
	res[top].x=(res[top].x+res[0].x)/2;
	res[top].y=(res[top].y+res[0].y)/2;
	unsigned long long ans=0;
	for(i=0;i<top;i++)
	{
		unsigned long long rlen=(res[top].x-res[i].x)*(res[top].x-res[i].x)+(res[top].y-res[i].y)*(res[top].y-res[i].y);//到中心距平方 
		if(ans<rlen)
		{
			ans=rlen; 
		}
	}
	printf("%llu\n",ans);
}
