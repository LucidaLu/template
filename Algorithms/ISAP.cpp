const int INF=1e9,XN=200+11;

struct Edge {
	int to,cap,v;
	Edge *rev,*pre;
	
	Edge(int to,int cap,Edge *pre):to(to),cap(cap),v(0),rev(0),pre(pre) {}
	
	void *operator new(size_t flag) {
		static Edge *Pool=(Edge*)malloc((XN<<1)*sizeof(Edge)),*Me;
		return flag?Me++:(Me=Pool);
	}
}*G[XN],*preArc[XN];

int Aug(int t) {
	int d=INF;
	for(int pos=t;preArc[pos];pos=preArc[pos]->rev->to)
		Reduce(d,preArc[pos]->cap-preArc[pos]->v);
	for(int pos=t;preArc[pos];pos=preArc[pos]->rev->to) {
		preArc[pos]->v+=d;
		preArc[pos]->rev->v-=d;
	}
	return d;
}

int ISAP(int s,int t,int n) {
	static int num[XN],d[XN];
	static Edge *cArc[XN];
	std::fill(num+1,num+n,0);
	std::fill(d+1,d+1+n,0);
	std::copy(G+1,G+1+n,cArc+1);
	num[0]=n;preArc[s]=0;
	int flow=0;
	for(int pos=s;d[s]<n;) {
		if(pos==t) {
			flow+=Aug(t);
			pos=s;
		}
		bool adv=0;
		for(Edge *&e=cArc[pos];e;e=e->pre) {
			int u=e->to;
			if(e->cap>e->v && d[u]+1==d[pos]) {
				adv=1;
				preArc[pos=u]=e;
				break;
			}
		}
		if(!adv) {
			if(--num[d[pos]]==0)
				break;
			d[pos]=n;
			for(Edge *e=cArc[pos]=G[pos];e;e=e->pre)
				if(e->cap>e->v)
					Reduce(d[pos],d[e->to]+1);
			num[d[pos]]++;
			if(pos!=s)
				pos=preArc[pos]->rev->to;//cArc
		}
	}
	return flow;
}
