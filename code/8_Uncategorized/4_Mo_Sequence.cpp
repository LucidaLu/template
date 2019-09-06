int block[XM],m;
struct Query {
	int l,r;
	unsigned int *ans;
}q[XM];

void Solve() {
	std::sort(q+1,q+1+m,[&](auto const &a,auto const &b)->bool {
		return block[a.l]==block[b.l]?(a.r<b.r)^(block[a.l]&1):block[a.l]<block[b.l];	
	});
	
	unsigned int Ans=0;
	static auto Update=[&](int pos,int sig) {
		
	};
	int l=1,r=0;
	for(int i=1;i<=m;++i) {
		for(;l>q[i].l;Update(--l,1));
		for(;r<q[i].r;Update(++r,1));
		for(;l<q[i].l;Update(l++,-1));
		for(;r>q[i].r;Update(r--,-1));
		*q[i].ans=Ans;
	}
	while(l<=r)
		Update(r--,-1);
}

