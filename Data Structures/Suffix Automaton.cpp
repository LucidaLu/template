struct SuffixAutomata {

	struct Node {
		std::map<int,Node*> son;
		Node *par;
		int maxRight;
		Node(int maxRight=0):par(0),maxRight(maxRight) {}
		void *operator new(size_t flag) {
			static *pool=(*)malloc(*sizeof()),*mem;
			return flag?mem++:mem=pool;
		}
	}*root,*last;
	
	long long cnt;
	SuffixAutomata():root(new Node),last(root),cnt(0) {}

	void Extend(int x) {
		Node *p=last,*nx=new Node(last->maxRight+1);
		for(;p && !p->son[x];p->son[x]=nx,p=p->par);
		if(p==0) {
			nx->par=root;
		} else {
			Node *ox=p->son[x];
			if(p->maxRight+1==ox->maxRight) {
				nx->par=ox;
			} else {
				Node *o=new Node(*ox);
				o->maxRight=p->maxRight+1;
				ox->par=nx->par=o;
				for(;p && p->son[x]==ox;p->son[x]=o,p=p->par);
			}
		}
		cnt+=nx->maxRight-nx->par->maxRight;
		last=nx;
	}
};

