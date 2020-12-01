#include<stdio.h>

long long n,m,a[1001],jcqm[1001]={1},jcqn[1001]={1},nn=1;
long long dp[520][520]={1},jl[520][520]={1};

long long q_mul(long long a,long long b,long long mod)
{
    unsigned long long ans=(long double)a/mod*b;
    long long ret=(unsigned long long)a*b-(unsigned long long)ans*mod;
    ret%=mod;
    if(ret<0)
	{
		ret+=mod;
	}
    return ret%mod;
}

long long q_pow(long long a,long long b,long long mod)
{
    long long ans=1;
    while(b)
	{
        if(b&1)
		{
			ans=q_mul(ans,a,mod);
		}
        b>>=1;
        a=q_mul(a,a,mod);
    }
    return ans;
}

int main()
{
    scanf("%lld %lld",&n,&m);
    int i;
    for(i=1;i<=n;i++)
	{
        nn=nn*i%998244353;
        jcqm[i]=nn;
        jcqn[i]=q_pow(nn,998244353-2,998244353);
    }
    for(i=1;i<=m;i++)
	{
        scanf("%lld",&a[i]);
        jl[i][0]=1;
    }
    for(i=1;i<=m;i++)
	{
		int j;
        for(j=0;j<=n;j++)
		{
            if(jl[i-1][j])
			{
				dp[i][j]=dp[i-1][j],jl[i][j]=1;
			}
			int k;
            for(k=1;k*a[i]<=j;k++)
			{
                long long temp2=k*a[i];
				long long temp=j-temp2;
				long long temp1=n-temp;//temp2新选出来的 temp原来?temp1原来剩下?
                if(!jl[i-1][temp])
				{
					continue;
				}
                dp[i][j]=(dp[i][j]+q_mul(q_mul((q_mul(dp[i-1][temp],q_mul(jcqm[temp1],jcqn[temp1-temp2],998244353),998244353)),jcqn[k],998244353),q_pow(jcqn[a[i]],k,998244353),998244353))%998244353;
                jl[i][j]=1;
            }
        }
    }
    printf("%lld",dp[m][n]);
    return 0;
}
