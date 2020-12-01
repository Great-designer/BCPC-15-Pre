#include<stdio.h>
#include<string.h>
#include<climits>
#include<queue>
#include<algorithm>

using namespace std;

long long point[200005];//�������� 
long long S[200005];//���겿�ֺ� 
unsigned long long delta[200005];//��� 
int nex[200005],pre[200005];//���� 

struct node
{
    int id;
    long long del;
    node(int id = 0, long long del = 0):id(id), del(del){}
    bool operator < (const node & o) const{
        return o.del < del;//����� 
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
            delta[i]=(long long)(point[i+1]-point[i]);//���
            S[i]=S[i-1]+point[i];//���ֺ� 
            nex[i]=i+1;
			pre[i]=i-1;
        }
        nex[n-1]=0;
		S[n]=S[n-1]+point[n];
        ans_max=(S[n]-S[n-k])-(S[k]-S[0]);
        for(i=1;i<n;++i)
		{
			pq.push(node(i,delta[i]));//��źͲ�� 
		}
        while(k--)
		{
            node temp=pq.top();//��С��ȡ�� 
			pq.pop();
            long long del=temp.del;//��� 
			int id=temp.id;//��� 
            if(del!=delta[id])//�����˲�һ�µ��������˵�����ﱻ��ֹ������������ѡ��һ�� 
			{
                ++k;
                continue;
            }
            ans_min+=del;//��Сֵ���Ӳ�� 
            int l_ban=pre[id];//���ڵ�������ֹ�������۵�����ȥ���ڵ� 
            pre[id]=pre[l_ban];
			nex[pre[id]]=id;
			int r_ban=nex[id];
            nex[id]=nex[r_ban];
			pre[nex[id]]=id;
            if(l_ban&&r_ban)//û��0 
			{
				delta[id]=delta[l_ban]+delta[r_ban]-delta[id];//����޸ģ�ʹ�÷���֮����ܺͲ���
			}
            else//��0�� 
			{
				delta[id]=0x3f3f3f3f;
			}
            delta[l_ban]=delta[r_ban]=0x3f3f3f3f;//���߸����� 
            pq.push(node(id,delta[id]));//������������ 
        }
        printf("Case #%d: %lld %lld\n",Case,ans_min,ans_max);
    }
}
