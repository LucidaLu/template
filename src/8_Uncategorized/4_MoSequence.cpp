//By SiriusRen
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
const int N=1050000;
int n,m,a[N],cnt1,cnt2,Block,block[N],xx,yy,ans,sum[N],last[N],Ans[N];
char op[105];
struct Query{
    int L,R,time,id;
    Query(int LL,int RR,int TT,int II){
        L=LL,R=RR,time=TT,id=II;
    }Query(){}
}query[N];
struct Change{
    int position,color,lastcolor;
    Change(int II,int CC,int LL){
        position=II,color=CC,lastcolor=LL;
    }Change(){}
}change[N];
bool operator<(Query a,Query b){
    if(block[a.L]==block[b.L]){
        if(a.R!=b.R)return a.R<b.R;
        return a.time<b.time;
    }
    return block[a.L]<block[b.L];
}
void update(int x,int f){
    if(f==1){if(!sum[x])ans++;sum[x]++;}
    else if(f==-1){if(sum[x]==1)ans--;sum[x]--;}
}
int main(){
    scanf("%d%d",&n,&m);
    Block=(int)pow(n,2.0/3.0);
    for(int i=1;i<=n;i++)scanf("%d",&a[i]),last[i]=a[i],block[i]=(i-1)/Block+1;
    for(int i=1;i<=m;i++){
        scanf("%s%d%d",op,&xx,&yy);
        if(op[0]=='Q')query[++cnt1]=Query(xx,yy,cnt2,cnt1);
        else change[++cnt2]=Change(xx,yy,last[xx]),last[xx]=yy;
    }
    sort(query+1,query+1+cnt1);
    for(int L=1,R=0,i=1,T=0;i<=cnt1;i++){
        for(;T<query[i].time;T++){
            if(change[T+1].position>=L&&change[T+1].position<=R)
                update(a[change[T+1].position],-1),update(change[T+1].color,1); 
            a[change[T+1].position]=change[T+1].color;
        }
        for(;T>query[i].time;T--){
            if(change[T].position>=L&&change[T].position<=R)
                update(a[change[T].position],-1),update(change[T].lastcolor,1);
            a[change[T].position]=change[T].lastcolor;
        }
        for(;R<query[i].R;R++)update(a[R+1],1);
        for(;R>query[i].R;R--)update(a[R],-1);
        for(;L<query[i].L;L++)update(a[L],-1);
        for(;L>query[i].L;L--)update(a[L-1],1);
        Ans[query[i].id]=ans;
    }
    for(int i=1;i<=cnt1;i++)printf("%d\n",Ans[i]);
}

