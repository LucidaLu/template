#include<bits/stdc++.h>
using namespace std;
const int N=100;
struct edge{int to,nxt;}e[N*2];
int head[N],n,ecnt;
int dfn[N],low[N],bccno[N],dfs_clock,bcc_cnt; 
bool iscut[N];
vector<int>bcc[N];
stack<pair<int,int> >stk;
void addedge(int u,int v){
    e[++ecnt]=(edge){v,head[u]};head[u]=ecnt;
    e[++ecnt]=(edge){u,head[v]};head[v]=ecnt;
}
void dfs(int u,int fa){
    low[u]=dfn[u]=++dfs_clock;
    int child=0;
    for(int i=head[u],v;i;i=e[i].nxt){
        if(!dfn[v=e[i].to]){
            stk.push(make_pair(u,v));
            ++child;
            dfs(v,u);
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]){
                iscut[u]=1;
                bcc[++bcc_cnt].clear();
                for(;;){
                    pair<int,int>x=stk.top();stk.pop();
                    if(bccno[x.first]!=bcc_cnt){
                        bcc[bcc_cnt].push_back(x.first);
                        bccno[x.first]=bcc_cnt;
                    }
                    if(bccno[x.second]!=bcc_cnt){
                        bcc[bcc_cnt].push_back(x.second);
                        bccno[x.second]=bcc_cnt;
                    }
                    if(x.first==u&&x.second==v)break;
                }
            }
        }else if(dfn[v]<dfn[u]&&v!=fa){
            stk.push(make_pair(u,v));
            low[u]=min(low[u],dfn[v]);
        }
    }
    if(fa<0&&child==1)iscut[u]=0;
}
void tarjan(){
    for(int i=1;i<=n;++i)
        if(!dfn[i])dfs(i,-1);
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        int u,v;
        scanf("%d %d",&u,&v);
        addedge(u,v);
    }
}