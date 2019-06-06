struct Line {
	int k,b;
	int operator() (int x) { return k*x+b; }
	friend double Cross(Line const &lhs,Line const &rhs) { return ((double)lhs.b-rhs.b)/(rhs.k-lhs.k); }
};

struct SegTree {
	struct Node {
		Node *son[2];
		Line l;
		Node(Line const &l):l(l) { son[0]=son[1]=0; }
	}*root;int L,R;
	SegTree(int L,int R):root(0),L(L),R(R) {}
	void Insert(Node *&pos,int L,int R,Line l) {
		if(!pos) pos=new Node(l);
		else {
			if(L==R) {
				if(pos->l(L)>l(L)) pos->l=l;
			} else {
				Line r=pos->l;if(l(L)>r(L)) std::swap(l,r);
				int M=L+R>=0?(L+R)/2:-((-L-R)/2);
				double x=Cross(l,r);
				if(l.k==r.k || x<L || R<x)//R>x
					pos->l=l;
				else if(x<=M) {
					pos->l=r;
					Insert(pos->son[0],L,M,l);
				} else {
					pos->l=l;
					Insert(pos->son[1],M+1,R,r);
				}
			}
		}
	}
	int Query(Node *pos,int L,int R,int x) {
		if(!pos) return INF;
		else {
			int M=L+R>=0?(L+R)/2:-((-L-R)/2);
			return std::min(pos->l(x),x<=M?Query(pos->son[0],L,M,x)
										  :Query(pos->son[1],M+1,R,x));
		}
	}
	void Insert(Line const &l) { Insert(root,L,R,l); }
	int Query(int x) { return Query(root,L,R,x); }
};

