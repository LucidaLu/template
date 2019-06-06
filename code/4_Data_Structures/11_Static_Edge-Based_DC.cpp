namespace StaticEdgeBasedDC {
	int vtc,n;

	struct Edge {
		int to,v;
		Edge *pre,*rev;
		bool ban;

		Edge(int to,int v,Edge *pre):to(to),v(v),pre(pre),ban(0) {}

	}*G[XN],*oG[XN];

	void AddEdge(Edge *G[],int x,int y,int v) {
		G[x]=new Edge(y,v,G[x]);
		G[y]=new Edge(x,v,G[y]);
		G[x]->rev=G[y];
		G[y]->rev=G[x];
	}

	void Rebuild(int pos,int fa) {
		int cur=pos,cnt=0;
		for(Edge *e=oG[pos];e;e=e->pre)
			if(e->to!=fa) {
				int u=e->to;
				if(++cnt==2) {
					cnt=0;
					AddEdge(G,cur,vtc,0);
					cur=vtc;
				}
				AddEdge(G,cur,u,1);
				Rebuild(u,pos);
			}
	}

	int size[XN];

	int GetSize(int pos,int fa) {
		size[pos]=1;
		for(Edge *e=G[pos];e;e=e->pre)
			if(!e->ban && e->to!=fa) {
				int u=e->to;
				size[pos]+=GetSize(u,pos);
			}
		return size[pos];
	}

	std::pair<int,Edge*> Bridge(int pos,int fa,int tol) {
		std::pair<int,Edge*> res=std::pair<int,Edge*>(INF,0);
		for(Edge *e=G[pos];e;e=e->pre)
			if(!e->ban && e->to!=fa) {
				int u=e->to;
				Reduce(res,std::min(Bridge(u,pos,tol),
							std::pair<int,Edge*>(std::max(size[u],tol-size[u]),e)));
			}
		return res;
	}

	long long DC(Edge *brg) {
		if(!brg)
			return 0;
		else {
			brg->ban=brg->rev->ban=1;
			int x=brg->to,y=brg->rev->to;
			long long res=Calc();
			Enlarge(res,std::max(DC(Bridge(x,0,GetSize(x,0)).second),
						DC(Bridge(y,0,GetSize(y,0)).second)));
			return res;
		}
	}

	long long Run() {
		Rebuild(1,0);
		return DC(Bridge(1,0,GetSize(1,0)).second);
	}
}
