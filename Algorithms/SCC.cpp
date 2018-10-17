#include<bits/stdc++.h>
using namespace std;
const int N=100;
struct edge{int to,nxt;}e[N];
int head[N],n,ecnt;
int low[N],dfn[N],stk[N],sccno[N],size[N],top,dfs_clock,scc_cnt;
bool instk[N];
void addedge(int u,int v){
    e[++ecnt]=(edge){v,head[u]};head[u]=ecnt;
}
void dfs(int u){
	dfn[u]=low[u]=++dfs_clock;
    stk[++top]=u;instk[u]=1;
    for(int i=head[u],v;i;i=e[i].nxt)
        if(!dfn[v=e[i].to]){
			dfs(v);
			low[u]=min(low[u],low[v]);
		}else if(instk[v]){
            low[u]=min(low[u],dfn[v]);
        }
	if(dfn[u]==low[u])
		for(++scc_cnt;;){
			int x=stk[top--];
            instk[x]=0;
			sccno[x]=scc_cnt;
			++size[scc_cnt];
			if(x==u)break;
		}
}
void tarjan(){
    for(int i=1;i<=n;++i)
        if(!dfn[i])dfs(i);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        int u,v;
        scanf("%d %d",&u,&v);
        addedge(u,v);
    }
}