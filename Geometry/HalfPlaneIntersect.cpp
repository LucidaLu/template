bool OnLeft(const Point &p,const Line &ln) {
	return sgn(Outer(ln.v,p-ln.p))>0;
}

bool Paral(const Line &ln1,const Line &ln2) {
	return sgn(Outer(ln1.v,ln2.v))==0;
}

int Intersect(Line ln[],int n,Line uni[]) {
	std::sort(ln+1,ln+1+n,[](Line const &a,Line const &b) { return a.ang<b.ang; });
	static Point Qp[XN];static Line Qln[XN];
	int head,tail;Qln[head=tail=1]=ln[1];
	for(int i=2;i<=n;++i) {
		while(tail-head>=1 && !OnLeft(Qp[tail-1],ln[i]))
			tail--;
		while(tail-head>=1 && !OnLeft(Qp[head],ln[i]))
			head++;
		Qln[++tail]=ln[i];
		if(Paral(Qln[tail-1],Qln[tail])){
			--tail;
			if(OnLeft(ln[i].p,Qln[tail]))
				Qln[tail]=ln[i];
		}
		if(tail-head>=1)
			Qp[tail-1]=Cross(Qln[tail-1],Qln[tail]);
	}
	while(tail-head>=1 && !OnLeft(Qp[tail-1],Qln[head]))
		tail--;
	if(tail-head>=1) {
		std::copy(Qln+head,Qln+tail+1,uni+1);
		return tail-head+1;
	} else
		return 0;
}


