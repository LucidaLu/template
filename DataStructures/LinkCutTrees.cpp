class LinkCutTrees {
public:
	LinkCutTrees() {}

	void Link(int id1,int id2) {
		Link(node[id1],node[id2]);
	}

	void Cut(int id1,int id2) {
		Cut(node[id1],node[id2]);
	}
private:
	struct Node {

		Node *son[2],*fa;
		bool rev;

		Node(void*):rev(0) {
			son[0]=son[1]=fa=0;
		}

		Node():rev(0) {
			son[0]=son[1]=fa=null;
		}

		void *operator new(size_t flag) {
			static Node *pool=(Node*)malloc(SIZE*sizeof(Node)),*mem;
			return flag?mem++:mem=pool;
		}

		int Type() {
			return fa->son[1]==this;
		}

		bool isRoot() {
			return fa->son[0]!=this && fa->son[1]!=this;
		}

		void Adopt(Node *s,int d) {
			son[d]=s;
			if(s!=null)
				s->fa=this;
		}

		void Reverse() {
			rev^=1;
			std::swap(son[0],son[1]);
		}

		void Up() {
		
		}

		void Down() {
			if(rev) {
				if(son[0]!=null)
					son[0]->Reverse();
				if(son[1]!=null)
					son[1]->Reverse();
				rev=0;
			}
		}

	}node*[];
	
	static Node *null;

	static void Trans(Node *pos) {
		Node *f=pos->fa,*g=f->fa;
		f->Down();pos->Down();
		int d=pos->Type();
		if(!f->isRoot())
			g->son[f->Type()]=pos;
		pos->fa=g;
		f->Adopt(pos->son[!d],d);f->Up();
		pos->Adopt(f,!d);
	}

	static void Splay(Node *pos) {
		pos->Down();
		for(Node *fa;!pos->isRoot();Trans(pos))
			if(!(fa=pos->fa)->isRoot())
				Trans(pos->Type()==fa->Type()?fa:pos);
		pos->Up();
	}

	static void Access(Node *pos) {
		for(Node *pred=null;pos!=null;pred=pos,pos=pos->fa) {
			Splay(pos);
			pos->son[1]=pred;
			pos->Up();
		}
	}

	static void Expose(Node *pos) {
		Access(pos);
		Splay(pos);
	}

	static Node *FindRoot(Node *pos) {
		Expose(pos);
		while(pos->son[0]!=null) {
			pos->Down();
			pos=pos->son[0];
		}
		return pos;
	}

	static void MakeRoot(Node *pos) {
		Expose(pos);
		pos->Reverse();
	}

	static void Cut(Node *p1,Node *p2) {
		MakeRoot(p1);
		Expose(p2);
		p2->son[0]=p1->fa=null;
		p2->Up();
	}

	static void Link(Node *p1,Node *p2) {
		MakeRoot(p1);
		p1->fa=p2;
	}
};
LinkCutTrees::Node *LinkCutTrees::null=new LinkCutTrees::Node((void*)0);
