namespace VirtualTree {
	struct Graph {
		struct Edge {
			int to,v;
			Edge *pre;

			Edge(int to,int v,Edge *pre):to(to),v(v),pre(pre) {}

		}*G[XN],*pool,*mem;

		int us[XN],T;

		Graph():pool((Edge*)malloc(XN*2*sizeof(Edge))),mem(pool) {}

		void Check(int x) {
			if(us[x]!=T) {
				us[x]=T;
				G[x]=0;
			}
		}

		Edge *&operator [](int x) {
			Check(x);
			return G[x];
		}

		void operator ()(int x,int y,int c=1) {
			Check(x);
			G[x]=new(mem++) Edge(y,c,G[x]);
		}

		void Reset() {
			mem=pool;
			++T;
		}
	}R;

	void Build(int h[],int hc) {
		std::sort(h+1,h+1+hc,[](int a,int b)->bool { return dfn[a]<dfn[b]; });
		static int stack[XN],top;
		stack[top=0]=0;R.Reset();
		for(int i=1;i<=hc;++i) {
			for(int lca=LCA(stack[top],h[i]);stack[top]!=lca;) {
				if(dep[lca]>dep[stack[top]])
					stack[++top]=lca;
				else {
					R(dep[stack[top-1]]>dep[lca]?stack[top-1]:lca,stack[top]);
					top--;
				}
			}
			stack[++top]=h[i];
		}
		for(;top;top--)
			R(stack[top-1],stack[top]);
	}
}
