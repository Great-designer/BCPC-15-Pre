#include<stdio.h>
#include<stdlib.h>

 long long a[100005];//������� 
 long long b[100005];//��ʱ���ֺ� 
 long long qqqq[100005];//�洢��ʱ��

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
	long long iii=0;//���� 
	long long S=0;//���㷣ʱ 
	long long sum=0;//�ݴ���ʱ�� 
	for(i=1;i<=n&&(sum+x+a[i]<=t||sum+x+x<=t);++i)
	{
		if(a[i]<x)
		{
			sum+=x+a[i];//��ʱ���ֺ� 
			b[i]=b[i-1]+sum+k;//Ҫ������ʱ���ֺ� 
		}
		else
		{
			sum+=x*2;
			b[i]=b[i-1]+sum;
		}
		++iii;//�洢���� 
		qqqq[i]=sum;
	}
	S=b[iii];//�洢��ʱ�䡣����ע���±�
	for(i=1;i<=iii&&a[i]<=x;++i)//����a[i]����x-k��x���䣬���Ը�������ʹ��ʱ��С 
	{
		long long ffff=iii-i;//�洢�޸ĵĸ��� 
		if(qqqq[i]+2*x*ffff<=t&&S>(b[i]+(qqqq[i]+(ffff+1)*x)*ffff))//��ʱ������ը��Ҳ���ܵò���ʧ 
		{
			S=b[i]+(qqqq[i]+(ffff+1)*x)*ffff;
		}
	}
	printf("%lld %lld\n",iii,S);
}
