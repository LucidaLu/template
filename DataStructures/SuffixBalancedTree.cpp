struct SuffixBalancedTree {
	static const double alpha=0.8;

	struct Node {		
		Node *son[2];
		double l,r,tag;
		int size,ndct;
		bool exist;
		char ch;
		Node *next;

		Node(double l,double r,char ch,Node *next):l(l),r(r),tag((l+r)/2),size(1),ndct(1),exist(1),ch(ch),next(next) {
			son[0]=son[1]=null;
		}

		Node(void*) {
			size=ndct=exist=0;
			ch=0;
			tag=-1;
			son[0]=son[1]=0;
		}

		void Up() {
			ndct=son[0]->ndct+1+son[1]->ndct;
			size=son[0]->size+exist+son[1]->size;
		}

		bool Unbalanced() {
			return ndct*alpha<std::max(son[0]->ndct,son[1]->ndct);
		}
	}*root;

	std::stack<Node*> nodes;

	static Node *null;

	SuffixBalancedTree():root(null) {
		nodes.push(null);
	}

	Node *&Insert(Node *&pos,double l,double r,char ch,Node *next) {
		if(pos==null) {
			pos=new Node(l,r,ch,next);
			nodes.push(pos);
			return null;
		} else {
			Node *&goat=ch<pos->ch || (ch==pos->ch && next->tag<pos->next->tag)
						?Insert(pos->son[0],l,(l+r)/2,ch,next)
						:Insert(pos->son[1],(l+r)/2,r,ch,next);
			pos->Up();
			return pos->Unbalanced()?pos:goat;
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

	static std::pair<Node*,Node*> Rebuild(Node *begin,double l,double r,int n) {
		if(n==0) {
			return std::pair<Node*,Node*>(null,begin);
		} else {
			int mid=(1+n)/2;
			std::pair<Node*,Node*> left=Rebuild(begin,l,(l+r)/2,mid-1);
			Node *pos=left.second;
			std::pair<Node*,Node*> right=Rebuild(pos->son[1],(l+r)/2,r,n-mid);
			pos->son[0]=left.first;
			pos->son[1]=right.first;
			pos->l=l,pos->r=r,pos->tag=(l+r)/2;
			pos->Up();
			return std::pair<Node*,Node*>(pos,right.second);
		}
	}

	static void Rebuild(Node *&root) {
		Node *begin=Flatten(root,null);
		root=Rebuild(begin,root->l,root->r,root->ndct).first;
	}

	static void Delete(Node *pos,Node *del) {
		if(pos==del) {
			pos->exist=0;
			pos->Up();
		} else {
			Delete(pos->son[pos->tag<del->tag],del);
			pos->Up();
		}
	}

	int LessCount(const char *s) {
		int res=0;
		for(Node *pos=root;pos!=null;) {
			Node *p=pos;
			const char *c=s;
			while(p->ch==*c) {
				p=p->next;
				++c;
			}
			if(p->ch<*c) {
				res+=pos->son[0]->size+pos->exist;
				pos=pos->son[1];
			} else
				pos=pos->son[0];
		}
		return res;
	}

	void Append(char ch) {
		Node *&goat=Insert(root,0,1,ch,nodes.top());
		if(goat!=null)
			Rebuild(goat);
	}

	void Pop() {
		Delete(root,nodes.top());
		nodes.pop();
	}

	int Count(char *s,int len) {
		s[len+1]=CHAR_MAX;
		int res=LessCount(s+1);
		s[len+1]=CHAR_MIN;
		res-=LessCount(s+1);
		//null's ch must satisfy CHAR_MIN < ch < ALL
		return res;
	}
};
const double SuffixBalancedTree::alpha;
SuffixBalancedTree::Node *SuffixBalancedTree::null=new SuffixBalancedTree::Node((void*)0);
