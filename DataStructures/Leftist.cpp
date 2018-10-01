struct Leftist {
	struct Node {
		Node *son[2];
		int v;
		int dist;

		Node(int const &v):v(v),dist(1) {
			son[0]=son[1]=null;
		}

		Node(void*):v(INF),dist(0) {
			son[0]=son[1]=0;
		}

		void Maintain() {
			if(son[0]->dist<son[1]->dist)
				std::swap(son[0],son[1]);
			dist=son[1]->dist+1;
		}
	}*root;
	
	static Node *null;

	Leftist():root(null) {}

	static Node *Merge(Node *p1,Node *p2) {
		if(p1==null || p2==null)
			return p1==null?p2:p1;
		else {
			if(p1->v>p2->v)
				std::swap(p1,p2);
			p1->son[1]=Merge(p1->son[1],p2);
			p1->Maintain();
			return p1;
		}
	}

	void Swallow(Leftist &other) {
		root=Merge(root,other.root);
		other.root=null;
	}

	void Push(int v) {
		root=Merge(root,new Node(v));
	}

	int Pop() {
		int res=root->v;
		root=Merge(root->son[0],root->son[1]);
		return res;
	}
};
Leftist::Node *Leftist::null=new Leftist::Node((void*)0);
