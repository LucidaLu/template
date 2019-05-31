#include<bits/stdc++.h>
using namespace std;
const int N=100;
struct edge{int to,nxt,flag;}e[N*2];
int head[N],n,ecnt=1;
int low[N],dfn[N],bccno[N],dfs_clock,bcc_cnt;
vector<pair<int,int> >bridge;
vector<int>bcc[N];
void addedge(int u,int v){
    e[++ecnt]=(edge){v,head[u],0};head[u]=ecnt;
    e[++ecnt]=(edge){u,head[v],0};head[v]=ecnt;
}
void dfs(int u,int fa){
	dfn[u]=low[u]=++dfs_clock;
    for(int i=head[u],v;i;i=e[i].nxt)
        if(!dfn[v=e[i].to]){
			dfs(v,u);
			low[u]=min(low[u],low[v]);
            if(low[v]>dfn[u]){
                bridge.push_back(make_pair(u,v));
                e[i].flag=e[i^1].flag=1;
            }
		}else if(dfn[v]<dfn[u]&&v!=fa){
            low[u]=min(low[u],dfn[v]);
        }
}
void dfs_(int u){
    bccno[u]=bcc_cnt;
    bcc[bcc_cnt].push_back(u);
    for(int i=head[u];i;i=e[i].nxt)
        if(!e[i].flag){
            dfs_(e[i].to);
        }
}
void tarjan(){
    for(int i=1;i<=n;++i)
        if(!dfn[i])dfs(i,-1);
    for(int i=1;i<=n;++i)
        if(!bccno[i]){
            ++bcc_cnt;
            dfs_(i);
        }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        int u,v;
        scanf("%d %d",&u,&v);
        addedge(u,v);
    }
}