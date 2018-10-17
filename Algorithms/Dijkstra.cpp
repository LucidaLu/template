#include <ext/pb_ds/priority_queue.hpp>

typedef __gnu_pbds::priority_queue<std::pair<long long,int>,std::greater<std::pair<long long,int> >,__gnu_pbds::pairing_heap_tag> Heap;
long long Dijkstra(int s,int t) {
	static long long sp[XN];
	static Heap::point_iterator ref[XN];
	Heap Q;
	memset(sp,31,sizeof(sp));
	sp[s]=0;
	Q.push(std::make_pair(0,s));
	while(!Q.empty()) {
		int pos=Q.top().second;Q.pop();
		for(Edge *e=G[pos];e;e=e->pre) {
			int u=e->to;
			if(Reduce(sp[u],sp[pos]+e->v)) {
				if(ref[u]!=0)
					Q.modify(ref[u],std::make_pair(sp[u],u));
				else
					ref[u]=Q.push(std::make_pair(sp[u],u));
			}
		}
	}
	return sp[t];
}
