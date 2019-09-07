const int XN=4e4+11,XM=1e5+11;

std::vector<int> G[XN];
int lbd[XN],rbd[XN],dfs[XN*2],dc,block[XN*2],w[XN],par[XN][20],dep[XN],lg2[XN];
void DFS(int pos) {
	dep[pos]=dep[par[pos][0]]+1;
	for(int b=1;b<=lg2[dep[pos]];++b)
		par[pos][b]=par[par[pos][b-1]][b-1];
	dfs[lbd[pos]=++dc]=pos;
	for(int u : G[pos])
		if(!lbd[u]) {
			par[u][0]=pos;
			DFS(u);
		}
	dfs[rbd[pos]=++dc]=pos;
}

int LCA(int x,int y) {
	if(dep[x]<dep[y])
		std::swap(x,y);
	for(int len=dep[x]-dep[y],b=lg2[len];b>=0;--b)
		if(len>>b&1)
			x=par[x][b];
	if(x!=y) {
		for(int b=lg2[dep[x]];b>=0;--b)
			if(par[x][b]!=par[y][b]) {
				x=par[x][b];
				y=par[y][b];
			}
		x=par[x][0];
	}
	return x;
}

struct Query {
	int l,r,lca,*ans;
};

void Solve(std::vector<Query> &query) {
	std::sort(query.begin(),query.end(),[&](auto const &a,auto const &b)->bool {
		return block[a.l]==block[b.l]?(a.r<b.r)^(block[a.l]&1):block[a.l]<block[b.l];	
	});

	static int occ[XN],Ans;

	static auto Modify=[&](int c,int sig) {

	};

	static auto Update=[&](int pos,int sig) {
		Modify(w[pos],(occ[pos]+=sig)==1?1:-1);
	};

	int l=1,r=0;
	for(auto &q : query) {
		for(;l>q.l;Update(dfs[--l],1));
		for(;r<q.r;Update(dfs[++r],1));
		for(;l<q.l;Update(dfs[l++],-1));
		for(;r>q.r;Update(dfs[r--],-1));
		if(q.lca) {
			assert(occ[q.lca]==0);
			Modify(w[q.lca],1);
			*q.ans=Ans;
			Modify(w[q.lca],-1);
		} else
			*q.ans=Ans;
	}
}

void Prep() {
	DFS(1);
	static int Ans[XM];
	std::vector<Query> q;
	for(int i=1;i<=m;++i) {
		int u,v;cin>>u>>v;
		if(lbd[u]>lbd[v])
			std::swap(u,v);
		int lca=LCA(u,v);
		if(lca==u)
			q.push_back({lbd[u],lbd[v],0,&Ans[i]});
		else
			q.push_back({rbd[u],lbd[v],lca,&Ans[i]});
	}
	int size=sqrt(2*n);//can be modified
	for(int i=1;i<=2*n;++i)
		block[i]=(i-1)/size;
	Solve(q);
}
