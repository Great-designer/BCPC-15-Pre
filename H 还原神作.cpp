#include<stdio.h>
#include<string.h>
#include<climits>
#include<queue>
#include<algorithm>

using namespace std;

long long point[200005];//读入坐标 
long long S[200005];//坐标部分和 
unsigned long long delta[200005];//差分 
int nex[200005],pre[200005];//链表 

struct node
{
    int id;
    long long del;
    node(int id = 0, long long del = 0):id(id), del(del){}
    bool operator < (const node & o) const{
        return o.del < del;//按差分 
    }
};

priority_queue<node> pq;

void init()
{
    memset(point,0,sizeof(point));
    memset(delta,0,sizeof(delta));
    memset(S,0,sizeof(S));
    memset(nex,0,sizeof(nex));
    memset(pre,0,sizeof(pre));
}

int main()
{
	int T,Case;
	scanf("%d",&T);
    for(Case=1;Case<=T;++Case)
	{
		init();
        while(!pq.empty())
		{
			pq.pop();
		}
		int n,k;
		scanf("%d",&n);
		scanf("%d",&k);
		long long ans_min=0;
		long long ans_max=0;
		int i;
        for(i=1;i<=n;++i)
		{
			scanf("%lld",&point[i]); 
		}
        sort(point+1,point+n+1);
        S[0]=0; 
        for(i=1;i<n;++i)
		{
            delta[i]=(long long)(point[i+1]-point[i]);//差分
            S[i]=S[i-1]+point[i];//部分和 
            nex[i]=i+1;
			pre[i]=i-1;
        }
        nex[n-1]=0;
		S[n]=S[n-1]+point[n];
        ans_max=(S[n]-S[n-k])-(S[k]-S[0]);
        for(i=1;i<n;++i)
		{
			pq.push(node(i,delta[i]));//编号和差分 
		}
        while(k--)
		{
            node temp=pq.top();//最小的取出 
			pq.pop();
            long long del=temp.del;//差分 
			int id=temp.id;//编号 
            if(del!=delta[id])//出现了不一致的情况，则说明这里被禁止。丢掉，接着选下一个 
			{
                ++k;
                continue;
            }
            ans_min+=del;//最小值增加差分 
            int l_ban=pre[id];//相邻的两个禁止，从讨论的链表去掉节点 
            pre[id]=pre[l_ban];
			nex[pre[id]]=id;
			int r_ban=nex[id];
            nex[id]=nex[r_ban];
			pre[nex[id]]=id;
            if(l_ban&&r_ban)//没到0 
			{
				delta[id]=delta[l_ban]+delta[r_ban]-delta[id];//差分修改，使得反悔之后的总和不变
			}
            else//到0了 
			{
				delta[id]=0x3f3f3f3f;
			}
            delta[l_ban]=delta[r_ban]=0x3f3f3f3f;//两边改无穷 
            pq.push(node(id,delta[id]));//重新塞进堆里 
        }
        printf("Case #%d: %lld %lld\n",Case,ans_min,ans_max);
    }
}
