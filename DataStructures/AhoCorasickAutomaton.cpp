struct AhoCorasickAutomaton {
	struct Node {
		Node *son[26],*fail,*last;
		int cnt;

		Node() {
			memset(son,0,sizeof(son));
			fail=last=0;
			cnt=0;
		}
		
	}*root;

	void Insert(char *s) {
		Node *pos=root;
		for(;*s;++s) {
			int c=*s-'a';
			if(!pos->son[c])
				pos->son[c]=new Node;
			pos=pos->son[c];
		}
		pos->cnt++;
	}

	void Build() {
		root->fail=root->last=root;
		std::queue<Node*> Q;
		for(int c=0;c<26;++c)
			if(root->son[c]) {
				root->son[c]->fail=root->son[c]->last=root;
				Q.push(root->son[c]);
			} else root->son[c]=root;
		while(!Q.empty()) {
			Node *cur=Q.front();Q.pop();
			for(int c=0;c<26;++c)
				if(cur->son[c]) {
					Node *u=cur->son[c];
					u->fail=cur->fail->son[c];
					u->last=u->fail->cnt?u->fail:u->fail->last;
					Q.push(u);
				} else cur->son[c]=cur->fail->son[c];
		}
	}

	int Calc(Node *pos) {
		int res=0;
		while(pos->cnt) {
			res+=pos->cnt;
			pos->cnt=0;
			pos=pos->last;
		}
		return res;
	}

	int Match(char *s) {
		Node *pos=root;
		int res=0;
		for(;*s;++s) {
			int c=*s-'a';
			pos=pos->son[c];
			if(pos->cnt)
				res+=Calc(pos);
		}
		return res;
	}
};

