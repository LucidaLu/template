struct Treap {
	struct Node {
		Node *son[2];
		int v,add,size;
		long long sum;

		Node(int v):v(v),add(0),size(1),sum(v) {
			son[0]=son[1]=null;
		}

		Node(void*):v(0),add(0),size(0),sum(0) {
			son[0]=son[1]=this;
		}

		void Add(int d) {
			add+=d;
			sum+=(long long)d*size;
			v+=d;
		}

		void Up() {
			sum=son[0]->sum+v+son[1]->sum;
			size=son[0]->size+1+son[1]->size;
		}

		void Down() {
			if(add) {
				if(son[0]!=null)
					(son[0]=new Node(*son[0]))->Add(add);
				if(son[1]!=null)
					(son[1]=new Node(*son[1]))->Add(add);
				add=0;
			}
		}
	}*root;

	static Node *null;

	Treap(int a[],int n):root(Build(a,1,n)) {}

	static Node *Build(int a[],int L,int R) {
		if(L>R)
			return null;
		else {
			int M=(L+R)/2;
			Node *pos=new Node(a[M]);
			pos->son[0]=Build(a,L,M-1);
			pos->son[1]=Build(a,M+1,R);
			pos->Up();
			return pos;
		}
	}

	static std::pair<Node*,Node*> Split(Node *pos,int k) {
		if(k==0)
			return std::pair<Node*,Node*>(null,pos);
		else if(k==pos->size)
			return std::pair<Node*,Node*>(pos,null);
		else {
			(pos=new Node(*pos))->Down();
			std::pair<Node*,Node*> res;
			if(k<=pos->son[0]->size) {
				res=Split(pos->son[0],k);
				pos->son[0]=res.second;
				pos->Up();
				res.second=pos;
			} else {
				res=Split(pos->son[1],k-pos->son[0]->size-1);
				pos->son[1]=res.first;
				pos->Up();
				res.first=pos;
			}
			return res;
		}
	}

	static Node *Merge(Node *p1,Node *p2) {
		if(p1==null || p2==null)
			return p1==null?p2:p1;
		else {
			Node *pos;
			if(rand()%(p1->size+p2->size)+1<=p1->size) { 
				(pos=new Node(*p1))->Down();
				pos->son[1]=Merge(pos->son[1],p2);
				pos->Up();
			} else {
				(pos=new Node(*p2))->Down();
				pos->son[0]=Merge(p1,pos->son[0]);
				pos->Up();
			}
			return pos;
		}
	}

	struct Triple {
		Node *L,*M,*R;
	};

	static Triple Split(Node *root,int l,int r) {
		std::pair<Node*,Node*> x=Split(root,r),y=Split(x.first,l-1);
		return {y.first,y.second,x.second};
	}

	static Node *Merge(Triple t) {
		return Merge(t.L,Merge(t.M,t.R));
	}
};
Treap::Node *Treap::null=new Treap::Node((void*)0);
