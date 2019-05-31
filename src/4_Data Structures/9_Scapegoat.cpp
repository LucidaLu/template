struct Scapegoat {
	static const double alpha=0.8;

	struct Node {
		Node *son[2];
		int v,cnt,size,ndct;

		Node(int v):v(v),cnt(1),size(1),ndct(1) {
			son[0]=son[1]=null;
		}

		Node(void*):size(0),ndct(0) {
			son[0]=son[1]=this;
		}

		void Up() {
			size=son[0]->size+cnt+son[1]->size;
			ndct=son[0]->ndct+1+son[1]->ndct;
		}

		bool Unbalanced() {
			return ndct*alpha<std::max(son[0]->ndct,son[1]->ndct);
		}
	}*root;

	static Node *null;

	Scapegoat():root(null) {}
	
	static Node *&Insert(Node *&pos,int v) {
		if(pos==null) {
			pos=new Node(v);
			return null;
		} else if(pos->v==v) {
			pos->cnt++;
			pos->Up();
			return null;
		} else {
			Node *&goat=Insert(pos->son[pos->v<v],v);
			pos->Up();
			return pos->Unbalanced()?pos:goat;
		}
	}

	static void Delete(Node *pos,int v) {
		if(pos==null)
			return;
		else if(pos->v==v) {
			pos->cnt--;
			pos->Up();
		} else {
			Delete(pos->son[pos->v<v],v);
			pos->Up();
		}
	}

	static Node *Flatten(Node *pos,Node *app) {
		if(pos==null)
			return app;
		else {
			pos->son[1]=Flatten(pos->son[1],app);
			return Flatten(pos->son[0],pos);
		}
	}

	static std::pair<Node*,Node*> Rebuild(Node *begin,int n) {
		if(n==0) {
			return std::pair<Node*,Node*>(null,begin);
		} else {
			int mid=(1+n)/2;
			std::pair<Node*,Node*> left=Rebuild(begin,mid-1);
			Node *pos=left.second;
			std::pair<Node*,Node*> right=Rebuild(pos->son[1],n-mid);
			pos->son[0]=left.first;
			pos->son[1]=right.first;
			pos->Up();
			return std::pair<Node*,Node*>(pos,right.second);
		}	
	}

	static void Rebuild(Node *&root) {
		Node *begin=Flatten(root,null);
		root=Rebuild(begin,root->ndct).first;
	}

	void Insert(int v) {
		Node *&goat=Insert(root,v);
		if(goat!=null)
			Rebuild(goat);
	}

	void Delete(int v) {
		Delete(root,v);
	}

	int Rank(int v) {
		int res=0;
		for(Node *pos=root;pos!=null;) {
			if(pos->v<v) {
				res+=pos->son[0]->size+pos->cnt;
				pos=pos->son[1];
			} else
				pos=pos->son[0];
		}
		return ++res;
	}

	int Kth(int k) {
		for(Node *pos=root;;) {
			int le=pos->son[0]->size+pos->cnt;
			if(k<=le) {
				if(pos->son[0]->size+1<=k && k<=le && pos->cnt)
					return pos->v;
				else
					pos=pos->son[0];
			} else {
				k-=le;
				pos=pos->son[1];
			}
		}
		throw;
	}

	int Pred(int v) {
		return Kth(Rank(v)-1);
	}

	int Succ(int v) {
		return Kth(Rank(v+1));
	}
};
const double Scapegoat::alpha;
Scapegoat::Node *Scapegoat::null=new Scapegoat::Node((void*)0);
