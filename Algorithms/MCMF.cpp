struct Edge {
	int to,cap,v,cost;
	Edge *rev,*pre;
	
	Edge(int to,int cap,int cost,Edge *pre):to(to),cap(cap),v(0),cost(cost),rev(0),pre(pre) {}
}*G[XN],*preArc[XN];
int sp[XN];
int Aug(int s,int t) {
	int d=INF;
	for(int pos=t;pos!=s;pos=preArc[pos]->rev->to)
		Reduce(d,preArc[pos]->cap-preArc[pos]->v);
	for(int pos=t;pos!=s;pos=preArc[pos]->rev->to) {
		preArc[pos]->v+=d;
		preArc[pos]->rev->v-=d;
	}
	return d;
}

bool Sp(int s,int t,int n) {
	static int Q[XN];
	static bool inq[XN];
	int *end=Q+n,*head=Q,*tail=Q;//Q+n!
	std::fill(sp+1,sp+1+n,INF);
	sp[s]=0;*tail++=s;inq[s]=1;
	while(head!=tail) {
		int pos=*head;
		inq[pos]=0;//inq!!!
		head=head==end?Q:head+1;
		for(Edge *e=G[pos];e;e=e->pre)
			if(e->cap>e->v) {
				int u=e->to;
				if(Reduce(sp[u],sp[pos]+e->cost)) {
					preArc[u]=e;
					if(!inq[u]) {
						inq[u]=1;
						if(sp[u]<sp[*head]) {
							head=head==Q?end:head-1;
							*head=u;
						} else {
							*tail=u;
							tail=tail==end?Q:tail+1;
						}
					}
				}
			}
	}
	return sp[t]!=INF;
}

int MCMF(int s,int t,int n) {
	int cost=0,flow=0;
	while(Sp(s,t,n)) {
		int d=Aug(s,t);
		cost+=d*sp[t];
		flow+=d;
	}
	return cost;
}
