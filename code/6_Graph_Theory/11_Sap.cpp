struct Edge {
	int to,cap,v;
	Edge *rev;
};
std::list<Edge> G[XN];
std::list<Edge>::iterator curr[XN];

void AddEdge(int x,int y,int cap) {
	G[x].push_back({y,cap,0,0});
	G[y].push_back({x,0,0,0});
	G[x].back().rev=&G[y].back();
	G[y].back().rev=&G[x].back();
}

long long Sap(int s,int t,int n) {
	static int dep[XN],gap[XN];
	std::function<int(int,int)> DFS=[&](int pos,int mx)->int {
		if(pos==t)
			return mx;
		else {
			int tot=0;
			for(auto &e=curr[pos];e!=G[pos].end();++e)
				if(dep[pos]==dep[e->to]+1 && e->cap>e->v) {
					int f=DFS(e->to,std::min(mx-tot,e->cap-e->v));
					e->v+=f;e->rev->v-=f;
					if((tot+=f)==mx)
						return tot;
				}
			if(!--gap[dep[pos]++])
				dep[s]=n+1;
			++gap[dep[pos]];
			curr[pos]=G[pos].begin();
			return tot;
		}
	};
	for(int i=1;i<=n;++i)
		curr[i]=G[i].begin();
	long long flow=0;
	for(gap[0]=n;dep[s]<=n;flow+=DFS(s,std::numeric_limits<int>::max()));
	return flow;
}
