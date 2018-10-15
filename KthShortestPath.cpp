#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;
#define N 100200
int n,m,xx[N],yy[N],zz[N],tot,first[1005],next[N],v[N],w[N],s,e,k,h[1005],vis[1005];
void add(int x,int y,int z){w[tot]=z,v[tot]=y,next[tot]=first[x],first[x]=tot++;}
struct Node{int now,h,g;}jy;
priority_queue<Node>pq;
bool operator < (Node a,Node b){return a.g+a.h>b.g+b.h;}
void Dijkstra(){
	memset(h,0x3f,sizeof(h));
	h[e]=0,jy.now=e;
	pq.push(jy);
	while(!pq.empty()){
		Node t=pq.top();pq.pop();
		if(!vis[t.now])vis[t.now]=1;
		else continue;
		for(int i=first[t.now];~i;i=next[i])
			if(!vis[v[i]]&&h[v[i]]>h[t.now]+w[i]){
				h[v[i]]=h[t.now]+w[i];
				jy.now=v[i];jy.g=h[v[i]];
				pq.push(jy);
			}
	}
}
int A_star(){
	memset(vis,0,sizeof(vis));
	jy.now=s;jy.g=0;jy.h=h[s];
	pq.push(jy);
	while(!pq.empty()){
		Node t=pq.top();pq.pop();
		vis[t.now]++;
		if(vis[t.now]>k)continue;
		if(vis[e]==k)return t.g;
		for(int i=first[t.now];~i;i=next[i]){
			jy.now=v[i],jy.g=t.g+w[i],jy.h=h[jy.now];
			pq.push(jy);
		}
	}
	return -1;
}

int main(){
	memset(first,-1,sizeof(first));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&xx[i],&yy[i],&zz[i]),add(yy[i],xx[i],zz[i]);
	scanf("%d%d%d",&s,&e,&k);
	if(s==e)k++;
	Dijkstra();
	tot=0,memset(first,-1,sizeof(first));
	for(int i=1;i<=m;i++)add(xx[i],yy[i],zz[i]);
	printf("%d\n",A_star());
}

