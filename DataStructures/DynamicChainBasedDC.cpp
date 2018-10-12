namespace DynamicChainBasedDC {
	struct Part {
		int top;
		Part(int top):top(top) {}
	}*cn[XN];

	int dfs[XN],dc,lbd[XN],rbd[XN],dep[XN],sz[XN],prefer[XN],fa[XN];
	void DFS(int pos) {
		int mxs=0;
		sz[pos]=1;
		for(Edge *e=G[pos];e;e=e->pre) {
			int u=e->to;
			fa[u]=pos;dep[u]=dep[pos]+1;
			DFS(u);
			sz[pos]+=sz[u];
			if(Enlarge(mxs,sz[u]))
				prefer[pos]=u;
		}
	}

	void Assign(int pos,int rt) {
		dfs[++dc]=pos;
		lbd[pos]=dc;
		cn[pos]=cn[rt]?cn[rt]:new Part(pos);
		if(prefer[pos]) {
			Assign(prefer[pos],rt);
			for(Edge *e=G[pos];e;e=e->pre)
				if(e->to!=prefer[pos])
					Assign(e->to,e->to);
		}
		rbd[pos]=dc;
	}

	void Divide() {
		DFS(1);
		cn[1]=new Part(1);
		Assign(1,1);
	}

	void Path(int p1,int p2) {
		while(cn[p1]!=cn[p2]) {
			if(dep[cn[p1]->top]<dep[cn[p2]->top])
				std::swap(p1,p2);
			//p1~cht[p1]
			p1=fa[cn[p1]->top];
		}
		if(lbd[p1]>lbd[p2])
			std::swap(p1,p2);
		//p1~p2
	}
}
