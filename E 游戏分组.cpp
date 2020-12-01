#include<stdio.h>
#include<string.h>
#include<algorithm>

using namespace std;

const long long MOD=998244353;
const long long ROOT=3;

long long QPow(long long bas,long long t)
{
    long long ret=1;
    for(;t;t>>=1,bas=(bas*bas)%MOD)
    {
        if(t&1LL)
        {
            ret=(ret*bas)%MOD;
        }
    }
    return ret;
}

long long GAM[20010];
long long FEG[20010];

void init()
{
	GAM[0]=1;
	long long i;
	for(i=1;i<20005;i++)
	{
		GAM[i]=(GAM[i-1]*i)%MOD;
	}
	FEG[20004]=QPow(GAM[20004],MOD-2);
	for(i=20003;i>=0;i--)
	{
		FEG[i]=(FEG[i+1]*(i+1))%MOD;
	}
}

long long rev[20005];

void NTT(long long A[],long long n,int inv)//数组A，长度n，逆变换（共轭）符号inv
{
	int bit=0;
	while((1<<bit)<n)
	{
		bit++;//根据数组长度n，确定单位根次数
	} 
	long long i; 
	for(i=0;i<n;i++)//初始化。rev数组存储位逆序置换
	{
	    rev[i]=(rev[i>>1]>>1)|((i&1)<<(bit-1));
		if(i<rev[i])
		{
			long long temp=A[i];
			A[i]=A[rev[i]];
			A[rev[i]]=temp;
		}
	}
	long long mid,j;
	for(mid=1;mid<n;mid<<=1)//mid是准备合并序列的长度的二分之一
	{
		long long now=mid<<1;//now是准备合并序列的长度 
		long long wn=QPow(ROOT,(MOD-1)/now);//单位根 
		if(inv==-1)
		{
			wn=QPow(wn,MOD-2);//逆变换时逆元
		}
		for(i=0;i<n;i+=now)//i是合并到了哪一位
		{
			long long w=1;
			for(j=0;j<mid;j++,w=1ll*w*wn%MOD)//蝴蝶变换
			{
				long long x=A[i+j];
				long long y=1ll*w*A[i+j+mid]%MOD;
				A[i+j]=(x+y)%MOD;
				A[i+j+mid]=(x-y+MOD)%MOD;
			}
		}
	}
	if(inv==-1)
	{ 
		long long p=QPow(n,MOD-2);
	    for(i=0;i<n;i++)
	    { 
	        A[i]=1LL*A[i]*p%MOD;
	    } 
	}
}

void Conv(long long a[],long long b[],int len)
{
	NTT(a,len,1);
	NTT(b,len,1);
	long long i;
	for(i=0;i<len;i++)
	{
		a[i]=a[i]*b[i]%MOD;
	}
	NTT(a,len,-1);
}

void derivative(long long h[],const int n,long long f[])
{
	long long i;
	for(i=1;i!=n;++i)
	{
		f[i-1]=(h[i]*i)%MOD;
	}
	f[n-1]=0;
}

void integrate(long long h[],const int n,long long f[])
{
	long long i;
	for(i=n-1;i;--i)
	{
		f[i]=(h[i-1]*((FEG[i]*GAM[i-1])%MOD))%MOD;
	}
	f[0]=0;
}

long long inv_t[20005];

void polyinv(long long h[],const int n,long long f[])
{
	memset(inv_t,0,sizeof(inv_t));
	std::fill(f,f+n+n,0);//后文exp调用的时候分段调用，这里不能memset 
	f[0]=QPow(h[0],MOD-2);
	int t;
	for(t=2;t<=n;t<<=1)
	{
		const int t2=t<<1;
		std::copy(h,h+t,inv_t);
		std::fill(inv_t+t,inv_t+t2,0);
		NTT(f,t2,1);
		NTT(inv_t,t2,1);
		long long i;
		for(i=0;i!=t2;++i)
		{
			f[i]=f[i]*((2LL-(f[i]*inv_t[i])%MOD+MOD)%MOD)%MOD;
		}
		NTT(f,t2,-1);
		std::fill(f+t,f+t2,0);
	}
}

long long ln_t[20005];

void polyln(long long h[],const int n,long long f[])
{
	memset(ln_t,0,sizeof(ln_t));
	const int t=n<<1;
	derivative(h,n,ln_t);
	std::fill(ln_t+n,ln_t+t,0);
	polyinv(h,n,f);
	Conv(ln_t,f,t);
	integrate(ln_t,n,f);
}

long long exp_t[20005];

void polyexp(long long h[],const int n,long long f[])//输入，输出 
{
	memset(exp_t,0,sizeof(exp_t));
	std::fill(f,f+n+n,0);//由于没被调用，这里可以换成memset。被调用时不可 
	f[0]=1;
	int t; 
	for(t=2;t<=n;t<<=1)
	{
		const int t2=t<<1;
		polyln(f,t,exp_t);//每次调用长度不同 
		exp_t[0]=(h[0]+1-exp_t[0]+MOD)%MOD;
		long long i;
		for(i=1;i!=t;++i)
		{
			exp_t[i]=(h[i]-exp_t[i]+MOD)%MOD;
		}
		std::fill(exp_t+t,exp_t+t2,0);
		Conv(f,exp_t,t2);
		std::fill(f+t,f+t2,0);
	}
}

int a[510];

long long func[20005];
long long wait[20005];

int main()
{
	init();
	int n,m;
	scanf("%d%d",&n,&m);
	int i;
	for(i=0;i<m;i++)
	{
		scanf("%d",&a[i]);
	}
	long long ans=GAM[n];
	memset(wait,0,sizeof(wait));
	for(i=0;i<m;i++)
	{
		wait[a[i]]=(wait[a[i]]+FEG[a[i]])%MOD;
	}
	memset(func,0,sizeof(func));
	polyexp(wait,2048,func);
	ans=(ans*func[n])%MOD;
	printf("%lld\n",ans);
}

