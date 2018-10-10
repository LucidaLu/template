namespace StaticVertexBasedDC {
	bool ud[XN];
	int size[XN];

	int GetSize(int pos,int fa) {
		size[pos]=1;
		for(Edge *e=G[pos];e;e=e->pre) {
			int u=e->to;
			if(!ud[u] && u!=fa)
				size[pos]+=GetSize(u,pos);
		}
		return size[pos];
	}

	int Centre(int pos,int fa,int const &tol) {
		static int f[XN]={INF};
		int res=0,mxs=0;
		for(Edge *e=G[pos];e;e=e->pre) {
			int u=e->to;
			if(!ud[u] && u!=fa) {
				int t=Centre(u,pos,tol);
				if(f[t]<f[res])
					res=t;
				Enlarge(mxs,size[u]);
			}
		}
		f[pos]=std::max(mxs,tol-size[pos]);
		return f[pos]<f[res]?pos:res;
	}


	void DC(int pos) {
		ud[pos]=1;
		for(Edge *e=G[pos];e;e=e->pre) {
			int u=e->to;
			if(!ud[u]) {
			
			}
		}
		
		for(Edge *e=G[pos];e;e=e->pre) {
			int u=e->to;
			if(!ud[u])
				DC(Centre(u,0,GetSize(u,0)));
		}

	}
}
