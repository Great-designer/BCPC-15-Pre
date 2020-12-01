#include<stdio.h>
#include<string.h>

const long long MOD=998244353;

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

long long f[1005][1005];//点在n侧 
long long g[1005][1005];//点在m侧 

int main()
{
	long long n,m;
	scanf("%lld%lld",&n,&m);
	long long nn=QPow(n,MOD-2);
	long long mm=QPow(m,MOD-2);
	long long last=QPow(n+m,MOD-2);
	f[m][n]=g[m][n]=0;
	long long i;
	for(i=m;i>0;i--)
	{
		long long j;
		for(j=n;j>0;j--)
		{
			long long temp=QPow(n*m-i*j,MOD-2);//要高斯消元。原方程组 
			g[i][j]=(m*(n-j)%MOD*f[i][j+1]%MOD+j*(m-i)%MOD*g[i+1][j]%MOD+m*(n+j))%MOD*temp%MOD;//j/nf[i][j]+(n-j)/nf[i][j+1]+1
			f[i][j]=(n*(m-i)%MOD*g[i+1][j]%MOD+i*(n-j)%MOD*f[i][j+1]%MOD+n*(m+i))%MOD*temp%MOD;//i/mg[i][j]+(m-i)/mg[i+1][j]+1
		}
	}
	long long ans=((m*f[1][1]%MOD+n*g[1][1]%MOD)*last%MOD+1)%MOD;
	printf("%lld\n",ans);
}




