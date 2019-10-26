struct Edge {
    int to,cap,v;
    Edge *rev;
};
std::list<Edge> G[XN];
std::list<Edge>::iterator curr[XN];
int dis[XN];
 
void AddEdge(int x,int y,int cap,int rev=0) {
    G[x].push_back({y,cap,0,0});
    G[y].push_back({x,rev,0,0});
    G[x].back().rev=&G[y].back();
    G[y].back().rev=&G[x].back();
}
 
int Dinic(int s,int t,int n) {
    auto BFS=[&]() {
        static int Q[XN];
        for(int i=1;i<=n;++i) {
            curr[i]=G[i].begin();
            dis[i]=-1;
        }
        int head=0,tail=0;
        Q[tail++]=s;dis[s]=0;
        while(head!=tail) {
            int pos=Q[head++];
            for(auto &[to,cap,v,rev] : G[pos])
                if(cap>v && dis[to]==-1) {
                    dis[to]=dis[pos]+1;
                    Q[tail++]=to;
                }
        }
        return dis[t]!=-1;
    };
 
    std::function<int(int,int)> DFS=[&](int pos,int mx)->int {
        if(pos==t)
            return mx;
        else {
            int tot=0;
            for(auto &e=curr[pos];e!=G[pos].end();++e)
                if(dis[pos]+1==dis[e->to] && e->cap>e->v) {
                    int f=DFS(e->to,std::min(mx-tot,e->cap-e->v));
                    e->v+=f;e->rev->v-=f;
                    if((tot+=f)==mx)
                        return tot;
                }
            return tot;
        }
    };
 
    int flow=0;
    for(;BFS();flow+=DFS(s,1e9));
    return flow;
}
