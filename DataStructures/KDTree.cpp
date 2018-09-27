struct Point {
	int d[XD];
};

long long Dist(Point const &a,Point const &b) {
	~;
}

struct KDTree {
	struct Node {
		Node *son[2];
		Point p,min,max;
	
		Node(Point p):p(p),min(p),max(p) {
			son[0]=son[1]=null;
		}

		Node(void*):min(~),max(~) {
			son[0]=son[1]=0;
		}

		void *operator new(size_t flag) {
			static Node *pool=(Node*)malloc(XN*sizeof(Node)),*mem=pool++;
			return flag?mem++:mem=pool;
		}

		void Up() {
			for(int i=0;i<k;++i) {
				min.d[i]=std::min(p.d[i],std::min(son[0]->min.d[i],son[1]->min.d[i]));
				max.d[i]=std::max(p.d[i],std::max(son[0]->max.d[i],son[1]->max.d[i]));
			}
		}

		long long Dist(Point const &q) {
			~;
		}
	}*root;

	static Node *null;

	KDTree(Point p[],int n):root(Build(p,1,n,0)) {}
	
	Node *Build(Point p[],int L,int R,int d) {
		if(L>R)
			return null;
		else {
			struct Compare {
				int d;
				Compare(int d):d(d) {}

				bool operator ()(Point const &a,Point const &b) {
					return a.d[d]<b.d[d];
				}
			};
			int M=(L+R)/2;
			std::nth_element(p+L,p+M,p+R+1,Compare(d));
			Node *pos=new Node(p[M]);
			pos->son[0]=Build(p,L,M-1,(d+1)%k);
			pos->son[1]=Build(p,M+1,R,(d+1)%k);
			pos->Up();
			return pos;
		}
	}

	~ Query(Point p) {
		~ res;
		Query(root,p,res);
		return res;
	}

	void Query(Node *pos,Point p,~ &res) {
		if(pos==null)
			return;
		else {
			Reduce(res,Dist(pos->p,p));
			if(pos->son[0]->Dist(p)<res)
				Query(pos->son[0],p,res);
			if(pos->son[1]->Dist(p)<res)
				Query(pos->son[1],p,res);
		}
	}
};
KDTree::Node *KDTree::null=new KDTree::Node((void*)0);
