#include<stdio.h>

int father[100005];
int bbb[100005];
int top;

int findfa(int x)
{
    return (father[x]==x)?x:father[x]=findfa(father[x]);
}

void merge(int x,int y)
{
    father[x]=y;
}

int main()
{
	int n,m;
    scanf("%d%d",&n,&m);
    int u,v;
    int i;
    for(i=1;i<=n;i++)
	{
        father[i]=i;
    }
    for(i=1;i<=m;i++)
	{
        scanf("%d%d",&u,&v);
        if(findfa(u)!=findfa(v))
		{
            merge(father[u],father[v]);
        }
    }
    top=0;
    for(i=2;i<=n;i++)
	{
        if(findfa(1)!=findfa(i))
		{
			bbb[top]=i;
			top++;
            merge(father[1],father[i]);
        }
    }
    printf("%d\n",top);
    for(i=0;i<top;i++)
    {
    	printf("1 %d\n",bbb[i]);
	}
}

