#include<stdio.h>
#include<stdlib.h>

 long long a[100005];//假想的数 
 long long b[100005];//用时部分和 
 long long qqqq[100005];//存储总时间

int compare(const void*a,const void*b)
{
	return *(long long*)a>*(long long*)b?1:-1;
}

int main()
{
	long long n,t,x,k;
	scanf("%lld%lld%lld%lld",&n,&t,&x,&k);
	long long i;
	for(i=1;i<=n;++i)
	{
		scanf("%lld",&a[i]);
	}
	qsort(a+1,n,sizeof(long long),compare);
	long long iii=0;//题数 
	long long S=0;//计算罚时 
	long long sum=0;//暂存总时间 
	for(i=1;i<=n&&(sum+x+a[i]<=t||sum+x+x<=t);++i)
	{
		if(a[i]<x)
		{
			sum+=x+a[i];//用时部分和 
			b[i]=b[i-1]+sum+k;//要加上用时部分和 
		}
		else
		{
			sum+=x*2;
			b[i]=b[i-1]+sum;
		}
		++iii;//存储题数 
		qqqq[i]=sum;
	}
	S=b[iii];//存储总时间。这里注意下标
	for(i=1;i<=iii&&a[i]<=x;++i)//对于a[i]落入x-k到x区间，可以更换策略使罚时变小 
	{
		long long ffff=iii-i;//存储修改的个数 
		if(qqqq[i]+2*x*ffff<=t&&S>(b[i]+(qqqq[i]+(ffff+1)*x)*ffff))//总时长不能炸，也不能得不偿失 
		{
			S=b[i]+(qqqq[i]+(ffff+1)*x)*ffff;
		}
	}
	printf("%lld %lld\n",iii,S);
}
