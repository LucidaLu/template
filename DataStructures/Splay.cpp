struct Splay {
	struct Node {
		Node *fa,*son[2];
		int size;

		Node(void*):size(0) {
			fa=son[0]=son[1]=0;
		}

		Node():size(1) {
			fa=son[0]=son[1]=null;
		}

		void Adopt(Node *s,int d) {
			if(s!=null)
				s->fa=this;
			son[d]=s;
		}

		bool Type() {
			return fa->son[1]==this;
		}

		void *operator new(size_t) {
			return *bin?*bin--:mem++;
		}

		void operator delete(void *p) {
			*++bin=(Node*)p;
		}

		void Up() {
			size=son[0]->size+1+son[1]->size;
		}

		void Down() {

		}
	}*root,*nil[2];

	static Node *mem,**bin,*null;

	Splay(int *a,int n) {
		root=nil[0]=new Node(0);
		nil[0]->Adopt(nil[1]=new Node(0),1);
		nil[1]->Adopt(Build(a,1,n),0);
		SplayTo(nil[1],null);
	}

	void Insert(int p,int a[],int n) {
		Node *newt=Build(a,1,n),*pl=Kth(p),*pr=Kth(p+1);
		SplayTo(pl,null);
		SplayTo(pr,pl);
		pr->Adopt(newt,0);
		SplayTo(newt,null);
	}

	void Delete(int l,int r) {
		Node *pos=Split(l,r);
		pos->fa->son[pos->Type()]=null;
		SplayTo(pos->fa,null);
		Recycle(pos);
	}

	static void Recycle(Node *pos) {
		if(pos->son[0]!=null)
			Recycle(pos->son[0]);
		if(pos->son[1]!=null)
			Recycle(pos->son[1]);
		delete pos;
	}

	static Node *Build(int *a,int l,int r) {
		if(l>r)
			return null;
		int mid=(l+r)/2;
		Node *pos=new Node(a[mid]);
		pos->Adopt(Build(a,l,mid-1),0);
		pos->Adopt(Build(a,mid+1,r),1);
		pos->Up();
		return pos;
	}

	static void Trans(Node *pos) {
		Node *fa=pos->fa,*grand=fa->fa;
		fa->Down();pos->Down();
		int d=pos->Type();
		if(grand!=null)
			grand->son[fa->Type()]=pos;
		pos->fa=grand;
		fa->Adopt(pos->son[!d],d);pos->Adopt(fa,!d);
		fa->Up();
	}

	void SplayTo(Node *pos,Node *goal) {
		for(;pos->fa!=goal;Trans(pos))
			if(pos->fa->fa!=goal)
				Trans(pos->Type()==pos->fa->Type()?pos->fa:pos);
		pos->Up();
		if(goal==null)
			root=pos;
	}

	Node *Kth(int k) {
		Node *pos=root;int x;
		++k;
		while(k) {
			pos->Down();
			if((x=pos->son[0]->size+1)==k)
				return pos;
			else if(k<x)
				pos=pos->son[0];
			else {
				k-=x;
				pos=pos->son[1];
			}
		}
		return 0;   
	}

	Node *Split(int l,int r) {//返回对应子树的根节点
		Node *pl=Kth(l-1),*pr=Kth(r+1);
		SplayTo(pl,null);SplayTo(pr,pl);
		return pr->son[0];
	}
};
Splay::Node *Splay::mem=(Splay::Node*)malloc(XN*sizeof(Splay::Node)),**Splay::bin=(Splay::Node**)malloc(XN*sizeof(Splay::Node*)),*Splay::null=new Splay::Node((void*)0);
