//By SiriusRen
#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N=100050;
int n,m,q,xx,yy,Block,block[N],cnt=1,fa[N][20],tot,top,cnt1,cnt2,op,num[N];
int first[N],next[N*2],v[N*2],C[N],stk[N],deep[N],V[N],W[N],last[N],vis[N];
typedef long long ll;ll Ans[N],ans;
struct Query{
    int l,r,lca,id,time;Query(){}
    Query(int ll,int rr,int zz,int ii,int tt){l=ll,r=rr,lca=zz,id=ii,time=tt;}
    friend bool operator<(Query a,Query b){
        if(block[a.l]==block[b.l]){
            if(block[a.r]==block[b.r])return a.time<b.time;
            return block[a.r]<block[b.r];
        }
        return block[a.l]<block[b.l];
    }
}query[N];
struct Change{
    int position,color,lastcolor;Change(){}
    Change(int pp,int cc,int ll){position=pp,color=cc,lastcolor=ll;}
}change[N];
void add(int x,int y){v[tot]=y,next[tot]=first[x],first[x]=tot++;}
void dfs(int x){
    for(int i=first[x];~i;i=next[i])if(v[i]!=fa[x][0])
        fa[v[i]][0]=x,deep[v[i]]=deep[x]+1,dfs(v[i]);
    stk[++top]=x;
    if(top==Block){
        for(int i=1;i<=top;i++)block[stk[i]]=cnt;
        top=0,cnt++;
    }
}
int lca(int x,int y){
    if(deep[x]<deep[y])swap(x,y);
    for(int i=19;i>=0;i--)if(deep[x]-(1<<i)>=deep[y])x=fa[x][i];
    if(x==y)return x;
    for(int i=19;i>=0;i--)if(fa[x][i]!=fa[y][i])x=fa[x][i],y=fa[y][i];
    return fa[x][0];
}
void reverse(int x){
    if(vis[x])ans-=(ll)V[C[x]]*W[num[C[x]]],num[C[x]]--;
    else num[C[x]]++,ans+=(ll)V[C[x]]*W[num[C[x]]];
    vis[x]^=1;
}
void change_color(int x,int y){
    if(vis[x])reverse(x),C[x]=y,reverse(x);
    else C[x]=y;
}
void work(int x,int y){
    while(x!=y){
        if(deep[x]<deep[y])swap(x,y);
        reverse(x),x=fa[x][0];
    }
}
int read(){
    char p=getchar();int x=0;
    while(p<'0'||p>'9')p=getchar();
    while(p>='0'&&p<='9')x=x*10+p-'0',p=getchar();
    return x;
}
int main(){
    memset(first,-1,sizeof(first));
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++)V[i]=read();
    for(int i=1;i<=n;i++)W[i]=read();
    Block=pow(n,2.0/3.0)*0.5;
    for(int i=1;i<n;i++)xx=read(),yy=read(),add(xx,yy),add(yy,xx);
    deep[1]=1,dfs(1);
    for(int i=1;i<=top;i++)block[stk[i]]=cnt;
    for(int j=1;j<=19;j++)
        for(int i=1;i<=n;i++)
            fa[i][j]=fa[fa[i][j-1]][j-1];
    for(int i=1;i<=n;i++)C[i]=read(),last[i]=C[i];
    for(int i=1;i<=q;i++){
        op=read(),xx=read(),yy=read();
        if(op){
            if(block[xx]>block[yy])swap(xx,yy);
            query[++cnt1]=Query(xx,yy,lca(xx,yy),cnt1,cnt2);
        }
        else change[++cnt2]=Change(xx,yy,last[xx]),last[xx]=yy;
    }
    sort(query+1,query+1+cnt1);
    for(int i=1,T=0;i<=cnt1;i++){
        for(;T<query[i].time;T++)change_color(change[T+1].position,change[T+1].color);
        for(;T>query[i].time;T--)change_color(change[T].position,change[T].lastcolor);
        if(i==1)work(query[i].l,query[i].r);
        else work(query[i-1].l,query[i].l),work(query[i-1].r,query[i].r);
        reverse(query[i].lca),Ans[query[i].id]=ans,reverse(query[i].lca);
    }
    for(int i=1;i<=cnt1;i++)printf("%lld\n",Ans[i]);
}
